#include "Firmware.h"

void setup() {

    InitGPIO();
    ConfigDIO(1,INPUT_PULLDOWN);
    ConfigDIO(2,OUTPUT);
    ConfigDIO(3,OUTPUT);
    ConfigDIO(4,OUTPUT);
    ConfigAUX(2,OUTPUT);
    ConfigAUX(3,OUTPUT);
    ConfigAUX(4,OUTPUT);

    digitalWrite(LED0, 0);
    digitalWrite(LED1, 0);
    digitalWrite(LED2, 0);
    digitalWrite(LED3, 0);

}

void sequenceLEDs(void) {
    static int led = 0;
    static int count = 500000;

    if (count-- == 0) {
        count = 500000;
    }
    else {
        return;
    }

    switch (led) {
       case 0:
       digitalWrite(LED0, 1);
       digitalWrite(LED2, 0);
       led = 1;
       break;
       case 1:
       digitalWrite(LED1, 1);
       digitalWrite(LED0, 0);
       led = 2;
       break;
       case 2:
       digitalWrite(LED2, 1);
       digitalWrite(LED1, 0);
       led = 0;
       break;
       case 3:
       digitalWrite(LED3, 1);
       digitalWrite(LED2, 0);
       led = 0;
       break;
    }
}

int trigger_pin = 2;
int state = 0;
int camera_input = 0;

void loop() {

  sequenceLEDs();
     
  camera_input = GPIOD_PDIR & 0x01;
  if ((state == 0) && (camera_input > 0)) { // rising edge
    WriteDIO(trigger_pin,1);
    WriteAUX(trigger_pin,1);
    state = 1;
    delay(2); // wait 2 ms before going on
  }
  else if ((state == 1) && (camera_input == 0)) { // falling edge
    WriteDIO(trigger_pin, 0);
    WriteAUX(trigger_pin, 0);
    state = 0;
    trigger_pin++;
    if (trigger_pin > 4)
      trigger_pin = 2;      
  }

}
