import ctypes
import string
import sys

def set_sensor_parameters_to_device( pSpecDevice, adc_gain , adc_range):
    """set register settings

    This function will set the ADC and Gain value to Apollo

    * \brief Set sensor registers
    *
    * This function changes sensor registers for ADC gain, ADC range, and ADC resolution.
    *
    * \code
    *   int adc_gain = 1;   // 1=1X (default), 0=4X
    *   int adc_range = 132; // 132 (default)
    *   int adc_resolution = 0; // 12-bit(fixed)
    *   int ret_value = duSetRegisters(adc_gain, adc_range, adc_resolution);
    * \endcode
    *
    * \param _adc_gain - ADC gain value [IN]
    * \param _adc_range - ADC range value [IN]
    * \param _adc_res - ADC resolution value [IN]
    *
    * \return
    * Returns one numeric value of:
    * - NSP_RETURN_VALUE_SUCCESS (1)
    * - NSP_RETURN_VALUE_FAILURE (-1)
    """

    print ("[PythonPrism] (ADC Gain ,  ADC Range) : (" , adc_gain  ," , " , adc_range, " )")

    ret = pSpecDevice.duSetSensorParameters(adc_gain,adc_range)

    if ret <=0:
        print ("[PythonPrismError] Setting Register Settings Failed")
        return -1;
    else:
        print ("[PythonPrism] Setting Register Settings Successful")
        return ret