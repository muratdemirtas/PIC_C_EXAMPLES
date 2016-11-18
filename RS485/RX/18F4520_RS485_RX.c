/*
 * Dosya    : main.c
 * Yazar    : Expkits - www.expkits.com
 * Uygulama : RS485 Haberleþme Uygulamasý
 * Sürüm    : v1.0
 * Tarih    : 05.04.2013
 * MCU      : PIC18F4520
 * Kristal  : 20Mhz
 * Kit      : EX8
 * Açýklama : Amaç RS485 protokolü üzerinden veri almaktýr.
 *
 * Uyarý    : CCS v4 ile derlenmiþtir.
 *           EX8 Kullanýcýlarý için;
 *           - SWDIP6 (SW1) EN anahtarý ON konumunda olmalýdýr.
 *           - SWDIP7 (SW1-2) RX TX anahtarlarý ON konumunda olmalýdýr.
 */
 
#include <18F4520.h>
#device adc=16

#FUSES NOWDT                    //No Watch Dog Timer
#FUSES WDT128                   //Watch Dog Timer uses 1:128 Postscale
#FUSES HS                       //High speed Osc (> 4mhz for PCM/PCH) (>10mhz for PCD)
#FUSES NOBROWNOUT               //No brownout reset
#FUSES NOLVP                    //No low voltage prgming, B3(PIC16) or B5(PIC18) used for I/O
#FUSES NOXINST                  //Extended set extension and Indexed Addressing mode disabled (Legacy mode)

#use delay(clock=20000000)

#use rs232(baud=9600,xmit=PIN_C6,rcv=PIN_C7, ENABLE=PIN_C5)

#include "EXLCD.C"

void main()
{
   lcd_init();
   delay_ms(100);
   
   lcd_gotoxy(1,1);
   printf(lcd_putc,"Expkits   ");
   lcd_gotoxy(1,2);
   printf(lcd_putc,"RS485 Recv Demo");   
   delay_ms(3000);

   output_drive(PIN_D4);
   output_low(PIN_D4);
   output_low(PIN_C5);
   while(TRUE)
   {
      if (getch()=='X')
       {
        output_toggle(PIN_D4);
       }
       delay_ms(250);
   }

}
