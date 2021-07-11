#include <16f877a.h>
#fuses XT,NOWDT,NOPROTECT,PUT,NOBROWNOUT,NOLVP
#use delay(clock=4000000)
#include <lcd.c>

#use i2c(SLAVE, SDA=PIN_C4, SCL=PIN_C3, ADDRESS=0Xa0)

#use standard_io(c)

void main(){
   lcd_init();
   int comando2;
   comando2=0;
   lcd_gotoxy(1,1);
   lcd_putc("Esperando");
   while(True){
      if(i2c_poll()){
         comando2 = i2c_read();
         lcd_putc("\f");
         lcd_putc(comando2);
      } 
   }
}
