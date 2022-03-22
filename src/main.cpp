#include <Arduino.h>
#include <WiFi.h>
#include <esp_now.h>
#include "messages.hpp"
#include "my_debug.hpp"

uint8_t broadcastAddress[] = {0x7C, 0x9E, 0xBD, 0x62, 0x12, 0x98};
typedef struct statistics
{
    int in = 0;
    int out = 0;
} t_stat;

t_stat s;
t_s2c s2c;
t_c2s c2s;

// Sensors pins assignments :
#define FEEDMAXREQ 25 // FEEDMAX Requirement sensor pin intialisation
#define ARBURGREQ 26  // ARBURG Requirement sensor pin intialisation
#define FEEDMAXLVL 27 // FEEDMAX Level sensor pin intialisation

// Actuators pins assignments :
#define FEEDMAXVAL 13 // FEEDMAX valve pin intialisation
#define DRYMAXVAL 14  // DRYMAX valve pin intialisation
#define CHARGERVAL 12 // Charger valve pin intialisation

void initESPNOW();
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status);
void OnDataRecv(const uint8_t *mac, const uint8_t *incomingData, int len);
void SendReadings();
void Send_task(void *parameter);

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
    s.out++;
    DBG_ODS(Serial.print("Send messages = %d\n", s.out);)
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
    s.in++;
    DBG_ODR(Serial.print("Received messages = %d\n", s.in);)
    /*DBG_ODR(char macStr[18];)
    DBG_ODR(Serial.print("Packet received from: ");)
    DBG_ODR(snprintf(macStr, sizeof(macStr), "%02x:%02x:%02x:%02x:%02x:%02x",
                     mac_addr[0], mac_addr[1], mac_addr[2], mac_addr[3], mac_addr[4], mac_addr[5]);)
    DBG_ODR(Serial.println(macStr);)
    memcpy(&Rec_Readings, incomingData, sizeof(Rec_Readings));
    holding_Data.id = Rec_Readings.id;
    holding_Data.stat_Cen = Rec_Readings.stat_Cen;*/
}

void SendReadings()
{
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