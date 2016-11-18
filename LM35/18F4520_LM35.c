/*
 * Dosya    : 18F4520_LM35.c
 * Yazar    : Expkits - www.expkits.com
 * Uygulama : LM35 Analog Isý Sensörü Testi
 * Sürüm    : v1.0
 * Tarih    : 05.04.2013
 * MCU      : PIC18F4520
 * Kristal  : 20Mhz
 * Kit      : EX8 
 * Açýklama : EX8 üzerindeki DS1820 yuvasýna takýlan LM35 ýsý sensörünün nasýl
 *            okunacaðýný gösterir.
 *            
 * Uyarý    : CCS v4 ile derlenmiþtir.
 *            EX8 Kullanýcýlarý;
 *           - SWDIP7 üzerindeki DS18-SR (SW8) anahtarýný ON konumuna alýnmalýdýr.
 *           - Okuma sorunu durumunda R22 (10K) direnci sökülmelidir. 
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

#define ROLE_PIN PIN_C3

#include "EXLCD.C"

void main()
{
   float value,value1;
   
   output_b (0x00);
   lcd_init();
   delay_ms(100);
   output_low(PIN_B7);
   setup_comparator(NC_NC_NC_NC);
   setup_port_a(AN0_TO_AN4);
   setup_adc(ADC_CLOCK_INTERNAL);
   
   set_adc_channel(4); // 18F4520 A5 pini AN4 kanalýdýr.
   while(TRUE)
   {
     delay_ms(500);
     value = read_adc ();
     value1 = 5 * value * 100/1024;
     printf(lcd_putc,"\fTemp: %2.1f%cC" ,value1,223);     
   }

}
