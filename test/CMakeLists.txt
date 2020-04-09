add_executable(test_vector2d test_vector2d.cpp)

target_link_libraries(test_vector2d ${GTEST_LIBRARIES} pthread vector2d)
