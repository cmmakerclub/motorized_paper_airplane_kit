   

#include "CMMC_Receiver.h"


#define LED 0

#define Motor_L_Pin 13
#define Motor_R_Pin 12


//#define Receiver_Debug

//Servo Motor;
//Servo Rudder;


void setup() {
  receriver_init();

  pinMode(LED, OUTPUT);
  pinMode(Motor_L_Pin, OUTPUT);
  pinMode(Motor_R_Pin, OUTPUT);


}

uint32_t time_now, time_prev1;

void loop() {


  time_now = millis();

  if (time_now - time_prev1 >= 20) {
    time_prev1 += 20;

#ifdef Receiver_Debug
    Serial.print(Get_ChannelValue(1)); Serial.print("\t");
    Serial.print(Get_ChannelValue(2)); Serial.print("\t");
    Serial.print(Get_ChannelValue(3)); Serial.print("\t");
    Serial.print(Get_ChannelValue(4)); Serial.println("\t");
#endif


    int tmp1 = (float)Get_ChannelValue(1) * 10.23f;


    int tmp2 = (float)Get_ChannelValue(2) * 10.23f;
    if (tmp2 > 1023)tmp2 = 1023;
    if (tmp2 < 0)tmp2 = 0;

    int tmp3 = tmp2 - (tmp1 / 2);
    int tmp4 = tmp2 + (tmp1 / 2);

    if (tmp3 > 1023)tmp3 = 1023;
    if (tmp3 < 0)tmp3 = 0;
    analogWrite(Motor_R_Pin, tmp3);

    if (tmp4 > 1023)tmp4 = 1023;
    if (tmp4 < 0)tmp4 = 0;
    analogWrite(Motor_L_Pin, tmp4);


  }

  receriver_loop();
}
