/*
**************************************************************************************************
*                        Embedded Systems Building Blocks
*                       PS/2 Keyboard 104 keys, NumPad driver
*
*               Original obtained from www.picant.com, C2C complier web site
*                  by Julio Cesar Silva Briano, modified by John Leung
*
* Filenmae       : ps2key.c
* Programmer    : John Leung, www.TechToys.com.hk under Downloads Section.
* Version      : Version 1.1 - 17th June 2004
* Remarks      : Consult www.beyong.org for PS/2 keyboard protocol
**************************************************************************************************
*                                 DESCRIPTION
*      This is a PS/2 keyboard driver for standard 101/104 keyboard or Numerical Keypad
*             Application software must include PS2Key.h and PS2ScanCode.h
*                     PS2Key.h contains hardware port configuration
*         PS2ScanCode.h configures if it is a complete 101 keyboard, or just the Numpad
*   Two lookup tables PS2KeyUnshifted[] and PS2KeyShifted[] map the PS2Key_Code to ASCII characters
* If it is going to be the Numpad ONLY, PS2KeyUnshifted[] and PS2KeyShifted[] can be undefined to save ROM
*               Application must declare the followings (see ps2key.h)
*   PS2key.c is PS/2 keyboard driver to handle ordinary PS/2 or AT-style keyboard with mcu
*   Global variable PS2Key_Code returns the raw key code of a key
*   Key Buffer is defined by constant PS2KEY_BUF_SIZE (in PS2Key.h)
*
*   PS2Key_Clk         The port address of the PS/2 CLK signal
*   PS2Key_Data         The port address of the PS/2 Data signal
*   PS2Key_BUF_SIZE    Size of the PS/2 keyboard buffer
**************************************************************************************************
*/

/*
**************************************************************************************************
*   Date: 2 Feb 2006
*   Revised for void PS2KeyIntHandler(void), bug reported by CSS forum that, this piece of code
*   didn't work for Xtal frequency 4Mhz. This is because the following switch case spent too much 
*   time
*   void PSKeyIntHandler(void){
*   ....
   case PS2Key_STOP:                              // Stop bit (PS2Key_STOP = 11)
            if (PS2Key_Code==0x12||PS2Key_Code==0x59)   // Key=Left shift or right shift
            {   if (PS2_BREAKCODE==TRUE)            
                  PS2_SHIFT=FALSE;
               else
                  PS2_SHIFT=TRUE;
            }

            if (PS2Key_Code==0xF0)                  // Is a break code!
               PS2_BREAKCODE=TRUE;                  // ignore break code
            else if (PS2_BREAKCODE==TRUE)
               PS2_BREAKCODE=FALSE;
            else
                PS2KeyBufIn (PS2Key_Code);            // put valid key in buffer

               PS2Key_bit_Ix=0;
*   ....}
*   CHECKING FOR SHIFT KEY OR BREAK KEY SHOULDN'T BE HANDLED UNDER RB0 INTERRUPT ROUTINE!
**************************************************************************************************
*/

/*
**************************************************************************************
*   Date 3 Feb 2005
*   Bug reported when Xtal = 4MHz. When Xtal = 20MHz, the original code ran OK
*   Revision :  1. Change to 4MHz crystal
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
**************************************************************************************************
                                 GLOBAL VARIABLES
**************************************************************************************************
*/

INT8U   PS2KeyBuf[PS2KEY_BUF_SIZE];   //PS2 Keyboard buffer, the register to store characters key in
INT8U   PS2KeyBufInIx;            //Index into PS/2 key buf where next scan code will be inserted
INT8U   PS2KeyBufOutIx;            //Index into PS/2 key buf where next scan code will be removed
INT8U   PS2KeyNRead;            //Number of keys read from the PS/2 keyboard
INT8U   PS2Key_Code;            //Key code from PS/2 keyboard
INT8U   PS2Key_bit_Ix;            //bit index of the byte stream, Start_bit(1), Parity(10), Stop_bit(11)
BOOLEAN PS2_SHIFT;               //TRUE if left or right shift pressed
BOOLEAN   PS2_BREAKCODE;            //TRUE if a BREAKCODE received

/*
**************************************************************************************************
                           LOCAL FUNCTION PROTOTYPES
**************************************************************************************************
*/
void    PS2KeyBufIn(INT8U code);            /* Insert scan code into keyboard buffer */
INT8U   PS2KeyDecode(void);               /* Function to decode a key stroke */


/*
**************************************************************************************************
*                        INSERT KEY CHARACTER INTO KEYBOARD BUFFER
* Description: This function inserts a key character into the keyboard buffer from a PS/2 keyboard
**************************************************************************************************
*/

void PS2KeyBufIn (INT8U code)
{
   if (PS2KeyNRead < PS2Key_BUF_SIZE) {      //make sure that we don't overflow the buffer
      PS2KeyNRead++;                     //Increment the number of keys read
      PS2KeyBuf[PS2KeyBufInIx++] = code;      //Store the scan code into the buffer
      if (PS2KeyBufInIx >= PS2Key_BUF_SIZE) {   //Adjust index to the next scan code to put in buffer
         PS2KeyBufInIx = 0;
      }
   }
}

/*
**************************************************************************************************
*                           DECODE PS/2 KEYBOARD SCAN CODE
* Description: This function is called to determine the key scane code of the PS/2 keyboard
* Arguments:   none
* Returns:      the key scan code
**************************************************************************************************
*/
INT8U PS2KeyDecode(void)
{
   ;
}

/*
**************************************************************************************************
*                              GET KEY   
* Description:    Get a PS/2 keyboard scan code from the keyboard driver
* Arguments:      none
* Returns:         !=0xFF is the key scan code of the PS/2 keyboard key pressed
*            ==0xFF indicates that there is on key in the PS2KeyBuf[PS2KEY_BUF_SIZE] buffer 
**************************************************************************************************
*/

INT8U PS2KeyGetKey (void)
{
   INT8U code;

         //OS_ENTER_CRITICAL();
   if (PS2KeyNRead > 0) {               /* See if we have keys in PS2KeyBuf[] */
      PS2KeyNRead--;                  /* Decrement the number of keys in the buffer */
      code = PS2KeyBuf[PS2KeyBufOutIx];   /* Get scan code from the buffer */
      PS2KeyBufOutIx++;
      if (PS2KeyBufOutIx >= PS2Key_BUF_SIZE) {
         PS2KeyBufOutIx = 0;
         }
         //OS_EXIT_CRITICAL();
      return (code);                  /* return the scan code of the key pressed */
      } else {
         //OS_EXIT_CRITICAL();
      return (0xFF);                  /* No scan codes in buffer, return -1 */
   }
}

/*
**************************************************************************************************
*                              SEND COMMAND
* Description:    Send command to the PS/2 keyboard
* Arguments:      cmd is the command to send
*            $ED Set Status LED's - This command can be used to turn on and off the Num Lock, Caps Lock & Scroll Lock LED's. 
*               After Sending ED, keyboard will reply with ACK (FA) and wait for another byte which determines their Status.
*               Bit 0 controls the Scroll Lock, Bit 1 the Num Lock and Bit 2 the Caps lock. Bits 3 to 7 are ignored.  
*             $EE Echo - Upon sending a Echo command to the Keyboard, the keyboard should reply with a Echo (EE) 
*            $F0 Set Scan Code Set. Upon Sending F0, keyboard will reply with ACK (FA) and wait for another byte, 
               01-03 which determines the Scan Code Used. 
               Sending 00 as the second byte will return the Scan Code Set currently in Use
*            $F3 Set Typematic Repeat Rate. Keyboard will Acknowledge command with FA and wait for second byte, 
               which determines the Typematic Repeat Rate. 
*            $F4 Keyboard Enable - Clears the keyboards output buffer, enables Keyboard Scanning and returns an Acknowledgment. 
*            $F5 Keyboard Disable - Resets the keyboard, disables Keyboard Scanning and returns an Acknowledgment. 
*            $FE Resend - Upon receipt of the resend command the keyboard will re- transmit the last byte sent. 
*            $FF Reset - Resets the Keyboard. 

* Returns:         none 
* Remarks:      Refer to AN1723 of Motorola for detailed description of Host-to-KBD protocol
*            Is NOT working as per 17th June 2004. Should work more on this function.
**************************************************************************************************
*/

void PS2SendComm(INT8U cmd)
{
   PS2Key_bit_Ix = 0;            //bit index of the byte stream, Start_bit(1), Parity(10), Stop_bit(11), ACK_bit(12)
   
   disable_interrupts(INT_EXT);   //disable external interrupt B0 on falling edge

   output_low(PS2Key_Clk);       //host forces PS2 clock line low.
   delay_us(35);               //After approx. 35us, the host pulls PS2 data line low
   output_low(PS2Key_Data);      //This sequence of event signals the keyboard that 
                           //the host is about to transfer a command
   delay_us(125);               //The clock signal is released and pulled high by the keyboard's pullup
   //PS2Key_ClkTris = 1;            //resisitor after the falling edge of the data signal
   output_float(PIN_B0);
   /* Transfer of data from host to keyboard will start approx. 1ms after the rising edge of the clock */
   /* shift bit to PS2Key_Data on every falling edge of the PS2Key_Clk line */
   do
   {   while (input(PS2Key_Clk))
         ; //hold when PS2Key_Clk is high
      output_bit(PS2Key_Data, cmd&0x01);
      cmd = cmd>>1;      
      //PS2Key_DataTris=1;
      PS2Key_bit_Ix++;
   }    while(PS2Key_bit_Ix<=12);

   PS2Key_bit_Ix = 0;
   /* send data from host complete */
   //PS2Key_DataTris = 1;         //release data line, reset to input
   output_float(PIN_E2);
   ext_int_edge(0, H_TO_L);      //set external interrupt to falling edge
    enable_interrupts(INT_EXT);      //release PS2 KBD clock line. driven high by PS2 KBD
}

/*
**************************************************************************************************
*                           SEE IF ANY KEY IN BUFFER   
* Description:    This function checks to see if a key was pressed
* Arguments:      none
* Returns:         TRUE if a key has been pressed
*            FALSE if no key pressed
**************************************************************************************************
*/

BOOLEAN PS2KeyHit(void)
{
   BOOLEAN hit;

   //OS_ENTER_CRITICAL();
   hit = (BOOLEAN)(PS2KeyNRead > 0)? TRUE : FALSE;
   //OS_EXIT_CRITICAL();
   return(hit);
}

/*
*********************************************************************************************************
*                                  PS2 KEYBOARD DRIVER INITIALIZATION
*
* Description : This function initializes the PS2 driver.
* Arguments   : None.
* Returns     : None.
*********************************************************************************************************
*/

void PS2KeyInit(void)
{
   PS2KeyNRead    =0;            //Clear the number of keys read
   PS2KeyBufInIx    =0;            //Clear the key codes inserted at the beginning of the buffer
   PS2KeyBufOutIx   =0;            //Clear the key codes removed at the beginning of the buffer
   PS2_BREAKCODE   =FALSE;
   PS2_SHIFT      =FALSE;

  // PS2Key_DataTris =1;            //Set Data line an input
   output_float(PIN_E2);
   //PS2Key_ClkTris   =1;            //Set clock line an input
   output_float(PIN_B0);
   ext_int_edge(0, H_TO_L);      //set external interrupt to falling edge
   enable_interrupts(INT_EXT);      //enable external interrupt B0
}

/*
*********************************************************************************************************
*                                     PS2 KEYBOARD INTERRUPT HANDLER
* Description:  This function is called by an interrupt handler (e.g. B0 EXT INT on falling edge)
*             Detect the clock pulse (High_to_Low) for new bit
*            Total 11 bits for a complete frame (keyboard -> Host)
* Arguments  :    none
* Returns    :    none
* Notes      :    Put a scan code to PS2KeyBuf[] if a valid byte acquired
*            Set PS2KeyNRead then
*********************************************************************************************************
*/

void PS2KeyIntHandler(void)
{
   BOOLEAN   PS2Key_Data_State;   //Temp variable for Data pin, PS2Key_Data_State
   BOOLEAN PS2Key_Clk_State;
   BOOLEAN   PS2Status_Parity;   //Parity bit   
      
      PS2Key_Data_State = input(PS2Key_Data);
      PS2Key_Clk_State  = input(PS2Key_Clk);
      PS2Key_bit_Ix++;

      if (PS2Key_bit_Ix==PS2Key_START)
        {      //  First bit, PS2Key_START = 1 as defined under ps2key.h
               if (PS2Key_Data_State || PS2Key_Clk_State)   PS2Key_bit_Ix=0;
            //   Start bit clock is a high_to_low transition.
               //   Start bit is a low bit. If data pin or Clk pin high for the Start bit,
            //  it must be a false trigger from RB0, thus setting PS2Key_bit_Ix=0
               PS2Key_Code=0;            
               PS2Status_Parity=0;   

      } 
      else if (PS2Key_bit_Ix==PS2Key_PARITY)
      {      //  Parity bit, PS2Key_PARITY = 10 as defined under ps2key.h
            PS2Status_Parity = PS2Key_Data_State;
      } 
      else if (PS2Key_bit_Ix==PS2Key_STOP)
      {      // Stop bit (PS2Key_STOP = 11), put key in buffer
            // Put valid byte in PS2KeyBuf[]
             PS2KeyBufIn (PS2Key_Code);            
               PS2Key_bit_Ix=0;
      } 
      else
      {      // For all bits from 2, 3...9 (total 8-bit)
              PS2Key_Code = PS2Key_Code >> 1;
                 if (PS2Key_Data_State) 
               PS2Key_Code = PS2Key_Code | 0x80;
        }
}



