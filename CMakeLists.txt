cmake_minimum_required(VERSION 3.5)

project(game)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

# Locate GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

#find_package(SDL2_image REQUIRED)
include_directories(${SDL2_IMAGE_INCLUDE_DIRS})
include_directories(${SDL_INCLUDE_DIR}/SDL2)

add_subdirectory(test)

add_subdirectory(vector)

add_subdirectory(game_object)

add_subdirectory(world)

add_subdirectory(game)

# add the executable
add_executable(main main.cpp)

target_link_libraries(main LINK_PUBLIC game 
                                       ${SDL2_LIBRARIES}
                                       ${SDL2_IMAGE_LIBRARIES})

