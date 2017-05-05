/*
NSP_DEVICE_API.H

Provides interface to apollo sensor 

*/

#ifndef __NSP_DEVICE_INTERFACE_MATLAB_H__
#define __NSP_DEVICE_INTERFACE_MATLAB_H__


#ifdef _WIN32
#define EXPORT_DLL __declspec(dllexport) //For exporting to DLL
#else
#define EXPORT_DLL __attribute__((visibility("default")))
    #include <stdint.h>
    #define EXPORT_DLL  __attribute__((dllexport))
    //#define HANDLE  int
    #define BOOL    bool
    #define LARGE_INTEGER   int64_t
    #define DWORD   unsigned long 
    //! this is standard machine precision for 32 bit floats
    #define MACHINE_PRECISION    5.96e-08
#endif

#ifndef	SENSOR_ID_STRING_LENGTH
#define	SENSOR_ID_STRING_LENGTH			26
#endif

#ifndef SENSOR_DATA_SIZE
#define	SENSOR_DATA_SIZE				1024
#endif

#define	NSP_DEVICE_SS_MIN				1
#define	NSP_DEVICE_SS_MAX				3000

#ifdef __cplusplus
extern "C"{ 
#endif

// function prefix: du - Device USB

/**
* \brief Connect to physical device(sensor)
*
* This function try to connect to physical device(sensor) and returns the total number of sensors in system.
*
* \code
*   int num_of_sensors = duConnect();
* \endcode
*
* \param void
*
* \return
* Returns one numeric value of:
* - total number of sensors in system (>0)
* - NSP_RETURN_VALUE_FAILURE (-1)
* - cc_ec_fail_to_create_device_obj
* - cc_ec_no_device_in_system
* 
* \sa duDisconnect
* \note_nsp_device_api
*/
EXPORT_DLL  int duConnect();

/**
* \brief Disconnect physical device(sensor)
*
* This function disconnects physical device(sensor).
*
* \code
*   int ret_value = duDisconnect();
* \endcode
*
* \param void
*
* \return
* Returns one numeric value of:
* - NSP_RETURN_VALUE_SUCCESS (1)
* - NSP_RETURN_VALUE_FAILURE (-1)
* 
* \sa duConnect
* \note_nsp_device_api
*/
EXPORT_DLL int duDisconnect();

/**
* \brief Get sensor ID list which are connected to system.
*
* This function returns a string list containing sensor IDs in your system.
*
* \code
* char** duGetSensorList();
* \endcode
*
* \param none
*
* \return
* Returns double pointers to char array:
* - char pointers array containing sensor ID
* 
* \sa duConnect, duDisconnect
* \note_nsp_device_api
*/
EXPORT_DLL char** duGetSensorList();

/**
* \brief Activate a specific sensor
*
* This function activates a specific sensor having a matched sensor index among multiple sensors if there are multiple sensors in system.
*
* \code
*   int sensor_index = 0; // default = 0 (1'th sensor)
*   int ret_value = duActivateSensorWithIndex(sensor_index);
* \endcode
*
* \param sensor_index - sensor index start from 0 [IN]
*
* \return
* Returns one numeric value of:
* - NSP_RETURN_VALUE_SUCCESS (1)
* - NSP_RETURN_VALUE_FAILURE (-1)
* - cc_ec_device_object_is_null
* 
* \sa duActivateSensorWithID
* \note_nsp_device_api
*/
EXPORT_DLL	int duActivateSensorWithIndex(int sensor_index);

/**
* \brief Get maximum count of supported sensors 
*
* This function returns the maximum number of sensors supported by API/SDK.
*
* \code
*   int max_sensors = duGetMaxSensorCount();
* \endcode
*
* \param none
*
* \return
* Returns one numeric value of:
* - maximum number of sensors
* - NSP_RETURN_VALUE_FAILURE (-1)
* 
* \sa duActivateSensorWithID
* \note_nsp_device_api
*/
EXPORT_DLL	int duGetMaxSensorCount();

/**
* \brief Activate a specific sensor
*
* This function activates a specific sensor having a matched sensor ID among multiple sensors if there are multiple sensors in system.
*
* \code
*   char* sensor_id_str = "Y8585-1-85-85-0";
*   int ret_value = duActivateSensorWithID(sensor_id_str);
* \endcode
*
* \param sensor_id_str - sensor ID string [IN]
*
* \return
* Returns one numeric value of:
* - sensor index (>=0)
* - NSP_RETURN_VALUE_FAILURE (-1)
* - cc_ec_device_object_is_null
* 
* \sa duActivateSensorWithIndex
* \note_nsp_device_api
*/
EXPORT_DLL	int duActivateSensorWithID(const char* sensor_id_str);

/**
* \brief Get devices count
*
* This function returns a total number of devices in system.
*
* \code
*   int total_num_of_sensors = duGetTotalSensors();
* \endcode
*
* \param void
*
* \return
* Returns one numeric value of:
* - total number of devices (>0)
* - NSP_RETURN_VALUE_FAILURE (-1)
* - cc_ec_device_object_is_null
* 
* \sa 
* \note_nsp_device_api
*/
EXPORT_DLL	int duGetTotalSensors();

/**
* \brief Get sensor ID of physical device(sensor)
*
* This function returns a sensor ID of currently activated physical device(sensor).
* Current sensor is an activated one by duActivateSensorWithIndex() function.
*
* \code
*	char sensor_id[SENSOR_ID_STRING_LENGTH];
*   int ret_value = duGetSensorID(sensor_id);
* \endcode
*
* \param pointer to char array for sensor ID data [OUT]
*
* \return
* Returns one numeric value of:
* - NSP_RETURN_VALUE_SUCCESS (1)
* - NSP_RETURN_VALUE_FAILURE (-1)
* - cc_ec_memory_is_null
* - cc_ec_device_object_is_null
* 
* \sa duActivateSensorWithIndex
* \note_nsp_device_api
*/
EXPORT_DLL int duGetSensorID(char* sensor_id );

/**
* \brief Get shutter speed
*
* This function returns a shutter speed value of currently activated sensor.
*
* \code
*   int cur_ss = 0;
*   cur_ss = duGetShutterSpeed();
* \endcode
*
* \param void
*
* \return
* Returns one numeric value of:
* - current shutter speed (>0)
* - NSP_RETURN_VALUE_FAILURE (-1)
* - cc_ec_device_object_is_null
* 
* \sa duSetShutterSpeed
* \note_nsp_device_api
*/
EXPORT_DLL int duGetShutterSpeed();

/**
* \brief Get shutter speed limits
*
* This function returns two limit values for shutter speed (minimum and maximum).
*
* \code
*   int ss_min, ss_max;
*   cur_ss = duGetShutterSpeedLimits(&ss_min, &ss_max);
* \endcode
*
* \param ss_min - int pointer to minimum shutter speed value [OUT]
* \param ss_max - int pointer to maximum shutter speed value [OUT]
*
* \return
* Returns one numeric value of:
* - NSP_RETURN_VALUE_SUCCESS (1)
* - NSP_RETURN_VALUE_FAILURE (-1)
* - cc_ec_device_object_is_null
* 
* \sa duSetShutterSpeed
* \note_nsp_device_api
*/
EXPORT_DLL int duGetShutterSpeedLimits(int* min_limit, int* max_limit);

/**
* \brief Convert shutter speed to exposure time (unit: ms)
*
* This function converts shutter speed to exposure time based on MASTER CLOCK of sensor.
*
* \code
*   int master_clock = 5; // MCLK = 5-MHz
*	int shutter_speed = 1000
*	double exposure_time_val = 0;
*   cur_ss = duShutterSpeedToExposureTime(master_clock, shutter_speed, &exposure_time_val);
* \endcode
*
* \param master_clock - master clock of MCU to sensor [IN]
* \param shutter_speed - shutter speed value [IN]
* \param exposure_time_val - double pointer to exposure time value [OUT]
*
* \return
* Returns one numeric value of:
* - NSP_RETURN_VALUE_SUCCESS (1)
* - NSP_RETURN_VALUE_FAILURE (-1)
* - cc_ec_device_object_is_null
* 
* \sa duExposureTimeToShutterSpeed
* \note_nsp_device_api
*/
EXPORT_DLL int duShutterSpeedToExposureTime(int master_clock, int shutter_speed, double* exposure_time_val);


/**
* \brief Convert exposure time (ms) to shutter speed 
*
* This function converts exposure time to shutter speed based on MASTER CLOCK of sensor.
*
* \code
*   int master_clock = 5; // MCLK = 5-MHz
*	double exposure_time_val = 100; // 100 msec
*	int shutter_speed = 0
*   cur_ss = duExposureTimeToShutterSpeed(master_clock, exposure_time_val, &shutter_speed);
* \endcode
*
* \param master_clock - master clock of MCU to sensor [IN]
* \param exposure_time_val - exposure time value (ms) [IN]
* \param shutter_speed - int pointer to shutter speed value [OUT]
*
* \return
* Returns one numeric value of:
* - NSP_RETURN_VALUE_SUCCESS (1)
* - NSP_RETURN_VALUE_FAILURE (-1)
* - cc_ec_device_object_is_null
* 
* \sa duShutterSpeedToExposureTime
* \note_nsp_device_api
*/
EXPORT_DLL int duExposureTimeToShutterSpeed(int master_clock, double exposure_time_val, int* shutter_speed);

/**
* \brief Change current shutter speed of a device(sensor)
*
* This function changes shutter speed of currently activated device(sensor).
*
* \code
*   int new_ss = 50;
*   int ret_value = duSetShutterSpeed(new_ss);
* \endcode
*
* \param shutter - shutter speed value [IN]
*
* \return
* Returns one numeric value of:
* - NSP_RETURN_VALUE_SUCCESS (1)
* - NSP_RETURN_VALUE_FAILURE (-1)
* - cc_ec_device_object_is_null
* 
* \sa duGetShutterSpeed
* \note_nsp_device_api
*/
EXPORT_DLL int duSetShutterSpeed(int shutter);

/**
* \brief Get optimal shutter speed by AE
*
* This function returns an optimal shutter speed value which found by AE(Auto-Exposure) function.
*
* \code
*   int optimal_ss = 0;
*	int	num_of_valid_filters = 1024;
*	int*	valid_filters_in = NULL;
*   int	target_DN = 3500;
*   optimal_ss = duGetOptimalShutterSpeed(valid_filters_in, num_of_valid_filters, target_DN);
* \endcode
*
* \param valid_filters_in - pointer to the integer array [IN]
* \param num_of_valid_filters - the size of array [IN]
* \param target_DN - the target DN (upper limit) [IN]
*
* \return
* Returns one numeric value of:
* - optimal shutter speed (>0)
* - NSP_RETURN_VALUE_FAILURE (-1)
* - cc_ec_device_object_is_null
* 
* \sa csGetSpectrumLength, csGetResolution, csCalculateSpectrum
* \note_nsp_device_api
*/
EXPORT_DLL int duGetOptimalShutterSpeed(int* valid_filters_in, int num_of_valid_filters);
EXPORT_DLL int duGetOptimalShutterSpeed2(int* valid_filters_in, int num_of_valid_filters, int target_DN);

/**
* \brief Get raw filter data from physical device(sensor).
*
* This function acquires one raw filter data from physical device(sensor).
*
* \code
*   double filter_data[SENSOR_DATA_SIZE];
*   int frame_averages = 50;
*   int ret_value = duGetFilterData(filter_data, frame_averages);
* \endcode
*
* \param output - double pointer to raw filter data [OUT]
* \param number_of_averages - number of frame averages [IN]
*
* \return
* Returns one numeric value of:
* - NSP_RETURN_VALUE_SUCCESS (1)
* - NSP_RETURN_VALUE_FAILURE (-1)
* - cc_ec_device_object_is_null
* 
* \sa duSetShutterSpeed, duSetSensorParameters
* \note_nsp_device_api
*/
EXPORT_DLL int duGetFilterData(double *output,int number_of_averages);

/**
* \brief Set sensor registers
*
* This function changes sensor registers for ADC gain, ADC range, and ADC resolution.
*
* \code
*   int adc_gain = 1;	// 1=1X (default), 0=4X
*   int adc_range = 132; // 132 (default)
*   int ret_value = duSetSensorParameters(adc_gain, adc_range);
* \endcode
*
* \param _adc_gain - ADC gain value [IN]
* \param _adc_range - ADC range value [IN]
*
* \return
* Returns one numeric value of:
* - NSP_RETURN_VALUE_SUCCESS (1)
* - NSP_RETURN_VALUE_FAILURE (-1)
* - cc_ec_device_object_is_null
* 
* \sa duGetSensorParameters
* \note_nsp_device_api
*/
EXPORT_DLL int duSetSensorParameters(int _adc_gain, int _adc_range);

/**
* \brief Get settings of sensor registers
*
* This function returns the current settings of sensor registers (ADC gain and ADC range).
*
* \code
*   int adc_gain = 1;	// 1=1X (default), 0=4X
*   int adc_range = 132; // 132 (default)
*   int ret_value = duGetSensorParameters(&adc_gain, &adc_range);
* \endcode
*
* \param _adc_gain - integer pointer to ADC gain value [OUT]
* \param _adc_range - integer pointer to ADC range value [OUT]
*
* \return
* Returns one numeric value of:
* - NSP_RETURN_VALUE_SUCCESS (1)
* - NSP_RETURN_VALUE_FAILURE (-1)
* - cc_ec_device_object_is_null
* 
* \sa duSetSensorParameters
* \note_nsp_device_api
*/
EXPORT_DLL int duGetSensorParameters(int* _adc_gain, int* _adc_range);

#ifdef __cplusplus
}
#endif


#endif // __NSP_DEVICE_INTERFACE_MATLAB_H__
