/*
 * Dosya    : 18F4520_PWM.c
 * Yazar    : Expkits - www.expkits.com
 * Uygulama : PWM Uygulamasi
 * Sürüm    : v1.0
 * Tarih    : 05.04.2013
 * MCU      : PIC18F4520
 * Kristal  : 20Mhz
 * Kit      : EX8
 * Açýklama : CCP olan C2 pini PWM olarak ayarlanir. Bu pine bagli C2 Led'i
 *            POT0 ile kontrol edilir.
 * Uyarý    : CCS v4 ile derlenmiþtir.
 *            EX8 Kullanicilari;
 *			  - SWDIP8 uzerindeki SW1(PORTA-E) ve SW3(PORTC) anahtarlari ON konumuna almalidir.
 */
#include <18F4520.h>
#device adc=8
#FUSES NOWDT                    //No Watch Dog Timer
#FUSES WDT128                   //Watch Dog Timer uses 1:128 Postscale
#FUSES HS                       //High speed Osc (> 4mhz FOR PCM/PCH) (>10mhz for PCD)
#FUSES NOBROWNOUT               //No brownout reset
#FUSES NOLVP                    //No low voltage prgming, B3(PIC16) or B5(PIC18) used FOR I/O
#FUSES NOXINST                  //Extended set extension and Indexed Addressing mode disabled (Legacy mode)
#use delay(clock=20000000)

VOID main(void)
 {
   UNSIGNED int8 value;
   setup_ccp1 (CCP_PWM);               
   setup_timer_2(T2_DIV_BY_16,127, 1);
   setup_port_a (AN0) ;
   setup_adc (adc_clock_internal) ;
   set_adc_channel (0);

   WHILE (TRUE)
   {
     value = read_adc () ;
     set_pwm1_duty (value);
   }
 }

