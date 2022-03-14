#----------------------------------------------------------------------------
# Setup the project
#
cmake_minimum_required(VERSION 3.16...3.21)
#set (CMAKE_CXX_STANDARD 11)

#
project(ENLegnSim)

#----------------------------------------------------------------------------
# Find Geant4 package, activating all available UI and Vis drivers by default
# You can set WITH_GEANT4_UIVIS to OFF via the command line or ccmake/cmake-gui
# to build a batch mode only executable
#
option(WITH_GEANT4_UIVIS "Build example with Geant4 UI and Vis drivers" ON)
option(GEANT4_USE_QT ON)
if(WITH_GEANT4_UIVIS)
#find_package(Geant4 REQUIRED ui_all vis_all)
find_package(Geant4 REQUIRED gdml ui_all vis_all)
else()
find_package(Geant4 REQUIRED)
endif()



#----------------------------------------------------------------------------
# Setup Geant4 include directories and compile definitions
# Setup include directory for this project
#
include(${Geant4_USE_FILE})

#----------------------------------------------------------------------------
# Find ROOT (required package)
#
list(APPEND CMAKE_PREFIX_PATH $ENV{ROOTSYS})
find_package(ROOT REQUIRED)
if(ROOT_FOUND)
  message(STATUS "ROOT ok !!!")
  message("Directory :" ${ROOT_USE_FILE})
endif()

# Include ROOT's CMake functions for dictionary generation
#  since root6.20, the file is renamed and included by default, so include
#  only when we find the *old* name
   if(EXISTS "${ROOT_DIR}/modules/RootNewMacros.cmake")
     include("${ROOT_DIR}/modules/RootNewMacros.cmake")
   endif()

include_directories(${PROJECT_SOURCE_DIR}/include
                    ${Geant4_INCLUDE_DIR}
                    ${ROOT_INCLUDE_DIRS})

#----------------------------------------------------------------------------
# Locate sources and headers for this project
# NB: headers are included so they will show up in IDEs


set(PROJECT_SRC
	${CMAKE_CURRENT_SOURCE_DIR}/src/Geometry.cc
	${CMAKE_CURRENT_SOURCE_DIR}/src/ENLegnSimEventAction.cc
	${CMAKE_CURRENT_SOURCE_DIR}/src/ENLegnSimVisManager.cc
	${CMAKE_CURRENT_SOURCE_DIR}/src/ENLegnSimMaterials.cc
	${CMAKE_CURRENT_SOURCE_DIR}/src/ENLegnSimPhysics.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/src/ENLegnSimGeometry.cc
	${CMAKE_CURRENT_SOURCE_DIR}/src/ENLegnSimPrimaryGeneratorAction.cc
	${CMAKE_CURRENT_SOURCE_DIR}/src/ENLegnSimRunAction.cc
	${CMAKE_CURRENT_SOURCE_DIR}/src/ENLegnSimSteppingAction.cc
    )

set(PROJECT_HEADER

	${CMAKE_CURRENT_SOURCE_DIR}/include/Geometry.hh
	${CMAKE_CURRENT_SOURCE_DIR}/include/ENLegnSimEventAction.hh
	${CMAKE_CURRENT_SOURCE_DIR}/include/ENLegnSimVisManager.hh
	${CMAKE_CURRENT_SOURCE_DIR}/include/ENLegnSimGeometry.hh
	${CMAKE_CURRENT_SOURCE_DIR}/include/ENLegnSimMaterials.hh
	${CMAKE_CURRENT_SOURCE_DIR}/include/ENLegnSimPhysics.hh
	${CMAKE_CURRENT_SOURCE_DIR}/include/ENLegnSimPrimaryGeneratorAction.hh
	${CMAKE_CURRENT_SOURCE_DIR}/include/ENLegnSimRunAction.hh
	${CMAKE_CURRENT_SOURCE_DIR}/include/ENLegnSimSteppingAction.hh
    )

#----------------------------------------------------------------------------
# Add the executable, and link it to the Geant4 libraries
#
add_executable(ENLegnSim ENLegnSim.cc ${PROJECT_HEADER} ${PROJECT_SRC})
#
target_link_libraries(ENLegnSim ${Geant4_LIBRARIES} ${ROOT_LIBRARIES} )

#link_directories( ${ROOT_LIBRARY_DIR} )

#----------------------------------------------------------------------------
# Install the executable to 'bin' directory under CMAKE_INSTALL_PREFIX
#
set(EXECUTABLE_OUTPUT_PATH  ${CMAKE_CURRENT_SOURCE_DIR}/bin)
install(TARGETS ENLegnSim DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/bin)
#install(TARGETS ENLegnSim DESTINATION ../bin)
message("Directory :" ${CMAKE_CURRENT_SOURCE_DIR}/bin)
