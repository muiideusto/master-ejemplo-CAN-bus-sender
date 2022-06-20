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
CANMessage rxMsg;
void printMessage(CANMessage msg);

int main() {
  printf("This is the bare metal blinky example running on Mbed OS %d.%d.%d.\n",
         MBED_MAJOR_VERSION, MBED_MINOR_VERSION, MBED_PATCH_VERSION);

  while (true) {
    txBuff[0] = counter;
    txMsg = CANMessage(txID, txBuff, 8);

    if (can1.write(txMsg)) {
      counter++;
      printf("Message sent: %d\n", counter);
    }
    if (can1.read(rxMsg)) {
      printMessage(rxMsg);
    }
    thread_sleep_for(WAIT_TIME_MS);
  }
}

void printMessage(CANMessage msg) {
  printf("Message received with id %X and length %d with data:", msg.id,
         msg.len);
  for (int i = 0; i < msg.len; i++) {
    printf(" %X", msg.data[i]);
  }
  printf("\n");
}
