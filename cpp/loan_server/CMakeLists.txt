add_library(loan_application_server
  source/LoanHandler.cc
)
add_library(mikado::loan_application_server ALIAS loan_application_server)
target_link_libraries(loan_application_server
  PRIVATE
    cesanta::mongoose
    mikado::settings
)

add_executable(loan_server
  source/LoanServer.cc
)
target_link_libraries(loan_server
  PRIVATE
    mikado::loan_application_server
    mikado::settings
)

add_library(settings INTERFACE)
add_library(mikado::settings ALIAS settings)
target_compile_features(settings INTERFACE cxx_std_14)

add_subdirectory(tests)

