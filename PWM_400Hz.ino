/* 
Andrea Toscano 2015
Microcontroller : Atmega32u4
PWM FREQUENCY  400Hz

PIN   5,9,10,11*/

#define motor0 OCR1A // PIN 9
#define motor1 OCR1B // PIN 10
#define motor2 OCR1C // PIN 11
#define motor3 OCR3A // PIN 5
#define MIN 2200
#define MAX 3800

int motorValue = 0;

unsigned long newMills = 0;
unsigned long oldMills = 0;

void setup()  {

  //*************************************************
  // Timer 1
  //*************************************************
  // Pin Setup
  // Output Direction
  DDRB |= (1 << 7) | (1 << 6) | (1 << 5);
  // 
  ICR1 = 0x1387;  // 400Hz
  
 /* 
 [COM1A1,COM1A0,COM1B1,COM1B0,COM1C1,COM1C0,WGM11.WGM10]
 bit 7:2 Compare output mode 3 channels.  Setting OCnA/OCnB/OCnC on comptare match, set output to LOW
 bit 1:0  Fast PWM, TOP: ICRn  Modality
 */
  TCCR1A = 0b10101010;
/*
[ICNC1,ICES1,–,WGM13,WGM12,CS12,CS11,CS10]
bit 7:5 Don't Care
bit 4:3  Fast PWM
bit 2:0 Prescaler: clock/8

*/
  TCCR1B = 0b00011010;

  // Initializing output variables
  motor0 = 0;
  motor1 = 0;
  motor2 = 0;

  //*************************************************
  // Timer 3
  //*************************************************

  DDRC |= (1 << PC6); // motor3  PWM Port.
  ICR3 = 0x1387;  

  TCCR3A = 0b10101010;
  TCCR3B = 0b00011010;
  
   // Initializing output var
  motor3 = 0;
  motorValue = MIN;
}

// Test with the oscilloscope the dutycycle 
void loop()
{
  newMills = millis();

  if (newMills - oldMills > 100)
  {
    motorValue += 5;
    if (motorValue == MAX)
      motorValue = MIN;

    motor0 = motorValue;
    motor1 = motorValue;
    motor2 = motorValue;
    motor3 = motorValue;

    oldMills = newMills;
    Serial.println(motorValue);
  }
}
