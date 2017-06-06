import ctypes
import string
import sys

def ss_to_exposure_time(pSpecDevice, master_clock, shutter_speed):
    """converting shutter speed value to exposure time value

    This function converts shutter speed to exposure time based on MASTER CLOCK of sensor.

    * \brief Convert shutter speed to exposure time (unit: ms)
    *
    * This function converts shutter speed to exposure time based on MASTER CLOCK of sensor.
    *
    * \code
    *   int master_clock = 5; // MCLK = 5-MHz
    *   int shutter_speed = 1000
    *   double exposure_time_val = 0;
    *   cur_ss = duShutterSpeedToExposureTime(master_clock, shutter_speed, &exposure_time_val);
    * \endcode
    *
    * \param master_clock - master clock of MCU to sensor [IN]
    * \param shutter_speed - shutter speed value [IN]
    * \param exposure_time_val - double pointer to exposure time value [OUT]
    *
    * \return
    * Returns one numeric value of:
    * - NSP_RETURN_VALUE_SUCCESS (1)
    * - NSP_RETURN_VALUE_FAILURE (-1)
    """

    exposure_time_value   = ctypes.c_double()

    ret = pSpecDevice.duShutterSpeedToExposureTime(master_clock,shutter_speed, ctypes.byref(exposure_time_value))

    if ret <=0:
        print ("[PythonPrismError] Converting shutter speed value to exposure time failed")
        return (-1,-1,-1)
    else:
        print ("[PythonPrism-FromDevice]  ShutterSpeed: ", shutter_speed , " with master clock: ", master_clock, " equals to Exposure Time: ",exposure_time_value.value)
        return (exposure_time_value.value)