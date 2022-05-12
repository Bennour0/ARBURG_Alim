#include <Arduino.h>

#define Btn1_GPIO   18
#define LED1_GPIO   2
 
 int nbChanges = 0;
void IRAM_ATTR Ext_INT1_ISR()
{
  // Toggle The LED
  digitalWrite(LED1_GPIO, !digitalRead(LED1_GPIO));
  Serial.printf("State changed %5d\n", ++nbChanges);
}
 
void setup()
{
  Serial.begin(9600);
  Serial.printf("Start setup\n");
  pinMode(LED1_GPIO, OUTPUT);
  pinMode(Btn1_GPIO, INPUT_PULLDOWN);
  attachInterrupt(Btn1_GPIO, Ext_INT1_ISR, RISING);
  Serial.printf("End setup\n");
}
 
void loop()
{
  // Do Nothing...
}