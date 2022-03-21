#include <Arduino.h>
#include <WiFi.h>
#include <esp_now.h>
#include "messages.hpp"

void initESPNOW();
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status);
void OnDataRecv(const uint8_t *mac, const uint8_t *incomingData, int len);

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

    /*esp_now_peer_info_t peerInfo;
    // Register peer
    memcpy(peerInfo.peer_addr, broadcastAddress, 6);
    peerInfo.channel = 0;
    peerInfo.encrypt = false;
    // Add peer
    if (esp_now_add_peer(&peerInfo) != ESP_OK)
    {
        Serial.println("Failed to add peer");
        return;
    }*/
}

void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status)
{
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
    /*DBG_ODR(char macStr[18];)
    DBG_ODR(Serial.print("Packet received from: ");)
    DBG_ODR(snprintf(macStr, sizeof(macStr), "%02x:%02x:%02x:%02x:%02x:%02x",
                     mac_addr[0], mac_addr[1], mac_addr[2], mac_addr[3], mac_addr[4], mac_addr[5]);)
    DBG_ODR(Serial.println(macStr);)
    memcpy(&Rec_Readings, incomingData, sizeof(Rec_Readings));
    holding_Data.id = Rec_Readings.id;
    holding_Data.stat_Cen = Rec_Readings.stat_Cen;*/
}