/*
 * Dosya    : 18F4520_EEPROM.c
 * Yazar    : Expkits - www.expkits.com
 * Uygulama : Harici EEPROM Okuma/Yazma Uygulamasi
 * Sürüm    : v1.0
 * Tarih    : 05.04.2013
 * MCU      : PIC18F4520
 * Kristal  : 20Mhz
 * Kit      : EX8
 * Açýklama : Amaç I2C Harici EEPROM' un okunup yazýlmasýný göstermektir.
 * Uyarý    : CCS v4 ile derlenmiþtir.
 *            EX8BIG-B Kullanicilari;
 * 			  - SWDIP7 uzerindeki SDA, SCK (SW3-4) anahtarlarini ON konumuna almalidir.
 *			  - PULL U/D PORTC SW3 ve SW4 ON konumuna alýnarak pull up saðlanmalýdýr.
 * 			  - SWDIP8 üzerinde bulunan PORTC(SW3) anahtarý OFF konuma alýnmalýdýr.
 * 			  - SWDIP8 üzerinde bulunan PORTD(SW4) anahtarý ON konuma alýnmalýdýr.
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

#define EEPROM_SDA  PIN_C4
#define EEPROM_SCL  PIN_C3

#include <2402.C>
#include "EXLCD.C"


void main()
{
   BYTE value=56;

   setup_adc_ports(NO_ANALOGS);
   setup_adc(ADC_OFF);
   
   lcd_init();
   delay_ms(100);
   init_ext_eeprom();

   while(TRUE)
   {
    printf(lcd_putc,"\fEpr:%d D0:- D1:+",value);
     lcd_gotoxy(1,2);printf(lcd_putc,"D2:YAZ D3:OKU");
      if (input(pin_d0)==1){value=--value;}
       if (input(pin_d1)==1){value=++value;}
        if (input(pin_d2)==1){write_ext_eeprom(10, value );delay_ms(100);}
         if (input(pin_d3)==1){value = read_ext_eeprom (10);}
          delay_ms(500);
   }

}
