import ctypes
import sys


def total_sensors_connected(pSpecDevice):
    """Total Device Connected

    This function will return the total number of sensors connected

    * \brief Get devices count
    *
    * This function returns a total number of devices in system.
    *
    * \code
    *   int total_num_of_devices = duGetTotalDevices();
    * \endcode
    *
    * \param void
    *
    * \return
    * Returns one numeric value of:
    * - total number of devices (>0)
    * - NSP_RETURN_VALUE_FAILURE (-1)
    """

    ret = pSpecDevice.duGetTotalSensors()

    if ret <=0:
        print "[PythonPrismError] No Device Attached to the system!"
        return -1;
    else:
        print "[PythonPrism] Total Device/s Attached: ", ret
        return ret