#include <Arduino.h>
#ifdef ESP32
  #include <WiFi.h>
#else
  #include <ESP8266WiFi.h>
#endif
#include <esp_now.h>
#include "messages.hpp"
#include "my_debug.hpp"
#define ENCADRANT

// All MAC ADD
#ifdef ENCADRANT
  #define ADDMAC1     {0xAC, 0x67, 0xB2, 0x29, 0xAF, 0x38}  // 4
  #define ADDMAC2     {0x7C, 0x9E, 0xBD, 0x07, 0xDF, 0xCC}  // 2
  #define ADDMAC3     {0xC4, 0x4F, 0x33, 0x7C, 0x56, 0x41}  // 1
#else
  #define ADDMAC1     {0x84, 0xCC, 0xA8, 0x6A, 0xB9, 0x7C}
  #define ADDMAC2     {0x84, 0xCC, 0xA8, 0x6A, 0xA1, 0xF0}
#endif
#define NBARBURG 2

class ServerP{
public:
  void printLocalMacAdd(); 
  void startESPNOW();
  void broadcast(t_s2c s2c);
  void send2client(const uint8_t *mac, t_s2c s2c);
private:
  static void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status);
  static void OnDataRecv(const uint8_t *mac, const uint8_t *incomingData, int len);
  static void printMacAdd(const uint8_t * mac);
  static void printClientInfo(const t_c2s *c2s);
  uint8_t arburgMacAdd[NBARBURG][6] = {ADDMAC1, ADDMAC2};
  static t_c2s arburgs_data[NBARBURG];
};
//uint8_t arburgMacAdd[][6] = {ADDMAC1, ADDMAC2};

//t_c2s arburgs_data[NBARBURG];

#define SENSORSTATE(bState) ((bState) ? "Activated" : "Not Activated")
uint8_t arburgMacAdds[NBARBURG][6] = {ADDMAC1, ADDMAC2};

// stuct to be sent by central
//t_s2c s2c;