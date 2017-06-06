/*
NSP_CORE_API.H

Provides API functions

*/

#ifndef __NSP_CORE_API_H__
#define __NSP_CORE_API_H__


#ifdef _WIN32
#define EXPORT_DLL __declspec(dllexport) //For exporting to DLL 
#endif
#if defined(__linux) || defined(__APPLE__) || defined(__CYGWIN__)
#define EXPORT_DLL __attribute__((visibility("default")))
#endif


#ifdef __cplusplus
extern "C"{ 
#endif

	
// function prefix: cs - Core Spectrum

/**
* \brief Initialize Core Spectrum C API.
*
* This function create a core spectrum object.
*
* \code
* int ret_val = csCreate();
* \endcode
*
* \param void
*
* \return
* Returns one numeric values of NSP_RETURN_VALUE_SUCCESS, NSP_RETURN_VALUE_FAILURE, or exception.
* - NSP_RETURN_VALUE_SUCCESS.
* - NSP_RETURN_VALUE_FAILURE.
* - cc_ec_fail_to_create_core_spectrum_obj.
* 
* \sa csDestroy
* \note_core_spectrum_api
*/
EXPORT_DLL  int csCreate(void);

/**
* \brief Destroy Core Spectrum C API.
*
* This function finalize a core spectrum object.
*
* \code
*   int ret_val = csDestroy();
* \endcode
*
* \param void
*
* \return
* Returns one numeric value of NSP_RETURN_VALUE_SUCCESS.
* - NSP_RETURN_VALUE_SUCCESS.
* 
* \sa csCreate
* \note_core_spectrum_api
*/
EXPORT_DLL  int csDestroy(void);

/**
* \brief Add one sensor to sensor calibration data container (DB).
*
* This function add one sensor to Core Spectrum object by loading sensor calibration data file.
*
* \code
* // 'Y8585-1-85-85-0' is a sensor ID of a specific physical sensor.
* char* sensor_cal_data_path = "./config/sensor_Y8585-1-85-85-0.dat";
* int ret_val = csRegister(sensor_cal_data_path);
* \endcode
*
* \param sensor_cal_file_path - sensor calibration file path [IN]
*
* \return
* Returns one numeric values of NSP_RETURN_VALUE_SUCCESS, NSP_RETURN_VALUE_FAILURE, or exception.
* - the number of sensors in the sensor cal data container(>0).
* - NSP_RETURN_VALUE_FAILURE.
* - cc_ec_fail_to_create_core_spectrum_obj.
* - cc_ec_sensor_id_is_empty.
* 
* \sa csCreate, csDestroy
* \note_core_spectrum_api
*/
EXPORT_DLL  int csRegister(const char* sensor_cal_file_path);

/**
* \brief Get capacity of sensor data list.
*
* This function returns total number of sensors in sensor data list.
*
* \code
* int total_sensors = csCapacity();
* \endcode
*
* \param void
*
* \return
* Returns one numeric values of total number of sensors in sensor data list, NSP_RETURN_VALUE_FAILURE, or exception.
* - the number of sensors in the sensor cal data container(>0).
* - NSP_RETURN_VALUE_FAILURE.
* - cc_ec_fail_to_create_core_spectrum_obj.
* - cc_ec_sensor_id_is_empty.
* 
* \sa csCreate, csDestroy
* \note_core_spectrum_api
*/
EXPORT_DLL  int csCapacity(void);

/**
* \brief Get sensor ID list.
*
* This function returns 2D string array havin sensor IDs.
*
* \code
* char **sensor_id_list = NULL;
* sensor_id_list = csGetSensorList();
* \endcode
*
* \param none
*
* \return
* Returns double pointer to the array having sensor IDs.
* - a list of sensors IDs.
* - NULL.
* 
* \sa csGetSensorID
* \note_core_spectrum_api
*/
EXPORT_DLL  char** csGetSensorList();

/**
* \brief Get sensor ID of sensor calibration data.
*
* This function returns sensor ID in sensor calibration data file.
*
* \code
*   char sensor_id_str[SENSOR_ID_STRING_LENGTH];
*   int ret_val = csGetSensorID(sensor_id_str);
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
* \sa csRegister
* \note_core_spectrum_api
*/
EXPORT_DLL int csGetSensorID(char* sensor_id_str);

/**
* \brief Activate one sensor data.
*
* This function activates one sensor data of input sensor ID.
*
* \code
*   char sensor_id_str[SENSOR_ID_STRING_LENGTH];
*   int ret_val = csActivateSensorWithID(sensor_id_str);
* \endcode
*
* \param sensor_id_str - char buffer to contain sensor ID [OUT]
*
* \return
* Returns one numeric value of NSP_RETURN_VALUE_SUCCESS.
* - NSP_RETURN_VALUE_SUCCESS (1).
* - NSP_RETURN_VALUE_FAILURE (-1)
* - cc_ec_spectrum_core_object_is_null
* - cc_ec_memory_is_null
* 
* \sa csRegister
* \note_core_spectrum_api
*/
EXPORT_DLL int csActivateSensorWithID(const char* sensor_id_str);

/**
* \brief Get wavelength information data.
*
* This function returns wavelength range information for spectrum data.
*
* \code
*   double start_wavelength, end_wavelength, wavelength_interval;
*   int ret_val = csGetWavelengthInfo(&start_wavelength, &end_wavelength, &wavelength_interval);
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
* \sa csGetResolution
* \note_core_spectrum_api
*/
EXPORT_DLL int csGetWavelengthInfo(double *start_wavelength, double *end_wavelength, double *interval_wavelength);

/**
* \brief Get spectrum resolution.
*
* This function returns spectrum resolution information.
*
* \code
*   double spectrum_resolution;
*   int ret_val = csGetResolution(&spectrum_resolution);
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
* \sa csGetWavelengthInfo
* \note_core_spectrum_api
*/
EXPORT_DLL int csGetResolution(double* resolution); 


/**
* \brief Get number of valid filters
*
* This function returns the number of valid filters among 1024 filters.
*
* \code
*   int num_of_valid_filters;
*   num_of_valid_filters = csGetNumOfValidFilters();
* \endcode
*
* \param void
*
* \return
* Returns one numeric value of:
* - the number of valid filters (>0)
* - NSP_RETURN_VALUE_FAILURE (-1)
* - cc_ec_spectrum_core_object_is_null
* 
* \sa csGetWavelengthInfo, csGetResolution, csCalculateSpectrum
* \note_core_spectrum_api
*/
EXPORT_DLL int csGetNumOfValidFilters(void);


/**
* \brief Get valid filters
*
* This function returns the valid filters.
*
* \code
*   int* valid_filters = NULL;
*   valid_filters = csGetValidFilters();
* \endcode
*
* \param void
*
* \return
* Returns one numeric value of:
* - the pointer to the integer array of valid filters
* - NULL
* 
* \sa csGetWavelengthInfo, csGetResolution, csCalculateSpectrum
* \note_core_spectrum_api
*/
EXPORT_DLL int* csGetValidFilters(void);

/**
* \brief Get size of spectrum data
*
* This function returns the size(length) of spectrum data.
*
* \code
*   int spectrum_length;
*   spectrum_length = csGetSpectrumLength();
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
* \sa csGetWavelengthInfo, csGetResolution, csCalculateSpectrum
* \note_core_spectrum_api
*/
EXPORT_DLL int csGetSpectrumLength(void);

/**
* \brief Get register settings
*
* This function returns ADC register settings from physical device (sensor).
*
* \code
*   int adc_gain, adc_range;
*   int ret_value = csGetSensorParameters(&adc_gain, &adc_range);
* \endcode
*
* \param adc_gain - pointer to ADC gain info: 0 or 1(default) [OUT]
* \param adc_range - pointer to ADC range info (0~255) [OUT]
*
* \return
* Returns one numeric value of:
* - NSP_RETURN_VALUE_SUCCESS (1)
* - NSP_RETURN_VALUE_FAILURE (-1)
* - cc_ec_spectrum_core_object_is_null
* 
* \sa csGetWavelengthInfo, csGetResolution
* \note_core_spectrum_api
*/
EXPORT_DLL int csGetSensorParameters(int* adc_gain, int* adc_range);

/**
* \brief Set background filter data
*
* This function set input filter data as background data.
* Background data will be used to correct background signal before spectrum calculation.
*
* \code
*   double filter_data[SENSOR_DATA_SIZE];
*   // acquire raw filter data at SS=1
*
*   int ret_value = csSetBackground((double *)filter_data);
* \endcode
*
* \param background_data - double pointer to raw filter data [IN]
*
* \return
* Returns one numeric value of:
* - NSP_RETURN_VALUE_SUCCESS (1)
* - NSP_RETURN_VALUE_FAILURE (-1)
* - cc_ec_spectrum_core_object_is_null
* - cc_ec_background_buffer_is_null
* 
* \sa csCalculateSpectrum
* \note_core_spectrum_api
*/
EXPORT_DLL int csSetBackground(double *background_data);

/**
* \brief Calculate spectrum
*
* This function returns a calculated spectrum and wavelength data with input filter data.
*
* \code
*   int cur_ss = 50;
*   double filter_data[SENSOR_DATA_SIZE];
*   // acquire raw filter data from device(sensor) with shutter speed 'cur_ss'
*
*   // get spectrum length
*   int spectrum_length = csGetSpectrumLength();
*   double* spectrum_data = (double*)malloc(sizeof(double)*spectrum_length);
*   double* wavelength_data = (double*)malloc(sizeof(double)*spectrum_length);
*   int ret_value = csCalculateSpectrum(filter_data, cur_ss, spectrum_data, wavelength_data );
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
* \sa csGetSpectrumLength, csGetResolution, csCalculateSpectrum
* \note_core_spectrum_api
*/
EXPORT_DLL int csCalculateSpectrum(double* filter_input, int cur_ss, double* spec_output, double* wavelength_output);

#ifdef __cplusplus
}
#endif

#endif // __NSP_CORE_API_H__
