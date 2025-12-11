cmake_minimum_required(VERSION 3.16)
project(interceptor)

include_directories(inc/)
add_executable(main main.cpp src/Atmos.cpp src/Integrator.cpp src/Rhss.cpp)