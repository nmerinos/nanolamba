/******************************************************************************
*									ds1086.h                                                            *
*******************************************************************************
* AUTHOR	: Billy Shin
* COMPANY	: nanolambda
* DATE		: 2016-03-03
* PROJECT	: STM32
* SYSTEM	: STM32F429AIH6
* DESCRIPTION
*    
*
*******************************************************************************
*/



#ifndef __UTILS_H
#define __UTILS_H


/******************************************************************************

			E X T E R N A L   R E F E R E N C E
							
*******************************************************************************/










/******************************************************************************

			I N C L U D E   H E A D E R   F I L E S 
							
*******************************************************************************/
#include "main.h"










/******************************************************************************

			C O N S T A N T   D E F I N I T I O N
							
******************************************************************************/









/******************************************************************************

			M A C R O   D E F I N I T I O N 
							
******************************************************************************/









/******************************************************************************

			T Y P E   D E F I N I T I O N
							
******************************************************************************/










/******************************************************************************

						G L O B A L   A L L O C A T I O N

******************************************************************************/










/******************************************************************************

					F U N C T I O N   D E F I N I T I O N

******************************************************************************/
uint16_t getSensorIntegTime();
void setSensorInitValue();
int result2n(int input);

#endif
