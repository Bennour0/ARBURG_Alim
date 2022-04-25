#include <Arduino.h>
#include <WiFi.h> 
#include <esp_now.h>
#include "messages.hpp"

#define ENCADRANT

// All MAC ADD
#ifdef ENCADRANT
  #define ADDMAC     {0xC4, 0x4F, 0x33, 0x7C, 0x56, 0x41}  // 1
#else
  #define ADDMAC     {0x84, 0xCC, 0xA8, 0x6A, 0xB9, 0x7C}
#endif

extern "C" {void OnSent(const uint8_t *mac_addr, esp_now_send_status_t status);}
class ClientP{
public:
  ClientP(uint8_t id, uint8_t sen_feedmax_pin, uint8_t sen_arburg_pin, uint8_t sen_feedmax_lvl_pin,
          uint8_t vlv_charger_pin, uint8_t vlv_feedmax_pin, uint8_t vlv_drymax_pin);
  void printMacAdd();
  void startESPNOW();
  void send2server(t_c2s c2s);
  void printServer();
private:
  static void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status);
  static void OnDataRecv(const uint8_t *mac, const uint8_t *incomingData, int len);
  void printMacAdd(const uint8_t *mac);
  uint8_t id;
  uint8_t serverMacAdd[6] = ADDMAC;
  uint8_t sen_feedmax;
  uint8_t sen_arburg;
  uint8_t sen_feedmax_lvl;
  uint8_t vlv_charger;
  uint8_t vlv_feedmax;
  uint8_t vlv_drymax;
  static t_s2c s2c;
};

