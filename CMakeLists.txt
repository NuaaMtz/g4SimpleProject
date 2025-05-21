cmake_minimum_required(VERSION 2.6 FATAL_ERROR)

project(main)
set(CMAKE_CXX_STANDARD 17) # get all function
set(CMAKE_CXX_STANDARD_REQUIRED ON)


add_definitions(-DmyGEANT4RUN)
#add_definitions(-DmyROOTRUN)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_BUILD_TYPE Debug)

#set(ROOT_DIR "/home/mtzmo/sofeware/root")

find_package(ROOT REQUIRED COMPONENTS RIO Net Hist Tree Eve)


find_package(Geant4 REQUIRED vis_all ui_all)

include(${Geant4_USE_FILE})
include(${ROOT_USE_FILE})

file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)
file(GLOB includes ${PROJECT_SOURCE_DIR}/include/*.hh)


file(GLOB macro_file ${PROJECT_SOURCE_DIR}/*.mac)

file(COPY ${macro_file} DESTINATION ${PROJECT_BINARY_DIR})

file(GLOB data_file ${PROJECT_SOURCE_DIR}/*.dat)

#* 1. copy detector data
file(COPY ${data_file} DESTINATION ${PROJECT_BINARY_DIR})
include_directories(${PROJECT_SOURCE_DIR}/include ${ROOT_INCLUDE_DIRS})
#include_directories(${PROJECT_SOURCE_DIR}/include )


add_executable(main main.cc ${sources} ${includes} ${ROOT_LIBRARIES} )
target_compile_options(main PRIVATE -Wno-shadow)


target_link_libraries(main ${Geant4_LIBRARIES} ${ROOT_LIBRARIES}) 
add_custom_target(x_ray_image depends main)


















