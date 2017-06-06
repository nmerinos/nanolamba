import ctypes
import sys

def initialize_device_api(crystal_port_library_path):
    """Initializing Device API

    This function will initialize Device API

    if sys.version_info[0] < 3:
        print "[PythonPrism] CrystalPortPath: ", crystal_port_library_path
    else:
        print ("[PythonPrism] CrystalPortPath: ", crystal_port_library_path)
    """
    pSpecDevice = ctypes.CDLL(crystal_port_library_path)

    print "[PythonPrism] CrystalPort Library Loaded Successfully!"

    return pSpecDevice