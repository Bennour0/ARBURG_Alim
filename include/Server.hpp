#include <Arduino.h>
#include <iostream>
#include <queue>
#include <ESP32Time.h>

ESP32Time rtc;
using std::queue;

#ifdef ESP32
  #include <WiFi.h>
#else
  #include <ESP8266WiFi.h>
#endif
#include <esp_now.h>
#include "messages.hpp"
#include "my_debug.hpp"
//#define ENCADRANT

// All MAC ADD
#ifdef ENCADRANT
  #define ADDMAC1     {0xAC, 0x67, 0xB2, 0x29, 0xAF, 0x38}  // 4
  #define ADDMAC2     {0x7C, 0x9E, 0xBD, 0x07, 0xDF, 0xCC}  // 2
  #define ADDMAC3     {0xC4, 0x4F, 0x33, 0x7C, 0x56, 0x41}  // 1
#else
  #define ADDMAC1     {0x84, 0xCC, 0xA8, 0x6A, 0xA1, 0xF0}
  #define ADDMAC2     {0x84, 0xCC, 0xA8, 0x6A, 0xB9, 0x7C}
#endif
#define NBARBURG 2

class ServerP{
public:
  /**
   * @brief Construct a new Server P object
   * 
   * @param pump_pin Central pump pin number
   * @param vlv1_pin Central pump valve one pin number
   * @param vlv2_pin Central pump valve two pin number
   * @param vlvr_pin Central tank valve pin number
   */
  ServerP(uint8_t pump_pin, uint8_t vlv1_pin, uint8_t vlv2_pin, uint8_t vlvr_pin);
  /**
   * @brief function that returns local MAC address
   * 
   */
  void printLocalMacAdd();
  /**
   * @brief function that initialize ESP NOW protocol
   * 
   */
  void startESPNOW();
  /**
   * @brief function that broadcast data to all system clients
   * 
   */
  void broadcast();
  /**
   * @brief function that sends data to client
   * 
   * @param mac client MAC address
   * @param s2c struct to be sent
   */
  void send2client(const uint8_t *mac, t_s2c s2c);
  /**
   * @brief function that checks server queue
   * 
   */
  void checkSQ();
  /**
   * @brief function that shows server queue
   * 
   * @param g queue to be shown
   */
  static void showQ(queue<t_c2s> g);
  /**
   * @brief function that runs server
   * 
   */
  void runServer();
  /**
   * @brief function that initialize the system
   * 
   */
  void begin();
private:
  /**
   * @brief function that setup server pins
   * 
   */
  void setupPins();
   /**
   * @brief function to be executed when a message is sent
   * 
   * @param mac_addr Mac address
   * @param status Protocol status
   */
  static void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status);
  /**
   * @brief function to be executed when a message is received
   * 
   * @param mac Mac addrees
   * @param incomingData received message
   * @param len received message length
   */
  static void OnDataRecv(const uint8_t *mac, const uint8_t *incomingData, int len);
  /**
   * @brief function that prints MAC addresses
   * 
   * @param mac MAC address to be printed
   */
  static void printMacAdd(const uint8_t * mac);
  /**
   * @brief functions that shows client informations
   * 
   * @param c2s client struct that contains the informations
   */
  static void printClientInfo(const t_c2s *c2s);
  /**
   * @brief clients MAC addresses
   * 
   */
  uint8_t arburgMacAdd[NBARBURG][6] = {ADDMAC1, ADDMAC2};
  /**
   * @brief system client numbers
   * 
   */
  static t_c2s arburgs_data[NBARBURG];
  /**
   * @brief Central pump pin number
   * 
   */
  static uint8_t central_pump;
  /**
   * @brief Central pump valve one pin number
   * 
   */
  static uint8_t pump_vlv1;
  /**
   * @brief Central pump valve two pin number
   * 
   */
  static uint8_t pump_vlv2;
  /**
   * @brief Central tank valve pin number
   * 
   */
  static uint8_t tank_vlv;
  /**
   * @brief struct to be received from client
   * 
   */
  static t_c2s c2s;
  /**
   * @brief struct to be sent to client
   * 
   */
  static t_s2c s2c;
  /**
   * @brief counter struct that will count in and out data
   * 
   */
  static t_inout inout;
};
//uint8_t arburgMacAdd[][6] = {ADDMAC1, ADDMAC2};

//t_c2s arburgs_data[NBARBURG];

#define SENSORSTATE(bState) ((bState) ? "Activated" : "Not Activated")
uint8_t arburgMacAdds[NBARBURG][6] = {ADDMAC1, ADDMAC2};

// stuct to be sent by central
//t_s2c s2c;

