
#include <mega8.h>
#include <alcd.h>
#include <delay.h>
#include <stdlib.h>  
#include <stdio.h> 


unsigned int counter = 0 ;
float distance  = 0;
unsigned char str[10] ;
interrupt [TIM0_OVF] void timer0_ovf_isr(void) {
TCNT0 = 0 ;
counter++ ;
TIFR=0x01;
}
void main(void)
{
DDRB = 0xff;
DDRC = 0x05;



lcd_init(16);

 lcd_clear() ;
 lcd_puts("Ali Qasemi");
 delay_ms(2000);
 lcd_clear();
    
  TCNT0=0X00;
  TIMSK=0x01;
  #asm("sei")


while (1)
      {
      PORTC.0 = 1 ;
      delay_us(10) ;
      PORTC.0 = 0 ; 

      while(PINC.1 == 0);
      {
      TCCR0 = 0x01 ;    //frequency 1
      counter = 0 ;
      TCNT0 = 0 ;
      }      
      while(PINC.1 == 1);
      {
      TCCR0 = 0x00 ; // stop timer
      }

      distance = 0 ;
      distance = (counter * 256 + TCNT0) * 0.01724 ; // evaluate for distance 
      if(distance < 15){
      PORTC.2 = 1 ;
      }
      else{
      PORTC.2 = 0 ;
      }
      
      //show on lcd
      lcd_clear() ;
      lcd_puts("distance=");
      lcd_gotoxy(0,1);
      ftoa(distance,2,str);
      lcd_puts(str);  
      lcd_gotoxy(5 , 1) ;
      lcd_puts("cm") ; 
      delay_ms(500) ;
      
      }
}
