import ctypes
import string
import sys

def get_sensor_id_file(pSpecCore):
    """get sensor id

    This function will get the sensor ID from sensor file

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
    """

    sensorIDBuffer = ctypes.c_char * 26
    sensorID = sensorIDBuffer()

    ret = pSpecCore.csGetSensorID(sensorID)

    if ret <=10:
        print "[PythonPrismError] UnKnown Sensor ID From File: " , sensorID.value
        return (-1,-1)
    else:
        print "[PythonPrism] SensorID From File: ", sensorID.value
        return (ret,sensorID.value)