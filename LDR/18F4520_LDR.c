/*
 * Dosya    : 18F4520_LDR.c
 * Yazar    : Expkits - www.expkits.com
 * Uygulama : LDR Test
 * Sürüm    : v1.0
 * Tarih    : 05.04.2013
 * MCU      : PIC18F4520
 * Kristal  : 20Mhz
 * Kit      : EX8 
 * Açýklama :LDR degerini (A0) 2x16 LCD de gosterir. 
 * 			 Level (m) degeri ile isik seviyuesi ayarlanir.             
 *			 D0 ile level eksiltilir , D1 ile artirilir. 
 *  		 Isik seviyesi bu deger uzerinde oldugunda                  
 *  		 role  (Role2) tetiklenir                                   
 *  		 LDR: Karanlik=355  , Aydinlik=60                           
 *  		 R44 : 5mm LDR takili olmali , SWDIP6:LDR=ON olmali         
 *  		 klemensteki +5V ve GND yi kullanabilirsiz.                 
 *            
 * Uyarý    : CCS v4 ile derlenmiþtir.
 *            EX8 Kullanýcýlarý;
 *			  - SWDIP7 üzerindeki AN IN 0 (SW5) anahtarýný ON konumuna almalýdýr.
 *            
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
   unsigned int16 value, min, max,m;
   unsigned int8 i;
   
   output_b (0x00);
   lcd_init();
   delay_ms(100);
   setup_port_a(AN0);
   setup_adc(ADC_CLOCK_INTERNAL);
   set_adc_channel(0);
   m=180;
   
   while(TRUE)
   {
      min=0xffff;
      max=0;
      for(i=0; i<=16; ++i) {
         delay_ms(50);
          value = Read_ADC();
           if(value<min)
            min=value;
             if(value>max)
               max=value;
      }
         if(input(pin_d0)==1){m=--m;}     //level degerini 1 eksilt
          if(input(pin_d1)==1){m=++m;}     //level degerini 1 artir
           printf(lcd_putc,"\fLDR:%4ld",value);
            lcd_gotoxy(1,2);
             printf(lcd_putc,"Level:%lu",m);
              if (value>m){output_high(ROLE_PIN); lcd_gotoxy(12,1);printf(lcd_putc,"Gece");}
                else {output_low(ROLE_PIN);lcd_gotoxy(12,1);printf(lcd_putc,"Gun");}
   }

}
