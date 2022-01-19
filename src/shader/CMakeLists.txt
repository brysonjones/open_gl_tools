add_library(shader STATIC shader.cpp)

add_library(oglt::shader ALIAS shader)

target_link_libraries(shader 
                      glm)

target_include_directories(shader PUBLIC
                          ${glm_repo_SOURCE_DIR})


          