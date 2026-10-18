cmake_minimum_required(VERSION 4.4)

project(order_book LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(benchmark  REQUIRED)

add_executable(order_book
  src/main.cpp
  src/order_book.cpp
)

add_executable(order_book_bench
  src/benchmark.cpp
  src/order_book.cpp
)

target_link_libraries(order_book_bench
  PRIVATE benchmark::benchmark_main
)

target_compile_features(order_book_bench
  PRIVATE
    cxx_std_23
)

target_compile_features(order_book
  PRIVATE
    cxx_std_23
)

target_compile_options(order_book
  PRIVATE
    -Wall
    -Wextra
    -Wshadow
    -Wconversion
    -Wfloat-equal
)

