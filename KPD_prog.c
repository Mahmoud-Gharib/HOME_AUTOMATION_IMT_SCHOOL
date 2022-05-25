/***************************************************************************************/
/****************************  IMT School Training Center ******************************/
/***************************************************************************************/
/** This file is developed by IMT School training center, All copyrights are reserved **/
/***************************************************************************************/
/* Description ! Keypad driver for 4x4 keypad                                          */
/* Release Date! 28/6/2016                                                             */
/* Version     ! V01                                                                   */
/***************************************************************************************/


/********************************** Header Files INCLUSIONS ****************************/
#include "LIB/types.h"
#include "LIB/BIT_MATH.h"

#define F_CPU 8000000UL
#include <util/delay.h>

#include "DIO_interface.h"
#include "KPD_interface.h"
/***************************************************************************************/

/************* KeyPad Key Index ***************/                         
/*         Col_0    Col_1   Col_2   Col_3     */
/*	                                          */
/* row_0      1        2       3       4      */
/*	                                          */
/* row_1  	  5        6       7       8      */
/*	                                          */
/* row_2	  9        10      11      12     */
/*	                                          */
/* row_3	  13       14      15      16     */
/**********************************************/


/*************************************** Constants *************************************/
/* Values of the Key Pad switches                                                      */
/* Matrix is not standard it depends on the connection between the Micro and KeyPad    */
const u8 KPD_au8SwitchVal[4][4] = { { 0x01 , 0x05 , 0x09 , 0x0D },
								    { 0x02 , 0x06 , 0x0A , 0x0E },
                                    { 0x03 , 0x07 , 0x0B , 0x0F },
                                    { 0x04 , 0x08 , 0x0C , 0x10 } };

/***************************************************************************************/


/***************************************** Macros **************************************/
#define KPD_PORT   DIO_u8_PORTD

#define COL_INIT   0

#define COL_FIN    4

#define ROW_INIT   4

#define ROW_FIN    8

/***************************************************************************************/


/***************************************************************************************/
/* Description! Interface to get the ID of the pressed key, return 0 incase no key     */
/*              is pressed, this function doesn't handle the sitaution if 2 keys are   */
/*              pressed at the same time                               	     		   */
/* Input      ! Nothing                                                                */
/* Output     ! Nothing                                                                */
/***************************************************************************************/
u8 KPD_u8GetPressedKey(void)
{

  u8 LOC_u8Column;

  u8 LOC_u8Row;

  /* Initialize the switch status to NOT Pressed                                                                     */
  u8 LOC_u8Retrun = KPD_NOT_PRESSED;

  /* Looping on columns of the Key Pad                                                                               */
  for (LOC_u8Column = 0 + COL_INIT; LOC_u8Column < COL_FIN; LOC_u8Column++)
  {
    /* Activate the Column                                                                                           */
    DIO_voidSetPinValue(KPD_PORT, LOC_u8Column, DIO_u8_LOW);

    /* Loop on the rows of the Key Pad                                                                               */
    for (LOC_u8Row = 0 + ROW_INIT; LOC_u8Row < ROW_FIN; LOC_u8Row++)
    {
      /* Check the status of the switch                                                                              */
      if (!DIO_u8GetPinValue(KPD_PORT, LOC_u8Row))
      {
        /* Get the value of the currently pressed switch                                                             */
        LOC_u8Retrun = KPD_au8SwitchVal[LOC_u8Column - COL_INIT][LOC_u8Row - ROW_INIT];

        /* Wait until the switch is released (Single Press)                                                          */
        while (!DIO_u8GetPinValue(KPD_PORT, LOC_u8Row));

        /* Delay to avoid bouncing                                                                                   */
        _delay_ms(10);

      }
    }

    /* Deactivate the Column                                                                                         */
    DIO_voidSetPinValue(KPD_PORT, LOC_u8Column, DIO_u8_HIGH);
  }

  return LOC_u8Retrun;
}
