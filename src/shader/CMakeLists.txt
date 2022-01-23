add_library(shader STATIC shader.cpp)

add_library(oglt::shader ALIAS shader)

target_link_libraries(shader PUBLIC
                      glad_libs
                      glm::glm)
          
target_include_directories(shader PUBLIC
                           glm)