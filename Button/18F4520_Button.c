/*
 * Dosya    : 18F4520_Button.c
 * Yazar    : Expkits - www.expkits.com
 * Uygulama : Buton Test Uygulamasý
 * Sürüm    : v1.0
 * Tarih    : 05.04.2013
 * MCU      : PIC18F4520
 * Kristal  : 20Mhz
 * Kit      : EX8
 * Açýklama : Amaç basýlan butonun LCD' de gösterilmesidir.
 * Uyarý    : CCS v4 ile derlenmiþtir.
 *            EX8 için;
 *            - Jumper J13 BUTTON PULL (UP) konumunda olmalýdýr.
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

#include "EXLCD.C"

void main()
{
   lcd_init();
   delay_ms(100);

   while(TRUE)
   {
        printf(lcd_putc,"\fC0/D0 butona bas");
        if (input(pin_d0)==1){ printf(lcd_putc,"\fD0 butonu basili");}
        if (input(pin_c0)==1){ printf(lcd_putc,"\fC0 butonu basili");}
        delay_ms(250);
   }

}
