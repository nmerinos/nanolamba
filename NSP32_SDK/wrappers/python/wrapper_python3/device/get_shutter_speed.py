import ctypes
import string
import sys

def get_shutter_speed(pSpecDevice):
    """get shutter speed

    This function get the already set shutter speed from the device

    * \brief Get shutter speed
    *
    * This function returns a shutter speed value of currently activated sensor.
    *
    * \code
    *   int cur_ss = 0;
    *   cur_ss = duGetShutterSpeed();
    * \endcode
    *
    * \param void
    *
    * \return
    * Returns one numeric value of:
    * - current shutter speed (>0)
    * - NSP_RETURN_VALUE_FAILURE (-1)
    """

    ret = pSpecDevice.duGetShutterSpeed()

    print ("[PythonPrism] Current Shutter Speed is:  ", ret)
    return ret