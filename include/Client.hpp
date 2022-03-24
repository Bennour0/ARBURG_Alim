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

// Board PID
#define PID 1

// Sensors pins assignments :
#define FEEDMAXREQ 25 // FEEDMAX Requirement sensor pin intialisation
#define ARBURGREQ 26  // ARBURG Requirement sensor pin intialisation
#define FEEDMAXLVL 27 // FEEDMAX Level sensor pin intialisation

// Actuators pins assignments :
#define CHARGERVAL 12 // Charger valve pin intialisation
#define FEEDMAXVAL 13 // FEEDMAX valve pin intialisation
#define DRYMAXVAL 14  // DRYMAX valve pin intialisation

/**
 * @brief Initialization Fonction
 *
 */
void initESPNOW();

/**
 * @brief Callback when data is sent fonction
 *
 * @param mac_addr MAC ADD
 * @param status STATUS
 */
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status);

/**
 * @brief Callback when data is received fonction
 *
 * @param mac MAC ADD
 * @param incomingData RECEIVING DATA
 * @param len RECEIVING DATA LENGTH
 */
void OnDataRecv(const uint8_t *mac, const uint8_t *incomingData, int len);

/**
 * @brief Send Readings fonction
 *
 */
void SendReadings();

/**
 * @brief Send Readings for RTOS
 *
 * @param parameter RTOS Parameter
 */
void Send_task(void *parameter);
