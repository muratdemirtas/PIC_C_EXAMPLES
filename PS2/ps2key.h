/*
**************************************************************************************************
*                        Embedded Systems Building Blocks
*                        PS/2 Keyboard 101/104 keys driver
*
*               Original obtained from www.picant.com, C2C complier web site
*                  by Julio Cesar Silva Briano, modified by John Leung
*
* Filenmae       : ps2key.h
* Programmer    : John Leung, www.TechToys.com.hk under Downloads Section.
* Version      : Version 1.1 - 17th June 2004
* Remarks      : Consult www.beyong.org for PS/2 keyboard protocol
**************************************************************************************************
*/

/*
**************************************************************************************************
*                              DESCRIPTION
*              The keyboard is assumed to be a standard PS/2 104 keyboard, or NumPad
**************************************************************************************************
*                               PORT configuration                                     
*  Hardware pin map:                                                          
*  B0 CLOCK signal from PS/2, interrupt on falling edge.
*  B1 DATA signal from PS/2.
*
**************************************************************************************************
*/

/*
**************************************************************************************
*   Date 3 Feb 2005
*   Bug reported when Xtal = 4MHz. When Xtal = 20MHz, the original code runs OK
*   Revission : 1. Change to 4MHz crystal
*            2. Add #use fast_io(b) in main()
*            3. Change A4 -> B1 for PS2Key_Data (for hardware simplicity only)
*            4. The key modification in void PS2KeyIntHandler(void). Previously
*               switch (PS2Key_bit_Ix) case... applied but the assembly code
*               generated took too long for clock signal detection of keyboard
*               Instead of switch, a simple if() else if ... selection employed
*            5. Detection of PS2_BREAKCODE and PS2_SHIFT deleted from 
*               PS2KeyIntHandler(void) to save interrupt time.
**************************************************************************************
*/
/*
#byte  TRISB   = 0x86
#bit   TRISB0   = TRISB.0
#byte  TRISE   = 0x00
#bit   TRISE2  = TRISE.2
*/               
#define PS2Key_Clk      PIN_B0   /* The pin address of the CLK signal (input) */         
#define PS2Key_ClkTris(x)  set_tris_b(x)  /* The pin direction of the CLK signal (1=input) */

#define PS2Key_Data     PIN_E2   /* The pin address of the DATA signal (input) */
#define PS2Key_DataTris(x) set_tris_e(x)  /* The pin direction of the DATA signal (1=input) */

/*
**************************************************************************************************
*                                 CONSTANTS                                  *
**************************************************************************************************
*/


#define PS2Key_BUF_SIZE   10                  /* Size of PS2 keyboard buffer */
#define PS2Key_START    1                  /* Start bit for PS/2 protocol */
#define PS2Key_PARITY  10                  /* Parity bit for PS/2 protocol */
#define PS2Key_STOP    11                  /* Stop bit for PS/2 protocol */

/*
**************************************************************************************************
*                               FUNCTION PROTOTYPES                            *
**************************************************************************************************
*/

INT8U PS2KeyGetKey(void);      /* Get a PS/2 scan code from driver if one is present, -1 else */
void PS2SendComm(INT8U cmd);   /* (not finished) Send a one byte command to PS/2 keyboard */
BOOLEAN PS2KeyHit(void);      /* See if a key has been pressed (TRUE if so, FALSE if not) */
void PS2KeyInit(void);         /* Initialize the PS2 Keyboard handler */

/*
**************************************************************************************************
*                               FUNCTION PROTOTYPES
*                                HARDWARE SPECIFIC
**************************************************************************************************
*/
void PS2KeyIntHandler( void );               /* Function for B0 INT, edge from HIGH to LOW */
