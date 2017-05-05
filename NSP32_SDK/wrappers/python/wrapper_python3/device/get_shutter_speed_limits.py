import ctypes
import string
import sys

def get_shutter_speed_limits(pSpecDevice):
    """getting min and max shutter speed

    This function returns two limit values for shutter speed (minimum and maximum).

    * \brief Get shutter speed limits
    *
    * This function returns two limit values for shutter speed (minimum and maximum).
    *
    * \code
    *   int ss_min, ss_max;
    *   cur_ss = duGetShutterSpeedLimits(&ss_min, &ss_max);
    * \endcode
    *
    * \param ss_min - int pointer to minimum shutter speed value [OUT]
    * \param ss_max - int pointer to maximum shutter speed value [OUT]
    *
    * \return
    * Returns one numeric value of:
    * - NSP_RETURN_VALUE_SUCCESS (1)
    * - NSP_RETURN_VALUE_FAILURE (-1)
    """

    min_ss   = ctypes.c_int()
    max_ss   = ctypes.c_int()

    ret = pSpecDevice.duGetShutterSpeedLimits(ctypes.byref(min_ss), ctypes.byref(max_ss))

    if ret <=0:
        print ("[PythonPrismError] Getting shutter speed limits From Device Failed")
        return (-1,-1,-1)
    else:
        print ("[PythonPrism-FromDevice]  Min SS: ", min_ss.value , ", Max SS: ", max_ss.value)
        return (min_ss.value,max_ss.value)