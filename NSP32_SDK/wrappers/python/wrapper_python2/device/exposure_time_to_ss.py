import ctypes
import string
import sys

def exposure_time_to_ss(pSpecDevice, master_clock, exposure_time_value):
    """converting shutter speed value to exposure time value

    This function converts shutter speed to exposure time based on MASTER CLOCK of sensor.

    * \brief Convert exposure time (ms) to shutter speed
    *
    * This function converts exposure time to shutter speed based on MASTER CLOCK of sensor.
    *
    * \code
    *   int master_clock = 5; // MCLK = 5-MHz
    *   double exposure_time_val = 100; // 100 msec
    *   int shutter_speed = 0
    *   cur_ss = duExposureTimeToShutterSpeed(master_clock, exposure_time_val, &shutter_speed);
    * \endcode
    *
    * \param master_clock - master clock of MCU to sensor [IN]
    * \param exposure_time_val - exposure time value (ms) [IN]
    * \param shutter_speed - int pointer to shutter speed value [OUT]
    *
    * \return
    * Returns one numeric value of:
    * - NSP_RETURN_VALUE_SUCCESS (1)
    * - NSP_RETURN_VALUE_FAILURE (-1)
    """

    shutter_speed   = ctypes.c_int()

    ret = pSpecDevice.duShutterSpeedToExposureTime(master_clock,exposure_time_value, ctypes.byref(shutter_speed))

    if ret <=0:
        print "[PythonPrismError] Converting Exposure Time value to shutter speed failed"
        return (-1,-1,-1)
    else:
        print "[PythonPrism-FromDevice]  Exposure time: ", exposure_time_value , " with master clock: ", master_clock, " equals to SS: ",shutter_speed.value
        return (exposure_time_value.value)