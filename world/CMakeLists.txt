add_library(world world.cpp behavior.cpp)

target_link_libraries(world LINK_PUBLIC vector2d game_object entity_manager
                                        ${SDL_LIBRARIES} ${SDL_IMAGE_LIBRARIES})

target_include_directories (world PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
