#ifndef	__NSP_BASE_TYPES_H__
#define	__NSP_BASE_TYPES_H__


#ifdef	BOOST_INCLUDED
	#include "boost/smart_ptr.hpp"	//For scoped pointer 
#endif

#ifdef __linux__
//#include <sys/io.h>
#endif
#include <stdio.h>
#include <fstream>
#ifdef _WIN32
#include <io.h>
#endif


#include <stdlib.h>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <algorithm>
#include <time.h>
#include <vector>
#include <bitset>
#include <limits>
#include <list>		//for list template in Spectrum_List
#include <map>

#include "alglib3/interpolation.h"

using namespace std;
using namespace alglib;

//! double-type 1D array for nano-filter data
typedef std::vector<double>				SFilterData1D;
//! double-type 2D array for nano-filter data set
typedef	std::vector<SFilterData1D >		SFilterData2D;
//! double-type 1D array for shutter speed data
typedef SFilterData1D					SShutterData1D;
//! double-type 2D array for shutter speed data set
typedef	std::vector<SFilterData1D >		SShutterData2D;
//! double-type 1D array as data container
typedef std::vector<double>				SDataArray1D;

//! Convert binary string to a numeric number (unsigned long)
#define	BIN_STRING_TO_NUM(str)	bitset<numeric_limits<unsigned long>::digits>(str).to_ulong()

//! definition to check current time based on system clock
#ifdef	_WIN32
#define TIME( arg ) (((double) clock()) / CLOCKS_PER_SEC)
#elif	__linux__
#include <sys/time.h>
#define TIME( arg ) 0.0
#endif

/*!
FLOAT64_TYPE defines the data type that will be used to represent decimal point numbers (for spectrum data) 
currently, only double (64 bit FLOAT64_TYPE) is supported 
*/
typedef double FLOAT64_TYPE; 
typedef float  FLOAT32_TYPE; 

//!FilterInfomration struct 
typedef struct {
	
	int num_filters;				// number of filters
	int	num_valid_filters;			// number of valid filters
	int num_resolution;				// number of resolution
	int interp_resolution;			// number of interpolation resolution
	FLOAT64_TYPE start_wavelength;	// starting wavelength of filter measurement
	FLOAT64_TYPE end_wavelength;		// ending wavelength of filter measurement
	FLOAT64_TYPE interval;			// interval between filter measurement in wavelength
	FLOAT64_TYPE start_wavelength_interp; // starting wavlength of interpolation data
	FLOAT64_TYPE end_wavelength_interp; // ending wavelength of interpolation data
	FLOAT64_TYPE interval_interp;		// interval between interpolation in wavelength
	FLOAT64_TYPE *filter_data_ptr;	// filter response (M matrix)
	FLOAT64_TYPE *interp_data_ptr;	// interpolation response (S matrix) 
	int *valid_filters;				// indices of valid filters (length num_filters)
	int algorithm;					// indicates which algorithm to use 
	int			sensorid_size;		// sensor id size
	char sensorid[15]; 
} FilterInformation; 


//Used to indicate filter output level  during spectrum reconstruction  
enum OutputLevel {
		good, //Filter output is just right
		saturated, //Filter output is saturated
		low //Filter output is low 
};

//! Modes for filter data correction (linearity, dark, ...)
#define	FILTER_DATA_CORRECTION_MODE_NONE			0	// no correction.
#define	FILTER_DATA_CORRECTION_MODE_ADVANCED		1	// filter data correction (default)
#define	FILTER_DATA_CORRECTION_MODE_ONBOARD			2	// filter data correction on embedded MCU or dedicated FPGA

//! Definitions for NaN and Inf.
#define	CRYSTAL_LIB_NAN			std::numeric_limits<FLOAT64_TYPE>::quiet_NaN()
#define	CRYSTAL_COLOR_NAN		-9999999 //std::numeric_limits<FLOAT64_TYPE>::quiet_NaN()
#define	CRYSTAL_LIB_POS_INF		std::numeric_limits<FLOAT64_TYPE>::infinity()
#define	CRYSTAL_LIB_NEG_INF		-std::numeric_limits<FLOAT64_TYPE>::infinity()
#define	NaN						std::numeric_limits<FLOAT64_TYPE>::quiet_NaN()
#define	INF						std::numeric_limits<FLOAT64_TYPE>::infinity()

//! Class definition for INT data pair of 'key' and 'val'.
class IntDataPair
{
  public:
	int		key;
	int		val;
};

//! Class definition for DOUBLE data pair of 'key' and 'val'.
class DoubleDataPair
{
  public:
	int		key;
	double	val;
};


//! enum definition for interpolation methods
enum eInterp_Methods
{
	eInterpMethod_Linear = 1,
	eInterpMethod_Cubic,
	eInterpMethod_Hermite,
	eInterpMethod_Akima,
	eInterpMethod_MAXINDEX,	// total count of items
};


enum eVectorShape
{
	eVectorShape_Gaussian = 1,
	eVectorShape_Triangle,
	eVectorShape_MultiGaussian,
	eVectorShape_Rectangle,
	eVectorShape_Sin2,
	eVectorShape_Random,
	eVectorShape_MexicanHat,
	eVectorShape_xyz,
	eVectorShape_illuminance,
	eVectorShape_i1,
	eVectorShape_MAXINDEX,	// total count of items
};

// Smoothing filter types
enum SmoothingAlgoType
{
	eSmoothingAlgoType_None = 0,
	eSmoothingAlgoType_SG,	// Savitzky-Golay
	eSmoothingAlgoType_Median,
	eSmoothingAlgoType_Mean,
	eSmoothingAlgoType_Gaussian,
};
//!----------------------------------------------------------
//! Struct definition for chromaticity(x, y)
typedef struct SChromaticity
{
	double	x;
	double	y;

	SChromaticity()
	{
		x = y = 0.0;
	}

	SChromaticity(double x_, double y_)
	{
		x = x_;
		y = y_;
	}
}SChromaticity;

//! Struct definition for INT-type RGB(r,g,b)
typedef struct SRGB {
    int		r;
    int		g;
    int		b;

	SRGB()
	{
		r = g = b = 0;
	}
	SRGB(int r_, int g_, int b_)
	{
		r = r_;
		g = g_;
		b = b_;
	}

}SRGB;

//! Struct definition for DOUBLE-type rgb color space
typedef struct SRGBf {
    double	r;
    double	g;
    double	b;
	SRGBf()
	{
		r = g = b = 0.0;
	}
	SRGBf(double r_, double g_, double b_)
	{
		r = r_;
		g = g_;
		b = b_;
	}
}SRGBf;

//! Struct definition for YUV color space
struct YUV {
    float	y;
    float	u;
    float	v;
};

//! Struct definition for XYZ color space
typedef struct SXYZ {
	double	x;
	double	y;
	double	z;

	SXYZ()
	{
		x = y = z = 0.0;
	}

	SXYZ(double x_, double y_, double z_)
	{
		x = x_;
		y = y_;
		z = z_;
	}
}SXYZ;

//! Struct definition for UVW color space
typedef struct SUVW {
	double	u;
	double	v;
	double	w;

	SUVW()
	{
		u = v = w = 0.0;
	}
	SUVW(double u_, double v_, double w_)
	{
		u = u_;
		v = v_;
		w = w_;
	}
}SUVW;


//! Struct definition for xyY color space
typedef struct SxyY {
	double	x;
	double	y;
	double	Y;

	SxyY()
	{
		x = y = Y = 0.0;
	}
	SxyY(double x_, double y_, double Y_)
	{
		x = x_;
		y = y_;
		Y = Y_;
	}
}SxyY;

//! Struct definition for Lab color space
typedef struct SLAB {
	double	L;
	double	a;
	double	b;

	SLAB()
	{
		L = a = b = 0.0;
	}
	SLAB(double L_, double a_, double b_)
	{
		L = L_;
		a = a_;
		b = b_;
	}

}SLAB;

//! Struct definition for LCH color space
typedef struct SLCH
{
	double	L;
	double	C;
	double	h;
} SLCH;

struct COLOR {
/*
	uchar	r;
	uchar	g;
	uchar	b;
*/
	float	x;
	float	y;
	float	z;
};

typedef	int								NspStatus;

#endif	// __NSP_BASE_TYPES_H__
