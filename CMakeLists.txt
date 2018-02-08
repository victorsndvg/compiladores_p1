#################################################################
# HEADER
#################################################################
CMAKE_MINIMUM_REQUIRED(VERSION 2.8.7)
PROJECT(lexlib C)

SET(${PROJECT_NAME}_VERSION 0.0.1)
SET(${PROJECT_NAME}_SOVERSION 1)
SET(LIB ${PROJECT_NAME})

#SET(CMAKE_VERBOSE_MAKEFILE TRUE)

#################################################################
# DEFINE PATHS
#################################################################

SET(SRC_PATH ${CMAKE_SOURCE_DIR}/src)
SET(LIB_PATH ${SRC_PATH}/lib)
SET(EXAMPLES_PATH ${SRC_PATH}/examples)
SET(TESTS_PATH ${SRC_PATH}/tests)
SET(INCLUDES_PATH ${SRC_PATH}/include)

#SET(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/CMake/Modules/")


#################################################################
# ADD INCLUDE DIRS
#################################################################

include_directories(${INCLUDES_PATH})

#################################################################
# BUILD PATHS
#################################################################

SET(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)
SET(TEST_OUTPUT_PATH ${PROJECT_BINARY_DIR}/test)
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
SET(CMAKE_Fortran_MODULE_DIRECTORY ${PROJECT_BINARY_DIR}/modules)
SET(THIRDPARTY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/thirdparty)
INCLUDE_DIRECTORIES(${CMAKE_Fortran_MODULE_DIRECTORY})

#################################################################
# CONFIGURATION TYPES & BUILD MODE
#################################################################

SET(CMAKE_CONFIGURATION_TYPES DEBUG RELEASE)
IF(NOT CMAKE_BUILD_TYPE)
  SET(CMAKE_BUILD_TYPE RELEASE CACHE STRING
      "Choose the type of build, options are: NONE DEBUG RELEASE"
      FORCE)

  SET_PROPERTY(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS NONE DEBUG RELEASE)
ENDIF(NOT CMAKE_BUILD_TYPE)

#################################################################
# List of external libraries
#################################################################

SET(EXT_LIBS  )

#################################################################
# Find packages
#################################################################

FOREACH(EXT_LIB ${EXT_LIBS})
    IF(DEFINED ${PROJECT_NAME}_ENABLE_${EXT_LIB} AND ${PROJECT_NAME}_ENABLE_${EXT_LIB} AND NOT ${EXT_LIB}_FOUND)
        FIND_PACKAGE( ${EXT_LIB} )
    
        IF (${EXT_LIB}_FOUND)
            ADD_DEFINITIONS(-DENABLE_${EXT_LIB})
            IF(IS_DIRECTORY ${${EXT_LIB}_INCLUDE_DIR})
               INCLUDE_DIRECTORIES(${${EXT_LIB}_INCLUDE_DIR})
            ENDIF()
            LINK_DIRECTORIES(${${EXT_LIB}_LIBRARIES})
        ENDIF()

    ELSEIF(DEFINED ${PROJECT_NAME}_ENABLE_${EXT_LIB} AND NOT ${PROJECT_NAME}_ENABLE_${EXT_LIB})
        UNSET(${EXT_LIB}_INCLUDES CACHE)
        UNSET(${EXT_LIB}_LIBS CACHE)
        UNSET(${EXT_LIB}_INCLUDE_DIR CACHE)
        UNSET(${EXT_LIB}_LIBRARIES CACHE)

    ELSE(NOT DEFINED ${PROJECT_NAME}_ENABLE_${EXT_LIB})
        FIND_PACKAGE( ${EXT_LIB} )

        IF (${${EXT_LIB}_FOUND})
           SET(NO_LIBS FALSE)
           OPTION(${PROJECT_NAME}_ENABLE_${EXT_LIB} "Enable/disable ${EXT_LIB} library" ON)
           ADD_DEFINITIONS(-DENABLE_${EXT_LIB})
           IF(IS_DIRECTORY ${${EXT_LIB}_INCLUDE_DIR})
               INCLUDE_DIRECTORIES(${${EXT_LIB}_INCLUDE_DIR})
           ENDIF()
            LINK_DIRECTORIES(${${EXT_LIB}_LIBRARIES})
        ELSE()
           OPTION(${PROJECT_NAME}_ENABLE_${EXT_LIB} "Enable/disable ${EXT_LIB} library" OFF)
           UNSET(${EXT_LIB}_INCLUDES CACHE)
           UNSET(${EXT_LIB}_LIBS CACHE)
           UNSET(${EXT_LIB}_INCLUDE_DIR CACHE)
           UNSET(${EXT_LIB}_LIBRARIES CACHE)
        ENDIF()
    ENDIF()
ENDFOREACH ()


#################################################################
# FFLAGS depend on the compiler and the build type
#################################################################

IF(CMAKE_BUILD_TYPE STREQUAL "DEBUG")
    ADD_DEFINITIONS(-DDEBUG)
ENDIF()

#################################################################
# ENABLE TESTING
#################################################################

ENABLE_TESTING()
INCLUDE(CTest)

#################################################################
# STATIC LIBRARIES
#################################################################
# Try to search first static libraries
IF(NOT ${BUILD_SHARED_LIBS})
    SET(CMAKE_FIND_LIBRARY_SUFFIXES ".a ${CMAKE_FIND_LIBRARY_SUFFIXES}")
ENDIF()

#################################################################
# ADD SOURCE SUBDIRS
#################################################################

ADD_SUBDIRECTORY(${LIB_PATH})
ADD_SUBDIRECTORY(${TESTS_PATH})
ADD_SUBDIRECTORY(${EXAMPLES_PATH})

