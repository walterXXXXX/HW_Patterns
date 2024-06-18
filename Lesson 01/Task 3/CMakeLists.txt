cmake_minimum_required(VERSION 3.22.2)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

project(SQL_QUERY_BUILDER)

add_executable(SQL_QUERY_BUILDER main.cpp sql_select_query_builder.h sql_select_query_builder.cpp advanced_sql_select_query_builder.cpp advanced_sql_select_query_builder.h)