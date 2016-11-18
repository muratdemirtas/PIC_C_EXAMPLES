/*
 * Dosya    : 18F4520_ADC-Lcd.c
 * Yazar    : Expkits - www.expkits.com
 * Uygulama : LDR Test
 * Sürüm    : v1.0
 * Tarih    : 05.04.2013
 * MCU      : PIC18F4520
 * Kristal  : 20Mhz
 * Kit      : EX8
 * Açýklama : Amaç ADC0 ve ADC1 giriþlerindeki POT'larýn okunarak LCD'de okunan degerin gösterilmesidir.
 *
 * Uyarýlar : CCS v4 ile derlenmiþtir.
 *            EX8 Kullanýcýlarý SWDIP7 üzerindeki AN IN 0 (SW5) anahtarýný
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

#include <string.h>
#include <math.h>

#include "EXLCD.C"

void main()
{
   int16 value;

   setup_port_a(AN0_TO_AN1);
   setup_adc( ADC_CLOCK_INTERNAL );
   
   lcd_init();
   delay_ms(100);
   lcd_gotoxy(1,1);
   printf(lcd_putc,"Expkits ADC Demo");
   delay_ms(2000);
   while(TRUE)
   {
     delay_ms(300);
     set_adc_channel(0);
     value = Read_ADC();
     printf(lcd_putc,"\fADC1:%4ld",value);
     set_adc_channel( 1 );
     value = Read_ADC();
     lcd_gotoxy(1,2);
     printf(lcd_putc,"ADC2:%4ld",value);
   }

}
