import ctypes
import sys


def load_sensor_file(pSpecCore,sensor_file_path):
    """loading sensor file

    This function add one sensor to Core Spectrum object by loading sensor calibration data file.

    * \brief Add one sensor to sensor calibration data container (DB).
    *
    * This function add one sensor to Core Spectrum object by loading sensor calibration data file.
    *
    * \code
    * // 'Y8585-1-85-85-0' is a sensor ID of a specific physical sensor.
    * char* sensor_cal_data_path = "./config/sensor_Y8585-1-85-85-0.dat";
    * int ret_val = csRegister(sensor_cal_data_path);
    * \endcode
    *
    * \param sensor_cal_file_path - sensor calibration file path [IN]
    *
    * \return
    * Returns one numeric values of NSP_RETURN_VALUE_SUCCESS, NSP_RETURN_VALUE_FAILURE, or exception.
    * - the number of sensors in the sensor cal data container(>0).
    * - NSP_RETURN_VALUE_FAILURE.
    """

    ret = pSpecCore.csRegister(sensor_file_path)

    if ret <=0:
        print "[PythonPrismError] Sensor File Loading Failed!"
        return -1;
    else:
        print "[PythonPrism] Sensor File Successfully Loaded!"
        return ret