# ref: https://stackoverflow.com/questions/8507723/how-to-start-working-with-gtest-and-cmake
# https://cmake.org/cmake/help/latest/module/ExternalProject.html

#------------------------------ GoogleTest -------------------------------------
include(ExternalProject)
ExternalProject_Add(
    gtest URL https://github.com/google/googletest/archive/release-1.10.0.zip
    PREFIX ${CMAKE_CURRENT_BINARY_DIR}/gtest
    INSTALL_COMMAND ""
)
ExternalProject_Get_Property(gtest SOURCE_DIR BINARY_DIR)
include_directories(${SOURCE_DIR}/include)
set(GTestLibs ${BINARY_DIR}/lib/libgtest.a ${BINARY_DIR}/lib/libgtest_main.a)

#---------------------------- macro definition ---------------------------------
macro(CompileTest node libs)
    add_executable(${node} ${node}.cpp)
    add_dependencies(${node} gtest)
    target_link_libraries(${node} PRIVATE ${libs})
    add_test(NAME ${node} COMMAND ${node})
endmacro()

#------------------------------ compile test -----------------------------------
set(libs ${PROJECT_NAME} ${GTestLibs} pthread)

CompileTest("test_data_provider_EuRoC" "${libs}")
CompileTest("test_stats" "${libs}")