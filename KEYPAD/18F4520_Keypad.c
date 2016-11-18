/*
 * Dosya    : 18F4520_Keypad.c
 * Yazar    : Expkits - www.expkits.com
 * Uygulama : Keypad Test Uygulamasý
 * Sürüm    : v1.0
 * Tarih    : 05.04.2013
 * MCU      : PIC18F4520
 * Kristal  : 20Mhz
 * Kit      : EX8
 * Açýklama : Amaç keypad üzerinde basýlan butonun LCD ekranda görüntülenmesidir.
 * Uyarý    : CCS v4 ile derlenmiþtir.
 *            EX8 için;
 *            - SWDIP8 üzerindeki PORTD anahtarý (SW4) kapalý olmalýdýr.
 *            - PULL U/D SW PORTD (D4,D5,D6,D7) ON konumuna alýnarak PULLUP edilmelidir. 
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

//Keypad baðlantýlarý:
#define row0 PIN_D4
#define row1 PIN_D5
#define row2 PIN_D6
#define row3 PIN_D7
#define col0 PIN_D0
#define col1 PIN_D1
#define col2 PIN_D2
#define col3 PIN_D3

// Keypad düzeni:
char const KEYS[4][4] =
{
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}
};


#define KBD_DEBOUNCE_FACTOR 33 // Tuþlar ne sýklýkla taranacak

void kbd_init()
{
    set_tris_d (0xF0);
    output_d (0xF0);
}

short int ALL_ROWS (void)
{
    if (input (row0) & input (row1) & input (row2) & input (row3) )
        return (0);
    else
        return (1);
}

char kbd_getc()
{
    static byte kbd_call_count;
    static short int kbd_down;
    static char last_key;
    static byte col;
    byte kchar;
    byte row;
    kchar = '\0';

    if (++kbd_call_count > KBD_DEBOUNCE_FACTOR)
    {
        switch (col)
        {
            case 0:
                output_low (col0);
                output_high (col1);
                output_high (col2);
                output_high (col3);
                break;

            case 1:
                output_high (col0);
                output_low (col1);
                output_high (col2);
                output_high (col3);
                break;

            case 2:
                output_high (col0);
                output_high (col1);
                output_low (col2);
                output_high (col3);
                break;

            case 3:
                output_high (col0);
                output_high (col1);
                output_high (col2);
                output_low (col3);
                break;
        }

        if (kbd_down)
        {
            if (!ALL_ROWS() )
            {
                kbd_down = false;
                kchar = last_key;
                last_key = '\0';
            }
        }
        else
        {
            if (ALL_ROWS() )
            {
                if (!input (row0) )
                    row = 0;
                else
                    if (!input (row1) )
                        row = 1;
                    else
                        if (!input (row2) )
                            row = 2;
                        else
                            if (!input (row3) )
                                row = 3;

                last_key = KEYS[row][col];
                kbd_down = true;
            }
            else
            {
                ++col;

                if (col == 4)
                    col = 0;
            }
        }

        kbd_call_count = 0;
    }

    return (kchar);
}

//===========================
void main()
{
    char k;
    lcd_init();
    delay_ms (100);
    output_low (PIN_B7);
    kbd_init();
    printf (lcd_putc, "\fKeypad Hazir..");
    delay_ms (2000);

    while (TRUE)
    {
        lcd_gotoxy (1, 2);
        k = kbd_getc();

        if (k != 0)
        {
            printf (lcd_putc, "\fBasilan tus..");
            lcd_gotoxy (1, 2);

            if (k == '*')
                printf (lcd_putc, "%c", '*');
            else
                printf (lcd_putc, "%c", k);
        }
    }
}

