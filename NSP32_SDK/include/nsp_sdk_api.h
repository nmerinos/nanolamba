/*
NSP_SDK_API.H

Provides API functions

*/

#ifndef __NSP_SDK_API_H__
#define __NSP_SDK_API_H__


#ifdef _WIN32
#define EXPORT_DLL __declspec(dllexport) //For exporting to DLL 
#endif
#if defined(__linux__) || defined(__APPLE__)
#define EXPORT_DLL __attribute__((visibility("default")))
#endif

#ifdef __cplusplus
extern "C"{ 
#endif

// function prefix: sdk - SDK (unified)

/**
* \brief Create SDK Object
*
* This function create one SDK object.
*
* \code
*   int ret_value = sdkCreate();
* \endcode
*
* \param void
*
* \return
* Returns one numeric value of:
* - NSP_RETURN_VALUE_SUCCESS (1)
* - NSP_RETURN_VALUE_FAILURE (-1)
* - cc_ec_no_device_in_system
* - cc_ec_fail_to_load_sensor_cal_data
* - cc_ec_fail_to_initialize_color_object
* 
* \sa sdkDestroy
* \note_nsp_sdk_api
*/
EXPORT_DLL  int sdkCreate(void);

/**
* \brief Destroy SDK Object
*
* This function destroy SDK object.
*
* \code
*   int ret_value = sdkDestroy();
* \endcode
*
* \param void
*
* \return
* Returns one numeric value of:
* - NSP_RETURN_VALUE_SUCCESS (1)
* - NSP_RETURN_VALUE_FAILURE (-1)
* 
* \sa sdkCreate
* \note_nsp_sdk_api
*/
EXPORT_DLL  int sdkDestroy();

/**
* \brief Add one sensor to active sensor list.
*
* This function add one sensor to active sensor list by loading sensor calibration data.
*
* \code
*	const char* sensor_cal_file_path = "./config/sensor_Y8585-1-85-85-0.dat";
*   int total_count_of_active_sensors = sdkRegister(sensor_cal_file_path);
* \endcode
*
* \param sensor_cal_file_path - file path for sensor calibration data [IN]
*
* \return
* Returns one numeric value of:
* - total count of active sensors
* - NSP_RETURN_VALUE_FAILURE (-1)
* - cc_ec_no_device_in_system
* - cc_ec_fail_to_load_sensor_cal_data
* - cc_ec_fail_to_initialize_color_object
* 
* \sa sdkCreate, sdkDestroy
* \note_nsp_sdk_api
*/
EXPORT_DLL  int sdkRegister(const char* sensor_cal_file_path);

/**
* \brief Get maximum count of supported sensors 
*
* This function returns the maximum number of sensors supported by API/SDK.
*
* \code
*   int max_sensors = sdkGetMaxSensorCount();
* \endcode
*
* \param none
*
* \return
* Returns one numeric value of:
* - maximum number of sensors
* - NSP_RETURN_VALUE_FAILURE (-1)
* 
* \sa sdkCreate
* \note_nsp_sdk_api
*/
EXPORT_DLL	int sdkGetMaxSensorCount();

/**
* \brief Get total number of valid filters 
*
* This function returns the total number of valid filters in sensor calibration data.
*
* \code
*   int max_sensors = sdkGetNumOfValidFilters();
* \endcode
*
* \param none
*
* \return
* Returns one numeric value of:
* - total number of valid filters
* - NSP_RETURN_VALUE_FAILURE (-1)
* 
* \sa sdkCreate
* \note_nsp_sdk_api
*/
EXPORT_DLL	int sdkGetNumOfValidFilters();

/**
* \brief Get valid filters 
*
* This function returns the valid filters data in sensor calibration data.
*
* \code
*   int* valid_filters = sdkGetValidFilters();
* \endcode
*
* \param none
*
* \return
* Returns pointer of:
* - integer array of valid filters
* - NULL
* 
* \sa sdkCreate
* \note_nsp_sdk_api
*/
EXPORT_DLL	int* sdkGetValidFilters();

/**
* \brief Get sensor ID of physical device(sensor)
*
* This function returns a sensor ID of currently activated physical device(sensor).
* Current sensor is an activated one by sdkActivateSensorWithID() or sdkActivateSensorWithIndex() functions.
*
* \code
*	char sensor_id[SENSOR_ID_STRING_LENGTH];
*   int ret_value = sdkGetSensorIDFromDevice(sensor_id);
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
* \sa sdkGetSensorIDFromCalData
* \note_nsp_sdk_api
*/
EXPORT_DLL int sdkGetSensorIDFromDevice(char* sensor_id_str );


/**
* \brief Get sensor ID of sensor calibration data.
*
* This function returns sensor ID in sensor calibration data file.
*
* \code
*   char sensor_id_str[SENSOR_ID_STRING_LENGTH];
*   int ret_val = sdkGetSensorIDFromCalData(sensor_id_str);
* \endcode
*
* \param sensor_id_str - char buffer to contain sensor ID [OUT]
*
* \return
* Returns one numeric value of NSP_RETURN_VALUE_SUCCESS.
* - the length of sensor ID string (>0).
* - NSP_RETURN_VALUE_FAILURE (-1)
* - cc_ec_spectrum_core_object_is_null
* - cc_ec_memory_is_null
* 
* \sa sdkGetSensorIDFromDevice
* \note_nsp_sdk_api
*/
EXPORT_DLL int sdkGetSensorIDFromCalData(char* sensor_id_str);

/**
* \brief Activate a specific sensor with index
*
* This function activates a specific sensor having a matched sensor index among multiple sensors if there are multiple sensors in system.
*
* \code
*   int sensor_index = 0; // default = 0 (1'th sensor)
*   int ret_value = sdkActivateSensorWithIndex(sensor_index);
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
* \sa duConnect, duDisconnect
* \note_nsp_sdk_api
*/
EXPORT_DLL	int sdkActivateSensorWithIndex(int sensor_index);


/**
* \brief Activate a specific sensor
*
* This function activates a specific sensor having a matched sensor index among multiple sensors if there are multiple sensors in system.
*
* \code
*   const char* sensor_id_str = "Y8585-1-85-85-0";
*   int ret_value = sdkActivateSensorWithID(sensor_id_str);
* \endcode
*
* \param sensor_id_str - sensor ID string [IN]
*
* \return
* Returns one numeric value of:
* - NSP_RETURN_VALUE_SUCCESS (1)
* - NSP_RETURN_VALUE_FAILURE (-1)
* - cc_ec_device_object_is_null
* 
* \sa duConnect, duDisconnect
* \note_nsp_sdk_api
*/
EXPORT_DLL	int sdkActivateSensorWithID(const char* sensor_id_str);

/**
* \brief Get shutter speed
*
* This function returns a shutter speed value of currently activated sensor.
*
* \code
*   int cur_ss = 0;
*   cur_ss = sdkGetShutterSpeed();
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
* \sa sdkSetShutterSpeed
* \note_nsp_sdk_api
*/
EXPORT_DLL int sdkGetShutterSpeed();

/**
* \brief Change current shutter speed of a device(sensor)
*
* This function changes shutter speed of currently activated device(sensor).
*
* \code
*   int new_ss = 50;
*   int ret_value = sdkSetShutterSpeed(new_ss);
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
* \note_nsp_sdk_api
*/
EXPORT_DLL int sdkSetShutterSpeed(int shutter);

/**
* \brief Get Shutter Speed Limist
*
* This function returns two shutter speed limits (minimum and maximum).
*
* \code
*   int ss_min, ss_max;
*   int ret_value = sdkGetShutterSpeedLimits(&ss_min, &ss_max);
* \endcode
*
* \param ss_min - int pointer to the minimum shutter speed (OUT)
* \param ss_max - int pointer to the maximum shutter speed (OUT)
*
* \return
* Returns one numeric value of:
* - NSP_RETURN_VALUE_SUCCESS (1)
* - NSP_RETURN_VALUE_FAILURE (-1)
* 
* \sa sdkGetShutterSpeed, sdkSetShutterSpeed, sdkShutterSpeedToExposureTime
* \note_core_spectrum_api
*/
EXPORT_DLL int sdkGetShutterSpeedLimits(int* min_limit, int* max_limit);

/**
* \brief Convert shutter speed to exposure time(msec)
*
* This function converts a shutter speed value to exposure time (unit: msec).
*
* \code
*	int	master_clock = 5;	// 5 MHz
*   int cur_ss = 50;
*	double exposure_time = 0.0;
*   int ret_value = sdkShutterSpeedToExposureTime(master_clock, cur_ss, &exposure_time );
* \endcode
*
* \param master_clock - master clock of MCU to sensor (IN)
* \param cur_ss - current shutter speed (IN)
* \param exposure_time - double pointer to exposure time (OUT)
*
* \return
* Returns one numeric value of:
* - NSP_RETURN_VALUE_SUCCESS (1)
* - NSP_RETURN_VALUE_FAILURE (-1)
* 
* \sa sdkGetShutterSpeed, sdkSetShutterSpeed, sdkGetShutterSpeedLimits, sdkExposureTimeToShutterSpeed
* \note_core_spectrum_api
*/
EXPORT_DLL int sdkShutterSpeedToExposureTime(int master_clock, int shutter_speed_val, double* exposure_time);

/**
* \brief Convert exposure time (ms) to shutter speed
*
* This function converts a exposure time (unit: msec) to shutter speed value based on sensor's master clock.
*
* \code
*	int master_clock = 5; // 5-MHz
*	double exposure_time = 100.0;
*   int shutter_speed = 0;
*   int ret_value = sdkShutterSpeedToExposureTime(cur_ss, &exposure_time );
* \endcode
*
* \param master_clock - master clock of MCU to sensor (IN)
* \param exposure_time - exposure time value (msec) (IN)
* \param shutter_speed_val - int pointer to shutter speed (OUT)
*
* \return
* Returns one numeric value of:
* - NSP_RETURN_VALUE_SUCCESS (1)
* - NSP_RETURN_VALUE_FAILURE (-1)
* 
* \sa sdkGetShutterSpeed, sdkSetShutterSpeed, sdkGetShutterSpeedLimits, sdkShutterSpeedToExposureTime
* \note_core_spectrum_api
*/
EXPORT_DLL int sdkExposureTimeToShutterSpeed(int master_clock, double exposure_time, int* shutter_speed_val);

/**
* \brief Get optimal shutter speed by AE
*
* This function returns an optimal shutter speed value which found by AE(Auto-Exposure) function.
*
* \code
*   int optimal_ss = 0;
*   optimal_ss = sdkGetOptimalShutterSpeed();
* \endcode
*
* \param void
*
* \return
* Returns one numeric value of:
* - optimal shutter speed (>0)
* - NSP_RETURN_VALUE_FAILURE (-1)
* - cc_ec_device_object_is_null
* 
* \sa sdkGetShutterSpeed, sdkSetShutterSpeed
* \note_nsp_sdk_api
*/
EXPORT_DLL int sdkGetOptimalShutterSpeed();

/**
* \brief Get wavelength information data.
*
* This function returns wavelength range information for spectrum data.
*
* \code
*   double start_wavelength, end_wavelength, wavelength_interval;
*   int ret_val = sdkGetWavelengthInfo(&start_wavelength, &end_wavelength, &wavelength_interval);
* \endcode
*
* \param start_wavelength - double pointer to start wavelength [OUT]
* \param end_wavelength - double pointer to end wavelength [OUT]
* \param wavelength_interval - double pointer to wavelength interval[OUT]
*
* \return
* Returns one numeric value of NSP_RETURN_VALUE_SUCCESS.
* - NSP_RETURN_VALUE_SUCCESS (1)
* - NSP_RETURN_VALUE_FAILURE (-1)
* - cc_ec_spectrum_core_object_is_null
* 
* \sa sdkGetResolution
* \note_nsp_sdk_api
*/
EXPORT_DLL int sdkGetWavelengthInfo(double *start_wavelength, double *end_wavelength, double *interval_wavelength);

/**
* \brief Get spectrum resolution.
*
* This function returns spectrum resolution information.
*
* \code
*   double spectrum_resolution;
*   int ret_val = sdkGetResolution(&spectrum_resolution);
* \endcode
*
* \param spectrum_resolution - double pointer to spectrum resolution [OUT]
*
* \return
* Returns one numeric value of:
* - NSP_RETURN_VALUE_SUCCESS (1)
* - NSP_RETURN_VALUE_FAILURE (-1)
* - cc_ec_spectrum_core_object_is_null
* 
* \sa sdkGetSpectrumLength
* \note_nsp_sdk_api
*/
EXPORT_DLL int sdkGetResolution(double* resolution); 

/**
* \brief Get size of spectrum data
*
* This function returns the size(length) of spectrum data.
*
* \code
*   int spectrum_length;
*   spectrum_length = sdkGetSpectrumLength();
* \endcode
*
* \param void
*
* \return
* Returns one numeric value of:
* - spectrum data size(length) (>0)
* - NSP_RETURN_VALUE_FAILURE (-1)
* - cc_ec_spectrum_core_object_is_null
* 
* \sa sdkGetWavelengthInfo, sdkGetResolution, sdkCalculateSpectrum
* \note_nsp_sdk_api
*/
EXPORT_DLL int sdkGetSpectrumLength();

/**
* \brief Calculate spectrum
*
* This function returns a calculated spectrum and wavelength data with input filter data.
*
* \code
*   int cur_ss = 50;
*	int	frame_averages = 50;
*   // get spectrum length
*   int spectrum_length = sdkGetSpectrumLength();
*   double* spectrum_data = (double*)malloc(sizeof(double)*spectrum_length);
*   double* wavelength_data = (double*)malloc(sizeof(double)*spectrum_length);
*   int ret_value = sdkCalculateSpectrum(cur_ss, frame_averages, spectrum_data, wavelength_data );
* \endcode
*
* \param cur_ss - current shutter speed [IN]
* \param frame_averages - frame count for averaging [IN]
* \param spec_output - double pointer to spectrum data [OUT]
* \param wavelength_output - double pointer to wavelength data [OUT]
*
* \return
* Returns one numeric value of:
* - spectrum data size(length) (>0)
* - NSP_RETURN_VALUE_FAILURE (-1)
* - cc_ec_memory_for_spectrum_data_buffer_is_null
* - cc_ec_memory_for_wavelength_data_buffer_is_null
* 
* \sa sdkGetSpectrumLength, sdkGetResolution, sdkGetWavelengthInfo
* \note_core_spectrum_api
*/
EXPORT_DLL int sdkCalculateSpectrum(int cur_ss, int frame_averages, double* spec_output, double* wavelength_output);

/**
* \brief Get color information of current spectrum data.
*
* Calculate color information and returns in \p X, \p Y, \p Z, \p r, \p g, \p b,
* \p x, \p y, \p z, \p cct.
*
* \code
*	double	*spectrum_data;		// from csCalculateSpectrum() function
*	double	*wavelength_data;	// from csCalculateSpectrum() function
*	int		spectrum_length;	// from csCalculateSpectrum() function
*   double	X, Y, Z;
*   double	r, g, b;
*   double	x, y, z;
*	double	cct;
*   int ret_value = sdkCalculateColor(spectrum_data, wavelength_data, spectrum_length,
*									&X, &Y, &Z, &r, &g, &b, &x, &y, &z, &cct);
* \endcode
*
* \param spectrum - Spectrum data [IN]
* \param wavelength - Wavelength data [IN]
* \param spectrum_length - Spectrum length [IN]
* \param X - Pointer to a double which the numerical value for color (X) is returned [OUT]
* \param Y - Pointer to a double which the numerical value for color (Y) is returned [OUT]
* \param Z - Pointer to a double which the numerical value for color (Z) is returned [OUT]
* \param r - Pointer to a double which the numerical value for color (R) is returned [OUT]
* \param g - Pointer to a double which the numerical value for color (G) is returned [OUT]
* \param b - Pointer to a double which the numerical value for color (B) is returned [OUT]
* \param x - Pointer to a double which the numerical value for color (x) is returned [OUT]
* \param y - Pointer to a double which the numerical value for color (y) is returned [OUT]
* \param z - Pointer to a double which the numerical value for color (z) is returned [OUT]
* \param cct - Pointer to a double which the numerical value for CCT is returned [OUT]
*
* \return
* - NSP_RETURN_VALUE_FAILURE
* - NSP_RETURN_VALUE_SUCCESS
* - cc_ec_color_object_is_null
* - cc_ec_memory_for_spectrum_data_buffer_is_null
* - cc_ec_memory_for_wavelength_data_buffer_is_null
* \note_app_color_api_calc_color
* 
* \sa sdkGetSpectrumLength, sdkCalculateSpectrum
*/
EXPORT_DLL int sdkCalculateColor(double* spectrum,  double* wavelength, int spectrum_length, double* X, double* Y, double* Z, double* r, double* g, double* b, double* x, double*y, double* z, double* cct);

#ifdef __cplusplus
}
#endif

#endif // __NSP_SDK_API_H__
