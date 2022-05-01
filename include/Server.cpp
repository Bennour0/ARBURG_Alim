#include "Server.hpp"

t_inout ServerP::inout;

/**
 * @brief Prints a MAC add
 * 
 * @param mac const uint8_t *. A pointer to the mac address to be prented
 */
void ServerP::printMacAdd(const uint8_t *mac){
    for(int i=0; i<6; i++){
        Serial.printf("%X%c", mac[i], ((i==5)?' ':':'));
    }
}

void ServerP::printLocalMacAdd(){
    D_PMA(Serial.println("Start ServerP::printMacAdd()");)
    Serial.print(WiFi.macAddress());
    D_PMA(Serial.println("\nEnd ServerP::printMacAdd()");)
}

void ServerP::startESPNOW(){
    D_SESPNOW(Serial.println("Start ServerP::startESPNOW()");)
    // Set device as a Wi-Fi Station
    WiFi.mode(WIFI_STA);
    D_SESPNOW(Serial.println("Set board as Wifi station");)
    // Init ESP-NOW
    if (esp_now_init() != ESP_OK)
    {
        Serial.println("Error initializing ESP-NOW");
        return;
    }
    D_SESPNOW(Serial.println("ESP-NOW protol initialised");)
    // Once ESPNow is successfully Init, we will register for Send CB to
    // get the status of Trasnmitted packet
    esp_now_register_send_cb(OnDataSent);
    D_SESPNOW(Serial.println("OnDataSent registred");)
    // Register for a callback function that will be called when data is received
    esp_now_register_recv_cb(OnDataRecv);
    D_SESPNOW(Serial.println("OnDataRecv registred");)

    esp_now_peer_info_t peerInfo = {};

    // Registering peers
    for (int i = 0; i < NBARBURG; i++)
    {
        memcpy(peerInfo.peer_addr, arburgMacAdd[i], 6);
        peerInfo.channel = 0;
        peerInfo.encrypt = false;
        if (esp_now_add_peer(&peerInfo) != ESP_OK)
        {
            Serial.println("Failed to add peer");
            return;
        }
    }
    D_SESPNOW(Serial.printf("Register %d stations\n", NBARBURG);)
    D_SESPNOW(Serial.println("End ServerP::startESPNOW()");)
}
void ServerP::OnDataSent(const uint8_t *mac, esp_now_send_status_t status){
    D_ODS(Serial.println("Start ServerP::OnDataSent()");)
    D_ODS(Serial.print("Sending to: ");)
    D_ODS(printMacAdd(mac);)
    inout.out++;
    Serial.printf("\n%4d | %4d | %4d | %4d | %4d | %4d | %4d | %4d | ",
    inout.in+inout.out, inout.in, inout.out, -1,
    -1, -1, -1, -1);
    printMacAdd(mac);
    Serial.println(rtc.getTime("| %A, %B %d %Y %H:%M:%S"));
    D_ODS(Serial.println("\nEnd ServerP::OnDataSent()");)
}
void ServerP::OnDataRecv(const uint8_t *mac, const uint8_t *incomingData, int len){
    D_ODR(Serial.println("Start ServerP::OnDataRecv()");)
    D_ODR(Serial.print("Receive data from: ");)
    D_ODR(printMacAdd(mac);)
    D_ODR(Serial.println();)
    t_c2s c2s;
    
    //DBG_ODR(Serial.print("Inside OnDataRecv\n");)
    memcpy(&c2s, incomingData, sizeof(c2s));
    //arburgs_data[c2s.ID - 1] = c2s;
    // printClientInfo(&c2s);
    inout.in++;
    Serial.printf("\n%4d | %4d | %4d | %4d | %4d | %4d | %4d | %4d | ",
    inout.in+inout.out, inout.in, inout.out, c2s.inout.in,
    c2s.inout.out, c2s.Freq_sensor, c2s.Areq_sensor, c2s.Flevel_sensor);
    printMacAdd(mac);
    Serial.println(rtc.getTime("| %A, %B %d %Y %H:%M:%S"));
    D_ODR(Serial.println("End ServerP::OnDataRecv()");)
}

void ServerP::printClientInfo(const t_c2s *c2s){
    #define PRINT_STATUS(x) ((x)?"Up":"Down")
    Serial.printf("%d[%5s, %5s, %5s]", c2s->ID, PRINT_STATUS(c2s->Freq_sensor),
    PRINT_STATUS(c2s->Flevel_sensor),PRINT_STATUS(c2s->Areq_sensor));
}

void ServerP::broadcast(t_s2c s2c){
    D_BRCAST(Serial.println("Start ServerP::broadcast()");)
    for(int i=0; i<1; i++){
        send2client(arburgMacAdd[i], s2c);
    }
    D_BRCAST(Serial.println("End ServerP::broadcast()");)
    // esp_err_t result = esp_now_send(0, (uint8_t *)&s2c, sizeof(s2c));
}
void ServerP::send2client(const uint8_t *mac, t_s2c s2c){
    D_S2C(Serial.println("Start ServerP::send2client()");)
    D_S2C(esp_err_t result = )esp_now_send(mac, (uint8_t *)&s2c, sizeof(s2c));
    D_S2C(Serial.println("Sending to client %s\n", ((result)?"succeed" : "failed"));)
    D_S2C(Serial.println("End ServerP::send2client()");)
}
void Queue::initQ()
{
}
void Queue::showQ(queue<c2s> q)
{
    queue<c2s> temp = q;
    while (!temp.empty())
    {
        D_SHQ(Serial.printf("%4d | %4d | %4d | %4d ",temp.front().ID,temp.front().Freq_sensor,temp.front().Areq_sensor,temp.front().Flevel_sensor);)
        temp.pop();
    }
    D_SHQ(Serial.print("|");)
}