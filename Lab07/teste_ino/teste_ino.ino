int analogPin = 0;     // potentiometer wiper (middle terminal) connected to analog pin 3

                       // outside leads to ground and +5V

int val = 0;           // variable to store the value read



void setup()

{

  Serial.begin(9600);          //  setup serial

}

int RMS(int repeat){
  unsigned long i = 0;
  unsigned long digital_value = 0;
  unsigned long accumulated = 0, average = 0;
    while(i < repeat) {
        digital_value = analogRead(analogPin);   //convert the analog-value (voltage) to digital one (0-1024)
        accumulated += digital_value*digital_value;      //accumulate all the digital-values “repeat” times
        i++;
    }
    average = accumulated / repeat;
    return sqrt(average);
}

void loop()

{

 val = RMS(30);    // read the input pin
  
  delay(500);
  Serial.println(val);             // debug value
  Serial.println(val*0.004887586); 

}

