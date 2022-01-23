cmake_minimum_required(VERSION 3.15.0)
project (oglt VERSION 1.0.0
                     DESCRIPTION "A library for OpenGL tools"
                     HOMEPAGE_URL "https://github.com/brysonjones/open_gl_tools")
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
FetchContent_GetProperties(glm_repo)
if(NOT glm_repo_POPULATED)
  FetchContent_Populate(glm_repo)
  add_subdirectory(${glm_repo_SOURCE_DIR} ${glm_repo_BINARY_DIR})
  include_directories(${glm_repo_SOURCE_DIR})
endif()

# FetchContent_Declare(
#   glad_repo
#   GIT_REPOSITORY https://github.com/Dav1dde/glad.git
#   GIT_TAG        master
# )
# FetchContent_MakeAvailable(glad_repo)

FetchContent_Declare(
  linmath_repo
  GIT_REPOSITORY https://github.com/datenwolf/linmath.h.git
  GIT_TAG        master
)
FetchContent_MakeAvailable(linmath_repo)
include_directories(${linmath_repo_SOURCE_DIR})

add_subdirectory(src)

# Self
# set(oglt_INCLUDE_DIRS ${oglt_INCLUDE_DIRS} 
#     "${PROJECT_SOURCE_DIR}/src/shader/" 
#     "${PROJECT_SOURCE_DIR}/src/windows/" 
#     "${PROJECT_SOURCE_DIR}/src/graphics/")
# set(oglt_LIBRARIES ${oglt_LIBRARIES} 
#     "${PROJECT_BINARY_DIR}/lib/liboglt.a")

# add_library(oglt INTERFACE
#             ${CMAKE_CURRENT_SOURCE_DIR}/src/shader/shader.cpp
#             ${CMAKE_CURRENT_SOURCE_DIR}/src/window/window.cpp
#             ${CMAKE_CURRENT_SOURCE_DIR}/src/graphics/graphics.cpp
#             ${CMAKE_CURRENT_SOURCE_DIR}/src/glad/glad.c)


# set(oglt_INCLUDE_DIRS ${oglt_INCLUDE_DIRS} 
#     ${GLFW_INCLUDE_DIRS}
#     ${linmath_repo_SOURCE_DIR}
#     ${glm_repo_SOURCE_DIR}/glm
#     )
# set(oglt_LIBRARIES ${oglt_LIBRARIES} 
#     ${GLFW_LIBRARIES}
#     ${CMAKE_DL_LIBS}
#     ${OPENGL_LIBRARIES}
#   )

# configure_file(${PROJECT_NAME}Config.cmake.in "${CMAKE_BINARY_DIR}/${PROJECT_NAME}Config.cmake")

# add_executable(main src/main.cpp)

# set(CMAKE_INCLUDE_CURRENT_DIR ON)
                    
# target_link_libraries(main 
#                       glfw ${GLFW_LIBRARIES} 
#                       OpenGL::GL ${CMAKE_DL_LIBS}
#                       oglt::window
#                       oglt::graphics
#                       oglt::shader
#                       glad_libs)

# set_target_properties(
#                     window
#                     graphics
#                     shader 
#                     glm
#     PROPERTIES
#     ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
#     LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
#     RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/Release"
# )


# install(TARGETS 
#             window
#             graphics
#             shader 
#             glm
#         ARCHIVE DESTINATION ARCHIVE_OUTPUT_DIRECTORY
#         LIBRARY DESTINATION LIBRARY_OUTPUT_DIRECTORY
#         RUNTIME DESTINATION RUNTIME_OUTPUT_DIRECTORY)

# # Self
# set(oglt_INCLUDE_DIRS ${oglt_INCLUDE_DIRS} "${PROJECT_SOURCE_DIR}/include")
# set(oglt_LIBRARIES ${oglt_LIBRARIES} "${PROJECT_BINARY_DIR}/libgraphics.a")
