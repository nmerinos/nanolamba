// examples_device_spectrum_color_api.cpp : Defines the entry point for the console application.
// This console application is to show how programmer can create, use, and destroy of device object.
//
// (c) nanolamda 2012~2016

#include <stdio.h>
#include <stdlib.h>

#include "nsp_core_common.h"
#include "nsp_base_api.h"
#include "nsp_device_api.h"
#include "nsp_core_api.h"
#include "nsp_app_color_api.h"

#include "nsp_device_def.h"

/*
	Example: NSP32 device, spectrum and color APIs

	This example shows how user can use API to get raw filter data, spectrum data, and color info.
		1) acquire raw filter data from deivce
		2) reconstruct spectrum by spectrum API
		3) calculate color(X,Y,Z,x,y,z,R,G,B,cct) by color API
*/
extern char* g_sensor_cal_file_path;

int examples_device_spectrum_color_api(bool dump_to_file)
{
	int		current_device_index = 0;
	int		total_num_of_sensors = 0;
	int		return_value = 0;
	double	sensor_data_buf[SENSOR_DATA_SIZE];
	double	background_data_buf[SENSOR_DATA_SIZE];
	int		frame_averages = 50;

	try
	{
		char str_sensor_id[SENSOR_ID_STRING_LENGTH];
		char str_sensor_id2[SENSOR_ID_STRING_LENGTH];

		// open(connect) device (sensor)
		int ret_value = duConnect();
		if( ret_value <= 0 ){
			//char* error_msg = bsGetErrorString(ret_value);
			//printf("[examples_device_spectrum_color_api] Device is not connected.\n");
			throw nsp_base_exception(cc_ec_fail_to_connect_device);
		}
		// another function to have total count of device
		total_num_of_sensors = duGetTotalSensors();

		// get sensor ID
		duGetSensorID(str_sensor_id);
		
		// create Core Spectrum object for spectrum calculation
		if( csCreate() != NSP_RETURN_VALUE_SUCCESS ){
			throw nsp_base_exception(cc_ec_fail_to_create_core_spectrum_obj);
		}

		// add one sensor to active sensor list
		char	sensor_cal_file_path[1024];
		sprintf(sensor_cal_file_path, "./config/sensor_%s.dat", str_sensor_id);
		int total_count_of_active_sensors =	csRegister(sensor_cal_file_path);
		if( total_count_of_active_sensors == 0 ){
			throw nsp_base_exception(cc_ec_fail_to_add_sensor_to_active_sensor_list);
		}

		if( ret_value <= 0 )
			throw nsp_base_exception(cc_ec_fail_to_load_sensor_cal_data);

		// get sensor ID from sensor calibration data for matching.
		int id_size = csGetSensorID(str_sensor_id2);
		if( id_size <= 0 ){
			printf("[examples_device_spectrum_color_api] Error: sensor ID is not available in calibration data.\n");
			return NSP_RETURN_VALUE_FAILURE;
		}

		// check if sensor ID is matched between device and sensor(device) calibration data.
		if( strncmp(str_sensor_id, str_sensor_id2, SENSOR_ID_STRING_LENGTH) == 0  )
			printf("[examples_device_spectrum_color_api] Sensor ID is matched (%s <-> %s).\n", str_sensor_id, str_sensor_id2);
		else {
			printf("**************************************************************************************************************\n");
			printf("[examples_device_spectrum_color_api] Error: Sensor ID is NOT matched (%s <-> %s).\n", str_sensor_id, str_sensor_id2);
			printf("[examples_device_spectrum_color_api] Error: Spectrum (and color) data will not correct.\n");
			printf("[examples_device_spectrum_color_api] Solution: Get correct sensor calibration file for %s.\n", str_sensor_id);
			printf("**************************************************************************************************************\n");
		}

		// initialize 'application color' interface
		ret_value = acInitialize();
		if( ret_value <= 0 )
			throw nsp_base_exception(cc_ec_fail_to_initialize_color_object);

		// set sensor parameters for all sensors in the system.
		for(int i=0;i<total_num_of_sensors;i++){
			int	current_device_index = i;

			// activate a specific device(sensor)
			return_value = duActivateSensorWithIndex(current_device_index);
			if( return_value == cc_ec_undefined_fail )
				return (int)cc_ec_undefined_fail;

			// get sensor id of currently activated device(sensor)
			return_value = duGetSensorID(str_sensor_id);
			if( return_value == cc_ec_success )
				printf("[examples_device_spectrum_color_api] sensor index: %d, Sensor ID: %s\n", current_device_index, str_sensor_id);
			else
				memcpy(str_sensor_id, "unknown_ID", 10*sizeof(char));

			// activate sensor calibration data with sensor ID
			return_value = csActivateSensorWithID(str_sensor_id);	// sensor ID from physical sensor
			if( return_value == NSP_RETURN_VALUE_FAILURE )
				continue;	// just skip this sensor ID

			// get ADC settings info. from sensor calibration data.
			int	adc_gain = 0, adc_range = 0;
			csGetSensorParameters(&adc_gain, &adc_range);

			// change ADC settings of device
			duSetSensorParameters(adc_gain, adc_range);
		}

		for(int i=0;i<total_num_of_sensors;i++){
			int	current_device_index = i;

			/////////////////////////////////////////////////////////////////////////////////////////
			// Acquire raw filter data

			// activate a specific device(sensor)
			return_value = duActivateSensorWithIndex(current_device_index);
			if( return_value == cc_ec_undefined_fail )
				return (int)cc_ec_undefined_fail;

			// get sensor id of currently activated device(sensor)
			return_value = duGetSensorID(str_sensor_id);
			if( return_value == cc_ec_success )
				printf("[examples_device_spectrum_color_api] sensor index: %d, Sensor ID: %s\n", current_device_index, str_sensor_id);
			else
				memcpy(str_sensor_id, "unknown_ID", 10*sizeof(char));

			// get background data
			// set/change shutter speed of device(sensor)
			return_value = duSetShutterSpeed(1);
			
			// get one filter output (sensor data)
			return_value = duGetFilterData(background_data_buf, frame_averages);

			// activate sensor calibration data with sensor ID
			csActivateSensorWithID(str_sensor_id);	// sensor ID from physical sensor

			// set background data
			csSetBackground(background_data_buf);

			// get current shutter speed from device(sensor)
			// note: after sensor open (initialized), shutter speed is always 1.
			int old_shutter_speed = duGetShutterSpeed(); 
			int	new_shutter_speed = 100;
			if(1){
				// get valid filters except for monitoring filters
				int	num_of_valid_filters = csGetNumOfValidFilters();
				int* valid_filters = csGetValidFilters();

				// Get shutter speed with AE
				new_shutter_speed = duGetOptimalShutterSpeed(valid_filters, num_of_valid_filters);
				printf("[examples_device_spectrum_color_api] optimal SS by AE = %d\n", new_shutter_speed);
			}

			// set/change shutter speed of device(sensor)
			return_value = duSetShutterSpeed(new_shutter_speed);
			
		// convert shutter speed to exposure time (ms) for your reference.
			int	master_clock = NSP_DEVICE_MASTER_CLOCK;
			double	exposure_time_val = 0;
			return_value = duShutterSpeedToExposureTime(master_clock, new_shutter_speed, &exposure_time_val);
			printf("[examples_device_spectrum_color_api] current shutter speed: %d (exposure time = %.3f)\n", new_shutter_speed, exposure_time_val);

			// get one filter output (sensor data)
			return_value = duGetFilterData(sensor_data_buf, frame_averages);

			printf("[examples_device_spectrum_color_api] sensor data at SS = %d\n", new_shutter_speed);
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

				/////////////////////////////////////////////////////////////////////////////////////////
				// Calculate color
				double	X, Y, Z;
				double	r, g, b;
				double	x, y, z;
				double	cct;
				acCalculateColor(spectrum_data_out, wavelength_data_out, spectrum_data_size, &X, &Y, &Z, &r, &g, &b, &x, &y, &z, &cct);

				printf("[examples_app_color_api] spectrum to color:\n");
				printf("\t[X, Y, Z] = %lf, %lf, %lf\n", X, Y, Z);
				printf("\t[R, G, B] = %lf, %lf, %lf\n", r, g, b);
				printf("\t[x, y, Z] = %lf, %lf, %lf\n", x, y, z);
				printf("\t[CCT] = %lf\n", cct);

				// dump related information and data to CSV format file.
				if( dump_to_file == true ){
					////////////////////////////////////////////////////
					// saving spectrumdata to csv
					std::string outputFileName = "examples_device_spectrum_color_api_" + std::string(str_sensor_id) + "_result.csv";
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

						filestream << "Color information" << endl;
						filestream << "XYZ," << X << "," << Y << "," << Z << endl;
						filestream << "xyz," << x << "," << y << "," << z << endl;
						filestream << "RGB," << r << "," << g << "," << b << endl;
						filestream << "CCT," << cct << endl;
						filestream << endl;

						filestream.close();
					}
					printf("[examples_device_spectrum_color_api] Spectrum dump to \"%s\" -- done!\n", outputFileName.c_str());
				}
			}
			else{
				throw nsp_base_exception(cc_ec_fail_to_calculate_spectrum);
			}
		}

		// finalize spectrum API
		csDestroy();

		// initialize 'application color' interface
		acFinalize();

		// close(disconnect) device(sensor)
		duDisconnect();

		return NSP_RETURN_VALUE_SUCCESS;
	}
	catch(nsp_base_exception &e){
		csDestroy();
		acFinalize();
		duDisconnect();

		printf("[examples_device_spectrum_color_api] NSP_BASE_EXCEPTION happened: %s\n", e.what());
		return (int)-e.error_code; 
	}
	catch(...){
		csDestroy();
		acFinalize();
		duDisconnect();

		printf("[examples_device_spectrum_color_api] std::exception happed !!\n");
		return NSP_RETURN_VALUE_FAILURE;
	}
}