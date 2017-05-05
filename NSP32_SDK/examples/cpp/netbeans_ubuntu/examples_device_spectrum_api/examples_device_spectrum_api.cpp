// examples_device_spectrum_api.cpp : Defines the entry point for the console application.
// This console application is to show how programmer can create, use, and destroy of device object.
//
// (c) nanolamda 2012~2017

#include <stdio.h>
#include <stdlib.h>

#include "nsp_core_common.h"
#include "nsp_device_api.h"
#include "nsp_core_api.h"

#include "nsp_device_def.h"

/*
	Example: apollo device and spectrum API

	This example shows how user can use API to get raw filter data and spectrum data.
		1) acquire raw filter data from deivce
		2) reconstruct spectrum by spectrum API
*/

int examples_device_spectrum_api(bool dump_to_file)
{
	int		current_device_index = 0;
	int		total_num_of_sensors = 0;
	int		frame_averages = 50;					// 50 frames are needed to have reliable/stable spectrum.
	int		new_shutter_speed = 150;				// user can change this for different illumination condition.
	double	sensor_data_buf[SENSOR_DATA_SIZE];		// raw sensor(filter) data
	double	background_data_buf[SENSOR_DATA_SIZE];	// background sensor data
	int		return_value = 0;

	try{
		char str_sensor_id[SENSOR_ID_STRING_LENGTH];
		char str_sensor_id2[SENSOR_ID_STRING_LENGTH];

		// open(connect) device (sensor)
		int	total_num_of_sensors = duConnect();
		if( total_num_of_sensors <= 0 ){
			printf("[examples_device_spectrum_api] Device is not connected.\n");
			return NSP_RETURN_VALUE_FAILURE;
		}

		// get sensor ID from physical device (sensor)
		duGetSensorID(str_sensor_id);
		
		// create Core Spectrum object for spectrum calculation
		if( csCreate() != NSP_RETURN_VALUE_SUCCESS ){
			throw "Fail to create Core Spectrum object.";
		}

		// add one sensor to active sensor list
		char	sensor_cal_file_path[1024];
		sprintf(sensor_cal_file_path, "./config/sensor_%s.dat", str_sensor_id);
		int total_count_of_active_sensors =	csRegister(sensor_cal_file_path);
		if( total_count_of_active_sensors == 0 ){
			throw "Fail to add one sensor to active sensor list.";
		}

		// get sensor ID from sensor calibration data for matching.
		int id_size = csGetSensorID(str_sensor_id2);
		if( id_size == 0 ){
			printf("[examples_device_spectrum_api] Error: sensor ID is not available in calibration data.\n");
		}

		// check if sensor ID is matched between device and sensor(device) calibration data.
		if( strncmp(str_sensor_id, str_sensor_id2, SENSOR_ID_STRING_LENGTH) == 0  )
			printf("[examples_device_spectrum_api] Sensor ID is matched (%s <-> %s).\n", str_sensor_id, str_sensor_id2);
		else {
			printf("**************************************************************************************************************\n");
			printf("[examples_device_spectrum_api] Error: Sensor ID is NOT matched (%s <-> %s).\n", str_sensor_id, str_sensor_id2);
			printf("[examples_device_spectrum_api] Error: Spectrum (and color) data will not correct.\n");
			printf("[examples_device_spectrum_api] Solution: Get correct sensor calibration file for %s.\n", str_sensor_id);
			printf("**************************************************************************************************************\n");
		}

		// get ADC settings info. from calibration data.
		int	adc_gain = 0, adc_range = 132;
		csGetSensorParameters(&adc_gain, &adc_range);

		// change ADC settings of device
		duSetSensorParameters(adc_gain, adc_range);

		// another function to have total count of device
		total_num_of_sensors = duGetTotalSensors();

		for(int i=0;i<total_num_of_sensors;i++){
			int	current_device_index = i;

			/////////////////////////////////////////////////////////////////////////////////////////
			// Acquire raw filter data

			// activate a specific device(sensor)
			return_value = duActivateSensorWithIndex(current_device_index);
			if( return_value == NSP_RETURN_VALUE_FAILURE || return_value == NSP_RETURN_VALUE_UNKNOWN )
				return NSP_RETURN_VALUE_FAILURE;

			// get sensor id of currently activated device(sensor)
			return_value = duGetSensorID(str_sensor_id);
			if( return_value == NSP_RETURN_VALUE_SUCCESS )
				printf("[examples_device_spectrum_api] sensor index: %d, Sensor ID: %s\n", current_device_index, str_sensor_id);
			else
				memcpy(str_sensor_id, "unknown_ID", 10*sizeof(char));

			// get background data
			// set/change shutter speed of device(sensor)
			return_value = duSetShutterSpeed(1);
			
			// get one filter output (sensor data)
			return_value = duGetFilterData(background_data_buf, frame_averages);

			// set background data
			csSetBackground(background_data_buf);

			// get current shutter speed from device(sensor)
			// note: after sensor open (initialized), shutter speed is always 1.
			int old_shutter_speed = duGetShutterSpeed(); 

			// set/change shutter speed of device(sensor)
			new_shutter_speed = 500;
			if(0){
				// Get shutter speed with AE
				int	num_of_valid_filters = csGetNumOfValidFilters();
				int* valid_filters = csGetValidFilters();
				new_shutter_speed = duGetOptimalShutterSpeed(valid_filters, num_of_valid_filters);
				printf("[examples_device_spectrum_api] optimal SS by AE = %d\n", new_shutter_speed);
			}

			return_value = duSetShutterSpeed(new_shutter_speed);
		
			// convert shutter speed to exposure time (ms) for your reference.
			int	master_clock = NSP_DEVICE_MASTER_CLOCK;
			double	exposure_time_val = 0;
			return_value = duShutterSpeedToExposureTime(master_clock, new_shutter_speed, &exposure_time_val);
			printf("[examples_device_spectrum_api] current shutter speed: %d (exposure time = %.3f)\n", new_shutter_speed, exposure_time_val);

			// get one filter output (sensor data)
			return_value = duGetFilterData(sensor_data_buf, frame_averages);
			printf("[examples_device_spectrum_api] sensor data at SS = %d\n", new_shutter_speed);
			for(int j=0;j<SENSOR_DATA_SIZE;j++){
				if( j != 0 && j % 15 == 0 )	printf("\n");
				printf("%*.2f, ", 7, sensor_data_buf[j]);
			}
			printf("\n");

			/////////////////////////////////////////////////////////////////////////////////////////
			// Calculate spectrum

			double	filter_data_in[SENSOR_DATA_SIZE];
			double	*spectrum_data_out = NULL;
			double	*wavelength_data_out = NULL;

			// use a sample data as input filter data.
			memset(filter_data_in, 0, sizeof(double)*SENSOR_DATA_SIZE);
			for(int i=0;i<SENSOR_DATA_SIZE;i++)
				filter_data_in[i] = sensor_data_buf[i];

			// get spectrum data size from sensor calibration data
			int		spectrum_data_size = csGetSpectrumLength();
			printf("[examples_spectrum_core_api] spectrum_data_size: %d\n", spectrum_data_size);

			// allocate memory for spectrum and wavelength data.
			spectrum_data_out = (double *)malloc(sizeof(double)*spectrum_data_size);
			if( spectrum_data_out == NULL )	throw "fail to allocate memory for spectrum data.";
			wavelength_data_out = (double *)malloc(sizeof(double)*spectrum_data_size);
			if( wavelength_data_out == NULL )	throw "fail to allocate memory for wavelength data.";

			// get spectrum data
			int ret_val = csCalculateSpectrum(filter_data_in, new_shutter_speed, spectrum_data_out, wavelength_data_out);
			if( ret_val == spectrum_data_size ){

				for(int i=0;i<spectrum_data_size;i++){
					if( i != 0 && i % 3 == 0 )	printf("\n");
					printf("%4.0f(nm) - %*.2f, ", wavelength_data_out[i], 7, spectrum_data_out[i]);
				}
				printf("\n");

				// dump related information and data to CSV format file.
				if( dump_to_file == true ){
					////////////////////////////////////////////////////
					// saving spectrumdata to csv
					std::string outputFileName = "examples_device_spectrum_api_" + std::string(str_sensor_id) + "_result.csv";
					fstream filestream;
					filestream.open(outputFileName.c_str(), ofstream::out);
					if (filestream.is_open() == true) {
						filestream << "Sensor ID, " << str_sensor_id << endl;

						filestream << "Raw filter data at SS=" << new_shutter_speed << endl;
						for (int i = 0; i < SENSOR_DATA_SIZE; i++) {
							filestream << sensor_data_buf[i];
							if (i != (SENSOR_DATA_SIZE - 1))
								filestream << ",";
						}
						filestream << endl;
						filestream << "Raw filter data at SS=" << 1 << endl;
						for (int i = 0; i < SENSOR_DATA_SIZE; i++) {
							filestream << background_data_buf[i];
							if (i != (SENSOR_DATA_SIZE - 1))
								filestream << ",";
						}
						filestream << endl;
						
						filestream << "Wavelength data" << endl;
						for (int i = 0; i < (int) spectrum_data_size; i++) {
							filestream << wavelength_data_out[i];
							if (i != (spectrum_data_size - 1))
								filestream << ",";
						}
						filestream << endl;
						filestream << "Spectrum data" << endl;
						for (int i = 0; i < (int) spectrum_data_size; i++) {
							filestream << spectrum_data_out[i];
							if (i != (spectrum_data_size - 1))
								filestream << ",";
						}
						filestream << endl;
						filestream.close();
					}
					printf("[examples_device_spectrum_api] Spectrum dump to \"%s\" -- done!\n", outputFileName.c_str());
				}
			}
		}

		// Destroy Core Spectrum Object
		csDestroy();

		// close(disconnect) device(sensor)
		duDisconnect();
		return NSP_RETURN_VALUE_SUCCESS;
	}
	catch(nsp_base_exception &e){
		csDestroy();
		duDisconnect();

		printf("[examples_device_spectrum_api] NSP_BASE_EXCEPTION happened: %s\n", e.what());
		return (int)-e.error_code; 
	}
	catch(...){
		csDestroy();
		duDisconnect();

		printf("[examples_device_spectrum_api] std::exception happed !!\n");
		return NSP_RETURN_VALUE_FAILURE;
	}
}