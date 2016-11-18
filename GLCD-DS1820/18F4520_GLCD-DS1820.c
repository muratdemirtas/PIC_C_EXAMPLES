/*
 * Dosya    : main.c
 * Yazar    : Expkits - www.expkits.com
 * Uygulama : Grafik LCD (KS108) Uygulamasi
 * Sürüm    : v1.0
 * Tarih    : 05.04.2013
 * MCU      : PIC18F4520
 * Kristal  : 20Mhz (MCU FOSC 20Mhz)
 * Kit      : EX8
 * Açýklama : GLCD kullanarak ekranda animasyon gösterilir.
 *
 * Uyarý    : Microchip C18 v3.45 ile derlenmiþtir.
 *			  SWDIP10 GLCD_LED ON konumuna alýnmalýdýr.
 *			  SWDIP8 PORT D kesinlikle kapalý olmalýdýr.
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

#define FAST_GLCD

#include <HDM64.c>
#include <graphics.c>
#include <math.h>
#include <1wire.c> 
#include <ds1820.c> 

float temperature;  
char *temp[10];
static char text1[] = "o";
static char text2[] = "EXPKITS";

void main()
{
   setup_adc_ports (NO_ANALOGS);
   setup_adc (ADC_OFF);
   
   glcd_init (ON);

   while (true)
   {
      temperature = ds1820_read ();
      sprintf (temp, "%3.1f", temperature);
      glcd_rect (0, 0, 127, 63, NO, ON); 
      glcd_text57 (4, 42, text2, 2, ON);
      glcd_text57 (75, 8, text1, 2, ON);
      glcd_circle (100, 13, 4, YES, ON);  
      glcd_rect (96, 13, 104, 40, YES, ON);
      glcd_circle (100, 40, 10, YES, ON);  
      glcd_rect (5, 5, 80, 35, YES, OFF);
      glcd_text57 (5, 14, temp, 3, ON);
      glcd_text57 (75, 8, text1, 2,  ON);      
      glcd_update();
   }
}

