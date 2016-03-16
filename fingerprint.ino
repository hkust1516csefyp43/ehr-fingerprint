/*************************************************** 
  This is an example sketch for our optical Fingerprint sensor

  Adafruit invests time and resources providing this open source code, 
  please support Adafruit and open-source hardware by purchasing 
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.  
  BSD license, all text above must be included in any redistribution
 ****************************************************/
#include "fingerprints.h"
#include <SoftwareSerial.h>

int getFingerprintIDez();

// pin #2 is IN from sensor (GREEN wire)
// pin #3 is OUT from arduino  (WHITE wire)
SoftwareSerial mySerial(2, 3);
int i;

Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);

void setup()  
{
  while(!Serial);
  Serial.begin(9600);
  Serial.println("finger template test");

  // set the data rate for the sensor serial port
  finger.begin(57600);
  
  bool cannot_leave = true;
  do {
    if (finger.verifyPassword()) {
      Serial.println("Found fingerprint sensor!");
      cannot_leave = false;
    } else {
      Serial.println("Did not find fingerprint sensor :(");
        delay(2000);  //wait for 2 seconds and try again
    }
  } while (cannot_leave);

  i = 0;
  //TODO initiate bluetooth
  //TODO loop until bluetooth is connected
}

void loop()
{
  //TODO some kind of bluetooth listener
  Serial.print("run #"); Serial.println(i);
  uint8_t f = getFingerprintEnroll();
  i++;
  delay(5000);    //Delay for 5 seconds
}

uint8_t getFingerprintEnroll() {

  int p = -1;
  Serial.println("Put a finger to the scanner. Extraction in");
  Serial.print("5 ");
  delay(999);
  Serial.print("4 ");
  delay(999);
  Serial.print("3 ");
  delay(999);
  Serial.print("2 ");
  delay(999);
  Serial.print("1 ");
  delay(999);
  Serial.print("now");
  while (p != FINGERPRINT_OK) {
    p = finger.getImage();
    switch (p) {
    case FINGERPRINT_OK:
      Serial.println("");
      Serial.println("Image taken");
      break;
    case FINGERPRINT_NOFINGER:
      Serial.print(".");
      break;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.print("Communication error");
      break;
    case FINGERPRINT_IMAGEFAIL:
      Serial.print("Imaging error");
      break;
    default:
      Serial.print("Unknown error");
      break;
    }
  }
  
  p = finger.image2Tz(1);
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image converted");
      break;
    case FINGERPRINT_IMAGEMESS:
      Serial.println("Image too messy");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      return p;
    case FINGERPRINT_FEATUREFAIL:
      Serial.println("Could not find fingerprint features");
      return p;
    case FINGERPRINT_INVALIDIMAGE:
      Serial.println("Could not find fingerprint features");
      return p;
    default:
      Serial.println("Unknown error");
      return p;
  }
  
  Serial.println("Please remove finger");
  delay(2000);
  p = 0;
  while (p != FINGERPRINT_NOFINGER) {
    p = finger.getImage();
  }
  p = -1;
  
  Serial.println("Put the same finger to the scanner. Matching sequence in");
  Serial.print("5 ");
  delay(999);
  Serial.print("4 ");
  delay(999);
  Serial.print("3 ");
  delay(999);
  Serial.print("2 ");
  delay(999);
  Serial.print("1 ");
  delay(999);
  Serial.print("now");
  while (p != FINGERPRINT_OK) {
    p = finger.getImage();
    switch (p) {
    case FINGERPRINT_OK:
      Serial.println("");
      Serial.println("Image taken");
      break;
    case FINGERPRINT_NOFINGER:
      Serial.print(".");
      break;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      break;
    case FINGERPRINT_IMAGEFAIL:
      Serial.println("Imaging error");
      break;
    default:
      Serial.println("Unknown error");
      break;
    }
  }
  
  p = finger.image2Tz(2);
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image converted");
      break;
    case FINGERPRINT_IMAGEMESS:
      Serial.println("Image too messy");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      return p;
    case FINGERPRINT_FEATUREFAIL:
      Serial.println("Could not find fingerprint features");
      return p;
    case FINGERPRINT_INVALIDIMAGE:
      Serial.println("Could not find fingerprint features");
      return p;
    default:
      Serial.println("Unknown error");
      return p;
  }

  p = finger.createModel();
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Prints matched!");
      break;
    case FINGERPRINT_ENROLLMISMATCH:
      Serial.println("Mismatch");
      return p;
    default:
      Serial.println("Unknown error");
      return p;  
  }
  
  p = finger.upChar();
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("template transferring");
      break;
   default:
      Serial.print("Unknown error "); Serial.println(p);
      return p;
  }
  
  uint8_t templateBuffer2 = 0;
  int index=0;
  uint32_t starttime = millis();
  while ((index < 256) && ((millis() - starttime) < 5000))
  {
    if (mySerial.available())
    {
      templateBuffer2 = mySerial.read();
      index++;
      Serial.print("#"); Serial.print(index); Serial.print("= "); Serial.println(mySerial.read());
    }
  }
  Serial.print(index); Serial.println(" bytes read");
}

uint8_t fingerprintValidation() {
  //put input template into cb2
  //get image
  //image2tz cb1
  //createModel
  //TODO repeat { write finger to CharBuffer2, then compare CB1 & CB2 }

}

uint8_t fingerprintValidation2() {
  //Push a whole bunch of template into db and ask db to do the searching
}

uint8_t scanFinger() {

}

uint8_t scanFingerTwice() {
  
}

