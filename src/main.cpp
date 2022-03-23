#include <Arduino.h>
#include <WiFi.h>
#include <esp_now.h>
#include "messages.hpp"
#include "my_debug.hpp"

// All MAC ADD
#define NBARBURG        2
uint8_t arburgMacAdd [][6] = {{0x84, 0xCC, 0xA8, 0x6A, 0xB9, 0x7C},
                {0x84, 0xCC, 0xA8, 0x6A, 0xA1, 0xF0}};

/*// Client 1 MAC address :
uint8_t broadcastAddress1[] = {0x84, 0xCC, 0xA8, 0x6A, 0xB9, 0x7C};
// Client 2 MAC address :
uint8_t broadcastAddress2[] = {0x84, 0xCC, 0xA8, 0x6A, 0xA1, 0xF0};
*/
t_c2s arburgs_data[NBARBURG];
/*
// Struct that will hold Client 1 receivings
t_c2s Client1_data;
// Struct that will hold Client 2 receivings
t_c2s Client2_data;
*/

// Initialization fonction
void initESPNOW();

// Callback when data is sent fonction
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status);

// Callback when data is received fonction
void OnDataRecv(const uint8_t *mac, const uint8_t *incomingData, int len);

// Send readings fonction
void SendReadings();

// Send readings task for RTOS
void Send_task(void *parameter);

void ShowReceivings();

// stuct to be sent by central
t_s2c s2c;

// struct to be received by central
//t_c2s c2s;

void setup()
{
    Serial.begin(115200);
    initESPNOW();
}
void loop()
{
}

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
    for(int i=0; i<NBARBURG; i++){
        memcpy(peerInfo.peer_addr, arburgMacAdd[i], 6);
        peerInfo.channel = 0;
        peerInfo.encrypt = false;
        if (esp_now_add_peer(&peerInfo) != ESP_OK)
        {
            Serial.println("Failed to add peer");
            return;
        }
    }
    /*
    // Register 1 peer
    memcpy(peerInfo.peer_addr, broadcastAddress1, 6);
    peerInfo.channel = 0;
    peerInfo.encrypt = false;
    if (esp_now_add_peer(&peerInfo) != ESP_OK)
    {
        Serial.println("Failed to add peer");
        return;
    }

    // Register 2 peer
    memcpy(peerInfo.peer_addr, broadcastAddress2, 6);
    peerInfo.channel = 0;
    peerInfo.encrypt = false;
    if (esp_now_add_peer(&peerInfo) != ESP_OK)
    {
        Serial.println("Failed to add peer");
        return;
    }
    */
    xTaskCreatePinnedToCore(
        Send_task,   // Function to be called
        "Send_task", // Name of task
        5000,        // stack size (bytes in ESP32, words in FreeRTOS)
        NULL,        // Parameter to pass to function
        1,           // Task priority (0 to configMAX_PRIORITIES - 1)
        NULL,        // Task handle
        CONFIG_ARDUINO_RUNNING_CORE);
}

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

void OnDataRecv(const uint8_t *mac, const uint8_t *incomingData, int len)
{
    t_c2s c2s;
    DBG_ODR(Serial.print("Inside OnDataRecv\n");)
    memcpy(&c2s, incomingData, sizeof(c2s));
    arburgs_data[c2s.ID - 1] = c2s;
    /*memcpy(&c2s, incomingData, sizeof(c2s));
    if (c2s.ID == 1)
    {
        Client1_data.ID = c2s.ID;
        Client1_data.Freq_sensor = c2s.Freq_sensor;
        Client1_data.Areq_sensor = c2s.Areq_sensor;
        Client1_data.Flevel_sensor = c2s.Flevel_sensor;
    }
    if (c2s.ID == 2)
    {
        Client2_data.ID = c2s.ID;
        Client2_data.Freq_sensor = c2s.Freq_sensor;
        Client2_data.Areq_sensor = c2s.Areq_sensor;
        Client2_data.Flevel_sensor = c2s.Flevel_sensor;
    }*/
}

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

void Send_task(void *parameter)
{
    while (1)
    {
        SendReadings();
        delay(1000);
    }
}
void ShowReceivings()
{
    /*DBG_SHR(Serial.print("ID = 1 ");)
    DBG_SHR(Serial.print(" Freq : ");)
    //DBG_SHR(Serial.print(Client1_data.Freq_sensor);)
    DBG_SHR(Serial.print(" Areq : ");)
    //DBG_SHR(Serial.print(Client1_data.Areq_sensor);)
    DBG_SHR(Serial.print(" Flevel : ");)
    DBG_SHR(Serial.print(Client1_data.Flevel_sensor);)
    DBG_SHR(Serial.print(" || ");)
    DBG_SHR(Serial.print("ID = 2 ");)
    DBG_SHR(Serial.print(" Freq : ");)
    //DBG_SHR(Serial.print(Client2_data.Freq_sensor);)
    DBG_SHR(Serial.print(" Areq : ");)
    DBG_SHR(Serial.print(Client2_data.Areq_sensor);)
    DBG_SHR( Serial.print(" Flevel : ");)
    DBG_SHR(Serial.print(Client2_data.Flevel_sensor);)*/
}