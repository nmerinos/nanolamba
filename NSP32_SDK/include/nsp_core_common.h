#ifndef __NSP_CORE_COMMON_H__
#define	__NSP_CORE_COMMON_H__

#include "nsp_base_exceptions.h"

#ifndef	SENSOR_ID_STRING_LENGTH
#define	SENSOR_ID_STRING_LENGTH			26
#endif

#ifndef SENSOR_DATA_SIZE
#define	SENSOR_DATA_SIZE				1024
#endif

static bool		g_bVerbose = true;

#define	NUM_OF_DARK_PIXELS		28
#define	DARK_PIXE_START_INDEX	34	// 2'nd pixel of 2'nd row

#define	INIT_VAL_ADC_RANGE		132

// !!! NOTE: temporary definitions which get from CrystalPort
#define	STM_SENSOR_ID_SIZE					5		// bytes
#define	EFM32_SENSOR_ID_SIZE				5		// bytes
#ifdef	CONTROLLER_BOARD_STM
#define	SENSOR_ID_SIZE					STM_SENSOR_ID_SIZE
#else
#define	SENSOR_ID_SIZE					EFM32_SENSOR_ID_SIZE
#endif
#define	SENSOR_DARK_BASE_MAP_SIZE		1024
#define	SENSOR_DARK_WEIGHTS_MAP_SIZE	1024
// !!! NOTE: temporary definitions which get from CrystalPort


// scale factor for converting integer shutter speed to actual integration time(ms)
#ifdef	CONTROLLER_BOARD_STM
#define	STM_MCLK						5.0
#define	CONVERT_SS_TO_INTEG_TIME(ss)	((((384+(16*(32+1)))*ss)+160)/(STM_MCLK*1000))
#define	CONVERT_INTEG_TIME_TO_SS(msec)	(((msec*(STM_MCLK*1000)-160)-384)/(16*(32+1)))
#else
// 5MHz
#define	EFM32_MCLK						5.0
#define	CONVERT_SS_TO_INTEG_TIME(ss)	((((384+16*(32+1))*ss)+160)/(EFM32_MCLK*1000)) //((((384+(16*32))*ss)+160)/(EFM32_MCLK*1000))
#define	CONVERT_INTEG_TIME_TO_SS(msec)	(((msec*(EFM32_MCLK*1000)-160)-384)/(16*(32+1)))
#endif

#endif	// __NSP_CORE_COMMON_H__