// examples_sdk_device_spectrum.cpp : Defines the entry point for the console application.
// This console application is to show how programmer can create, use, and destroy of device object.
//
// (c) nanolamda 2012~2017

#include <stdio.h>
#include <stdlib.h>


#include "nsp_core_common.h"
#include "nsp_device_def.h"
#include "nsp_sdk_api.h"

/*
	Example: NSP32 device and spectrum APIs

	This example shows how user can use API to get raw filter data, spectrum data, and color info.
		1) acquire raw filter data from deivce
		2) reconstruct spectrum by spectrum API
*/
extern char* g_sensor_cal_file_path;

int examples_sdk_device_spectrum(bool dump_to_file)
{
	int	ret_value = 0;
	double	*spec_output = NULL;
	double	*wavelength_output = NULL;
	char str_sensor_id1[SENSOR_ID_STRING_LENGTH];
	char str_sensor_id2[SENSOR_ID_STRING_LENGTH];

	try{
		// initialize API for spectrum calculation
		ret_value = sdkCreate();

		if( ret_value > 0 ){
			// add one sensor to container
			int total_count_of_active_sensors = sdkRegister(g_sensor_cal_file_path);
			if( total_count_of_active_sensors == 0 ){
				throw "Fail to add one sensor to active sensor list.";
			}

			// get sensor ID from sensor calibration data.
			int id_size = sdkGetSensorIDFromCalData(str_sensor_id2);
			if( id_size == 0 ){
				printf("[examples_sdk_device_spectrum] Error: sensor ID is not available in calibration data.\n");
			}

			// activate a physical device(sensor)
			int	current_device_index = 0;	// 1'st device (default)
			ret_value = sdkActivateSensorWithID(str_sensor_id2);
			if( ret_value == NSP_RETURN_VALUE_NO_MATCHED_SENSOR ){
				printf("[examples_sdk_device_spectrum] Error: there is no matched sensor in your system: %s\n", str_sensor_id2);
				throw "there is no matched sensor in your system.";
			}
			else if( ret_value == NSP_RETURN_VALUE_NO_MATCHED_CAL_DATA ){
				printf("[examples_sdk_device_spectrum] Error: there is no matched calibration data in your system: %s\n", str_sensor_id2);
				throw "there is no matched calibration data in your system.";
			}

			// get sensor ID from device (sensor).
			id_size = sdkGetSensorIDFromDevice(str_sensor_id1);
			if( id_size == 0 ){
				printf("[examples_sdk_device_spectrum] Error: sensor ID is not available in calibration data.\n");
			}

			// check if sensor ID is matched between device and sensor(device) calibration data.
			if( strncmp(str_sensor_id1, str_sensor_id2, SENSOR_ID_STRING_LENGTH) == 0  )
				printf("[examples_sdk_device_spectrum] Sensor ID is matched (%s <-> %s).\n", str_sensor_id1, str_sensor_id2);
			else {
				printf("**************************************************************************************************************\n");
				printf("[examples_sdk_device_spectrum] Error: Sensor ID is NOT matched (%s <-> %s).\n", str_sensor_id1, str_sensor_id2);
				printf("[examples_sdk_device_spectrum] Error: Spectrum (and color) data will not correct.\n");
				printf("[examples_sdk_device_spectrum] Solution: Get correct sensor calibration file for %s.\n", str_sensor_id1);
				printf("**************************************************************************************************************\n");
			}

			// OR, you can get optimal SS by AE
			int	cur_ss = 10;
			if(1){
				cur_ss = sdkGetOptimalShutterSpeed();
				printf("SS by AE: %d\n", cur_ss);

				if( cur_ss == NSP_DEVICE_AE_SATURATION_INDICATOR )	// saturated
				{
				}
				else if ( cur_ss == NSP_DEVICE_MAX_SS || cur_ss == NSP_DEVICE_MIN_SS )
				{
				}
			}
			else{
				cur_ss = 50;
				printf("SS by manual: %d\n", cur_ss);
			}
			// set shutter speed
			sdkSetShutterSpeed(cur_ss);

			// convert shutter speed to exposure time (ms) for your reference.
			int	master_clock = NSP_DEVICE_MASTER_CLOCK;
			double	exposure_time_val = 0;
			sdkShutterSpeedToExposureTime(master_clock, cur_ss, &exposure_time_val);
			printf("[examples_sdk_device_spectrum] current shutter speed: %d (exposure time = %.3f)\n", cur_ss, exposure_time_val);

			// calculate spectrum data
			int spectrum_data_size = sdkGetSpectrumLength();
			if( spectrum_data_size <= 0 )	throw "Invalid spectrum length.";
			printf("Spectrum data size: %d\n", spectrum_data_size);
			spec_output = (double *)malloc(spectrum_data_size*sizeof(double));
			if( spec_output == NULL )	throw "Fail to allocate memory for spectrum data.";
			wavelength_output = (double *)malloc(spectrum_data_size*sizeof(double));
			if( wavelength_output == NULL )	throw "Fail to allocate memory for wavelength data.";

			int	frame_averages = 50;
			ret_value = sdkCalculateSpectrum(cur_ss, frame_averages, spec_output, wavelength_output);
			if( ret_value < 0 ){
				throw "Fail to calculate spectrum.";
			}

			// dump related information and data to CSV format file.
			if( dump_to_file == true ){
				////////////////////////////////////////////////////
				// saving spectrumdata to csv
				std::string outputFileName = "examples_sdk_device_spectrum_color_" + std::string(str_sensor_id1) + "_result.csv";
				fstream filestream;
				filestream.open(outputFileName.c_str(), ofstream::out);
				if (filestream.is_open() == true) {
					filestream << "Sensor ID, " << str_sensor_id1 << endl;
					filestream << "Shutter speed=, " << cur_ss << endl;

					filestream << "Wavelength data" << endl;
					for (int i = 0; i < (int) spectrum_data_size; i++) {
						filestream << wavelength_output[i];
						if (i != (spectrum_data_size - 1))
							filestream << ",";
					}
					filestream << endl;
					filestream << "Spectrum data" << endl;
					for (int i = 0; i < (int) spectrum_data_size; i++) {
						filestream << spec_output[i];
						if (i != (spectrum_data_size - 1))
							filestream << ",";
					}
					filestream << endl;
					filestream.close();
				}
				printf("[examples_sdk_device_spectrum] Spectrum dump to \"%s\" -- done!\n", outputFileName.c_str());
			}

			if( spec_output )		delete spec_output;
			if( wavelength_output )	delete wavelength_output;

			// destroy SDK object.
			sdkDestroy();
		}
		return NSP_RETURN_VALUE_SUCCESS;
	}
	catch(nsp_base_exception &e){
		if( spec_output )		delete spec_output;
		if( wavelength_output )	delete wavelength_output;

		// destroy SDK object.
		sdkDestroy();

		printf("[examples_sdk_device_spectrum] NSP_BASE_EXCEPTION happened: %s\n", e.what());
		return -(int)e.error_code; 
	}
	catch(...){
		if( spec_output )		delete spec_output;
		if( wavelength_output )	delete wavelength_output;

		printf("[examples_sdk_device_spectrum] std::exception happed !!\n");
		return NSP_RETURN_VALUE_FAILURE; 
	}
}