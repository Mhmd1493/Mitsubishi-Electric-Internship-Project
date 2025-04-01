#include <Servo.h>
// Define BUTTON pins
#define StartButton    2                        // FLOOR 0 BUTTON 
#define StopButton     3                        // FLOOR 1 BUTTON   

// Define LED pins
#define LED0     6                        // FLOOR 0 LED 
#define LED1     7                        // FLOOR 1 LED   
#define LED2     8                        // FLOOR 2 LED   

// Define IR pins
#define IR     4                        // CAR SENSOR  

Servo myservo;
int pos = 0;
// Define servo pin 
#define servopin          9              //  DOOR SERVO MOTORS                  

// Define buzzer pin
#define Buzzer            12              // BUZZER

// Define Motor pins
#define EN             A0               // BUZZER
#define IN1            10              // BUZZER
#define IN2            11              // BUZZER

#define Ton               300             // On time
#define Toff              50              // Off time
#define motor_speed       255             
#define pos_close         0               // servo motor limit during close
#define pos_open          90              // servo motor limit during open

/*int buttonState = 0;         // Variable to store the button state
int lastButtonState = 0;     // Variable to store the previous button state
unsigned long lastDebounceTime = 0;  // Last time the button state changed
unsigned long debounceDelay = 50;     // Debounce delay in milliseconds

int val = 0; // variable for reading the pin status
int counter = 0;
int currentState = 0;
int previousState = 0;

unsigned long startMillis = 0;
const long interval = 5000; // Interval in milliseconds (5 seconds)*/



void setup()
{
  Serial.begin(115200);                   // Initiate serial port

  pinMode(StopButton, INPUT);
  pinMode(StopButton, INPUT);
  pinMode(IR, INPUT);                   //IR SENSORS CONFIGURATION
  pinMode(LED0, OUTPUT);                  // Configuration of LED pins
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);                  
  pinMode(Buzzer, OUTPUT);                // Configuration of Buzzer pin 
  pinMode(servopin, OUTPUT);              // Configuration of Servo pin
  pinMode(EN, OUTPUT);                // Configuration of Buzzer pin 
  pinMode(IN1, OUTPUT);                // Configuration of Buzzer pin 
  pinMode(IN2, OUTPUT);              // Configuration of Servo pin
  myservo.attach(servopin);
  Serial.println("Elevator V5");          //Courtsey from ReneRobotics Youtube channel.
  delay(1000); 
  LED();

  if (digitalRead(IR) == 0)
  {
    move_down();
  }
  else 
  {
    stop();
  }  
}

void close_door(void)
{
  myservo.write(pos_close); //close door
}

void open_door(void)
{
  myservo.write(pos_open); //open door
}

int move_up(void)
{
  analogWrite(EN, motor_speed);
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,LOW);
}

void move_down(void)
{
  analogWrite(EN, motor_speed);
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,HIGH);
}

void stop(void)
{
  if (digitalRead(StopButton))
  {
    analogWrite(EN, 0);
    digitalWrite(IN1,LOW);
    digitalWrite(IN2,LOW);
  }
  small_buzz();
  delay(500);
  open_door();
  delay(500);
  close_door();
  small_buzz();
}

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

void small_buzz(void)
{
  tone(Buzzer, 440, 1000); 
}

void loop() 
{
move_up();
}