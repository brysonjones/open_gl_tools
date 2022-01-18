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
#     PROPERTIES
#     ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
#     LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
#     RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/Release"
# )


# install(TARGETS 
#             window
#             graphics
#             shader 
#         ARCHIVE DESTINATION ARCHIVE_OUTPUT_DIRECTORY
#         LIBRARY DESTINATION LIBRARY_OUTPUT_DIRECTORY
#         RUNTIME DESTINATION RUNTIME_OUTPUT_DIRECTORY)

# install(EXPORT glm 
#         DESTINATION "${CMAKE_BINARY_DIR}/lib")
# INSTALL(FILES
#         DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})


include(CMakePackageConfigHelpers)

set(exported_targets_name "${PROJECT_NAME}Targets")
set(exported_targets_filename "${exported_targets_name}.cmake")
set(export_dirpath "${CMAKE_BINARY_DIR}/lib/cmake/")
set(config_basename "${PROJECT_NAME}Config")
set(config_filename "${config_basename}.cmake")
set(version_filename "${config_basename}Version.cmake")

# write_basic_package_version_file(
#     ${version_filename}
#     COMPATIBILITY SameMajorVersion
# )

# configure_file("cmake/${config_filename}.in" "${config_filename}" @ONLY)

install(
    TARGETS     window
                graphics
                shader 
                glm
                glad_libs
    EXPORT ${exported_targets_name}
    ARCHIVE DESTINATION "lib"
    PUBLIC_HEADER DESTINATION "include/cppuuid"
)
install(
    EXPORT ${exported_targets_name}
    FILE ${exported_targets_filename}
    # NAMESPACE cppuuid::
    DESTINATION ${export_dirpath}
)
install(
    FILES
        "${CMAKE_CURRENT_BINARY_DIR}/${config_filename}"
        "${CMAKE_CURRENT_BINARY_DIR}/${version_filename}"
    DESTINATION
        ${export_dirpath}
)
install(
    DIRECTORY
        "${CMAKE_CURRENT_SOURCE_DIR}/include/cppuuid"
        "${CMAKE_CURRENT_BINARY_DIR}/include/cppuuid"
    DESTINATION
        "include"
)


