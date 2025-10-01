cmake_minimum_required(VERSION 3.20)

add_executable(matrix_tests test_matrix.cpp)
target_include_directories(matrix_tests PRIVATE ${CMAKE_SOURCE_DIR}/include)

target_link_libraries(matrix_tests
  PRIVATE
    matrix_lib
    GTest::gtest_main
    GTest::gtest
    Threads::Threads
)

# Регистрируем ОДИН тест — сам бинарь gtest
add_test(NAME matrix_tests COMMAND matrix_tests)
