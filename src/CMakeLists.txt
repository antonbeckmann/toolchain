cmake_minimum_required(VERSION 2.8.9)
project(app)
add_subdirectory(cpr)
include_directories(${CPR_INCLUDE_DIRS})
file(GLOB app_SRC
  "*.hpp"
  "*.cpp"
)
add_executable(app ${app_SRC})
target_link_libraries(app ${CPR_LIBRARIES})
