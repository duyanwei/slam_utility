cmake_minimum_required(VERSION 3.5)
project(slam_utility)

# version
set(SLAM_UTILITY_VERSION_MAJOR 0)
set(SLAM_UTILITY_VERSION_MINOR 1)

# option
option(BUILD_TESTS "Build tests" OFF)

# compile flags
set(CMAKE_CXX_FLAGS "-std=c++11 -O3 -Wall -Wunused -Wextra")
# set(CMAKE_CXX_FLAGS "-std=c++11 -O3 -Wall -Werror -Wextra")
# set(CMAKE_CXX_FLAGS "-std=c++11 -O3 -Wall -Wno-unused-parameter -Wextra")

# set cmake path
# set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR}/cmake)

# packages
find_package(OpenCV 4 QUIET)
if(NOT OpenCV_FOUND)
   find_package(OpenCV 3 QUIET)
   if(NOT OpenCV_FOUND)
      message(FATAL_ERROR "OpenCV > 3.0 not found.")
   endif()
endif()
include_directories((${OpenCV_INCLUDE_DIRS}))

# headers
include_directories(include)

# add library
add_library(
    ${PROJECT_NAME} 
    SHARED 
    src/degeneracy_estimation/solution.cpp
    src/data_provider/data_provider_EuRoC.cpp
    src/camera/undistorter.cpp
    # NAMESPACE 
    # ${PROJECT_NAME}::
)

target_link_libraries(
    ${PROJECT_NAME}
    PUBLIC 
    ${OpenCV_LIBS}
)

# add test
if (BUILD_TESTS)
    enable_testing()
    add_subdirectory(test)
endif()