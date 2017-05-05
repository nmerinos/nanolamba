import ctypes
import sys

def device_ID_activation(pSpecDevice, sensorID):
    """activet the sensor with sensor ID

    This function activates a specific sensor having a matched sensor ID among multiple sensors if there are multiple sensors in system.

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
    """

    ret = pSpecDevice.duActivateSensorWithID(sensorID)

    if ret <=0:
        print ("[PythonPrismError] Activating Sensor with Index failed!")
        return -1;
    else:
        print ("[PythonPrism] Successfully Activated the sesnor with specific index: ",sensor_index)
        return ret