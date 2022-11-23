/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"

#define WAIT_TIME_MS 500
CAN can1(PB_8, PB_9, 500000);
char counter = 0;
char txBuff[8];
unsigned int txID = 1337;
CANMessage txMsg;


void printMessage(CANMessage msg);

int main() {

  while (true) {
    txBuff[0] = counter;
    txMsg = CANMessage(txID, txBuff, 8);

    if (can1.write(txMsg)) {
      counter++;
      printf("Message sent: %d\n", counter);
    }
  
    thread_sleep_for(WAIT_TIME_MS);
  }
}
