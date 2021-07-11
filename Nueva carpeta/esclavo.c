#include <16f877.h>
//#include <stdio.h>

#fuses XT

#use delay(clock = 4000000)

#use i2c (SLAVE, SDA= PIN_C4, SLOW, SCL= PIN_C3, ADDRESS = 0xa0, NOFORCE_SW)

#define use_portd_lcd TRUE

#include <lcd.c>


#use standard_io(c)

#byte porta = 0x05
#byte trisa = 0x85

#byte portb = 0x06
#byte trisb = 0x86

#byte portc = 0x07
#byte trisc = 0x87

#byte portd = 0x08
#byte trisd = 0x88


void main () {
   trisc=0x00;
   portc=0x00;
   trisc=0xff;
   
   lcd_init();
   
   int comando2;
   comando2 = 0;
   
   lcd_gotoxy(1,1);
   lcd_putc("ESPERANDO" ) ;

   while(true){
      if(i2c_poll()){ //Si recibio el dato del bus devuelve verdadero
      comando2 = i2c_read(); //Guarda el dato del bus en la variable comando2
      lcd_putc("\f" ) ; //Borra la LCD
      lcd_putc(comando2); //Escribe en la LCD el dato obtenido del bus
      }
   }
}
