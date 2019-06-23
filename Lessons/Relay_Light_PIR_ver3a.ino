int relay = 8;
volatile byte relayState = LOW;

int pirSensor = 2;

// Timer Variables
long lastDebounceTime = 0;  
long debounceDelay = 10000;

void setup() {
  pinMode(relay, OUTPUT);
  digitalWrite(relay, HIGH);
  pinMode(pirSensor, INPUT);
  //Whenever the PIR motion sensor is triggered, it calls the detectMotion() function declared at the end of the code to turn the relay on
  attachInterrupt(digitalPinToInterrupt(pirSensor), detectMotion, RISING);
  // Serial communication for debugging purposes
  Serial.begin(9600);
}

void loop() {
  // If 10 seconds have passed, the relay is turned off
  if((millis() - lastDebounceTime) > debounceDelay && relayState == HIGH){
    digitalWrite(relay, HIGH);
    relayState = LOW;
    Serial.println("OFF");
  }
  delay(50);
}

void detectMotion() {
  Serial.println("Motion");
  if(relayState == LOW){
    digitalWrite(relay, LOW);
  }
  relayState = HIGH;  
  Serial.println("ON");
  lastDebounceTime = millis();  // reset the debouncing timer
}
