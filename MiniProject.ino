/*
 * Typical pin layout used:
 * -----------------------------------------------------------------------------------------
 *             MFRC522      Arduino       Arduino   Arduino    Arduino          Arduino
 *             Reader/PCD   Uno/101       Mega      Nano v3    Leonardo/Micro   Pro Micro
 * Signal      Pin          Pin           Pin       Pin        Pin              Pin
 * -----------------------------------------------------------------------------------------
 * RST/Reset   RST          9             5         D9         RESET/ICSP-5     RST
 * SPI SS      SDA(SS)      10            53        D10        10               10
 * SPI MOSI    MOSI         11 / ICSP-4   51        D11        ICSP-4           16
 * SPI MISO    MISO         12 / ICSP-1   50        D12        ICSP-1           14
 * SPI SCK     SCK          13 / ICSP-3   52        D13        ICSP-3           15

 
 *
 * 
 */

#include <SPI.h>
#include <MFRC522.h>
#define RST_PIN         9          // Configurable, see typical pin layout above
#define SS_PIN          10         // Configurable, see typical pin layout above

MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create MFRC522 instance
byte accessUID[4]={0x37, 0xE2, 0xDB, 0xD7};
void setup() {
  pinMode (4, OUTPUT); //Buzzer Pin 
  pinMode (7, INPUT); // LDR(500);
  pinMode(2,OUTPUT); // Laser
  delay(500);
	Serial.begin(9600);		// Initialize serial communications with the PC
	while (!Serial);		// Do nothing if no serial port is opened (added for Arduinos based on ATMEGA32U4)
	SPI.begin();			// Init SPI bus
	mfrc522.PCD_Init();		// Init MFRC522
	delay(4);				// Optional delay. Some board do need more time after init to be ready, see Readme
	mfrc522.PCD_DumpVersionToSerial();	// Show details of PCD - MFRC522 Card Reader details
	Serial.println(F("Scan PICC to see UID, SAK, type, and data blocks..."));
}
void loop(){
    //int i=0;
  if(digitalRead(7)==HIGH){
  //a:
  digitalWrite(2,HIGH);
  delay(1);
  digitalWrite(2,LOW);
  delay(1);
  digitalWrite(4, HIGH); 
  delay(2000);
  digitalWrite(4,LOW);
  delay(3);
  //i++;
  //if (i<50){
  //goto a;
  //}    
    }
    else{
    // Reset the loop if no new card present on the sensor/reader. This saves the entire process when idle.
    if ( ! mfrc522.PICC_IsNewCardPresent()) {
      return;
    }
    // Select one of the cards
    if ( ! mfrc522.PICC_ReadCardSerial()) {
      return;
    }
	// Dump debug info about the card; PICC_HaltA() is automatically called
    if(mfrc522.uid.uidByte[0]==accessUID[0] && mfrc522.uid.uidByte[1]==accessUID[1] && mfrc522.uid.uidByte[2]==accessUID[2] && mfrc522.uid.uidByte[3]==accessUID[3]){
        Serial.println("Access Granted");
        digitalWrite(2,HIGH);
        //digitalWrite(2,HIGH);
        delay(5000);
        digitalWrite(2,LOW);
        //digitalWrite(2,LOW);
    }
    else{
      Serial.println("Access Denied");
      //digitalWrite(2,HIGH);
      digitalWrite(4,HIGH);
      //digitalWrite(2,HIGH);
      delay(2000);
      //digitalWrite(2,LOW);
      digitalWrite(4,LOW);
    }
    mfrc522.PICC_HaltA();
    delay(50);
  }
}

