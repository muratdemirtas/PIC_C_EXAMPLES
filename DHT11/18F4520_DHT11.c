/*
 * Dosya    : 18F4520_DHT11.c
 * Yazar    : Expkits - www.expkits.com
 * Uygulama : DHT11 Isý & Nem Sensörü Uygulamasý
 * Sürüm    : v1.0
 * Tarih    : 05.04.2013
 * MCU      : 18F4x20
 * Kristal  : 20Mhz (MCU FOSC 20Mhz)
 * Kit      : EX8
 * Açýklama : DHT11 Sensörü okunarak ýsý ve nem 16x2 LCD' de gösterilir.
 * Uyarý    : CCS v4 ile derlenmiþtir.
 *            SWDIP7 (SW3) - SCK  ON konumunda olmalýdýr.
 *            PULL U/D C3 (SW5) ON edilmelidir. Aksi halde sensör devreye girmez.
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

#define dht11 PIN_C3

#include "DHT11.C"
#include "EXLCD.C"

void main()
{
   lcd_init();
   delay_ms(100);

   dht_init();
   while(TRUE)
   {
      read_dht(); // Check dht_dat variable after this funciton
   /*   byte dht11_check_sum = dht_dat[0]+dht_dat[1]+dht_dat[2]+dht_dat[3];// check check_sum
      if(dht_dat[4]!= dht11_check_sum)
      {
         printf(lcd_putc, "DHT11 checksum error");
      }
      else
      {*/
         lcd_gotoxy(1,1);
         printf(lcd_putc,"HUMI RH :%d.%d %%  ",dht_dat[0],dht_dat[1]);
         lcd_gotoxy(1,2);
         printf(lcd_putc,"TEMP :%d.%d %cC  ",dht_dat[2],dht_dat[3],223);
      //}
      delay_ms(2000);
   }

}
