# Arduino_Fast_PWM_Atmega32u4
Generating PWM @400Hz for quadcopter's ESC

The main issue using the Servo Library is that you can hardly go faster than 125Hz,  with a huge amount of interrupts generated.
I use instead 16bit Timer1 and Timer3 to generate PWM signals @400Hz on 4 pins
