#include "utils.h"

uint16_t getSensorIntegTime()
{
	uint16_t sensorValue=0;
	//HAL_StatusTypeDef returnValue;
	
	uint8_t tempTxBuffer[2] = {0,};
	uint8_t tempRxBuffer[2] = {0,};
	
	tempTxBuffer[0] = (APOLLO_INTEG_TIME_UP << 1); tempTxBuffer[1] = 0;
	if( HAL_SPI_TransmitReceive(&SpiHandle, (uint8_t *)tempTxBuffer, (uint8_t *)tempRxBuffer, 2, 5000) != HAL_OK)
	{
		//printf("\n\r [ERROR] STM32 can't cummuniate to Sensor via SPI interface for APOLLO_INTEG_TIME_UP.");
	}
	else
	{
		//printf("\n\r[GET] APOLLO_INTEG_TIME_UP register :%02X", tempRxBuffer[1]);	
	}
	sensorValue = tempRxBuffer[1] << 8;
	
	tempTxBuffer[0] = (APOLLO_INTEG_TIME_DOWN << 1); tempTxBuffer[1] = 0;
	if( HAL_SPI_TransmitReceive(&SpiHandle, (uint8_t *)tempTxBuffer, (uint8_t *)tempRxBuffer, 2, 5000) != HAL_OK)
	{
		//printf("\n\r [ERROR] STM32 can't cummuniate to Sensor via SPI interface for APOLLO_INTEG_TIME_DOWN.");
	}
	else
	{
		//printf("\n\r[GET] APOLLO_INTEG_TIME_DOWN register :%02X", tempRxBuffer[1]);	
	}
	sensorValue = (sensorValue & 0xFF00) + tempRxBuffer[1];
	
	return sensorValue;
}


void setSensorInitValue()
{
	uint8_t tempTxBuf[2];
	//uint8_t tempRxBuf[2];

	//HAL_StatusTypeDef returnValue;
	
	tempTxBuf[0] = (APOLLO_MODE_SELECTION << 1) + 1; tempTxBuf[1] = POWER_ON_WAITING_MODE;
	if( HAL_SPI_TransmitReceive(&SpiHandle, (uint8_t *)tempTxBuf, (uint8_t *)tempTxBuf, 2, 5000) != HAL_OK)
	{
		//printf("\n\r [ERROR] STM32 can't cummuniate to Sensor via SPI interface for APOLLO_MODE_SELECTION.");
	}
	else
	{
		//printf("\n\r[WRITE] Apollo sensor power on waiting mode");		
	}
	HAL_Delay(50);
		
	tempTxBuf[0] = (APOLLO_INTEG_TIME_UP << 1) + 1; tempTxBuf[1] = 0x00;
	if(HAL_SPI_TransmitReceive(&SpiHandle, (uint8_t *)tempTxBuf, (uint8_t *)tempTxBuf, 2, 5000) != HAL_OK)
	{
		//printf("\n\r [ERROR] STM32 can't cummuniate to Sensor via SPI interface for APOLLO_INTEG_TIME_UP.");
	}
	else
	{
		//printf("\n\r[WRITE] Default value to APOLLO_INTEG_TIME_UP register");
	}
	HAL_Delay(50);

	//tempTxBuf[0] = (APOLLO_INTEG_TIME_DOWN << 1) + 1; tempTxBuf[1] = 0x1F;
	tempTxBuf[0] = (APOLLO_INTEG_TIME_DOWN << 1) + 1; tempTxBuf[1] = 0x00;		// Default Value
	//tempTxBuf[0] = (APOLLO_INTEG_TIME_DOWN << 1) + 1; tempTxBuf[1] = 0x01;
	if(HAL_SPI_TransmitReceive(&SpiHandle, (uint8_t *)tempTxBuf, (uint8_t *)tempTxBuf, 2, 5000) !=HAL_OK)
	{
		//printf("\n\r [ERROR] STM32 can't cummuniate to Sensor via SPI interface for APOLLO_INTEG_TIME_DOWN.");
	}
	else
	{
		//printf("\n\r[WRITE] Default value to APOLLO_INTEG_TIME_DOWN register");
	}
	HAL_Delay(50);

	tempTxBuf[0] = (APOLLO_BLANK_TIME_UP << 1) + 1; tempTxBuf[1] = 0x00;
	if(HAL_SPI_TransmitReceive(&SpiHandle, (uint8_t *)tempTxBuf, (uint8_t *)tempTxBuf, 2, 5000) != HAL_OK)
	{
		//printf("\n\r [ERROR] STM32 can't cummuniate to Sensor via SPI interface for APOLLO_BLANK_TIME_UP.");
	}
	else
	{
		//printf("\n\r[WRITE] Default value to APOLLO_BLANK_TIME_UP register");

	}
	HAL_Delay(50);

	tempTxBuf[0] = (APOLLO_BLANK_TIME_DOWN << 1) + 1; tempTxBuf[1] = 0x02;
	if(HAL_SPI_TransmitReceive(&SpiHandle, (uint8_t *)tempTxBuf, (uint8_t *)tempTxBuf, 2, 5000) != HAL_OK)
	{
		//printf("\n\r [ERROR] STM32 can't cummuniate to Sensor via SPI interface for APOLLO_BLANK_TIME_DOWN.");
	}
	else
	{
		//printf("\n\r[WRITE] Default value to APOLLO_BLANK_TIME_DOWN register");
	}
	HAL_Delay(50);

	tempTxBuf[0] = (APOLLO_START_ROW << 1) + 1; tempTxBuf[1] = 0x00;
	if(HAL_SPI_TransmitReceive(&SpiHandle, (uint8_t *)tempTxBuf, (uint8_t *)tempTxBuf, 2, 5000) != HAL_OK)
	{
		//printf("\n\r [ERROR] STM32 can't cummuniate to Sensor via SPI interface for APOLLO_START_ROW.");
	}
	else
	{
		//printf("\n\r[WRITE] Default value to APOLLO_START_ROW register");
	}	
	HAL_Delay(50);

	tempTxBuf[0] = (APOLLO_START_COL << 1) + 1; tempTxBuf[1] = 0x00;
	if(HAL_SPI_TransmitReceive(&SpiHandle, (uint8_t *)tempTxBuf, (uint8_t *)tempTxBuf, 2, 5000) != HAL_OK)
	{
		//printf("\n\r [ERROR] STM32 can't cummuniate to Sensor via SPI interface for APOLLO_START_COL.");
	}
	else
	{
		//printf("\n\r[WRITE] Default value to APOLLO_START_COL register");
	}	
	HAL_Delay(50);

	tempTxBuf[0] = (APOLLO_NUMBER_ROW_READ << 1) + 1; tempTxBuf[1] = 0x1F;
	if(HAL_SPI_TransmitReceive(&SpiHandle, (uint8_t *)tempTxBuf, (uint8_t *)tempTxBuf, 2, 5000) != HAL_OK)
	{
		//printf("\n\r [ERROR] STM32 can't cummuniate to Sensor via SPI interface for APOLLO_NUMBER_ROW_READ.");
	}
	else
	{
		//printf("\n\r[WRITE] Default value to APOLLO_NUMBER_ROW_READ register");
	}	
	HAL_Delay(50);

	tempTxBuf[0] = (APOLLO_NUMBER_COL_READ << 1) + 1; tempTxBuf[1] = 0x1F;
	if(HAL_SPI_TransmitReceive(&SpiHandle, (uint8_t *)tempTxBuf, (uint8_t *)tempTxBuf, 2, 5000) != HAL_OK)
	{
		//printf("\n\r [ERROR] STM32 can't cummuniate to Sensor via SPI interface for APOLLO_NUMBER_COL_READ.");
	}
	else
	{
		//printf("\n\r[WRITE] Default value to APOLLO_NUMBER_COL_READ register");
	}	
	HAL_Delay(50);

	tempTxBuf[0] = (APOLLO_ADC << 1) + 1; tempTxBuf[1] = 0x84;
	if(HAL_SPI_TransmitReceive(&SpiHandle, (uint8_t *)tempTxBuf, (uint8_t *)tempTxBuf, 2, 5000) != HAL_OK)
	{
		//printf("\n\r [ERROR] STM32 can't cummuniate to Sensor via SPI interface for APOLLO_ADC.");
	}
	else
	{
		//printf("\n\r[WRITE] Default value to APOLLO_ADC register");
	}	
	HAL_Delay(50);

	tempTxBuf[0] = (APOLLO_INTEG_TIME_UP << 1); tempTxBuf[1] = 0;
	if(HAL_SPI_TransmitReceive(&SpiHandle, (uint8_t *)tempTxBuf, (uint8_t *)tempTxBuf, 2, 5000) != HAL_OK)
	{
		//printf("\n\r [ERROR] STM32 can't cummuniate to Sensor via SPI interface for APOLLO_INTEG_TIME_UP.");
	}
	else
	{
		//printf("\n\r[READ] APOLLO_INTEG_TIME_UP register :%02X", tempTxBuf[1]);
	}	
	HAL_Delay(50);

	tempTxBuf[0] = (APOLLO_INTEG_TIME_DOWN<< 1); tempTxBuf[1] = 0;
	if(HAL_SPI_TransmitReceive(&SpiHandle, (uint8_t *)tempTxBuf, (uint8_t *)tempTxBuf, 2, 5000) != HAL_OK)
	{
		//printf("\n\r [ERROR] STM32 can't cummuniate to Sensor via SPI interface for APOLLO_INTEG_TIME_DOWN.");
	}
	else
	{
		//printf("\n\r[READ] APOLLO_INTEG_TIME_DOWN register :%02X", tempTxBuf[1]);
	}	
	HAL_Delay(50);

	tempTxBuf[0] = (APOLLO_BLANK_TIME_UP<< 1); tempTxBuf[1] = 0;
	if(HAL_SPI_TransmitReceive(&SpiHandle, (uint8_t *)tempTxBuf, (uint8_t *)tempTxBuf, 2, 5000) != HAL_OK)
	{
		//printf("\n\r [ERROR] STM32 can't cummuniate to Sensor via SPI interface for APOLLO_BLANK_TIME_UP.");
	}
	else
	{
		//printf("\n\r[READ] APOLLO_BLANK_TIME_UP register :%02X", tempTxBuf[1]);
	}	
	HAL_Delay(50);

	tempTxBuf[0] = (APOLLO_BLANK_TIME_DOWN<< 1); tempTxBuf[1] = 0;
	if(HAL_SPI_TransmitReceive(&SpiHandle, (uint8_t *)tempTxBuf, (uint8_t *)tempTxBuf, 2, 5000) != HAL_OK)
	{
		//printf("\n\r [ERROR] STM32 can't cummuniate to Sensor via SPI interface for APOLLO_BLANK_TIME_DOWN.");
	}
	else
	{
		//printf("\n\r[READ] APOLLO_BLANK_TIME_DOWN register :%02X", tempTxBuf[1]);
	}	
	HAL_Delay(50);

	tempTxBuf[0] = (APOLLO_START_ROW << 1); tempTxBuf[1] = 0;
	if(HAL_SPI_TransmitReceive(&SpiHandle, (uint8_t *)tempTxBuf, (uint8_t *)tempTxBuf, 2, 5000) != HAL_OK)
	{
		//printf("\n\r [ERROR] STM32 can't cummuniate to Sensor via SPI interface for APOLLO_START_ROW.");
	}
	else
	{
		//printf("\n\r[READ] APOLLO_START_ROW register :%02X", tempTxBuf[1]);
	}	
	HAL_Delay(50);

	tempTxBuf[0] = (APOLLO_START_COL << 1); tempTxBuf[1] = 0;
	if(HAL_SPI_TransmitReceive(&SpiHandle, (uint8_t *)tempTxBuf, (uint8_t *)tempTxBuf, 2, 5000) != HAL_OK)
	{
		//printf("\n\r [ERROR] STM32 can't cummuniate to Sensor via SPI interface for APOLLO_START_COL.");
	}
	else
	{
		//printf("\n\r[READ] APOLLO_START_COL register :%02X", tempTxBuf[1]);
	}	
	HAL_Delay(50);

	tempTxBuf[0] = (APOLLO_NUMBER_ROW_READ << 1); tempTxBuf[1] = 0;
	if(HAL_SPI_TransmitReceive(&SpiHandle, (uint8_t *)tempTxBuf, (uint8_t *)tempTxBuf, 2, 5000) != HAL_OK)
	{
		//printf("\n\r [ERROR] STM32 can't cummuniate to Sensor via SPI interface for APOLLO_NUMBER_ROW_READ.");
	}
	else
	{
		//printf("\n\r[READ] APOLLO_NUMBER_ROW_READ register :%02X", tempTxBuf[1]);
	}	
	HAL_Delay(50);

	tempTxBuf[0] = (APOLLO_NUMBER_COL_READ << 1); tempTxBuf[1] = 0;
	if(HAL_SPI_TransmitReceive(&SpiHandle, (uint8_t *)tempTxBuf, (uint8_t *)tempTxBuf, 2, 5000) != HAL_OK)
	{
		//printf("\n\r [ERROR] STM32 can't cummuniate to Sensor via SPI interface for APOLLO_NUMBER_COL_READ.");
	}
	else
	{
		//printf("\n\r[READ] APOLLO_NUMBER_COL_READ register :%02X", tempTxBuf[1]);
	}	
	HAL_Delay(50);

	tempTxBuf[0] = (APOLLO_ADC << 1); tempTxBuf[1] = 0;	
	if(HAL_SPI_TransmitReceive(&SpiHandle, (uint8_t *)tempTxBuf, (uint8_t *)tempTxBuf, 2, 5000) != HAL_OK)
	{
		//printf("\n\r [ERROR] STM32 can't cummuniate to Sensor via SPI interface for APOLLO_ADC.");
	}
	else
	{
		//printf("\n\r[READ] APOLLO_ADC register :%02X", tempTxBuf[1]);
	}	
	HAL_Delay(50);

	tempTxBuf[0] = (APOLLO_TEST_VALUE << 1); tempTxBuf[1] = 0;
	if(HAL_SPI_TransmitReceive(&SpiHandle, (uint8_t *)tempTxBuf, (uint8_t *)tempTxBuf, 2, 5000) != HAL_OK)
	{
		//printf("\n\r [ERROR] STM32 can't cummuniate to Sensor via SPI interface for APOLLO_TEST_VALUE.");
	}
	else
	{
		//printf("\n\r[READ] APOLLO_TEST_VALUE register :%02X", tempTxBuf[1]);
	}	
	HAL_Delay(50);

	tempTxBuf[0] = (APOLLO_SENSOR_ID_01 << 1); tempTxBuf[1] = 0;	
	if(HAL_SPI_TransmitReceive(&SpiHandle, (uint8_t *)tempTxBuf, (uint8_t *)tempTxBuf, 2, 5000) != HAL_OK)
	{
		//printf("\n\r [ERROR] STM32 can't cummuniate to Sensor via SPI interface for APOLLO_SENSOR_ID_01.");
	}
	else
	{
		MySensorID[0] = tempTxBuf[1];
		//printf("\n\r[READ] APOLLO_SENSOR_ID : 0x%02X", tempTxBuf[1]);	
	}
	
	tempTxBuf[0] = (APOLLO_SENSOR_ID_02 << 1); tempTxBuf[1] = 0;
	if(HAL_SPI_TransmitReceive(&SpiHandle, (uint8_t *)tempTxBuf, (uint8_t *)tempTxBuf, 2, 5000) != HAL_OK)
	{
		//printf("\n\r [ERROR] STM32 can't cummuniate to Sensor via SPI interface for APOLLO_SENSOR_ID_02.");
	}
	else
	{
		MySensorID[1] = tempTxBuf[1];
		//printf("%02X", tempTxBuf[1]);
	}	
	
	tempTxBuf[0] = (APOLLO_SENSOR_ID_03 << 1); tempTxBuf[1] = 0;
	if(HAL_SPI_TransmitReceive(&SpiHandle, (uint8_t *)tempTxBuf, (uint8_t *)tempTxBuf, 2, 5000) != HAL_OK)
	{
		//printf("\n\r [ERROR] STM32 can't cummuniate to Sensor via SPI interface for APOLLO_SENSOR_ID_03.");
	}
	else
	{
		MySensorID[2] = tempTxBuf[1];
		//printf("%02X", tempTxBuf[1]);
	}	

	tempTxBuf[0] = (APOLLO_SENSOR_ID_04 << 1); tempTxBuf[1] = 0;
	if(HAL_SPI_TransmitReceive(&SpiHandle, (uint8_t *)tempTxBuf, (uint8_t *)tempTxBuf, 2, 5000) != HAL_OK)
	{
		//printf("\n\r [ERROR] STM32 can't cummuniate to Sensor via SPI interface for APOLLO_SENSOR_ID_04.");
	}
	else
	{
		MySensorID[3] = tempTxBuf[1];
		//printf("%02X", tempTxBuf[1]);
	}
	
	tempTxBuf[0] = (APOLLO_SENSOR_ID_05 << 1); tempTxBuf[1] = 0;
	if(HAL_SPI_TransmitReceive(&SpiHandle, (uint8_t *)tempTxBuf, (uint8_t *)tempTxBuf, 2, 5000) != HAL_OK)
	{
		//printf("\n\r [ERROR] STM32 can't cummuniate to Sensor via SPI interface for APOLLO_SENSOR_ID_05.");
	}
	else
	{
		MySensorID[4] = tempTxBuf[1];
		//printf("%02X", tempTxBuf[1]);
	}
}

int result2n(int input)
{
	int result=0;

	if( input % 1 != 0 )
		return -1;

	do{
		input = input / 2;
		//printf("temp=%d", temp);
		result++;
	}while(input);

	return result-1;
}
