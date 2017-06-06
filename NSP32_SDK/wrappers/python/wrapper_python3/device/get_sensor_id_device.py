import ctypes
import string
import sys

def get_sensor_id_device(pSpecDevice):
    """get sensor id

    This function will get the sensor ID from Apollo

    * \brief Get sensor ID of physical device(sensor)
    *
    * This function returns a sensor ID of currently activated physical device(sensor).
    * Current sensor is an activated one by duActivateDevice() function.
    *
    * \code
    *   char sensor_id[SENSOR_ID_STRING_LENGTH];
    *   int ret_value = duGetSensorID(sensor_id);
    * \endcode
    *
    * \param pointer to char array for sensor ID data [OUT]
    *
    * \return
    * Returns one numeric value of:
    * - NSP_RETURN_VALUE_SUCCESS (1)
    * - NSP_RETURN_VALUE_FAILURE (-1)
    """



    sensorIDBuffer = ctypes.c_char * 26
    sensorID = sensorIDBuffer()


    ret = pSpecDevice.duGetSensorID(sensorID)

    if ret <=0:
        print ("[PythonPrismError] UnKnown Sensor ID From Device" , sensorID.value)
        return (-1,-1)
    else:
        print ("[PythonPrism] SensorID From Device: ", sensorID.value)
        return (ret,sensorID.value)