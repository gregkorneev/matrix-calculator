cmake_minimum_required(VERSION 3.20)
project(Matrix_Calculator VERSION 0.1 LANGUAGES CXX)
include(FetchContent)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        v1.13.0
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
find_package(Threads REQUIRED)


# Если системный GTest по каким-то причинам "пустой" или не подходит —
# просто всегда используем встроенный (можно условно, но для надёжности — без условий).
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        v1.13.0   # та же версия, что у вас в системе; можно обновить до v1.15.2
)
# Для ускорения сборки тестов на релизных флагах
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)


# Use modern C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# -----------------------------------------------------------------------------
# Build the library. The library consists of the implementation file and the
# public header. Making the header part of the library sources ensures that
# changes to it trigger recompilation.
# -----------------------------------------------------------------------------
add_library(matrix_lib src/matrix.cpp include/matrix.h)
target_include_directories(matrix_lib PUBLIC include)

# -----------------------------------------------------------------------------
# Build the demonstration executable. This program exercises the matrix
# functions defined in the library and is not required for the unit tests.
# -----------------------------------------------------------------------------
add_executable(matrix_calculator src/main.cpp)
target_link_libraries(matrix_calculator PRIVATE matrix_lib)

# -----------------------------------------------------------------------------
# Tests
#
# Enable the test framework and delegate building of the tests to the tests
# directory. CTest will discover and execute any tests registered there.
# -----------------------------------------------------------------------------
enable_testing()
add_subdirectory(tests)
