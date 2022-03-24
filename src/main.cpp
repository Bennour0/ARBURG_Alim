#include <Arduino.h>
#include <WiFi.h>
#include <esp_now.h>
#include "messages.hpp"

// Central Mac address :
uint8_t broadcastAddress[] = {0x7C, 0x9E, 0xBD, 0x62, 0x12, 0x98};

// struct to sent to the central
t_s2c s2c;

// struct to recieve from the central
t_c2s c2s;

// struct that holds serveur/central receivings
t_s2c Central_data;

#define PID 1

// Sensors pins assignments :
#define FEEDMAXREQ 25 // FEEDMAX Requirement sensor pin intialisation
#define ARBURGREQ 26  // ARBURG Requirement sensor pin intialisation
#define FEEDMAXLVL 27 // FEEDMAX Level sensor pin intialisation

// Actuators pins assignments :
#define CHARGERVAL 12 // Charger valve pin intialisation
#define FEEDMAXVAL 13 // FEEDMAX valve pin intialisation
#define DRYMAXVAL 14  // DRYMAX valve pin intialisation

// Initialization Fonction
void initESPNOW();

// Callback when data is sent fonction
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status);

// Callback when data is received fonction
void OnDataRecv(const uint8_t *mac, const uint8_t *incomingData, int len);

// Send Readings fonction
void SendReadings();

// Send Readings for RTOS
void Send_task(void *parameter);

void setup()
{
    Serial.begin(115200);
    c2s.ID = PID;
    initESPNOW();
    // Sensors pins configurations
    pinMode(FEEDMAXREQ, INPUT);
    pinMode(ARBURGREQ, INPUT);
    pinMode(FEEDMAXLVL, INPUT);
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
    // Register peer
    memcpy(peerInfo.peer_addr, broadcastAddress, 6);
    peerInfo.channel = 0;
    peerInfo.encrypt = false;
    // Add peer
    if (esp_now_add_peer(&peerInfo) != ESP_OK)
    {
        Serial.println("Failed to add peer");
        return;
    }
    xTaskCreatePinnedToCore(
        Send_task,                    // Function to be called
        "Send_task",                  // Name of task
        5000,                         // stack size (bytes in ESP32, words in FreeRTOS)
        NULL,                         // Parameter to pass to function
        1,                            // Task priority (0 to configMAX_PRIORITIES - 1)
        NULL,                         // Task handle
        CONFIG_ARDUINO_RUNNING_CORE); // Running core
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
    DBG_ODR(Serial.print("Inside OnDataRecv\n");)
    memcpy(&s2c, incomingData, sizeof(s2c));
    Central_data.ID = s2c.ID;
    Central_data.start = s2c.start;
}

void SendReadings()
{
    // Readings that will be sent
    c2s.Freq_sensor = digitalRead(FEEDMAXREQ);
    c2s.Areq_sensor = digitalRead(ARBURGREQ);
    c2s.Flevel_sensor = digitalRead(FEEDMAXLVL);
    // Send message via ESP-NOW
    esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *)&c2s, sizeof(c2s));
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