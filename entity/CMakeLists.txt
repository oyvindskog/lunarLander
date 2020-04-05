add_library(entity_manager entity.h 
                           entity_manager.cpp 
                           component.h 
                           body.cpp 
                           physics.cpp 
                           key_handler.cpp
                           collision.cpp)

target_link_libraries(entity_manager LINK_PUBLIC vector2d)

target_include_directories (entity_manager PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
