#ifndef	__NSP_ERROR_CODES_H__
#define	__NSP_ERROR_CODES_H__

// NSP API and SDK functions returns a value 
//		for success, unknown or failure or exception codes
#define	NSP_RETURN_VALUE_UNKNOWN				0
#define	NSP_RETURN_VALUE_SUCCESS				1
#define	NSP_RETURN_VALUE_FAILURE				-1
#define	NSP_RETURN_VALUE_NO_MATCHED_SENSOR		-2
#define	NSP_RETURN_VALUE_NO_MATCHED_CAL_DATA	-3

//!define error code for NSP API/SDK 
enum NSP_ERROR_CODE{
	cc_ec_start_code = 0,

	//GENERAL ERROR
	cc_ec_fail = -1, //failed for undefined reasons 
	cc_ec_undefined_fail = 0, //failed for undefined reasons 
	cc_ec_success = 1, //success
	cc_ec_memory_is_null,

	/* 
	DEVICE (SENSOR) INTERFACE LAYER ERROR
	*/
	cc_ec_no_device_in_system,
	cc_ec_fail_to_connect_device,
	cc_ec_fail_to_create_device_obj,
	cc_ec_fail_to_initialize_device, 
	cc_ec_device_object_is_null,
	cc_ec_sensor_id_is_empty,
	cc_ec_fw_recv_timeout,

	/*
	SPECTRAL COMMAND LAYER ERROR 
	For these errors, check for bugs in the message protocol implementation, usage of the functions
	*/
	cc_ec_fail_to_create_core_spectrum_obj,
	cc_ec_fail_to_initialize_core_spectrum_obj, 
	cc_ec_fail_to_load_sensor_cal_data,
	cc_ec_fail_to_add_sensor_to_active_sensor_list,
	cc_ec_sensor_cal_data_is_null,
	cc_ec_sensor_cal_for_input_sensor_id_is_not_valid,
	cc_ec_spectrum_core_object_is_null,
	cc_ec_memory_for_spectrum_data_buffer_is_null,
	cc_ec_memory_for_wavelength_data_buffer_is_null,
	cc_ec_filter_buffer_is_null,
	cc_ec_filter_data_is_nan,
	cc_ec_background_buffer_is_null,
	cc_ec_fail_to_calculate_spectrum,
	cc_ec_wrong_reply, 
	cc_ec_ill_defined_input, 
	cc_ec_ill_defined_output, 
	cc_ec_initialization_required,
	cc_ec_file_open_failed,

	/*
	SYNTHESIS LAYER ERROR
	These errors occured due to bugs in CrystalCore
	*/
	cc_ec_weights_matrix_allocation_fail,

	/*
	APPLICATION (COLOR) LAYER ERROR
	These errors occured due to bugs in application for color
	*/
	cc_ec_fail_to_create_color_object,
	cc_ec_fail_to_initialize_color_object,
	cc_ec_color_object_is_null,

	cc_ec_end_code,
};

#endif	// __NSP_ERROR_CODES_H__