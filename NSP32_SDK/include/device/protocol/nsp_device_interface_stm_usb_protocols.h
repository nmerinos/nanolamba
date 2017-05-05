#ifndef	__NSP_DEVICE_INTERFACE_STM_USB_PROTOCOLS_H__
#define	__NSP_DEVICE_INTERFACE_STM_USB_PROTOCOLS_H__

// Sensor operation modes
#define	HPK_CIS_MODE_POWER_SAVE			0x00
#define	HPK_CIS_MODE_POWER_ON_AND_WAIT	0x01
#define	HPK_CIS_MODE_SINGLE_CAPTURE		0x02
#define	HPK_CIS_MODE_CONTINUOUS_CAPTURE	0x03
#define	HPK_CIS_MODE_ALL_RESET			0x04

#ifdef	CONTROLLER_BOARD_STM
#define	STM_SENSOR_ID_SIZE					5		// bytes
#define	STM_SENSOR_DATA_SIZE				2048	// bytes
#define STM_SPECTRUM_DATA_SIZE				2048	// bytes

// Definitions for data acquisition mode
#define	STM_ACQUIRE_MODE_SINGLE				0x01
#define	STM_ACQUIRE_MODE_CONTINUOUS			0x02
#define	STM_ACQUIRE_MODE_TIME_INTERVAL		0x03
#define	STM_ACQUIRE_MODE_HW_TRIGGER			0x04

// Definitions for errors
#define	STM_ERROR_SENSOR_STOP				-0x01
#define	STM_ERROR_CONTROLLER_STOP			-0x02
#define	STM_ERROR_INVALID_EXPOSURE_TIME		-0x03
#define	STM_ERROR_INVALID_COMMAND			-0x04
#define	STM_ERROR_INVALID_LED_STATUS		-0x05
#define	STM_ERROR_INVALID_ACQUIRE_MODE		-0x06
#define	STM_ERROR_NOT_SUPPORTED_ALGO		-0x07
#define	STM_ERROR_UNKNOWN					-0xff

// Commands for USB communication
#define	STM_COMM_NO_OP          			0x00	// 8 bytes
#define	STM_COMM_GET_SENSOR_ID				0x01	// 8 bytes
#define	STM_COMM_GET_SENSOR_DATA			0x02	// 2048 bytes
#define	STM_COMM_SET_ACQUIRE_MODE			0x03	// 1(bulk mode on), 0(bulk mode off)
#define	STM_COMM_GET_LOW_EXPOSURE_TIME		0x04	// 1 bytes
#define	STM_COMM_GET_UPPER_EXPOSURE_TIME	0x24	// 1 bytes
#define	STM_COMM_SET_LOW_EXPOSURE_TIME		0x05	// 1 bytes
#define	STM_COMM_SET_UPPER_EXPOSURE_TIME	0x25	// 1 bytes

#define	STM_COMM_SET_LOW_BLANK_TIME			0x21	// 1 bytes
#define	STM_COMM_SET_UPPER_BLANK_TIME		0x22	// 1 bytes
#define	STM_COMM_GET_LOW_BLANK_TIME			0x26	// 1 bytes
#define	STM_COMM_GET_UPPER_BLANK_TIME		0x27	// 1 bytes

#define	STM_COMM_SET_ADC_RANGE				0x13	// 1 bytes
#define	STM_COMM_GET_ADC_RANGE				0x23	// 1 bytes
#define	STM_COMM_SET_ADC_RESOLUTION			0x14	// 1 bytes
#define	STM_COMM_GET_ADC_RESOLUTION			0x28	// 1 bytes

#define	STM_COMM_GET_SENSOR_STATUS			0x06	// 1 byte
#define	STM_COMM_GET_CONTROLLER_STATUS		0x07	// 1 byte
#define	STM_COMM_GET_LED_STATUS				0x08	// 4 bytes
#define	STM_COMM_SET_LED_STATUS				0x09	// 4 bytes
#define	STM_COMM_GET_ERROR					0x0a	// 1 byte
#define	STM_COMM_GET_SPECTRUM				0x0b	// 2048 bytes (actually 4 * wavelength rage (711)) about 3000 bytes
#define	STM_COMM_GET_XYZ					0x0c	// 12 bytes
#define	STM_COMM_GET_AMBIENT				0x0d	// 4 bytes
#define	STM_COMM_SET_MCU_MODE				0x0e	// 1 byte
#define	STM_COMM_SET_INTEG_TIME				0x0f	// 2 bytes
#define	STM_COMM_SET_ROI_START_POS			0x11	// 4 bytes
#define	STM_COMM_SET_ROI_SIZE				0x12	// 4 bytes
#define	STM_COMM_SET_ADC_RANGE				0x13	// 1 byte
#define	STM_COMM_SET_AMP_GAIN_RESOLUTION	0x14	// 1 byte
#define	STM_COMM_INIT_ACQ					0x16	// 1 byte
#define	STM_COMM_FIN_ACQ					0x17	// 1 byte
#define	STM_COMM_READ_REGISTER_DATA			0x18	// 1 byte
#define	STM_COMM_WRITE_REGISTER_ADD			0x19	// 1 byte
#define	STM_COMM_WRITE_REGISTER_DAT			0x1a	// 1 byte
#define	STM_COMM_GET_AVERAGED_SENSOR_DATA	0x1b	// 1 byte
#define	STM_COMM_SET_LED_TOGGLE				0x20	// 1 byte

#define	STM_COMM_SET_BURST_MODE				0x30	// 1 byte
// added by KSLEE, 2014.07.08, for TitanSensorTester (register I/O test)
#define STM_COMM_GET_TEST_BYTE  	        0x29    // 1 byte        
#define STM_COMM_GET_START_ROW  	        0x2a    // 1 byte        
#define STM_COMM_SET_START_ROW  	        0x31    // 1 byte        
#define STM_COMM_GET_START_COL  	        0x2b    // 1 byte        
#define STM_COMM_SET_START_COL  	        0x32    // 1 byte        
#define STM_COMM_GET_NUMB_ROW   	        0x2c    // 1 byte        
#define STM_COMM_SET_NUMB_ROW   	        0x33    // 1 byte        
#define STM_COMM_GET_NUMB_COL   	        0x2d    // 1 byte        
#define STM_COMM_SET_NUMB_COL   	        0x34    // 1 byte        

//! definitions for on-board processing
#define STM_COMM_GET_FRAME_AVERAGE			0x35    // 1 byte        
#define STM_COMM_SET_FRAME_AVERAGE			0x36    // 1 byte        
#define STM_COMM_TEST_BURST_MODE			0x37    // 1 byte        
#define STM_COMM_GET_DARK_FRAME     	    0x38    // 1 byte        //2014.08.05
#define STM_COMM_SET_DARK_CORRECTION_MODE 	0x39    // 1 byte        //2014.08.05
#define STM_COMM_GET_DARK_CORRECTION_MODE 	0x3a    // 1 byte        //2014.08.05

#define STM_COMM_SET_POI_COUNT            	0x40    // 1 byte        //2014.08.08
#define STM_COMM_GET_POI_COUNT            	0x41    // 1 byte        //2014.08.08
#define STM_COMM_CLEAR_POI_INDEX_LIST     	0x42    // 1 byte        // 2014.08.11
#define STM_COMM_SET_POI_INDEX_LIST       	0x43    // 1 byte        //2014.08.08
#define STM_COMM_GET_POI_INDEX_LIST       	0x44    // 1 byte        //2014.08.08
#define STM_COMM_GET_POI_DATA             	0x45    // 1 byte        //2014.08.08

// TEST for Bulk Transfer
#define STM_COMM_START_BULK_TRANSFER      	0x46    // 1 byte        //2015.08.07
#define STM_COMM_STOP_BULK_TRANSFER       	0x47    // 1 byte        //2015.08.07

#define	STM_COMM_SET_EXPOSURE_TIME			0x50	// 1 bytes
#define	STM_COMM_SET_BLANK_TIME				0x51	// 1 bytes

#define	STM_COMM_REBOOT						0xff	// 1 byte

#else

#define	EFM32_SENSOR_ID_SIZE				5		// bytes
#define	EFM32_SENSOR_DATA_SIZE				2048	// bytes
#define EFM32_SPECTRUM_DATA_SIZE			2048	// bytes

// Definitions for data acquisition mode
#define	EFM32_ACQUIRE_MODE_SINGLE			0x01
#define	EFM32_ACQUIRE_MODE_CONTINUOUS		0x02
#define	EFM32_ACQUIRE_MODE_TIME_INTERVAL	0x03
#define	EFM32_ACQUIRE_MODE_HW_TRIGGER		0x04

// Definitions for errors
#define	EFM32_ERROR_SENSOR_STOP				-0x01
#define	EFM32_ERROR_CONTROLLER_STOP			-0x02
#define	EFM32_ERROR_INVALID_EXPOSURE_TIME	-0x03
#define	EFM32_ERROR_INVALID_COMMAND			-0x04
#define	EFM32_ERROR_INVALID_LED_STATUS		-0x05
#define	EFM32_ERROR_INVALID_ACQUIRE_MODE	-0x06
#define	EFM32_ERROR_NOT_SUPPORTED_ALGO		-0x07
#define	EFM32_ERROR_UNKNOWN					-0xff

// Commands for USB communication
#define	EFM32_COMM_NO_OP          			0x00	// 8 bytes
#define	EFM32_COMM_GET_SENSOR_ID			0x01	// 8 bytes
#define	EFM32_COMM_GET_SENSOR_DATA			0x02	// 2048 bytes
#define	EFM32_COMM_SET_ACQUIRE_MODE			0x03	// 1(single=sw trigger), 2(continous),3(time-interval),4(hw trigger)
#define	EFM32_COMM_GET_LOW_EXPOSURE_TIME	0x04	// 1 bytes
#define	EFM32_COMM_GET_UPPER_EXPOSURE_TIME	0x24	// 1 bytes
#define	EFM32_COMM_SET_LOW_EXPOSURE_TIME	0x05	// 1 bytes
#define	EFM32_COMM_SET_UPPER_EXPOSURE_TIME	0x25	// 1 bytes

#define	EFM32_COMM_SET_LOW_BLANK_TIME		0x21	// 1 bytes
#define	EFM32_COMM_SET_UPPER_BLANK_TIME		0x22	// 1 bytes
#define	EFM32_COMM_GET_LOW_BLANK_TIME		0x26	// 1 bytes
#define	EFM32_COMM_GET_UPPER_BLANK_TIME		0x27	// 1 bytes

#define	EFM32_COMM_SET_ADC_RANGE			0x13	// 1 bytes
#define	EFM32_COMM_GET_ADC_RANGE			0x23	// 1 bytes
#define	EFM32_COMM_SET_ADC_RESOLUTION		0x14	// 1 bytes
#define	EFM32_COMM_GET_ADC_RESOLUTION		0x28	// 1 bytes

#define	EFM32_COMM_GET_SENSOR_STATUS		0x06	// 1 byte
#define	EFM32_COMM_GET_CONTROLLER_STATUS	0x07	// 1 byte
#define	EFM32_COMM_GET_LED_STATUS			0x08	// 4 bytes
#define	EFM32_COMM_SET_LED_STATUS			0x09	// 4 bytes
#define	EFM32_COMM_GET_ERROR				0x0a	// 1 byte
#define	EFM32_COMM_GET_SPECTRUM				0x0b	// 2048 bytes (actually 4 * wavelength rage (711)) about 3000 bytes
#define	EFM32_COMM_GET_XYZ					0x0c	// 12 bytes
#define	EFM32_COMM_GET_AMBIENT				0x0d	// 4 bytes
#define	EFM32_COMM_SET_MCU_MODE				0x0e	// 1 byte
#define	EFM32_COMM_SET_INTEG_TIME			0x0f	// 2 bytes
//#define	EFM32_COMM_SET_BLANK_TIME			0x10	// 2 bytes
#define	EFM32_COMM_SET_ROI_START_POS		0x11	// 4 bytes
#define	EFM32_COMM_SET_ROI_SIZE				0x12	// 4 bytes
#define	EFM32_COMM_SET_ADC_RANGE			0x13	// 1 byte
#define	EFM32_COMM_SET_AMP_GAIN_RESOLUTION	0x14	// 1 byte
#define	EFM32_COMM_INIT_ACQ					0x16	// 1 byte
#define	EFM32_COMM_FIN_ACQ					0x17	// 1 byte
#define	EFM32_COMM_READ_REGISTER_DATA       0x18	// 1 byte
#define	EFM32_COMM_WRITE_REGISTER_ADDR      0x19	// 1 byte
#define	EFM32_COMM_WRITE_REGISTER_DATA      0x1a	// 1 byte
#define	EFM32_COMM_GET_AVERAGED_SENSOR_DATA	0x1b	// 1 byte
#define	EFM32_COMM_SET_LED_TOGGLE			0x20	// 1 byte

#define	EFM32_COMM_SET_BURST_MODE			0x30	// 1 byte
// added by KSLEE, 2014.07.08, for TitanSensorTester (register I/O test)
#define EFM32_COMM_GET_TEST_BYTE            0x29    // 1 byte        
#define EFM32_COMM_GET_START_ROW            0x2a    // 1 byte        
#define EFM32_COMM_SET_START_ROW            0x31    // 1 byte        
#define EFM32_COMM_GET_START_COL            0x2b    // 1 byte        
#define EFM32_COMM_SET_START_COL            0x32    // 1 byte        
#define EFM32_COMM_GET_NUMB_ROW             0x2c    // 1 byte        
#define EFM32_COMM_SET_NUMB_ROW             0x33    // 1 byte        
#define EFM32_COMM_GET_NUMB_COL             0x2d    // 1 byte        
#define EFM32_COMM_SET_NUMB_COL             0x34    // 1 byte        

//! definitions for on-board processing
#define EFM32_COMM_GET_FRAME_AVERAGE		0x35    // 1 byte        
#define EFM32_COMM_SET_FRAME_AVERAGE		0x36    // 1 byte        
#define EFM32_COMM_TEST_BURST_MODE			0x37    // 1 byte        
#define EFM32_COMM_GET_DARK_FRAME           0x38    // 1 byte        //2014.08.05
#define EFM32_COMM_SET_DARK_CORRECTION_MODE 0x39    // 1 byte        //2014.08.05
#define EFM32_COMM_GET_DARK_CORRECTION_MODE 0x3a    // 1 byte        //2014.08.05

#define EFM32_COMM_SET_POI_COUNT            0x40    // 1 byte        //2014.08.08
#define EFM32_COMM_GET_POI_COUNT            0x41    // 1 byte        //2014.08.08
#define EFM32_COMM_CLEAR_POI_INDEX_LIST     0x42    // 1 byte        //2014.08.11
#define EFM32_COMM_SET_POI_INDEX_LIST       0x43    // 1 byte        //2014.08.08
#define EFM32_COMM_GET_POI_INDEX_LIST       0x44    // 1 byte        //2014.08.08
#define EFM32_COMM_GET_POI_DATA             0x45    // 1 byte        //2014.08.08

// TEST for Bulk Transfer
#define EFM32_COMM_START_BULK_TRANSFER      0x46    // 1 byte        //2015.08.07
#define EFM32_COMM_STOP_BULK_TRANSFER       0x47    // 1 byte        //2015.08.07

#define	EFM32_COMM_SET_EXPOSURE_TIME		0x50	// 1 bytes
#define	EFM32_COMM_SET_BLANK_TIME			0x51	// 1 bytes

#define	EFM32_COMM_REBOOT					0xff	// 1 byte

#endif

#endif	// __NSP_DEVICE_INTERFACE_STM_USB_PROTOCOLS_H__