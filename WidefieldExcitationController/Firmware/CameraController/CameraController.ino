
#define LED_I1 2
#define LED_I2 5
#define LED_I3 8
#define LED_I4 11

#define LED_O1 1
#define LED_O2 4
#define LED_O3 7
#define LED_O4 10

#define LED_ACT1 0
#define LED_ACT2 3
#define LED_ACT3 6
#define LED_ACT4 9

// IO1 23 - Also this is PTC2
// IO2 22 - Also this is PTC1
// IO3 21 - Also this is PTD6
// IO4 20 - Also this is PTD5
#define IO1 23
#define IO2 22
#define IO3 21
#define IO4 20

void setup() {

    pinMode(LED_I1, OUTPUT);
    pinMode(LED_I2, OUTPUT);
    pinMode(LED_I3, OUTPUT);
    pinMode(LED_I4, OUTPUT);
    pinMode(LED_O1, OUTPUT);
    pinMode(LED_O2, OUTPUT);
    pinMode(LED_O3, OUTPUT);
    pinMode(LED_O4, OUTPUT);
    pinMode(LED_ACT1, OUTPUT);
    pinMode(LED_ACT2, OUTPUT);
    pinMode(LED_ACT3, OUTPUT);
    pinMode(LED_ACT4, OUTPUT);

    digitalWrite(LED_I1, 1);
    digitalWrite(LED_I2, 0);
    digitalWrite(LED_I3, 0);
    digitalWrite(LED_I4, 0);
    
    digitalWrite(LED_O1, 0);
    digitalWrite(LED_O2, 1);
    digitalWrite(LED_O3, 1);
    digitalWrite(LED_O4, 1);

    pinMode(IO1, INPUT);
    pinMode(IO2, OUTPUT);
    pinMode(IO3, OUTPUT);
    pinMode(IO4, OUTPUT);
}

int trigger_pin = 0;
int state = 0;
int camera_input = 0;

int ActivityLEDs[] = {LED_ACT2, LED_ACT3, LED_ACT4};
int TriggerPorts[] = {IO2, IO3, IO3};

// long int test_counter = 100000;

void loop() {
     
  camera_input = GPIOC_PDIR & 0x02;

  /* For testing -- */
  /*
  if (test_counter-- == 0) {
    if (camera_input == 1)
      camera_input = 0;
    else
      camera_input = 1;
    test_counter = 100000;
  }
  */
  
  if ((state == 0) && (camera_input > 0)) { // rising edge
    digitalWrite(TriggerPorts[trigger_pin],1);
    digitalWrite(ActivityLEDs[trigger_pin],1);

    digitalWrite(LED_ACT1,1);

    state = 1;
    delay(2); // wait 2 ms before going on
  }
  else if ((state == 1) && (camera_input == 0)) { // falling edge
    digitalWrite(TriggerPorts[trigger_pin],0);
    digitalWrite(ActivityLEDs[trigger_pin],0);

    digitalWrite(LED_ACT1,0);
    state = 0;
    trigger_pin++;
    if (trigger_pin > 2)
      trigger_pin = 0;      
  }

}
