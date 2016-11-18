/*
 * Dosya    : 18F4520_DS1820.c
 * Yazar    : Expkits - www.expkits.com
 * Uygulama : DS1820 Sensor Uygulamasi
 * Sürüm    : v1.0
 * Tarih    : 05.04.2013
 * MCU      : PIC18F4520
 * Kristal  : 20Mhz (MCU FOSC 20Mhz)
 * Kit      : EX8
 * Açýklama : DS18x20 sensorlerini okuyarak LCD ekranda sicaklik bilgisi gosterir
 *			  ve bu bilgiyi RS232 üzerinden PC' ye aktarýr.
 * Uyarý    : CCS v4 ile derlenmiþtir.
 *            EX8 Kullanicilari;
 *			  - SWDIP7 uzerindeki DS18-SR (SW8) numarali anahtari ON konumuna almalidir.
 *			  - Tüm PULL U/D anahtarlarýnýn OFF olduðundan emin olun.
 *            - DS18x20 devresi kendi pullup direncine sahiptir.
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
#include "1wire.c"
#include "ds1820.c"

void main()
{
   float temperature; 

   setup_adc_ports(NO_ANALOGS); 
   setup_adc(ADC_OFF); 
   
   lcd_init(); 
   delay_ms(100);
      
   while(true)
   {
      temperature = ds1820_read(); 
      lcd_gotoxy(5,1); 
      printf(lcd_putc,"EXPKITS");
      lcd_gotoxy(3,2); 
      printf(lcd_putc,"TEMP: %3.1f", temperature); 
      printf("%3.1f\n",temperature);
      lcd_putc(223);
      lcd_putc("C");
      
   }

}
