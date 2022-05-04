#include <Arduino.h>
#include <WiFi.h> 
#include <esp_now.h>
#include <queue>
#include "messages.hpp"

using namespace std;

//#define ENCADRANT

// All MAC ADD
#ifdef ENCADRANT
  #define ADDMAC     {0xC4, 0x4F, 0x33, 0x7C, 0x56, 0x41}  // 1
#else
  #define ADDMAC     {0x7C, 0x9E, 0xBD, 0x62, 0x12, 0x98}
#endif

class ClientP{
public:
  ClientP(uint8_t id, uint8_t sen_feedmax_pin, uint8_t sen_arburg_pin, uint8_t sen_feedmax_lvl_pin,
          uint8_t vlv_charger_pin, uint8_t vlv_feedmax_pin, uint8_t vlv_drymax_pin);
  void printMacAdd();
  void startESPNOW();
  void send2server();
  void printServer();
  static void showQ(queue<int> g);
  static void runClient();
private:
  static void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status);
  static void OnDataRecv(const uint8_t *mac, const uint8_t *incomingData, int len);
  void printMacAdd(const uint8_t *mac);
  uint8_t id;
  uint8_t serverMacAdd[6] = ADDMAC;
  static uint8_t sen_feedmax;
  static uint8_t sen_arburg;
  static uint8_t sen_feedmax_lvl;
  static uint8_t vlv_charger;
  static uint8_t vlv_feedmax;
  static uint8_t vlv_drymax;
  static t_s2c s2c;
  static t_c2s c2s;
  /*static t_inout inout;*/
};

