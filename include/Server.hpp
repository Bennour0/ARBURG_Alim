#include <Arduino.h>
#include <WiFi.h>
#include <esp_now.h>
#include "messages.hpp"
#include "my_debug.hpp"

// All MAC ADD
#define NBARBURG 2
uint8_t arburgMacAdd[][6] = {{0x84, 0xCC, 0xA8, 0x6A, 0xB9, 0x7C},
                             {0x84, 0xCC, 0xA8, 0x6A, 0xA1, 0xF0}};

t_c2s arburgs_data[NBARBURG];

#define SENSORSTATE(bState) (bState) ? "Activated" : "Not Activated"

// stuct to be sent by central
t_s2c s2c;

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
