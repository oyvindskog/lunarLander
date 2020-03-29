add_library(game game.cpp)

target_link_libraries(game LINK_PUBLIC ${SDL2_LIBRARIES}
                                       ${SDL2_IMAGE_LIBRARIES}
                                       world)

target_include_directories (game PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
