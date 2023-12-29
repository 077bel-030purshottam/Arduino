 // MakeIdea [Hemant]
#include <avr/io.h>
#include <avr/interrupt.h>
#include <math.h>

#define SinDivisions (200)

static int microMHz = 16;
static int freq =50;   
static long int period;  
static unsigned int lookUp[SinDivisions];
static char theTCCR1A = 0b10000010; 

void setup()
{
  double temp; 
  
  period = microMHz*1e6/freq/SinDivisions;
  
  for(int i = 0; i < SinDivisions/2; i++)
  { 
    temp = sin(i*2*M_PI/SinDivisions)*period;
    lookUp[i] = (int)(temp+0.5);           
  }
  
  TCCR1A = theTCCR1A; 
       
  TCCR1B = 0b00011001;
       
  TIMSK1 = 0b00000001;
          
  ICR1   = period;   
  sei();             
  
  DDRB = 0b00000110; 
  pinMode(13, OUTPUT);
}

void loop(){;}

ISR(TIMER1_OVF_vect)
{
    static int num;
    static int delay1;
    static char trig;
    
    if(delay1 == 1)
    {
      theTCCR1A ^= 0b10100000;
      TCCR1A = theTCCR1A;
      delay1 = 0;             
    } 
    else if(num >= SinDivisions/2)
    {
      num = 0;                
      delay1++;
      trig ^=0b00000001;
      digitalWrite(13,trig);
    }
   
    OCR1A = OCR1B = lookUp[num];
    num++;
}
