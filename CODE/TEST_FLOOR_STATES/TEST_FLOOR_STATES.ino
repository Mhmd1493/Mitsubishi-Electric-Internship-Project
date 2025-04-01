// Include the servo library:
#include "Servo.h"

//Motor pins
#define EnMot     A0
#define In1Mot    A1  
#define In2Mot    A2  

// Define button pins
#define PinButton0  3                        
#define PinButton1  4                        
#define PinButton2  5                                               

// Define LED pins
#define LED0     6                        // PD6  
#define LED1     7                        // PD7  
#define LED2     8                        // PB0  

// Define floor swithes
#define PinSwitch0  9                       
#define PinSwitch1  10                      
#define PinSwitch2  11

// Define buzzer pin
#define Buzzer     12

// Define the servo pin:
#define servoPin    13

// Time constants
#define Pi                1500                      // (Timing constant Pi)
#define Pii               2200                      // (Timing constant Pii)

#define Ton               300                        // On time
#define Toff              50                         // Off time

// Create a new servo object:
Servo myservo;

// Define states
#define State_Stop        0                         // (Stopped)
#define State_Close       1                         // (Closing)
#define State_Idle        2                         // (Idle or Viewing)
#define State_Up          3                         // (Moving Up)
#define State_Down        4                         // (Moving Down)
#define State_Open        5                         // (Opening)

                  
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Global variables
unsigned char Button;
//This variable moves the car only if we have a button pressed, it might seem redundant but it ensures that the car wil not move against our will.
#define somebuttonpressed    Button    
int Destination, State = State_Stop, Position = 0, Floor0  = 0, Floor1  = 1, Floor2  = 2;

void LED(void)
{
  for (int i = 0; i < 3; i++)
  {
    digitalWrite(LED0, HIGH); digitalWrite(LED1, HIGH); digitalWrite(LED2, HIGH);
    tone(Buzzer, 1375);
    delay(100);
    digitalWrite(LED0, LOW);  digitalWrite(LED1, LOW);  digitalWrite(LED2, LOW);
    noTone(Buzzer);
    delay(100);
  }
  delay(50);
  digitalWrite(LED0, HIGH); tone(Buzzer, 1430); delay(Ton);    // Set led and tone
  digitalWrite(LED0, LOW);  noTone(Buzzer);     delay(Toff);      // Clear led and tone
  digitalWrite(LED1, HIGH); tone(Buzzer, 1485); delay(Ton);    // Set led and tone
  digitalWrite(LED1, LOW);  noTone(Buzzer);     delay(Toff);      // Clear led and tone
  digitalWrite(LED2, HIGH); tone(Buzzer, 1540); delay(Ton);    // Set led and tone
  digitalWrite(LED2, LOW);  noTone(Buzzer);     delay(Toff);      // Clear led and tone
  delay(Toff);
  digitalWrite(LED2, HIGH); tone(Buzzer, 1540); delay(Ton);    // Set led and tone
  digitalWrite(LED2, LOW);  noTone(Buzzer);     delay(Toff);      // Clear led and tone
  digitalWrite(LED1, HIGH); tone(Buzzer, 1485); delay(Ton);    // Set led and tone
  digitalWrite(LED1, LOW);  noTone(Buzzer);     delay(Toff);      // Clear led and tone
  digitalWrite(LED0, HIGH); tone(Buzzer, 1430); delay(Ton);    // Set led and tone
  digitalWrite(LED0, LOW);  noTone(Buzzer);     delay(Toff);      // Clear led and tone
  delay(500);

  for (int i = 0; i < 3; i++)
  {
    digitalWrite(LED0, HIGH); digitalWrite(LED1, HIGH); digitalWrite(LED2, HIGH);
    tone(Buzzer, 1375);
    delay(100);
    digitalWrite(LED0, LOW);   digitalWrite(LED1, LOW); digitalWrite(LED1, LOW);
    noTone(Buzzer);
    delay(100);
  }
  delay(500);
}

void Ring(void)
{
  tone(Buzzer, Pi);
  delay(80);
  noTone(Buzzer);
  delay(100);
  tone(Buzzer, Pi);
  delay(80);
  noTone(Buzzer);
  delay(160);
  tone(Buzzer, Pii);
  delay(140);
  noTone(Buzzer);
  delay(1000);
}


void ClearLED(void)
{
  digitalWrite(LED0, LOW); digitalWrite(LED1, LOW); digitalWrite(LED2, LOW);   Serial.println("Cleared LEDs");
}

void ClearButtons(void)
{
  Button = 0;   Serial.println("Cleared Button char");
}

void setup()
{
  Serial.begin(115200);                   // Initiate serial port

  pinMode(PinButton0, INPUT);
  pinMode(PinButton1, INPUT);             // Configuration of Input button pins
  pinMode(PinButton2, INPUT);

  pinMode(LED0, OUTPUT);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);               // Configuration of LED pins
  
  pinMode(PinSwitch0, INPUT);             // Configuration of Floor pins
  pinMode(PinSwitch1, INPUT);             
  pinMode(PinSwitch2, INPUT);    

  pinMode(Buzzer, OUTPUT);               // Configuration of Buzzer pin 
  
  LED();      
  Destination=Floor0;
  attachInterrupt(0,buttonPressed,LOW);   //We want the Arduino to read the button states whenever a buton is pressed, 
                                          //so we write an interrupt that is always activated by 
                                          //setting the interrupt mode to low and solidly grounding the Pin INT0=PD2 in our PCB.    
  Serial.println("AscensorNano V6.1");    //Courtsey from ReneRobotics Youtube channel.
  delay(1000); 
  ClearLED(); ClearButtons();
}
  

void loop() 
{
  if (somebuttonpressed) {setdestination(); }       //The value of somebuttonpressed is initially zero because we cleared it at the beginning of code 
                                                    //execution but it never resets back again once any single button is pressed, 
                                                    //this results in the continuous exection of setdestination and act functions.
  delay(10000);
}

void buttonPressed (void)
{
  if (!digitalRead(PinButton0)) bitSet(Button,0);
  if (!digitalRead(PinButton1)) bitSet(Button,1); 
  if (!digitalRead(PinButton2)) bitSet(Button,2); 
  Serial.print("Button number");
  int Button_int = (int)Button; 
  Serial.println(Button_int);
  delay(1000);
  State=State_Stop;
}

void setdestination(void)
{  
  switch  (State)
    {
      //we are stationary
      case 1:     
          //we are on floor 0
          if (digitalRead(PinSwitch0))
          {
              Position=Floor0;
              //if button pressed, then set light LED and set destination
              if      (bitRead(Button,0)) {Destination=Floor0;} else {digitalWrite(LED0,LOW);}
              if      (bitRead(Button,1)) {Destination=Floor1;} else {digitalWrite(LED1,LOW);}
              if      (bitRead(Button,2)) {Destination=Floor2;} else {digitalWrite(LED2,LOW);}
              Serial.print("Destination=");
              Serial.println(Destination);
              Serial.print("Position=");
              Serial.println(Position);
          }

          else if (digitalRead(PinSwitch1))
          {
              Position=Floor1;
              //if button pressed, then set light LED and set destination
              if      (bitRead(Button,0)) {Destination=Floor0;} else {digitalWrite(LED0,LOW);}
              if      (bitRead(Button,1)) {Destination=Floor1;} else {digitalWrite(LED1,LOW);}
              if      (bitRead(Button,2)) {Destination=Floor2;} else {digitalWrite(LED2,LOW);}
              Serial.print("Destination=");
              Serial.println(Destination);
              Serial.print("Position=");
              Serial.println(Position);
          }

          if (digitalRead(PinSwitch2))
          {
              Position=Floor2;
              //if button pressed, then set light LED and set destination
              if      (bitRead(Button,0)) {Destination=Floor0;} else {digitalWrite(LED0,LOW);}
              if      (bitRead(Button,1)) {Destination=Floor1;} else {digitalWrite(LED1,LOW);}
              if      (bitRead(Button,2)) {Destination=Floor2;} else {digitalWrite(LED2,LOW);}
              Serial.print("Destination=");
              Serial.println(Destination);
              Serial.print("Position=");
              Serial.println(Position);
          }

      break;
      case 2:    //we are non stationary 
      break;
    }
}




