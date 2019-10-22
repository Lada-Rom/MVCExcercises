cmake_minimum_required(VERSION 3.12)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_property(GLOBAL PROPERTY PREDEFINED_TARGETS_FOLDER "cmake")

project(tolstenko_l_s)

include(cmake/build_prefix.cmake)

include_directories(prj.lab prj.thirdparty)

add_subdirectory(prj.lab)
add_subdirectory(prj.test)
