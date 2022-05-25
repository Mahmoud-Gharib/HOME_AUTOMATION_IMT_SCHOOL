/***************************************************************************************/
/****************************  IMT School Training Center ******************************/
/***************************************************************************************/
/** This file is developed by IMT School training center, All copyrights are reserved **/
/***************************************************************************************/
/* Description ! Keypad driver for 4x4 keypad                                          */
/* Release Date! 28/6/2016                                                             */
/* Version     ! V01                                                                   */
/***************************************************************************************/


#ifndef KPD_H_
#define KPD_H_


#define KPD_NOT_PRESSED    0


/***************************************************************************************/
/* Description! Interface to get the ID of the pressed key, return 0 in case no key     */
/*              is pressed, this function doesn't handle the situation if 2 keys are   */
/*              pressed at the same time                               	     		   */
/* Input      ! Nothing                                                                */
/* Output     ! Nothing                                                                */
/***************************************************************************************/
u8 KPD_u8GetPressedKey(void);

#endif /* KPD_H_ */
