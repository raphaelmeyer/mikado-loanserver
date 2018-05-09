cmake_minimum_required(VERSION 3.9)
project(LoanServerCpp)

add_subdirectory(vendor/mongoose)
add_subdirectory(vendor/catch2)
add_subdirectory(vendor/json)
add_subdirectory(loan_server)

