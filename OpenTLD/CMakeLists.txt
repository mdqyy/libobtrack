# Open The CMake GUI
# specify the source directory and the binary directory
# press configure
# set CMAKE_INSTALL_PREFIX to the path where you want to install the program
# press configure
# check BUILD_WITH_QT if you want to build the program with a QT-Config GUI
# check GENERATE_DEB_PACKAGE if you want to build a debian package (only on Linux)
#
# UNIX Makefile:
# 1) go to the binary folder and type "make" to build the project
# 2) (optional) type "make install all" to install the files into the install
#    directory
# 3) (optional) type "make package" to create a package of the install folder
#    (.tgz file if GENERATE_DEB_PACKAGE=false, .deb file if GENERATE_DEB_PACKAGE=true)
#
# Microsoft Visual C++:
# 1) open the .sln file
# 2) change the mode to "Release" -> only Release is supported!
# 3) build the project "ALL_BUILD" to build the opentld project
# 4) build the project "INSTALL" to install the files into the install
#    directory
# 5) build the project "PACKAGE" to create an NSIS-installer (NSIS is required)


project(OpenTLD)

cmake_minimum_required(VERSION 2.6)

#-------------------------------------------------------------------------------
#version
set(TLD_VERSION_MAJOR 1)
set(TLD_VERSION_MINOR 2)
set(TLD_VERSION_PATCH 0)
set(TLD_VERSION ${TLD_VERSION_MAJOR}.${TLD_VERSION_MINOR}.${TLD_VERSION_PATCH})

#------------------------------------------------------------------------------
#build type
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING
        "Choose the type of build, options are: None Debug Release RelWithDebInfo MinSizeRel."
        FORCE)
endif(NOT CMAKE_BUILD_TYPE)

if(WIN32)
	add_definitions(-DLIBCONFIGXX_STATIC -DLIBCONFIG_STATIC) #Needed when linking libconfig statically
endif(WIN32)

if(APPLE)
	add_definitions(-DHAVE_XLOCALE_H)
endif(APPLE)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fopenmp -fPIC")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fopenmp -fPIC")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -lgomp")

find_package(OpenCV REQUIRED)

include_directories(src/cvblobs src/tld src/mftracker ${OpenCV_INCLUDE_DIRS})

#-------------------------------------------------------------------------------

file(GLOB cvblobs_SOURCES src/cvblobs/*.cpp)
file(GLOB cvblobs_HEADERS src/cvblobs/*.h)
file(GLOB mftracker_SOURCES src/mftracker/*.cpp)
file(GLOB mftracker_HEADERS src/mftracker/*.h)
file(GLOB tld_SOURCES src/tld/*.cpp)
file(GLOB tld_HEADERS src/tld/*.h)

SOURCE_GROUP(cvblobs FILES ${cvblobs_SOURCES} ${cvblobs_HEADERS})
SOURCE_GROUP(mftracker FILES ${mftracker_SOURCES} ${mftracker_HEADERS})
SOURCE_GROUP(tld FILES ${tld_SOURCES} ${tld_HEADERS})

add_library(OpenTLD ${cvblobs_SOURCES}
    ${cvblobs_HEADERS}
	${mftracker_SOURCES}
	${mftracker_HEADERS}
	${tld_SOURCES}
	${tld_HEADERS})

configure_file("${PROJECT_SOURCE_DIR}/OpenTLDConfig.cmake.in" "${PROJECT_BINARY_DIR}/OpenTLDConfig.cmake" @ONLY)

