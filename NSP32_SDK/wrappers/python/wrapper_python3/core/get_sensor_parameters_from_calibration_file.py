import ctypes
import string
import sys

def get_sensor_parameters_from_calibration_file(pSpecCore):
    """get register settings

    This function will get the ADC and Gain value from the sensor File

    * \brief Get register settings
    *
    * This function returns ADC register settings from physical device (sensor).
    *
    * \code
    *   int adc_gain, adc_range;
    *   int ret_value = csGetRegisterSettings(&adc_gain, &adc_range);
    * \endcode
    *
    * \param adc_gain - pointer to ADC gain info: 0 or 1(default) [OUT]
    * \param adc_range - pointer to ADC range info (0~255) [OUT]
    *
    * \return
    * Returns one numeric value of:
    * - NSP_RETURN_VALUE_SUCCESS (1)
    * - NSP_RETURN_VALUE_FAILURE (-1)
    """

    adc_gain = ctypes.c_int()
    adc_range = ctypes.c_int()

    ret = pSpecCore.csGetSensorParameters(ctypes.byref(adc_gain),ctypes.byref(adc_range))

    if ret <=0:
        print ("[PythonPrismError] Getting Register Settings Failed")
        return (-1,-1)
    else:
        print ("[PythonPrism] adcGain: ", adc_gain.value , ", adcRange: ", adc_range.value)
        return (adc_gain.value,adc_range.value)