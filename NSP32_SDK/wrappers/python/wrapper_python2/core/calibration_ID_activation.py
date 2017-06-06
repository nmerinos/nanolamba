import ctypes
import string
import sys

def calibration_ID_activation(pSpecCore,sensorID):
    """Acitivating the device with sensor ID from the calibration file

    This function activates one sensor data of input sensor ID.

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
    """

    ret = pSpecCore.csActivateSensorWithID(sensorID)

    if ret <=0:
        print "[PythonPrismError] Activating sensor with ID is Failed!"
        return -1;
    else:
        print "[PythonPrism] Successfully activated the sensor with ID!"
        return ret