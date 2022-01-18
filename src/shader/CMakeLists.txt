add_library(shader STATIC shader.cpp)

add_library(oglt::shader ALIAS shader)

target_link_libraries(shader 
                      glm)

          