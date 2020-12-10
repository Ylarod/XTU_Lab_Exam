cmake_minimum_required(VERSION 3.0.0)
project(ipTools VERSION 1.0.0)

#Generate the static library from the library sources
add_library(ipTools_library STATIC dataModel.cpp ipModel.cpp View.cpp Controller.cpp)

target_include_directories( ipTools_library PUBLIC ${PROJECT_SOURCE_DIR})

# Add an executable with the above sources
add_executable(ipTools main.cpp)

# link the new ipTools_library target with the ipTools target
target_link_libraries(ipTools PRIVATE ipTools_library)