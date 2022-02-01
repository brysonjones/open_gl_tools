add_library(graphics STATIC graphics.cpp
                            line.cpp)

add_library(oglt::graphics ALIAS graphics)

target_link_libraries(graphics 
                      line
                      glad_libs
                      glm::glm)

target_include_directories(graphics PUBLIC
                           glm)
