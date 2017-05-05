import ctypes
import string
import sys

def set_shutter_speed(pSpecDevice, newSS = 1):
    """set shutter speed

    This function set new shutter speed to the device

    * \brief Change current shutter speed of a device(sensor)
    *
    * This function changes shutter speed of currently activated device(sensor).
    *
    * \code
    *   int new_ss = 50;
    *   int ret_value = duSetShutterSpeed(new_ss);
    * \endcode
    *
    * \param shutter - shutter speed value [IN]
    *
    * \return
    * Returns one numeric value of:
    * - NSP_RETURN_VALUE_SUCCESS (1)
    * - NSP_RETURN_VALUE_FAILURE (-1)
    """

    ret = pSpecDevice.duSetShutterSpeed(newSS)

    if ret <=0:
        print "[PythonPrismError] Setting New Shutter Speed to the Device Failed"
        return -1;
    else:
        print "[PythonPrism] New Shutter Speed ( ", newSS, ") Successfully set to the Device"
        return ret