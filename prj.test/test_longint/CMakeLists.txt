add_executable(test_longint test_longint.cpp)
target_link_libraries(test_longint longint)
set_property(TARGET test_longint PROPERTY CXX_STANDARD 17)
