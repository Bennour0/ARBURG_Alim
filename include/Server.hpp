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

/**
 * @brief Initialization function
 *
 */
void initESPNOW();

/**
 * @brief Callback when data is sent function
 *
 * @param mac_addr MAC ADD
 * @param status STATUS
 */
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status);

/**
 * @brief Callback when data is received function
 *
 * @param mac MAC ADD
 * @param incomingData RECEIVING DATA
 * @param len  RECEIVING DATA LENGTH
 */
void OnDataRecv(const uint8_t *mac, const uint8_t *incomingData, int len);

/**
 * @brief Send readings function
 *
 */
void SendReadings();

/**
 * @brief Send readings task for RTOS
 *
 * @param parameter Parameter for RTOS
 */
void Send_task(void *parameter);

/**
 * @brief Show receiving function
 *
 */
void ShowReceivings();
