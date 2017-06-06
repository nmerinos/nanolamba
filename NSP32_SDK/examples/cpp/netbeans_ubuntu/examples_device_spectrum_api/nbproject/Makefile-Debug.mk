#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=GNU-Linux-x86
CND_DLIB_EXT=so
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/examples_device_spectrum_api.o \
	${OBJECTDIR}/examples_devices_spectrum_api.o \
	${OBJECTDIR}/main.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=-L../../../../lib/ubuntu -lcrystalbase -lcrystalbox -lcrystalcore -lcrystalport -lgsl -lgslcblas -lusb-1.0

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/examples_device_spectrum_api

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/examples_device_spectrum_api: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/examples_device_spectrum_api ${OBJECTFILES} ${LDLIBSOPTIONS} -lrt -pthread

${OBJECTDIR}/examples_device_spectrum_api.o: examples_device_spectrum_api.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../../../../include/3rd_party/alglib3 -I../../../../include/3rd_party -I../../../../include -I../../../../include/base -I../../../../include/device -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/examples_device_spectrum_api.o examples_device_spectrum_api.cpp

${OBJECTDIR}/examples_devices_spectrum_api.o: examples_devices_spectrum_api.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../../../../include/3rd_party/alglib3 -I../../../../include/3rd_party -I../../../../include -I../../../../include/base -I../../../../include/device -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/examples_devices_spectrum_api.o examples_devices_spectrum_api.cpp

${OBJECTDIR}/main.o: main.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../../../../include/3rd_party/alglib3 -I../../../../include/3rd_party -I../../../../include -I../../../../include/base -I../../../../include/device -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main.o main.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/examples_device_spectrum_api

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
