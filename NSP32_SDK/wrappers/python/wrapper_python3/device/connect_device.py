import ctypes
import sys

def connect_device(pSpecDevice):
    """Connecting Physical device

    This function try to connect to physical device(sensor) and returns the total number of sensors in system.

    * Connect to physical device(sensor)
    *
    * This function try to connect to physical device(sensor) and returns the total number of sensors in system.
    *
    * \code
    *   int num_of_sensors = duConnect();
    * \endcode
    *
    * \param void
    *
    * \return
    * Returns one numeric value of:
    * - total number of sensors in system (>0)
    * - NSP_RETURN_VALUE_FAILURE (-1)
    """
    ret = pSpecDevice.duConnect()

    if ret <=0:
        print ("[PythonPrismError] Device not Connected!")
        return -1;
    else:
        print ("[PythonPrism] Device Connected Successfully!")
        return ret