cmake_minimum_required(VERSION 3.10)
project(LoanServerCpp)

add_subdirectory(vendor/mongoose)
add_subdirectory(vendor/catch2)
add_subdirectory(loan_server)

