#include "Server.hpp"

/**
 * @brief Initialization function
 *
 */
void initESPNOW()
{
    // Set device as a Wi-Fi Station
    WiFi.mode(WIFI_STA);
    // Init ESP-NOW
    if (esp_now_init() != ESP_OK)
    {
        Serial.println("Error initializing ESP-NOW");
        return;
    }
    // Once ESPNow is successfully Init, we will register for Send CB to
    // get the status of Trasnmitted packet
    esp_now_register_send_cb(OnDataSent);
    // Register for a callback function that will be called when data is received
    esp_now_register_recv_cb(OnDataRecv);

    esp_now_peer_info_t peerInfo;

    // Registering peers
    for (int i = 0; i < NBARBURG; i++)
    {
        memcpy(peerInfo.peer_addr, arburgMacAdd[i], 6);
        peerInfo.channel = 0;
        peerInfo.encrypt = false;
        if (esp_now_add_peer(&peerInfo) != ESP_OK)
        {
            Serial.println("Failed to add peer");
            return;
        }
    }
    // Creating task for RTOS
    xTaskCreatePinnedToCore(
        Send_task,   // Function to be called
        "Send_task", // Name of task
        5000,        // stack size (bytes in ESP32, words in FreeRTOS)
        NULL,        // Parameter to pass to function
        1,           // Task priority (0 to configMAX_PRIORITIES - 1)
        NULL,        // Task handle
        CONFIG_ARDUINO_RUNNING_CORE);
}

/**
 * @brief Callback when data is sent function
 *
 * @param mac_addr MAC ADD
 * @param status STATUS
 */
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status)
{
    DBG_ODS(Serial.print("Inside OnDataSent\n");)
    /*DBG_ODS(Serial.print("\r\nLast Packet Send Status:\t");)
    DBG_ODS(Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");)
    if (status == 0)
    {
      success = "Delivery Success :)";
    }
    else
    {
      success = "Delivery Fail :(";
    }*/
}

/**
 * @brief Callback when data is received function
 *
 * @param mac MAC ADD
 * @param incomingData RECEIVING DATA
 * @param len  RECEIVING DATA LENGTH
 */
void OnDataRecv(const uint8_t *mac, const uint8_t *incomingData, int len)
{
    t_c2s c2s;
    DBG_ODR(Serial.print("Inside OnDataRecv\n");)
    memcpy(&c2s, incomingData, sizeof(c2s));
    arburgs_data[c2s.ID - 1] = c2s;
}

/**
 * @brief Send readings function
 *
 */
void SendReadings()
{
    // Send message via ESP-NOW
    esp_err_t result = esp_now_send(0, (uint8_t *)&s2c, sizeof(s2c));
    if (result == ESP_OK)
    {
        DBG_SR(Serial.println("Sent with success");)
    }
    else
    {
        DBG_SR(Serial.println("Error sending the data");)
    }
}

/**
 * @brief Send readings task for RTOS
 *
 * @param parameter Parameter for RTOS
 */
void Send_task(void *parameter)
{
    while (1)
    {
        SendReadings();
        delay(1000);
    }
}

/**
 * @brief Show receiving function
 *
 */
void ShowReceivings()
{
    DBG_SHR(Serial.print("Inside ShowReceivings\n");)

    for (int i = 0; i < NBARBURG; i++)
    {
        Serial.printf("%d --> [FEEDMAX %s; ARBURG %s; LEVELFEEDMAX %s]\n",
                      arburgs_data[i].ID,
                      SENSORSTATE(arburgs_data[i].Freq_sensor),
                      SENSORSTATE(arburgs_data[i].Areq_sensor),
                      SENSORSTATE(arburgs_data[i].Flevel_sensor));
    }
}