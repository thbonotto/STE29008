int btn1int = 0;
int btn2int = 1;
int led1pin = 8;
int led2pin = 9;
unsigned long debounce_limit = 500;

volatile int led1state = LOW;
volatile int led2state = LOW;

void setup() {
    Serial.begin(9600);
    pinMode(8, OUTPUT);
    pinMode(9, OUTPUT);
    attachInterrupt(btn1int, blinkLed1, RISING);
    attachInterrupt(btn2int, blinkLed2, RISING);
}

void loop() {
    digitalWrite(led1pin, led1state);
    digitalWrite(led2pin, led2state);
}

void blinkLed1() {
  if (debounce(0)){
    Serial.println("Interruption One");
    led1state = !led1state;
  }
}
void blinkLed2() {
  if (debounce(1)){
    Serial.println("Interruption Two");
    led2state = !led2state;
  }
}

int debounce(const unsigned short nInt){ 
    //debounce is the function responsible for stabilizing the interruption requests
  static unsigned long time_last_accepted_interrupt[2]= {0};
  unsigned long now = millis();
    if( (now - time_last_accepted_interrupt[nInt]) > debounce_limit) {
        time_last_accepted_interrupt[nInt] = now;
        return 1;
    }
    else
        return 0;
}
