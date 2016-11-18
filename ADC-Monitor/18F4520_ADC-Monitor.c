/*
 * Dosya    : 18F4520_ADC-Monitor.c
 * Yazar    : Expkits - www.expkits.com
 * Uygulama : ADC Monitör
 * Sürüm    : v1.0
 * Tarih    : 05.04.2013
 * MCU      : PIC18F4520
 * Kristal  : 20Mhz
 * Kit      : EX8
 * Açýklama : Amaç ADC0 giriþindeki POT' un okunarak RS32 üzerinden gönderilmesidir.
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

#use rs232(baud=9600,xmit=PIN_C6,rcv=PIN_C7)

#include "EXLCD.C"

void main()
{
   unsigned int16 value;
   setup_adc_ports(AN0);
   setup_adc( ADC_CLOCK_INTERNAL );
   set_adc_channel( 0 );
   lcd_init();
   delay_ms(100);
   while(TRUE)
   {
     delay_ms(100);
     value = Read_ADC();
     printf("\n\r%4Ld",value);
     printf(lcd_putc,"\fValue:%4ld",value);
   }

}
