import ctypes
import string
import sys

def get_capacity_sensor_data_list(pSpecCore):
    """Close Core API

    This function returns total number of sensors in sensor data list.

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
    """
    ret = pSpecCore.csCapacity()

    if ret <=0:
        print ("[PythonPrismError] Getting capacity list  Failed!")
        return -1;
    else:
        print ("[PythonPrism] Successfully got the capacity list:", ret)
        return ret