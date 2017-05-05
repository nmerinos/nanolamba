import ctypes
import sys

def index_activation(pSpecDevice, sensor_index):
    """activet the sensor with sensor index

    This function activates a specific sensor having a matched sensor index among multiple sensors if there are multiple sensors in system.

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
    """

    ret = pSpecDevice.duActivateSensorWithIndex(sensor_index)

    if ret <=0:
        print "[PythonPrismError] Activating Sensor with Index failed!"
        return -1;
    else:
        print "[PythonPrism] Successfully Activated the sesnor with specific index: ",sensor_index
        return ret