int relay = 8;
volatile byte relayState = LOW;


int pirSensor = 2;
int fsrSensor = A0;
int fsrReading = 0;

// Timer Variables
long lastDebounceTime = 0;
long debounceDelay = 15000;


#include <SPI.h>
#include <SD.h>
#include <Adafruit_VS1053.h>


#define SHIELD_RESET  -1      // VS1053 reset pin (unused!)
#define SHIELD_CS     7      // VS1053 chip select pin (output)
#define SHIELD_DCS    6      // VS1053 Data/command select pin (output)

#define CARDCS 4     // Card chip select pin
#define DREQ 3       // VS1053 Data request, ideally an Interrupt pin



Adafruit_VS1053_FilePlayer musicPlayer =
  Adafruit_VS1053_FilePlayer(SHIELD_RESET, SHIELD_CS, SHIELD_DCS, DREQ, CARDCS);

int stationOn = 0;

void setup() {
      Serial.begin(115200);
     
      pinMode(relay, OUTPUT);
      digitalWrite(relay, HIGH);
      pinMode(pirSensor, INPUT);
       
      attachInterrupt(digitalPinToInterrupt(pirSensor), detect_Motion, RISING);
         
    
      if (! musicPlayer.begin()) {
        Serial.println(F("Couldn't find VS1053, do you have the right pins defined?"));
        while (1);
      }
      Serial.println(F("VS1053 found"));
    
      //musicPlayer.sineTest(0x44, 500);
    
      if (!SD.begin(CARDCS)) {
        Serial.println(F("SD failed, or not present"));
        while (1);
      }
      Serial.println("SD OK!");     

      // Set volume for left, right channels. lower numbers == louder volume!
      musicPlayer.setVolume(20, 20);

     // audio playing
      musicPlayer.useInterrupt(VS1053_FILEPLAYER_PIN_INT);   
    }
    

void loop() {

   fsrReading = analogRead(fsrSensor);

  if ((millis() - lastDebounceTime) > debounceDelay && relayState == HIGH) {
    digitalWrite(relay, HIGH);
    relayState = LOW;
    musicPlayer.stopPlaying();
    stationOn=0;

    Serial.println("OFF");

  }

 if (fsrReading > 100) {
    Serial.println("Motion2 is sensed!");
    Serial.print("fsrReading = ");
    Serial.println(fsrReading);
    
    musicPlayer.setVolume(10,10);
    musicPlayer.stopPlaying();
    musicPlayer.startPlayingFile("TEST02.MP3"); 

    delay(50);
 }

}

void detect_Motion() {   

  Serial.println("Motion1 is sensed!");      
  
  if (relayState == LOW && stationOn==0) {
    digitalWrite(relay, LOW);
    stationOn = 1;
    musicPlayer.startPlayingFile("TEST01.MP3");  

    Serial.print("stationOn = ");
    Serial.println(stationOn);
    
    delay(50);
  }

  relayState = HIGH;
  Serial.println("ON");
  lastDebounceTime = millis();

    delay(50);
  }
