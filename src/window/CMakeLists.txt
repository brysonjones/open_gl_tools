add_library(window SHARED window.cpp)

add_library(oglt::window ALIAS window)

target_link_libraries(window 
                      glad_libs)