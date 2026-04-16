add_executable(smoke_test smoke_test.cpp)
target_link_libraries(smoke_test PRIVATE flight_computer_core)
add_test(NAME smoke_test COMMAND smoke_test)
