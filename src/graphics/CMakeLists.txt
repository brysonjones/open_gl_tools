add_library(graphics STATIC graphics.cpp)

add_library(oglt::graphics ALIAS graphics)

target_link_libraries(graphics 
                      glad_libs)