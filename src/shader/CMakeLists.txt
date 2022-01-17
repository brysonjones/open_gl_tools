add_library(shader SHARED shader.cpp)

add_library(oglt::shader ALIAS shader)

target_link_libraries(shader 
                      glm)
          