#include <Servo.h>
#include <Arduino.h>
#include <SPI.h>
#include <RF24.h>
#include <nRF24L01.h>

#define MIN_TX_INPUT 0 
#define MAX_TX_INPUT 1023

#define CE_RX 9
#define CSN_RX 10
RF24 RxRadio(CE_RX,CSN_RX);

#define RX_SERVO_PIN 2
Servo rxServo;


const uint64_t radioAddress = 0xB00B1E5000LL;

void rxSetup(){
}

void setup() {
	RxRadio.begin();
	RxRadio.setAutoAck(true);              
  	RxRadio.setRetries(5,15);        
	RxRadio.openReadingPipe(1,radioAddress);
	RxRadio.startListening();
	RxRadio.printDetails();

	rxServo.attach(RX_SERVO_PIN);

	Serial.begin(115200);
}	

void loop() {
	if (RxRadio.available()){
		unsigned int input;
		RxRadio.read(&input,sizeof(input));

		Serial.print("Receiving: ");
		Serial.println(input);
	
		rxServo.write(map(
			input,
			MIN_TX_INPUT,
			MIN_TX_INPUT,
			0,
			180
		));
	}
}

/*
MISO MOSI
SCK  SS
*/
