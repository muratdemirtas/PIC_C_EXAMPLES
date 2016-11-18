/*
 * Dosya    : 18F4520_Buzzer.c
 * Yazar    : Expkits - www.expkits.com
 * Uygulama : Buzzer Testi Uygulamasý
 * Sürüm    : v1.0
 * Tarih    : 05.04.2013
 * MCU      : PIC18F4520
 * Kristal  : 20Mhz
 * Kit      : EX8
 * Açýklama : Amaç I/O kullanarak buzzer ile ses üretmektir.
 * Uyarý    : CCS v4 ile derlenmiþtir.
 *            SWDIP7 üzerindeki BUZZER anahtarý ON konumunda olmalýdýr.
 */
 
#include <18F4520.h>

#FUSES NOWDT                    //No Watch Dog Timer
#FUSES HS                       //High speed osc with HW enabled 4X PLL
#FUSES NOBROWNOUT               //No brownout reset
#FUSES NOLVP                    //No low voltage prgming, B3(PIC16) or B5(PIC18) used for I/O
#FUSES NOXINST                  //Extended set extension and Indexed Addressing mode disabled (Legacy mode)

#use delay(clock=20000000)

#define BUZZER PIN_B7
#define D1  10
#define D2  20
#define D3  40
#define D4  80
#define D5  160


void main()
{

   //Example Buzzer Test program
   while(true)
   {
     /*********************************/
      output_low(BUZZER);
      delay_ms(D1);
      output_high(BUZZER);
      delay_ms(D1);
     /*********************************/
      output_low(BUZZER);
      delay_ms(D2);
      output_high(BUZZER);
      delay_ms(D2);
     /*********************************/
      output_low(BUZZER);
      delay_ms(D3);
      output_high(BUZZER);
      delay_ms(D3);
     /*********************************/
      output_low(BUZZER);
      delay_ms(D4);
      output_high(BUZZER);
      delay_ms(D4);
     /*********************************/
      output_low(BUZZER);
      delay_ms(D5);
      output_high(BUZZER);
      delay_ms(D5);
      
   }

}
