/*
 * Dosya    : 18F4520_OPTORELAY.c
 * Yazar    : Expkits - www.expkits.com
 * Uygulama : OPTO-RELAY Uygulamasý
 * Sürüm    : v1.0
 * Tarih    : 05.04.2013
 * MCU      : PIC18F4520
 * Kristal  : 20Mhz
 * Kit      : EX8
 * Açýklama : Amac Optik girislerin okunarak gosterimi ve D0 ve D1 butonlari ile
 *            role cikislarinin aktif edilmesidir.
 * Uyarý    : CCS v4 ile derlenmiþtir.
 *            EX8 Kullanicilari;
 *			  - SWDIP8 uzerindeki SW4-5-6-7-8 numarali anahtarlari ON konumuna almalidir.
 *            - Klemensteki +5V ve GND kullanilabilir.
 *            - Klemensteki CC girisi GND' ye baglanmalidir.
 */
#include <18F4520.h>
#device adc=10
#FUSES NOWDT                    //No Watch Dog Timer
#FUSES WDT128                   //Watch Dog Timer uses 1:128 Postscale
#FUSES HS                       //High speed Osc (> 4mhz FOR PCM/PCH) (>10mhz for PCD)
#FUSES NOBROWNOUT               //No brownout reset
#FUSES NOLVP                    //No low voltage prgming, B3(PIC16) or B5(PIC18) used FOR I/O
#FUSES NOXINST                  //Extended set extension and Indexed Addressing mode disabled (Legacy mode)
#use delay(clock=20000000)

#include "EXLCD.C"

#define ROLE1 PIN_C2
#define ROLE2 PIN_C3

byte in1,in2,rl1=0,rl2=0;

VOID main()
 {
   SET_TRIS_c (0b00000011);
   setup_port_a (NO_ANALOGS);
   lcd_init();
   delay_ms(100);
   
   WHILE(TRUE)
   {
      in1 = input_state (pin_C0);
      in2 = input_state (pin_C1);

      IF (input (pin_d0) == 1)
      {
         output_toggle (role1);
         rl1 = input_state (role1);
         delay_ms (50);
      }

      IF (input (pin_d1) == 1)
      {
         output_toggle (role2);
         rl2 = input_state (role2);
         delay_ms (50);
      }
     
      printf (lcd_putc, "\fIN1: %d", ( ! in1));
      lcd_gotoxy (10, 1); printf (lcd_putc, "IN2: %d", ( ! in2) );
      lcd_gotoxy (1, 2); printf (lcd_putc, "RL1: %d", rl1);
      lcd_gotoxy (10, 2); printf (lcd_putc, "RL2: %d", rl2);
      delay_ms (300) ;
   }
}

