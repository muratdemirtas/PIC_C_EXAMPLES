/*
 * Dosya    : 18F4520_GLCD.c
 * Yazar    : Expkits - www.expkits.com
 * Uygulama : Grafik LCD (KS108) Uygulamasi
 * Sürüm    : v1.0
 * Tarih    : 05.04.2013
 * MCU      : PIC18F4520
 * Kristal  : 20Mhz (MCU FOSC 20Mhz)
 * Kit      : EX8
 * Açýklama : GLCD kullanarak ekranda grafikler gösterilir.
 *
 * Uyarý    : CCS v4 ile derlenmiþtir.
 *			  SWDIP10 GLCD_LED ON konumuna alýnmalýdýr.
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

#define FAST_GLCD    // Bu tanýmlamayý devre dýþý býrakarak aradaki farký görünüz.

#include <HDM64.c>
#include <graphics.c>
#include <math.h>

void main()
{
   char text[] = "Expkits";
   glcd_init (ON);        // Must initialize the LCD
   while (TRUE)
   {
      glcd_rect (0, 0, 127, 63, NO, ON);   // dis cerceve ciz
      glcd_text57 (5, 3, text, 3, ON);   // en buyuk yazi
      glcd_text57 (5, 28, text, 2, ON);  //orta yazi
      glcd_text57 (5, 44, text, 1, ON);  //kucuk yazi
      glcd_circle (100, 43, 5, NO, ON);   // daire ciz
      glcd_circle (100, 43, 10, NO, ON);   // daire ciz
      glcd_circle (100, 43, 15, NO, ON);  // daire ciz
      glcd_line (100, 28, 100, 58, on) ; //yatay cizgi ciz
      glcd_line (85, 43, 115, 43, on) ; // dikey cizgi ciz
      delay_ms (100) ;
      glcd_update () ;
   }
}

