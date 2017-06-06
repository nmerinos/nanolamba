import ctypes
import string
import sys

def get_sensor_parameters_from_device(pSpecDevice):
    """get register value from physical device

    This function returns the current settings of sensor registers (ADC gain, ADC range, and ADC resolution).

    * \brief Get settings of sensor registers
    *
    * This function returns the current settings of sensor registers (ADC gain, ADC range, and ADC resolution).
    *
    * \code
    *   int adc_gain = 1;   // 1=1X (default), 0=4X
    *   int adc_range = 132; // 132 (default)
    *   int adc_resolution = 0; // 12-bit(fixed)
    *   int ret_value = duGetRegisters(&adc_gain, &adc_range, &adc_resolution);
    * \endcode
    *
    * \param _adc_gain - integer pointer to ADC gain value [OUT]
    * \param _adc_range - integer pointer to ADC range value [OUT]
    * \param _adc_res - integer pointer to ADC resolution value [OUT]
    *
    * \return
    * Returns one numeric value of:
    * - NSP_RETURN_VALUE_SUCCESS (1)
    * - NSP_RETURN_VALUE_FAILURE (-1)
    """

    adc_gain   = ctypes.c_int()
    adc_range   = ctypes.c_int()

    ret = pSpecDevice. duGetSensorParameters(ctypes.byref(adc_gain), ctypes.byref(adc_range))

    if ret <=0:
        print ("[PythonPrismError] Getting Register Settings From Device Failed")
        return (-1,-1,-1)
    else:
        print ("[PythonPrism-FromDevice] adcGain: ", adc_gain.value , ", adcRange: ", adc_range.value)
        return (adc_gain.value,adc_range.value)