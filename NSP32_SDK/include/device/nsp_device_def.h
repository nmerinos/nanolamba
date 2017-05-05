#ifndef	__NSP_DEVICE_DEF_H__
#define	__NSP_DEVICE_DEF_H__

//! maximum number of devices supported by API
#define	NSP_DEVICE_MAX_DEVICES			1

#ifdef CONTROLLER_BOARD_STM
	#define	DEVICE_SENSOR_WIDTH			32
	#define	DEVICE_SENSOR_HEIGHT		32
	#define DEVICE_MIN_SHUTTER_SPEED	1
	#define DEVICE_MAX_SHUTTER_SPEED	16777215
	#define DEVICE_NUM_FILTERS			1024
	#define	DEVICE_MIN_FILTER_OUT		0
	#define	DEVICE_MAX_FILTER_OUT		4095
	#define	DEVICE_MAX_FILTER_VALUE		DEVICE_MAX_FILTER_OUT
	#define DEFAULT_VID					0x0483		//default VID
	#define DEFAULT_PID					0x5740		//0x0481 //default PID
	#define	DEFAULT_VID_STR				L"0483"	// for enumerating device
	#define	DEFAULT_PID_STR				L"5740"	// for enumerating device

	#define	STM_MCLK						5.0
	#define	NSP_DEVICE_MASTER_CLOCK			STM_MCLK
#else	// CONTROLLER_BOARD_EFM32
	#define	DEVICE_SENSOR_WIDTH			32
	#define	DEVICE_SENSOR_HEIGHT		32
	#define DEVICE_MIN_SHUTTER_SPEED	1
	#define DEVICE_MAX_SHUTTER_SPEED	16777215
	#define DEVICE_NUM_FILTERS			1024
	#define	DEVICE_MIN_FILTER_OUT		0
	#define	DEVICE_MAX_FILTER_OUT		4095
	#define	DEVICE_MAX_FILTER_VALUE		DEVICE_MAX_FILTER_OUT
/*
	#define DEFAULT_VID			0x2544		//default VID
	#define DEFAULT_PID			0x0002		//0x0478 //default PID
	#define	DEFAULT_VID_STR		L"2544"	// for enumerating device
	#define	DEFAULT_PID_STR		L"0002"	// for enumerating device
*/
	#define DEFAULT_VID					0x16C1		//default VID
	#define DEFAULT_PID					0x0482		//0x0481 //default PID
	#define	DEFAULT_VID_STR				L"16C1"	// for enumerating device
	#define	DEFAULT_PID_STR				L"0482"	// for enumerating device

	#define	EFM32_MCLK						5.0
	#define	NSP_DEVICE_MASTER_CLOCK			EFM32_MCLK
#endif

//! definitions for AE-based optimal SS finding
#define	NSP_DEVICE_MIN_SS					1
#define	NSP_DEVICE_MAX_SS					1200
#define	NSP_DEVICE_AE_SATURATION_RATIO		0.5	// 50% - this is just heuristic number.
#define	NSP_DEVICE_AE_SATURATION_INDICATOR	-1

typedef struct _nsp_def_auto_exposure_parameters
{
	int		initial_ss;			// 5
	int		min_ss;				// 1
	int		max_ss;				// 1000
	int		target_dn_value;	// 3500
	int		upper_dn_value;		// 4000
	int		lower_dn_value;		// 3000
	int		mean_upper_dn_value;	// 4000
	int		mode;				// 1

	_nsp_def_auto_exposure_parameters()
	{
		init();
	}

	void init()
	{
		initial_ss			= 5;
		min_ss				= NSP_DEVICE_MIN_SS;
		// 20150623 - Jesse - changed for using AE for x1 sensor gain
		max_ss				= NSP_DEVICE_MAX_SS; // 1000;
		target_dn_value		= 3300;
		upper_dn_value		= 4000;
		lower_dn_value		= 3000;
		mean_upper_dn_value	= target_dn_value;
		mode				= 1;
	}
}nsp_def_auto_exposure_parameters;

#endif	 // __NSP_DEVICE_DEF_H__