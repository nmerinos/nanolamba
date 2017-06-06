import ctypes
import sys

def disconnect_device(pSpecDevice):
    """Disconnecting Physical device

    This function disconnects physical device(sensor).

    * brief Disconnect physical device(sensor)
    *
    * This function disconnects physical device(sensor).
    *
    * \code
    *   int ret_value = duDisconnect();
    * \endcode
        * \param void
        *
    * \return
    * Returns one numeric value of:
    * - NSP_RETURN_VALUE_SUCCESS (1)
    * - NSP_RETURN_VALUE_FAILURE (-1)
    """
    ret = pSpecDevice.duDisconnect()

    if ret <=0:
        print "[PythonPrismError] Device not Connected!"
        return -1;
    else:
        print "[PythonPrism] Device disConnected Successfully!"
        return ret