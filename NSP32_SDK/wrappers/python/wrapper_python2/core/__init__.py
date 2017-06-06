"""Package for using Core API

There are several functions defined at the top level that are imported
from modules contained in the package.
"""

import warnings
import sys


from initialize_core_api import initialize_core_api
from load_sensor_file import load_sensor_file
from get_sensor_id_file import get_sensor_id_file
from get_sensor_parameters_from_calibration_file import get_sensor_parameters_from_calibration_file
from set_background_data import set_background_data
from get_spectrum_length import get_spectrum_length
from calculate_spectrum import calculate_spectrum
from get_resolution import get_resolution
from get_wavelength_information  import get_wavelength_information
from close_core_object import close_core_object
from create_core_object import create_core_object
from get_capacity_sensor_data_list import get_capacity_sensor_data_list
from calibration_ID_activation import calibration_ID_activation
from get_num_of_valid_filters import get_num_of_valid_filters
from get_valid_filters import get_valid_filters
