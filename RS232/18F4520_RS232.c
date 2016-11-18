/*
 * Dosya    : 18F4520_RS232.c
 * Yazar    : Expkits - www.expkits.com
 * Uygulama : RS232 UART Test
 * Sürüm    : v1.0
 * Tarih    : 05.04.2013
 * MCU      : PIC18F4520
 * Kristal  : 20Mhz
 * Kit      : EX8
 * Açýklama : Amaç RS232 üzerinden PC Terminali ile haberle?mektir.
 *
 * Uyarý    : CCS v4 ile derlenmiþtir.
 *            EX8 Kullanýcýlarý SWDIP6 üzerindeki RX ve TX (SW3-4) anahtarlarýný
 *            ON konumuna almalýdýr.
 */

#include <18F4520.h>
#device adc=10

#FUSES NOWDT                    //No Watch Dog Timer
#FUSES WDT128                   //Watch Dog Timer uses 1:128 Postscale
#FUSES HS                       //High speed Osc (> 4mhz for PCM/PCH) (>10mhz for PCD)
#FUSES NOBROWNOUT               //No brownout reset
#FUSES NOPBADEN                 //PORTB pins are configured as digital I/O on RESET
#FUSES NOLVP                    //No low voltage prgming, B3(PIC16) or B5(PIC18) used for I/O
#FUSES NOXINST                  //Extended set extension and Indexed Addressing mode disabled (Legacy mode)

#use delay(clock=20000000)

#use rs232(baud=9600,xmit=PIN_C6,rcv=PIN_C7)

#include "EXLCD.C"

#define INTS_PER_SECOND 76 // (20000000/(4*256*256))

BYTE saniye,int_count;

#int_RTCC
void  RTCC_isr(void) 
{
    if(--int_count==0)
    {
      ++saniye;
      int_count=INTS_PER_SECOND;
    }
}



void main()
{
   lcd_init();
   delay_ms(100);
   
   int_count=INTS_PER_SECOND;

   setup_timer_0(RTCC_INTERNAL|RTCC_DIV_256|RTCC_8_bit);
   enable_interrupts(INT_RTCC);
   enable_interrupts(GLOBAL);
   lcd_gotoxy(1,1);
   printf(lcd_putc,"Expkits   ");
   lcd_gotoxy(1,2);
   printf(lcd_putc,"RS232 Demo");   
   delay_ms(3000);
   while(TRUE)
   {
      lcd_gotoxy(1,1);
      printf("\r\n Baslamak icin bir tusa bas.");
      getc();
      lcd_gotoxy(1,1);
      printf(lcd_putc,"\fBaslatildi.   ");      
      saniye=0;
      printf("\r\n Durmak icin bir tusa bas.");
      getc();
      lcd_gotoxy(1,1);
      printf(lcd_putc,"\fDurdu.        ");
      printf("\r\nGeçen süre %u saniye.",saniye);
      printf(lcd_putc,"\fGecen Sure:%u",saniye);
   }

}
