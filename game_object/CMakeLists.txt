add_library(game_object game_object.cpp)

target_link_libraries(game_object LINK_PUBLIC vector2d)

target_include_directories (game_object PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
