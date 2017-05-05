import ctypes
import sys


def get_optimal_shutter_speed(pSpecDevice,valid_filters_num,valid_filters):
    """Get Optimal Shutter Speed

    * This function returns an optimal shutter speed value which found by AE(Auto-Exposure) function.

    * Get optimal shutter speed by AE
    *
    * This function returns an optimal shutter speed value which found by AE(Auto-Exposure) function.
    *
    * \code
    *   int optimal_ss = 0;
    *   optimal_ss = duGetOptimalShutterSpeed();
    * \endcode
    * \param void
    *
    * \return
    * Returns one numeric value of:
    * - optimal shutter speed (>0)
    * - NSP_RETURN_VALUE_FAILURE (-1)
    """


    print ("[PythonPrism] Getting Optimal Shutter Speed.......")

    ret = pSpecDevice.duGetOptimalShutterSpeed(valid_filters,valid_filters_num)

    if ret <= 0:
        print "[PythonPrismError] Getting Optimal Shutter Speed from the Device Failed!"
        return -1
    else:
        print "[PythonPrism] Optimal Shutter Speed: ", ret
        return ret
