#include <Arduino.h>
#include <WiFi.h> 
#include <esp_now.h>
#include <queue>
#include "messages.hpp"

using std::queue;

//#define ENCADRANT

// All MAC ADD
#ifdef ENCADRANT
  #define ADDMAC     {0xC4, 0x4F, 0x33, 0x7C, 0x56, 0x41}  // 1
#else
  #define ADDMAC     {0x7C, 0x9E, 0xBD, 0x62, 0x12, 0x98}
#endif

class ClientP{
public:
/**
 * @brief Construct a new Client P object
 * 
 * @param id Client identification
 * @param sen_feedmax_pin FEEDMAX requirements sensor pin number
 * @param sen_arburg_pin ARBURG requirements sensor pin number
 * @param sen_feedmax_lvl_pin FEEDMAX level sensor pin number
 * @param vlv_charger_pin Charger valve pin number
 * @param vlv_feedmax_pin FEEDMAX valve pin number  
 * @param vlv_drymax_pin DRYMAX valve pin number
 */
  ClientP(uint8_t id, uint8_t sen_feedmax_pin, uint8_t sen_arburg_pin, uint8_t sen_feedmax_lvl_pin,
          uint8_t vlv_charger_pin, uint8_t vlv_feedmax_pin, uint8_t vlv_drymax_pin);
  /**
   * @brief function that returns client MAC address
   * 
   */
  void printMacAdd();
  /**
   * @brief function that initialize ESP NOW protocol
   * 
   */
  void startESPNOW();
  /**
   * @brief function that send data to server
   * 
   */
  void send2server();
  /**
   * @brief function that returnss server MAC address
   * 
   */
  void printServer();
  /**
   * @brief function that shows client queue
   *
   * 
   * @param g queue to be shown
   */
  static void showCQ(queue<int> g);
  /**
   * @brief function that runs the client when data is received
   * 
   */
  static void runClient();
  /**
   * @brief function that initialize the system
   * 
   */
  void begin();
  /**
   * @brief function that sends interruption data
   * 
   */
  void sendInterruption();
private:
  /**
   * @brief function that setup client pins
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
  void printMacAdd(const uint8_t *mac);
  /**
   * @brief FEEDMAX requirements sensor interruption function
   * 
   */
  static void IRAM_ATTR INT_FEEDMAX();
  /**
   * @brief ARBURG requirements sensor interruption function
   * 
   */
  static void IRAM_ATTR INT_ARBURG();
  /**
   * @brief FEEDMAX level sensor interruption function
   * 
   */
  static void IRAM_ATTR INT_FEEDMAX_LVL();
  /**
   * @brief Client identification
   * 
   */
  uint8_t id;
  /**
   * @brief table that holds server MAC address
   * 
   */
  uint8_t serverMacAdd[6] = ADDMAC;
  /**
   * @brief FEEDMAX requirements sensor pin number
   * 
   */
  static uint8_t sen_feedmax;
  /**
   * @brief ARBURG requirements sensor pin number
   * 
   */
  static uint8_t sen_arburg;
  /**
   * @brief FEEDMAX level sensor pin number
   * 
   */
  static uint8_t sen_feedmax_lvl;
  /**
   * @brief Charger valve pin number
   * 
   */
  static uint8_t vlv_charger;
  /**
   * @brief FEEDMAX valve pin number
   * 
   */
  static uint8_t vlv_feedmax;
  /**
   * @brief DRYMAX valve pin number
   * 
   */
  static uint8_t vlv_drymax;
  /**
   * @brief struct to be received from server
   * 
   */
  static t_s2c s2c;
  /**
   * @brief strut to be sent to server
   * 
   */
  static t_c2s c2s;
  /*static t_inout inout;*/
};