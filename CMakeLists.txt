cmake_minimum_required(VERSION 3.15.0)
project (OpenGLTools)
set(CMAKE_BUILD_TYPE Release)
set (CMAKE_CXX_STANDARD 17)
include(FetchContent)

enable_testing()

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

FetchContent_Declare(
  glm_repo
  GIT_REPOSITORY https://github.com/g-truc/glm.git
  GIT_TAG        master
)
FetchContent_MakeAvailable(glm_repo)
include_directories(${glm_repo_SOURCE_DIR})

FetchContent_Declare(
  glad_repo
  GIT_REPOSITORY https://github.com/Dav1dde/glad.git
  GIT_TAG        master
)
FetchContent_MakeAvailable(glad_repo)

FetchContent_Declare(
  linmath_repo
  GIT_REPOSITORY https://github.com/datenwolf/linmath.h.git
  GIT_TAG        master
)
FetchContent_MakeAvailable(linmath_repo)
include_directories(${linmath_repo_SOURCE_DIR})

add_subdirectory(src)
include_directories(src/shader)

# add_executable(main src/main.cpp)

# set(CMAKE_INCLUDE_CURRENT_DIR ON)
                    
# target_link_libraries(main 
#                       glfw ${GLFW_LIBRARIES} 
#                       OpenGL::GL ${CMAKE_DL_LIBS}
#                       oglt::window
#                       oglt::graphics
#                       glad_libs)

# set_target_properties(main
#     PROPERTIES
#     ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
#     LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
#     RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/Release"
# )



