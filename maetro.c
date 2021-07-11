#include <16f877.h>

#fuses XT, PUT, NOPROTECT, BROWNOUT, NOLVP, NOWDT

#use delay(clock = 4000000)

#use i2c (MASTER, SDA= PIN_C4, SLOW, SCL= PIN_C3, NOFORCE_SW) // Configuración global del bus a dos hilos.

#define use_portb_kbd TRUE //Se utiliza el puerto B para conectar el teclado
#include <kbd.c> //Se declara la libreria de teclado

#use standard_io(b)
#use standard_io(c)

#byte porta = 0x05 //Se declaran las direcciones de los puertos y el registro TRIS
#byte trisa = 0x85

#byte portb = 0x06
#byte trisb = 0x86

#byte portc = 0x07
#byte trisc = 0x87

#byte portd = 0x08
#byte trisd = 0x88

int8 comando; //La variable de tipo entero donde se guardara el dato obtenido del teclado


void main () {
   trisd = 0x00;
   portd = 0x00;
   comando =0;
   portc=0x00;
   
   kbd_init(); //Inicia configuración de teclado
   port_b_pullups(true); //Activa resistencias de pull-up en el puerto b
   
   while(1){
      comando=kbd_getc(); //Guarda el dato obtenido del teclado en la variable comando
      if(comando!=0){
         i2c_start(); //Empieza transmisión de datos en el bus
         i2c_write(0xa0); //Se envía la dirección del esclavo al cual se quiere comunicar
         i2c_write(comando); //Se escribe el dato obtenido del teclado
         i2c_stop(); //Finaliza la transmisión en el bus
         delay_ms(100); //Retardo para eliminar posibles errores
      }
   }
}
