cmake_minimum_required(VERSION 3.14)
project(cercle LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

find_package(SFML REQUIRED COMPONENTS graphics window system)
find_package(pugixml REQUIRED)

include_directories(
    	header
)

add_executable(circle main.cpp 
                     cpp_dir/graphica.cpp 
                     cpp_dir/logica.cpp 
                     cpp_dir/readfile.cpp)

target_link_libraries(circle sfml-graphics pugixml)
