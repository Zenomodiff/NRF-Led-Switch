#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(8, 10); // CE, CSN
const byte address[6] = "00001";

boolean button_state = 0;
int led_pin = 3;

void setup() {
pinMode(led_pin , OUTPUT);
Serial.begin(9600);
radio.begin();
radio.openReadingPipe(0, address);   
radio.setPALevel(RF24_PA_MIN);     
radio.startListening();           
}

void loop()
{
if (radio.available())              //Looking for the data.
{
char text[32] = "";                 //Saving the incoming data
radio.read(&text, sizeof(text));    //Reading the data
radio.read(&button_state, sizeof(button_state));    //Reading the data
if(button_state == HIGH)
{
digitalWrite(led_pin , HIGH);
Serial.println(text);
}
else
{
digitalWrite(led_pin , LOW);
Serial.println(text);}
}
delay(5);
}
