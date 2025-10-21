add_executable(test_tablr test_tablr.c)
target_link_libraries(test_tablr tablr)
add_test(NAME test_tablr COMMAND test_tablr)
