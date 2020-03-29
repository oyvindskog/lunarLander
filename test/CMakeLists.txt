add_executable(test_vector2d test_vector2d.cpp)

add_executable(test_game_object test_game_object.cpp)

target_link_libraries(test_vector2d ${GTEST_LIBRARIES} pthread vector2d)

target_link_libraries(test_game_object  ${GTEST_LIBRARIES} 
                                        pthread game_object 
                                        world ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES})
