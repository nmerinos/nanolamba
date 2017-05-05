#ifndef	__EMF32_COMM_H__
#define	__EMF32_COMM_H__

#include "nsp_base_def.h"
#include "nsp_sdk_common.h"
#ifdef _WIN32
//#include "lusb0_usb.h"
#include "libusb.h"
#include "lusb.h"
#include "lusbi.h"
#endif
#include "protocol/nsp_device_interface_stm_usb_protocols.h"
#if defined(__linux__) || defined(__APPLE__)
//#include "/usr/include/usb.h"
//#include "/usr/local/include/libusb-1.0/libusb.h"
#include "libusb.h"
#include "lusb.h"
#include "lusbi.h"
#endif

#ifdef	CONTROLLER_BOARD_STM
#define STM_GET_DATA_FROM_DEVICE	0x10
#define STM_SET_DATA_TO_DEVICE		0x11
#else
#define EFM32_GET_DATA_FROM_DEVICE	0x10
#define EFM32_SET_DATA_TO_DEVICE	0x11
#endif

#if _MSC_VER
	#define snprintf _snprintf
#endif

#define	ALLOW_NEGATIVE_SIGNAL	1
#undef	ALLOW_NEGATIVE_SIGNAL

#define	ALLOW_FRAME_DATA_CASTING_TO_INTEGER		1
#undef	ALLOW_FRAME_DATA_CASTING_TO_INTEGER

#define	LOWER_LIMIT_OF_FILTERS_DN		50	// after dark correction
#ifdef	CONTROLLER_BOARD_STM
#define	SLEEP_TIME_TO_ACQUISITION		10  // test for x1 sensor gain //20 //100
#else
#define	SLEEP_TIME_TO_ACQUISITION		30  // test for x1 sensor gain //20 //100
#endif
#define	BLANK_TIME_SCALE_FACTOR			0.7//1.0
#define	DOUBLE_SS_RATIO					0.5	// 50%

#define RECIEVED_BYTE_BUFFER	2048

#define	FMA_MAX_NUM_BUFFERS		100

using namespace std;

#ifndef USE_LIBUSB_10
// old
//static usb_dev_handle *pDevH = NULL;  // Usb device handle
static struct usb_device *pDev;
static struct usb_bus *pBus;

struct UsbDevHandle{
	static map<int, usb_dev_handle*> create_map()
	{
		map<int, usb_dev_handle*> m;
		map<int, usb_dev_handle*>::iterator iter;
		for(iter = m.begin(); iter != m.end(); ++iter)
			(*iter).second = NULL;
		return m;
	}
	static map<int, usb_dev_handle*> pDevH;
};

 struct UsbDevId{
	static map<int, int> create_map()
	{
		map<int, int> m;
		map<int, int>::iterator iter;
		for(iter = m.begin(); iter != m.end(); ++iter)
			(*iter).second = 0;
		return m;
	}
	static map<int, int> currentDevId;
};

typedef pair <int, usb_dev_handle*> dev_Pair;
typedef pair <int, int> dev_id_Pair;
static unsigned char leds;
#else
static struct libusb_device *pDev;
static struct libusb_device *pDevLED;

struct UsbDevHandle{
	static map<int, libusb_device_handle*> create_map()
	{
		map<int, libusb_device_handle*> m;
		map<int, libusb_device_handle*>::iterator iter;
		for(iter = m.begin(); iter != m.end(); ++iter)
			(*iter).second = NULL;
		return m;
	}
	static map<int, libusb_device_handle*> pDevH;
};

 struct UsbDevId{
	static map<int, int> create_map()
	{
		map<int, int> m;
		map<int, int>::iterator iter;
		for(iter = m.begin(); iter != m.end(); ++iter)
			(*iter).second = 0;
		return m;
	}
	static map<int, int> currentDevId;
};

typedef pair <int, libusb_device_handle*> dev_Pair;
typedef pair <int, int> dev_id_Pair;
static unsigned char leds;
#endif

//Device properties (Teensy)
#define EMF32_DEVICE_TAG				1
#define EMF32_MIN_SHUTTER_SPEED			1
#define EMF32_MAX_SHUTTER_SPEED			16777215
#define EMF32_NUM_FILTERS				1024
#define EMF32_START_LAM					350
#define EMF32_END_LAM					1100
#define EMF32_FILTER_INTERVAL			1
#define EMF32_FILTER_RESOLUTION			751
#define EMF32_DEFAULT_NUM_AVERAGES		1
#define EMF32_DEFAULT_COM_PORT			6
//#define	EMF32_DEFAULT_VID				0x2544	// vid of USB device
//#define	EMF32_DEFAULT_PID				0x0001	// pdi of USB device
#ifdef	CONTROLLER_BOARD_STM
#define	EMF32_DEFAULT_VID				0x0483	// vid of USB device
#define	EMF32_DEFAULT_PID				0x5740	// pdi of USB device
#define	EMF32_LEDDRIVER_VID				0x0483	// vid of USB device
#define	EMF32_LEDDRIVER_PID				0x5740	// pdi of USB device
#else
#define	EMF32_DEFAULT_VID				0x16C1	// vid of USB device
#define	EMF32_DEFAULT_PID				0x0482	// pdi of USB device
#define	EMF32_LEDDRIVER_VID				0x16C1	// vid of USB device
#define	EMF32_LEDDRIVER_PID				0x0483	// pdi of USB device
#endif

#define EMF32_MIN_FILTER_OUT			0
#define EMF32_MAX_FILTER_OUT			DEVICE_MAX_FILTER_OUT

#define	FRAME_NUM_FOR_SKIP				0
#define	INIT_VAL_BLANK_TIME				2
//#define	INIT_VAL_ADC_RANGE				255// H32
#define	INIT_VAL_ADC_RANGE				132	// H4-Type7
//#define	INIT_VAL_ADC_RANGE				252 // H4-Type1B
// 20150622 - sensor gain is changed from x4 to x1 for reducing spectrum variation
#if 0
#define	INIT_VAL_ADC_GAIN				0
#else
#define	INIT_VAL_ADC_GAIN				1
#endif
#define	SHUTTER_SPEED_BASE				32

#ifdef	CONTROLLER_BOARD_STM
#define	SENSOR_ID_SIZE					STM_SENSOR_ID_SIZE
#else
#define	SENSOR_ID_SIZE					EFM32_SENSOR_ID_SIZE
#endif

/*
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
		min_ss				= 1;
		// 20150623 - Jesse - changed for using AE for x1 sensor gain
		max_ss				= 1200; // 1000;
		target_dn_value		= 3300;
		upper_dn_value		= 4000;
		lower_dn_value		= 3000;
		mean_upper_dn_value	= target_dn_value;
		mode				= 1;
	}
}nsp_def_auto_exposure_parameters;

*/
// scale factor for converting integer shutter speed to actual integration time(ms)
#ifdef	CONTROLLER_BOARD_STM
#define	STM_MCLK						5.0
#define	CONVERT_SS_TO_INTEG_TIME(ss)	((((384+(16*(32+1)))*ss)+160)/(STM_MCLK*1000))
#define	CONVERT_INTEG_TIME_TO_SS(msec)	(((msec*(STM_MCLK*1000)-160)-384)/(16*(32+1)))
#define	NSP_DEVICE_MASTER_CLOCK			STM_MCLK
#else
// 5MHz
#define	EFM32_MCLK						5.0
#define	CONVERT_SS_TO_INTEG_TIME(ss)	((((384+16*(32+1))*ss)+160)/(EFM32_MCLK*1000)) //((((384+(16*32))*ss)+160)/(EFM32_MCLK*1000))
#define	CONVERT_INTEG_TIME_TO_SS(msec)	(((msec*(EFM32_MCLK*1000)-160)-384)/(16*(32+1)))
#define	NSP_DEVICE_MASTER_CLOCK			EFM32_MCLK
#endif

#define DEFAULT_INITIAL_SHUTTER_SPEED 1

//**************************************************************************************************************************
//*			Device initialization/finalization functions
//**************************************************************************************************************************
//! Connect to USB device
bool connect_device( unsigned int iDeviceId = 0 );
int connect_device(void);
bool connect_device( int iVID, int iPID, unsigned int iDeviceId = 0 );
bool connect_LED_device();

//! Disconnect USB device
bool disconnect_device( unsigned int iDeviceId = 0 );

//! Print device information
void print_device_info(struct usb_device *pDev);

//**************************************************************************************************************************
//*			Sensor initialization/finalization functions
//**************************************************************************************************************************
//! initialize sensor with initial register values
void initialize_sensor(unsigned int iDeviceId = 0);

//! initialize acquisition
void start_sensor(unsigned int iDeviceId = 0);	

//! finalize acquistion
void stop_sensor(unsigned int iDeviceId = 0);		

//! Write command to device with value
void send_command_to_device( int iCommand, int wValue, unsigned int iDeviceId = 0 );

//! Convert char array(2048) to double array(1024)
void convert_2048C_to_1024F(char* inputC, double* outputF);

//! Read data from device
unsigned char read_from_device( int iCommand, int wValue, unsigned int iDeviceId = 0 );

//! Send/Read data to/from device
unsigned char do_control_transfer( int iCommand, int wValue, unsigned int iDeviceId = 0 );

//! read data from a register
unsigned char read_register_data(unsigned char ucAddr, unsigned int iDeviceId = 0);

//! write data to register
void write_register_data(unsigned char ucAddr, unsigned char ucData, unsigned int iDeviceId = 0);

//! acquire one frame (returns dark value of currently acquired frame)
double acquire_frame_data(double* frameBuf, int iDarkCorrectionMode, unsigned int iDeviceId = 0);

//! acquire one frame without data conversion
int acquire_frame_data_2048(char* frameBuf, unsigned int iDeviceId = 0);

int alloc_transfer_bulk(unsigned int iDeviceId = 0);
int alloc_transfer_bulk_l(int num_iso_pack, int length, unsigned char* buffer, unsigned int iDeviceId = 0);
int acquire_frame_data_bulk(int iCommand, unsigned int iDeviceId = 0);
int acquire_frame_data_control(int iCommand, unsigned int iDeviceId = 0);

double acquire_sub_frame_data(int* frameBuf, int iDarkCorrectionMode, unsigned int iDeviceId = 0);

//	Initialization is required before using any of the other functions. 
//	Comport number where the Arudino is connected to is required as input  
NSP_ERROR_CODE initialize_device_interface(unsigned int iDeviceId = 0);
NSP_ERROR_CODE reconnect_device(unsigned int& iDeviceId, struct libusb_device *currDev, libusb_context *lctx, bool detach);

//	Close the serial port that Arduino is connected to 
 NSP_ERROR_CODE close_device_interface(unsigned int iDeviceId = 0);

// Set current device ID what sensor data acquired..
NSP_ERROR_CODE set_device_index(unsigned int iDeviceId = 0);

// Set acquisitioin mode what sensor data acquired..
NSP_ERROR_CODE set_LED_module_op_mode(unsigned int iOpMode, unsigned int iDeviceId = 0);

// Set acquisitioin mode what sensor data acquired..
NSP_ERROR_CODE set_frame_data_acq_mode(unsigned int iAcqMode, unsigned int iDeviceId = 0);

// Return the total number of devices which are connected to Host
unsigned get_connected_total_devices();

//  Return sensor ID
EXPORT_DLL NSP_ERROR_CODE get_sensor_id_with_index(char* SensorID, unsigned int iDeviceId = 0);
EXPORT_DLL NSP_ERROR_CODE get_sensor_id_with_index(char* lot_char, short* lot_id, short* wafer_id, short* x_coord, short* y_coord, short* sensor_type, unsigned int iDeviceId = 0 );
std::string decode_sensor_id_from_string(char* buf, unsigned int iDeviceId = 0);

NSP_ERROR_CODE get_firmware_version(unsigned char *version);

//**************************************************************************************************************************
//*			Sensor register set/get functions
//**************************************************************************************************************************
//	Change current iShutterSpeed speed 
EXPORT_DLL NSP_ERROR_CODE set_shutter_speed_to_sensor(int iShutterSpeed, unsigned int iDeviceId = 0);

// Get current shutter speed value
NSP_ERROR_CODE get_shutter_speed_from_sensor(int* iCurSS, unsigned int iDeviceId = 0);

//	Return current shutter speed 
NSP_ERROR_CODE get_current_shutter_speed(int *iShutterSpeed, unsigned int iDeviceId = 0);

//	Get current shutter speed from sensor.
//	1 is returned if test succeeds. 0 if failed
NSP_ERROR_CODE get_current_shutter_speed();

//	Change current blank time
NSP_ERROR_CODE set_blank_time_to_sensor(int iBlankTime, unsigned int iDeviceId = 0);

// Get current blank time
NSP_ERROR_CODE get_blank_time_from_sensor(int* iBlankTime, unsigned int iDeviceId = 0);

//	Change ADC range & Gain
EXPORT_DLL NSP_ERROR_CODE set_adc_setting_values(unsigned char ucADCRange, unsigned char ucGain, unsigned char ucRes, unsigned int iDeviceId = 0);

//	Get ADC range & Gain
NSP_ERROR_CODE get_adc_setting_values(unsigned char *ucADCRange, unsigned char *ucGain, unsigned char *ucRes, unsigned int iDeviceId = 0);

//**************************************************************************************************************************
//*			Special functions (AE, binning...)
//**************************************************************************************************************************
// Find optimal shutter (AE)
int initialize_ae_module(const char* strFileName_intensityLUT, const char* strFileName_ssLUT);
int find_optimal_shutter_speed_with_ae(std::vector<int>& valid_filters, int frame_average, int sleep_time=1000, unsigned int iDeviceId = 0);
bool set_params_for_ae_module(int saturation_DN, unsigned int iDeviceId=0);
bool set_params_for_ae_module(int target_DN, int upper_DN, int lower_DN, int mean_DN, int max_integ_DN, unsigned int iDeviceId=0);

//	Get filter pOutputFilterValue from HPK sensor. OUPTUT must be a array of doubles of length DEFAULT_NUM_OF_FILTERS. 
//	NUMBER_OF_AVERAGES indicate the number of averages to take.  
EXPORT_DLL double get_filter_data_from_sensor(double *pOutputFilterValue, int iNumOfAverages, int iDarkCorrectionMode, int useContAcq = 0, unsigned int iDeviceId = 0);

int read_roi_info_from_fw( int iCommand, int wValue, unsigned iDeviceId = 0);
void write_roi_info_to_fw( int iCommand, int wValue, unsigned int iDeviceId =0 );
std::vector<int> get_roi_info_from_sensor( int iCommand, int wValue, unsigned iDeviceId = 0);
void set_roi_info_to_sensor( int iCommand, std::vector<int> POI, unsigned int iDeviceId = 0);

void get_roi_info_from_sensor(std::vector<int>& poi, int iDeviceId = 0);
void set_roi_info_to_sensor(std::vector<int>& poi, int iDeviceId = 0);
void get_roi_data_from_sensor(std::vector<int>& poi_data, int iPoiSize, std::vector<double>& poi_background, int iDeviceId = 0);

//**************************************************************************************************************************
//*			On-board processing functions
//**************************************************************************************************************************
//! set/get on-board frame average count
void set_frame_average_count_for_on_board_processing(unsigned char ucData, unsigned int iDeviceId = 0);
unsigned char get_frame_average_count_for_on_board_processing(unsigned int iDeviceId = 0);

//! enable/disable on-board dark correction
void set_dark_correction_mode_for_on_board_processing(bool bEnable, unsigned int iDeviceId = 0);
unsigned char get_dark_correction_mode_for_on_board_processing(unsigned int iDeviceId = 0);
void get_dark_frame_for_on_board_processing(unsigned int iDeviceId = 0);

//**************************************************************************************************************************
//*			Utility functions
//**************************************************************************************************************************
// Get valid filters only
 bool get_valid_filters_only(std::vector<double>& input_frame, std::vector<int>& valid_filters, std::vector<double>& output_frame);

// get sleep time for changing shutter speed 
int get_sleep_time_for_shutter_speed(int iShutterSpeed);

//! Test function
void device_interface_test( double *fpFilterValueAveraged, int iAverageIndex, unsigned int iDeviceId = 0 );

// Convert number to binary
void convert_number_to_binary(int number);

//**************************************************************************************************************************
//*			LED device control functions
//**************************************************************************************************************************
//! Functions for LED driver
bool is_led_driver_open();
bool is_led_driver_close();

// Change LED on or off. This is indicated by the boolean array of size nNumOfLED where the first element of the 
// bool array indicates the status of LED1, second element LED2, and etc. 
NSP_ERROR_CODE set_state_to_led_device(bool* OnArray, int nNumOfLED, int intensity);
NSP_ERROR_CODE set_op_mode_to_led_device(int iOpMode, int iToggleIntervalTime);

// Change LED on or off. This is indicated by the boolean array of size nNumOfLED where the first element of the 
// bool array indicates the status of LED1, second element LED2, and etc. 
 NSP_ERROR_CODE set_led_state_values(bool* OnArray, int nNumOfLED, int intensity, unsigned int iDeviceId = 0 );
 NSP_ERROR_CODE set_led_op_mode_values( int iOpMode, int iToggleIntervalTime, unsigned int iDeviceId = 0 );

#endif	// __EMF32_COMM_H__
