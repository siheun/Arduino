int pirSensor = 2; // define output pin for pirSensor
int relayPin = 8;// define output pin for relay

// Timer Variables
//long lastDebounceTime = 0;  
//long debounceDelay = 5000;


void setup() {
  pinMode(pirSensor, INPUT_PULLUP);// define pin 2 as input
  pinMode(relayPin, OUTPUT);// define pin 8 as output

  Serial.begin(9600); // send debugging information via the Serial monitor

}

void loop() {
  
  if (digitalRead(pirSensor) == HIGH) {
    digitalWrite(relayPin, LOW);// turn the relay OFF (HIGH is OFF if relay is LOW trigger. change it to LOW if you have got HIGH trigger relay)
    Serial.println("detected!");
  }

  else {
    digitalWrite(relayPin, HIGH);

  }
  delay(500);// wait for 500 millisecond
}
