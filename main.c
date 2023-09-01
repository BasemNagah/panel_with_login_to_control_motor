/*
 * main.c
 *
 *  Created on: Aug 24, 2023
 *      Author: hp
 */
#include "MCAL/DIO/DIO_interface.h"
#include "HAL/KPD/KPAD_interface.h"
#include "HAL/CLCD/CLCD_interface.h"
#include "MCAL/ADC/ADC_interface.h"
#define F_CPU 8000000UL
#include <util/delay.h>


int main(void)
{
	//keypad
	KPAD_voidInit();
	DIO_voidSetPinDirection(DIO_PORTA , DIO_PIN4 , DIO_OUTPUT);
	DIO_voidSetPinDirection(DIO_PORTA , DIO_PIN5 , DIO_OUTPUT);
	CLCD_voidInit();


	while(1)
	{
		u8 num = 0 ;
		u8 getpressed = 0 ;
		CLCD_voidSendCommand(0x01);
		u16 divison = 1000 ;
		u32 Enterd_Password = 0 ;
		CLCD_voidSetPositoion(1,5);
		CLCD_voidSendString((u8*) "Password" ,8);
		CLCD_voidSetPositoion(2,5);


		while(getpressed != '=')
		{
			getpressed = KPAD_u8GetPressed() ;
			if(getpressed != 255)
			{
				CLCD_voidSendString((u8*) "*" ,2);
				Enterd_Password +=( (getpressed-'0')*divison);
				divison/=10 ;
				if( num>3 )
				{
					divison +=10 ;
				}
				num++ ;

			}
		}
		if(Enterd_Password == 1234 )
		{
			CLCD_voidSendCommand(0x01);
			CLCD_voidSetPositoion(1,5);
			CLCD_voidSendString((u8*) "Welcome!" ,8);
			_delay_ms(1000);
			CLCD_voidSendCommand(0x01);
			while(1)
			{
				DIO_voidSetPinValue( DIO_PORTA , DIO_PIN4 , DIO_LOW );
				DIO_voidSetPinValue( DIO_PORTA , DIO_PIN5 , DIO_LOW );
				CLCD_voidSetPositoion(1,1);
				CLCD_voidSendString( (u8 *)"1-Turn CW" , 11);
				CLCD_voidSetPositoion(2,1);
				CLCD_voidSendString( (u8 *)"2-Turn CCW" , 12);
				getpressed = KPAD_u8GetPressed() ;
				if (getpressed == '1')
				{
					DIO_voidSetPinValue( DIO_PORTA , DIO_PIN5 , DIO_LOW );
					DIO_voidSetPinValue( DIO_PORTA , DIO_PIN4 , DIO_HIGH );
					CLCD_voidSendCommand(0x01);
					CLCD_voidSetPositoion(1,4);
					CLCD_voidSendString((u8*)"MOTOR RIGHT" , 12);
					CLCD_voidSetPositoion(2,1);
					CLCD_voidSendString((u8*)"0-back" , 7);
					while(getpressed != '0')
					{
						getpressed = KPAD_u8GetPressed() ;
					}

				}
				else if (getpressed == '2')
				{
					DIO_voidSetPinValue( DIO_PORTA , DIO_PIN4 , DIO_LOW );
					DIO_voidSetPinValue( DIO_PORTA , DIO_PIN5 , DIO_HIGH );
					CLCD_voidSendCommand(0x01);
					CLCD_voidSetPositoion(1,4);
					CLCD_voidSendString((u8*)"MOTOR LEFT" , 11);
					CLCD_voidSetPositoion(2,1);
					CLCD_voidSendString((u8*)"0-back" , 7);
					while(getpressed != '0')
					{
						getpressed = KPAD_u8GetPressed() ;
					}

				}

			}

		}
		else
		{
			CLCD_voidSendCommand(0x01);
			CLCD_voidSetPositoion(1,2);
			CLCD_voidSendString((u8*) "Wrong password!" ,16);
			_delay_ms(1000);
		}




	}


	return 0 ;
}

