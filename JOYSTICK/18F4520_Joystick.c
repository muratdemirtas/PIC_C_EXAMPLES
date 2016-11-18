/*
 * Dosya    : 18F4520_Joystick.c
 * Yazar    : Expkits - www.expkits.com
 * Uygulama : Joystick Test Uygulamasý
 * Sürüm    : v1.0
 * Tarih    : 05.04.2013
 * MCU      : PIC18F4520
 * Kristal  : 20Mhz
 * Kit      : EX8
 * Açýklama : Amaç joystick versinin LCD ekranda görüntülenmesidir.
 * Uyarý    : CCS v4 ile derlenmiþtir.
 *            EX8 için;
 *            - Jumper J13 BUTTON PULL (UP) konumunda olmalýdýr.
 *            - Jumper J6 (PORTA-E PULL U/D yanýnda) (D)own pozisyonuna alýnacak.
 *            - PULL U/D SW SWDIP1(PORTA-E) SW5 (A3) ON konumuna alýnacak.
 *            - J5 (PORTA-E çýkýþlar) üzerindeki E2 çýkýþýndan GND'ye 4.7K direnç
 *              baðlanmasý gereklidir. Bu iþlem direkt ZIF soket üzerinden bir direnç
 *              ile de yapýlabilir. ZIF üzerinde GND ve E2 birbirine daha yakýndýr.
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

#include "EXLCD.C"
#define JOY_UP PIN_E0
#define JOY_DOWN PIN_A2
#define JOY_LEFT PIN_E1
#define JOY_RIGHT PIN_E2
#define JOY_ENTER PIN_A3
#define JOY_ESC PIN_A4


void main()
{
    setup_adc_ports (NO_ANALOGS);
    setup_adc (ADC_OFF);
    lcd_init();
    delay_ms (100);
    output_low (PIN_B7); // Buzzer kapalý.

    while (TRUE)
    {
        printf (lcd_putc, "\fJoystick Demo");
        lcd_gotoxy (1, 2);

        if (input (JOY_UP) == 1)
        {
            printf (lcd_putc, " UST");
        }

        if (input (JOY_DOWN) == 1)
        {
            printf (lcd_putc, " ALT");
        }

        if (input (JOY_RIGHT) == 1)
        {
            printf (lcd_putc, " SAG");
        }

        if (input (JOY_LEFT) == 1)
        {
            printf (lcd_putc, " SOL");
        }

        if (input (JOY_ENTER) == 1)
        {
            printf (lcd_putc, " ENTER");
        }

        if (input (JOY_ESC) == 1)
        {
            printf (lcd_putc, " ESC");
        }

        delay_ms (250);
    }
}
