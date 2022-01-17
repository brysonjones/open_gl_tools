add_library(shader SHARED shader.cpp)

add_library(oglt::shader ALIAS shader)

target_include_directories(shader PUBLIC
                           ${glm_repo_SOURCE_DIR})