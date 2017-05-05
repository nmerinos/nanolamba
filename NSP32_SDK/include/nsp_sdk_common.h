#ifndef	__NSP32_SDK_COMMON_H__
#define	__NSP32_SDK_COMMON_H__

// Interface to OpenCV
//#include "cv.h"
//#include "CrystalSpecific.h"
//#include "highgui.h"

#ifdef _WIN32
#include <windows.h>
#endif

#include <map>
#include <algorithm>
#include <cmath>
#include <deque>

#include <vector>
#include <string>
#include <iostream>
#include <fstream>

using namespace std;


#ifndef __APPLE__
#ifdef _WIN32
    #define EXPORT_DLL __declspec(dllexport)
    //! this is standard machine precision for 32 bit floats
    #define MACHINE_PRECISION    5.96e-08
#else
    #include <stdint.h>
    #define EXPORT_DLL  __attribute__((dllexport))
    #define HANDLE  int
    #define BOOL    bool
//    #define LARGE_INTEGER   int64_t
    #define DWORD   unsigned long 
    //! this is standard machine precision for 32 bit floats
    #define MACHINE_PRECISION    5.96e-08
#endif
#endif

#if defined(__linux) || defined(__APPLE__) || defined(__CYGWIN__)
#define EXPORT_DLL __attribute__((visibility("default")))
#endif

#include "nsp_base_types.h"

#define TIME( arg )		(((double) clock()) / CLOCKS_PER_SEC)

#ifndef	M_PI
#define	M_PI		3.141592653589793
#endif

#define	DEGREE_TO_RADIAN(degree) (degree*M_PI/180.0)
#define	RADIAN_TO_DEGREE(radian) (radian*180.0/M_PI)


#ifndef M_LOG10E
#define M_LOG10E    0.434294481903251827651
#endif

#define NUM_TO_STRING(x)						QString::number(x) //convert integers to string

#define N_(x) (x)
#define _(x) (x)
#ifndef __APPLE__
#define uchar unsigned char
#endif

#define SCALE_WIDTH   120
#define ENTRY_WIDTH     5
#define SCALE           1

//! Definitions for data normalization
#define	NORMALIZATION_MODE_NONE					0
#define	NORMALIZATION_MODE_0TO1					1
#define	NORMALIZATION_MODE_0TO100				2

//! Definitions for data conver mode (CrApolloSensorData.h)
#define	CONVERTMODE_NONE						0
#define	CONVERTMODE_IGNORE_BLANK_PIXEL			1
#define	CONVERTMODE_NORMALIZE_0TO1				2
#define	CONVERTMODE_NORMALIZE_0TO100			3

// Definition of the data info. size of data file
#define	DATAFILE_DATAINFO_SIZE					8	// data index, date, sensor type, sutter speed, average, data type, adc, gain
#define	SELECTED_WAVELENGTH_RANGE_VAL			150

//! Definitions for application initialization test
#define	APPINITSTATE_EVERYTHING_OK				0x00
#define	APPINITSTATE_DEVICE_NOTFOUND			0x01
#define	APPINITSTATE_SYSRESOURCE_LOW			0x02
#define	APPINITSTATE_FR_FILE_NOT_EXIST			0x04
#define	APPINITSTATE_DARK_FILE_NOT_EXIST		0x08
#define	APPINITSTATE_BACKGROUND_FILE_NOT_EXIST	0x10

// Definition for message
#define	MESSAGE_DEVICE_NOT_AVAILABLE	"Device is not available"

#define	TOOLBAR_ICON_SIZE	24
#define	TOOLBAR_BUTTON_SIZE	35

#define	MIN_SHUTTER_SPEED						1
#define	MAX_SHUTTER_SPEED						61534
#define	START_WAVELENGTH_FOR_CHART				300
#define	DEFAULT_FILTER_RESOLUTION				1	// nm

#define TO_RADIAN(degree)						((degree)*(M_PI/180.0f))
#define TO_DEGREE(radian)						((radian)*(180.0f/M_PI))

#define	DEFAULT_NUM_OF_FILTERS					1024

//
#define	START_WAVELENGTH_FOR_COLOR				400
#define	END_WAVELENGTH_FOR_COLOR				800

// Very small value
#define	DELTA_FOR_DIV_BY_ZERO					0.00000001

#define	CMF_START_WAVELENGTH					365
#define	CMF_END_WAVELENGTH						780
#define	CMF_WAVELENGTH_STEP						1		// nm

// Definitions for spectrum reconstruction algorithms
#define	SPEC_RECON_ALGOTYPE_NONE				-1
#define	SPEC_RECON_ALGOTYPE_NNLS_TIKHONOV		0
#define	SPEC_RECON_ALGOTYPE_NNLS_GCV			1
#define	SPEC_RECON_ALGOTYPE_NNLS_SC				2
#define	SPEC_RECON_ALGOTYPE_SYNTHESIS			3
			
typedef struct _SModelConfigForSVM
{
	int		svm_type;
	int		kernel_type;
	int		degree;
	double	NU;
	int		border_length;
	double	C;
	double	sigma;
	double	P;
	double	gamma;
	double	probability;

	_SModelConfigForSVM()
	{
		svm_type = 3;
		kernel_type = 0;
		degree = 2;
		NU = 0.5;
		border_length = 2;
		C = 1.0;
		sigma = 1.0;
		P = 0.00001;
		gamma = 1.0;
		probability = 0.95;
	}

} SModelConfigForSVM;

typedef struct _SModelConfigForANN
{
} SModelConfigForANN;


typedef struct _SSpectralData
{
public:
	int					wavelength;
	std::vector<int>	data;

	_SSpectralData()
	{
		Reset();
	}
	void Reset()
	{
		wavelength = 0;
		data.clear();
	}
} SSpectralData;

//! type defintions for different type of container (2D)
typedef std::map<std::string, std::vector<double> >	SpectralDataMap;
typedef std::map<int, std::vector<int> >	FilterDataInt2D;
typedef std::map<int, std::vector<float> >	FilterDataFloat2D;
typedef std::map<int, std::vector<double> >	FilterDataDouble2D;

//! definition for Filter Quality Score (FQS) enumeration
typedef enum FQS_TYPE
{
	FQS_TYPE_NONE = 0,
	FQS_TYPE_MSE,
	FQS_TYPE_RMSE,
	FQS_TYPE_CORR,
	FQS_TYPE_CORR2,
};

#define	THRESHOLD_FOR_QUALITY_SCORE		0.95

typedef enum RECON_ALGOTYPE
{
	RECON_ALGOTYPE_NONE = -1,
	RECON_ALGOTYPE_TNNLS_LCURVE,
	RECON_ALGOTYPE_TNNLS_GCV,
	RECON_ALGOTYPE_NNLS_SC,
	RECON_ALGOTYPE_NNLS_SCA_LCURVE,
	RECON_ALGOTYPE_NNLS_SCA_GCV,
	RECON_ALGOTYPE_NNLS_L1,
};

static char* pReconAlgoType[] =
{ "TNNLS-LCurve", "TNNLS-GCV", "NNLS-SC", "NNLS-SCA-LCurve", "NNLS-SCA-GCV", "NNLS-L1" };
 

#define	TOTAL_NUM_OF_SENSOR_DESIGN_TYPES	22
static char* g_pSensorDesignType[TOTAL_NUM_OF_SENSOR_DESIGN_TYPES] = {
	"None",
	"H31-1",
	"H31-2",
	"H31-3",
	"H32-FULL",
	"H32-CLR only",
	"H32-NIR only",
	"H32-PCM",
	"H4-C",
	"H4-PCM",
	"H4-ARC",
	"H42-C1",
	"H42-C2",
	"H42-C3",
	"H42-C4",
	"H42-C5_PCM1024",
	"H42-C5_PCM1054",
	"H61-C1",
	"H61-C2",
	"H61-C3",
	"H61-C4",
	"H61-C5",
};


typedef struct SDataCollectPlan
{
	int	ss_start;
	int	ss_end;
	int	ss_step;
	int	average;

	SDataCollectPlan()
	{
		ss_start = 100;
		ss_end = 10000;
		ss_step = 100;
		average = 1;
	}
} SDataCollectPlan;

typedef struct SDataProcessPlan
{
	bool	use_smooth;
	int		algo_type;
	int		func_order;
	int		window_size;
	int		data_type;

	SDataProcessPlan()
	{
		use_smooth = false;
		algo_type = 1;
		func_order = 1;
		window_size = 2;
		data_type = 1;
	}
} SDataProcessPlan;

//////////////////////////////////////////////////////////////////////
#define	SENSORTYPE_UNKNOWN	"unknown";

typedef enum
{
	FilterType_Unknown = 0,
	FilterType_SF_Ver1_1A,	// 2011.12
	FilterType_SF_Ver1_2A,
	FilterType_SF_Ver1_3A,
	FilterType_SF_Ver2_1A,	// 2012.06
	FilterType_SF_Ver2_2A,
	FilterType_SF_Ver2_3A,
	FilterType_TotalNum,
} eFilterType;

typedef enum
{
	AcqDataType_Unknown = 0,
	AcqDataType_Raw,
	AcqDataType_Spec,
	AcqDataType_Dark,
	AcqDataType_Ref,
}eAcqDataType;

typedef struct SDataAcqCondition
{
	int						deviceid;		// device id
	int						datasize;		// filter buffer size (default: 1024)
	std::string				sensortype;		// sensor info
	int						adc;			// adc value
	int						gain;			// gain value
	int						ss;				// shutter speed
	int						average;		// # averages
	int						frames;			// # frames
	bool					append;			// flag for append to list
	eAcqDataType			datatype;		// acquired data type
	bool					validpixelonly;	// acquire valid pixel only
	bool					normalized;		// acquire and normalize filter data
	bool					hdr;			// flag for HDR function
	int						hdrscale;		// scale factor for HDR
	bool					useAE;			// flag for utilizing AE(auto-exposure function)
	bool					ignoreOutliers;	//
	int						pixelBinningMode;	//
	int						darkcorrectionMode;		// dark noise level

	SDataAcqCondition()
	{
		reset();
	}

	SDataAcqCondition(int _ss, int _average)
	{
		reset();
		ss = _ss;
		average = _average;
	}

	void set_device_index(int device_index) { deviceid = device_index; }


	void reset()
	{
		deviceid		= 0;
		datasize		= 1024;	// 32x32
		sensortype		= SENSORTYPE_UNKNOWN;
		adc				= 132;
		gain			= 1;
		ss				= 250;
		average			= 1;
		frames			= 1;
		append			= true;
		datatype		= AcqDataType_Raw;
		validpixelonly	= true;
		normalized		= false;
		hdr				= false;
		hdrscale		= 1;
		useAE			= false;
		ignoreOutliers	= false;
		pixelBinningMode = 0;	// pixel binning is not used
		darkcorrectionMode		= 4;
	}
}SDataAcqCondition; 

typedef struct SOneFilterData
{
	std::string				date;		// time stamp
	std::vector<double>		raw;		// raw filter data
	std::vector<double>		spec;		// spectrum data
	SDataAcqCondition		condition;	// acqusition condition

	SOneFilterData()
	{
		reset();
	}

	void reset()
	{
		date.clear();
		raw.clear();
		spec.clear();
		condition.reset();
	}
} SOneFilterData;


typedef struct SOneSpecData
{
	std::string				sensor_id;		// sensor ID
	std::string				date;			// time stamp
	std::vector<double>		raw;			// raw filter data
	std::vector<double>		spec;			// spectrum data
	std::vector<double>		wavelength;		// wavelength data
	int						shutter_speed;	// shutter speed
	double					exposure_time;	// exposure time

	SOneSpecData()
	{
		reset();
	}

	void reset()
	{
		sensor_id.clear();
		date.clear();
		raw.clear();
		spec.clear();
		wavelength.clear();
		shutter_speed = 0;
		exposure_time = 0;
	}
} SOneSpecData;

typedef	std::vector<std::vector<double> >	SDoubleArray2D;

// filter measurement data for synthesis
typedef struct _SFilterRefData
{
	SDoubleArray2D			gray_filterout;			// <27x739 double>
	SDoubleArray2D			setWRGB_filterout;		// <4x739 double>
	SDoubleArray2D			allSamples_filterout;	// <127x739 double>
	std::string				data;					// 'Gray & Color samples'
	std::string				sensorType;				// 'H3_70'
	double					SHUTTER_SPEED;			// 55
	double					AVERAGES;				// 20
	double					satValue;				// 4095
	std::string				date;					// 12-Sep-2013'
	
	_SFilterRefData()
	{
		Reset();
	}

	void SetGrayData(SDoubleArray2D& dataIn) { gray_filterout = dataIn; }
	void SetWRGBData(SDoubleArray2D& dataIn) { setWRGB_filterout = dataIn; }
	void SetColorData(SDoubleArray2D& dataIn) { allSamples_filterout = dataIn; }
	void SetAverages(unsigned int iIn) { AVERAGES = iIn; }
	void SetShutterSpeed(unsigned int iIn) { SHUTTER_SPEED = iIn; }
	void SetSensorType(std::string& strIn) { sensorType = strIn; }
	void SetDate(std::string& strIn) { date = strIn; }
	void SetDataType(std::string& strIn) { data = strIn; }

	SDoubleArray2D& GetGrayData() { return gray_filterout; }
	SDoubleArray2D& GetWRGBData() { return setWRGB_filterout; }
	SDoubleArray2D& GetColorData() { return allSamples_filterout; }
	unsigned int GetAverages() { return (unsigned int)AVERAGES; }
	unsigned int GetShutterSpeed() { return (unsigned int)SHUTTER_SPEED; }
	std::string& GetSensorType() { return sensorType; }
	std::string& GetDate() { return date; }
	std::string& GetDataType() { return data; }

	void Reset()
	{
		gray_filterout.clear();
		setWRGB_filterout.clear();
		allSamples_filterout.clear();
		data			= "Gray & Color samples";
		sensorType		= "Unknown";
		SHUTTER_SPEED	= 5;
		AVERAGES		= 20;
		satValue		= 4095;
		date			= "unknown"; //nsp_utils_interface::GetTimeStampSimple();
	}
}SFilterRefData;

// spectrum measurement data with the reference devices (USB4000, apollo, OL731, i1Pro, Admesy, ...)
typedef struct _SSpecRefData
{
	SDoubleArray2D			spec_WRGB;				// <4x36 double>
	SDoubleArray2D			spec_gray;				// <27x36 double>
	SDoubleArray2D			spec_allSamples;		// <154x36 double>
	std::string				monitor;				// 'LG_IPS236'
	std::string				date;					// 12-Sep-2013'
	
	_SSpecRefData()
	{
		Reset();
	}

	void SetWRGBData(SDoubleArray2D& dataIn) { spec_WRGB = dataIn; }
	void SetGrayData(SDoubleArray2D& dataIn) { spec_gray = dataIn; }
	void SetColorData(SDoubleArray2D& dataIn) { spec_allSamples = dataIn; }
	void SetDeviceType(std::string& strIn) { monitor = strIn; }
	void SetDate(std::string& strIn) { date = strIn; }

	SDoubleArray2D& GetWRGBData() { return spec_WRGB; }
	SDoubleArray2D& GetGrayData() { return spec_gray; }
	SDoubleArray2D& GetColorData() { return spec_allSamples; }
	std::string& GetDeviceType() { return monitor; }
	std::string& GetDate() { return date; }

	void Reset()
	{
		spec_WRGB.clear();
		spec_gray.clear();
		spec_allSamples.clear();
		monitor		= "Unknown";
		date		= "unknown"; //nsp_utils_interface::GetTimeStampSimple();
	}
}SSpecRefData;

// spectrum measurement data with the reference devices (USB4000, apollo, OL731, i1Pro, Admesy, ...)
typedef struct _SOL731Data
{
	std::vector<double>		resolution;				// <1x153 double>
	double					shutter_speed;			// 1
	std::vector<double>		filter_data;			// <1x153 double>
	std::string				filter_device;			// 'OL731'
	double					saturation;				// 1
	double					zero;					// 0
	std::vector<double>		filter_data_wavelength;	// []
	double					dark_noise;				// 1.1790e-06
	double					slit_size;				// 10
	std::string				comments;				// 'HPK measurement'
	std::string				location;				// 'Korea'
	double					version;				// 1.1500
	std::string				id;						// '201449-1517_'
	double					monochromator_gain;		// 8.3000

	_SOL731Data()
	{
		Reset();
	}

	void Reset()
	{
		resolution.clear();
		shutter_speed				= 1;
		filter_data.clear();			
		filter_device				= "OL731";
		saturation					= 1.0;
		zero						= 0.0;
		filter_data_wavelength.clear();	
		dark_noise					= 1.1790e-06;
		slit_size					= 10.0;
		comments					= "HPK measurement";
		location					= "unknown";//nsp_utils_interface::GetLocale();
		version						= 1.1500;
		id							= "2";
		monochromator_gain			= 8.3000;
	}
}SOL731Data;

// spectrum measurement data with the reference devices (USB4000, apollo, OL731, i1Pro, Admesy, ...)
typedef struct _SApolloData
{
	std::string				date;					// '2015-01-28 01:53:47.000Z'
	std::string				sensor_id;				// 'Y8585-1-10-17-0'
	double					adc_range;				// 132
	double					shutter_speed;			//
	//std::map<std::string, std::vector<OL490PeakInfo> > sequence_data;
	std::string				sequence_data_path;		// data path for sequence data
	SDoubleArray2D			filter_data;			//
	std::vector<double>		dark_noise;				// 
	std::vector<double>		wavelength;				// 
	std::string				source_type;			// 'Mono', 'OL490'


	_SApolloData()
	{
		Reset();
	}

	void Reset()
	{
		date						= "2015-01-28 01:53:47.000Z";
		sensor_id					= "Y8585-1-10-17-0";
		adc_range					= 132;
		shutter_speed				= 1;
		sequence_data_path			= "";
		filter_data.clear();			
		dark_noise.clear();
		wavelength.clear();
		source_type					= "OL490";
	}
}SApolloData;

//
/*
			AVERAGES
			date
			measurand_filters
			dark_filterout_1st
			exposure_time_dk1
			integration_DN_dk1
			dark_filterout_2nd
			exposure_time_dk2
			integration_DN_dk2
			filterout
			dark_filterout
			exposure_time
			integration_DN
			ModeIndex
			stdData
			sensorType
			device
*/
typedef struct _SFilterMeasurementData
{
	std::string							date;					// '03-Jul-2015'
	int									AVERAGES;				// 40
	std::vector<double>					measurand_filters;		// <1x824 double>
	std::vector<double>					dark_filterout_1st;		// <1x824 double>
	double								exposure_time_dk1;		// 5.4080
	int									integration_DN_dk1;		// 30
	std::vector<double>					dark_filterout_2nd;		// <1x824 double>
	double								exposure_time_dk2;		// 5.4080
	int									integration_DN_dk2;		// 30
	std::map<int, std::vector<double> >	filterout;				// <10x824 double>
	std::map<int, std::vector<double> >	temporal_filterout;		// <10x824 double>
	std::map<int, std::vector<double> >	dark_filterout;			// <10x824 double>
	std::vector<double>					exposure_time;			// <1x10 double>
	std::vector<double>					integration_DN;			// <1x10 int>
	int									ModeIndex;				// 2
//	std::vector<double>					stdData;				// <1x824 double>
	std::string							sensorType;				// 'Y8585-1-18-16-0'
	std::string							device;					// 'Dark_SS30_Hot'

	_SFilterMeasurementData()
	{
		reset();
	}

	void reset()
	{
		date.clear();				
		AVERAGES				= 0;
		measurand_filters.clear();
		dark_filterout_1st.clear();
		exposure_time_dk1		= 0;
		integration_DN_dk1		= 0;
		dark_filterout_2nd.clear();
		exposure_time_dk2		= 0;
		integration_DN_dk2		= 0;
		filterout.clear();
		temporal_filterout.clear();
		dark_filterout.clear();
		exposure_time.clear();
		integration_DN.clear();
		ModeIndex				= 0;
//		stdData.clear();	
		sensorType.clear();
		device.clear();
	}
}SFilterMeasurementData;

typedef struct _OOIrradDataFileInfo
{
	std::string		Timestamp;
	std::string		Spectrometer;
	std::string		Lamp_SN;
	int				Integ_Time;
	int				Frame_average;
	int				Boxcar;
	double			Fiber_size;	// micron
}OOIrradDataFileInfo;

typedef struct _OOIrradData
{
	double	wavelength;
	double	power;		// uJoule/count
}OOIrradData;


typedef struct _SRefData
{
	std::string	strCreatedDate;
	std::string	strInstrument;
	int			iStartWL;
	int			iEndWL;
	int			iWLStep;

	std::vector<double>	SpectrumData;
	std::vector<int>	Wavelengths;

	std::vector<int>	WavelengthList;
	std::vector<int>	BandwidthList;
	std::vector<int>	IntensityList;
	
	_SRefData()
	{
		reset();
	}

	void reset()
	{
		strCreatedDate.clear();
		strInstrument.clear();
		
		iStartWL = 0;
		iEndWL = 0;
		iWLStep = 0;
		SpectrumData.clear();
		Wavelengths.clear();

		WavelengthList.clear();
		BandwidthList.clear();
		IntensityList.clear();
	}

}SRefData;

//---------------------------------------------------------------------
typedef struct _SSensorLocInTray
{
	double		orig_x;			// x coordinate of stage origin
	double		orig_y;			// y coordinate of stage origin
	int			slot_index;		// slot index in the sensor tray
	int			sensor_index;	// sensor index on the sensor tray
	std::string	sensor_id_str;	// sensor ID (string)
	double		x;				// tray loc: x-coordinate
	double		y;				// tray loc: y-coordinate
	int			row;			// tray loc: row
	int			col;			// tray loc: col

	_SSensorLocInTray()
	{
		orig_x			= 0.0;
		orig_y			= 0.0;
		slot_index		= -1;
		sensor_index	= -1;
		x				= 0.0;
		y				= 0.0;
		row				= -1;
		col				= -1;
	}
}SSensorLocInTray;

typedef	std::vector<SSensorLocInTray>	SSensorTray1D;
typedef std::vector<SSensorTray1D >	SSensorTray2D;

typedef struct _SSensorIDLocMapData
{
	std::string						system;
	std::string						date;
	int								num_axis;		// 
	std::vector<SSensorLocInTray>	sensor_loc;

	_SSensorIDLocMapData()
	{
		Reset();
	}

	void Reset()
	{
		system			= "unknown";
		date			= "";
		num_axis		= 1;
		sensor_loc.clear();
	}
}SSensorIDLocMapData;

typedef struct _SSensorTrayInfoData
{
	std::string						date;
	std::string						system;
	std::string						location;
	double							total_sensors;
	double							rows;
	double							cols;
	double							orig;
	double							row_interval;
	double							col_interval;
	double							threshold;

	std::vector<double>				sensor_pos;
	std::vector<double>				valid_slots;
	std::vector<double>				sensor_order;

	_SSensorTrayInfoData()
	{
		Reset();
	}

	void Reset()
	{
		date			= "2015-01-20";
		system			= "Alpha2-Mono";
		location		= "Korea";
		total_sensors	= 0;
		rows			= 0;
		cols			= 0;
		orig			= 0;
		row_interval	= 0;
		col_interval	= 0;
		threshold		= 0;

		sensor_pos.clear();
		valid_slots.clear();
		sensor_order.clear();
	}
}SSensorTrayInfoData;

typedef struct _STraySettings
{
	int		iLEDIntensity;
	int		iMatrixCol;
	int		iMatrixRow;
	double	iOrigX;
	double	iOrigY;
	double	iStepX;
	double	iStepY;
	int		iTestSS;
	int		iThresholdDN;

	double	iDistSensorToSensorX;
	double	iDistBoardToBoardX;
}STraySettings;

typedef struct _STitanPlan
{
	std::string		sensor_version;
	std::string		sensor_type;
	int				start_wavelength;
	int				end_wavelength;
	int				step_wavelength;
	int				adc_range;
	int				shutter_speed;
	int				frame_average;

	_STitanPlan()
	{
		Reset();
	}

	void Reset()
	{
		sensor_version.clear();
		sensor_type.clear();
		start_wavelength		= 340;
		end_wavelength			= 1100;
		step_wavelength			= 5;
		adc_range				= 132;
		shutter_speed			= 10;
		frame_average			= 10;

	}
}STitanPlan;


typedef struct _SSpectrumPeak
{
	double		wavelength;
	double		power;
	double		fwhm;
}SSpectrumPeak;

typedef std::vector<SSpectrumPeak>	SSpectrumContainer;

typedef struct _SDeviceInfo
{
	std::string		id;					// sensor ID
	std::string		product_name;		// spectrometer / multi-spectral imager.
	std::string		type;				// sensor type (VIS, FULL, NIR1, NIR2)
	double			wavelength_begin;	// sensor's left-most wavelength
	double			wavelength_end;		// sensor's right-most wavelength
	double			wavelength_left;	// wavelength region of interest(left)
	double			wavelength_right;	// wavelength region of interest(right)
	double			resolution;			// resolution
	int				average;			// frame average
	int				boxcar;				// boxcar size
	double			integ_time;			// integration time (ms)
	int				shutter_speed;		// shutter speed

	_SDeviceInfo()
	{
		reset();
	}

	void reset()
	{
		product_name = "apollo spectrometer";
		type = "-";
		wavelength_begin	= 0;
		wavelength_end		= 0;
		wavelength_left		= 0;
		wavelength_right	= 0;
		resolution			= 0;
		average				= 0;
		boxcar				= 0;
		integ_time			= 0;
		shutter_speed		= 0;
	}
}SDeviceInfo;

typedef struct _SLEDChannelInfo
{
	bool			available;
	bool			turn_on;
	int				channel_index;
	unsigned int	brightness;
	std::string		peak_wavelength;
	double			amphere;

	_SLEDChannelInfo()
	{
		Reset();
	}

	void Reset()
	{
		available			= false;
		turn_on				= true;
		channel_index		= 0;
		peak_wavelength		= "nan";
		brightness			= 0;
		amphere				= 0;
	}
}SLEDChannelInfo;

typedef std::vector<SLEDChannelInfo> SLEDChannels;

typedef struct _SLEDMatrixConfig
{
	std::string		date;
	std::string		manufacturer;
	std::string		source_type;
	int				num_channels;
	std::string		description;

	SLEDChannels	channels;

	_SLEDMatrixConfig()
	{
		reset();
	}

	void reset()
	{
		date = "-";
		manufacturer = "nanoLambda:Next_Eye";
		source_type = "LED";
		num_channels = 24;
		description = "Visible and NIR-ranges programmable light source";
		SLEDChannels::iterator it= channels.begin();
		for(; it!=channels.end();++it)
			(*it).Reset();
	}
} SLEDMatrixConfig;

// Jesse
// measurement data for calibration and performance test
typedef struct _SFilterDataCalibPerf
{
	double					measTime;				// 197.9263
	std::string				sensor_id;				// 'Y8585-1-18-19-0'
	std::string				sensor_type;			// 'VIS'
	std::string				device;					// 'LEDmixer_ch6'
	int						AVERAGES;				// 40
	int						ADC_RANGE_VAL;			// 246
	std::string				ADC_GAIN;				// '1x'
	std::string				date;					// '20-Oct-2016'
	std::vector<double>		measurand_filters;		// <824x1 double>

	std::vector<double>		filterout_raw_warmUp;	// <1x1024 double>
	int						integration_DN_warmUp;	// 144
	double					exposure_time_warmUp;	// 26.2976

	int						integration_DN;			// 144
	double					exposure_time;			// 26.2976

	int						integration_DN_SS1;		// 1
	double					exposure_time_SS1;		// 0.2144

	std::vector<double>		all_filter_out_raw;		// <1x1024 double>
	std::vector<double>		filterout;				// <1x824 double>
	std::vector<double>		filterout_SS1;			// <1x1024 double>

	 _SFilterDataCalibPerf()
	{
		Reset();
	}

	void Reset()
	{
		measTime					= 1;
		sensor_id					= "Y8585-1-18-19-0";
		sensor_type					= "VIS";
		device						= "HL2000_noFilter";
		AVERAGES					= 40;
		ADC_RANGE_VAL				= 246;
		ADC_GAIN					= "1x";
		date						= "20-Oct-2016";
		measurand_filters.clear();		// <824x1 double>

		filterout_raw_warmUp.clear();	// <1x1024 double>
		integration_DN_warmUp		= 144;
		exposure_time_warmUp		= 26.2976;

		integration_DN				= 144;
		exposure_time				= 26.2976;

		integration_DN_SS1			= 1;
		exposure_time_SS1			= 0.2144;

		all_filter_out_raw.clear();		// <1x1024 double>
		filterout.clear();				// <1x824 double>
		filterout_SS1.clear();			// <1x1024 double>
	}
}SFilterDataCalibPerf;


#define	USE_SINGLE_PRECISION_DATA_FOR_SENSOR	1
#undef USE_SINGLE_PRECISION_DATA_FOR_SENSOR
#ifdef USE_SINGLE_PRECISION_DATA_FOR_SENSOR
typedef float SENSOR_DATA_TYPE;
//#define	SENSOR_DATA_TYPE	float
#else
typedef		double		SDATA_TYPE;
typedef		float		SENSOR_DATA_TYPE;
//#define	SDATA_TYPE	double
#endif	// USE_SINGLE_PRECISION_DATA_FOR_SENSOR

#endif // __NSP32_SDK_COMMON_H__
