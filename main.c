/*
 * main.c
 *
 *  Created on: May 25, 2022
 *      Author: Abd El-Rahman
 */
#include "LIB/types.h"
#include "DIO_interface.h"
#include "LCD_interface.h"
#include "KPD_interface.h"
#include "avr/delay.h"

void main(void)
{

 u16  password = 1234 , chek_password = 0 , power=1 ;
 u8   counter =3 , key ='/0'  , i=0 , j=0 ;


 LCD_vidInit();
 DIO_voidSetPortDirection(DIO_u8_PORTB,DIO_u8_PORT_OUTPUT);
 DIO_voidSetPortDirection(DIO_u8_PORTC,DIO_u8_PORT_OUTPUT);
 DIO_voidSetPortDirection(DIO_u8_PORTD,0x0f);
 DIO_voidSetPortValue(DIO_u8_PORTD,0xf0);


 LCD_vidGotoxy(0,0);
 LCD_vidWriteString("password");


while(1)
{
	while(counter != 0)
	{
		for(i=0;i<4 ; i++)
		{
			while(key!='/0')
			key = KPD_u8GetPressedKey();
			LCD_vidGotoxy(1,i);
			LCD_vidWriteCharctr(key);
			for(j=0;j < 3-i;j++)
			{
				power *=10;
			}
			key-='0';
			chek_password += (power*key);
			power =1;
			key='/0';
		}
		if(password == chek_password)
		{
			 LCD_vidGotoxy(0,0);
			 LCD_vidWriteString("welcom");
			 break;
		}
		else{
			 LCD_vidGotoxy(0,0);
			 LCD_vidWriteString("wrong");
			 counter--;
		}
	}

}




}

