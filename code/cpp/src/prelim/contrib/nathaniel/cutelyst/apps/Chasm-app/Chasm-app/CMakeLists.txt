project(Chasm_app)

cmake_minimum_required(VERSION 3.16 FATAL_ERROR)

if(WIN32)
  if(MSVC)
    add_definitions(-D_SCL_SECURE_NO_WARNINGS)
    add_definitions(-D_CRT_SECURE_NO_DEPRECATE)
  endif()
endif()

find_package(Qt5 COMPONENTS Core Network REQUIRED)
find_package(Cutelyst3Qt5 REQUIRED)

# Auto generate moc files
set(CMAKE_AUTOMOC ON)

# As moc files are generated in the binary dir, tell CMake
# to always look for includes there:
set(CMAKE_INCLUDE_CURRENT_DIR ON)

file(GLOB_RECURSE TEMPLATES_SRC root/*)

add_subdirectory(src)

# tsi specific targets, acting like a "make install" ...
add_custom_target(copy-install ../copy-lib.sh)
add_custom_target(c-i make copy-install)
