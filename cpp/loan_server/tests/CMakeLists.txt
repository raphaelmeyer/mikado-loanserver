add_executable(loan_application_server_tests
  test_runner.cc
  dummy_test.cc
)
add_executable(mikado_tests::loan_application_server ALIAS loan_application_server_tests)

target_link_libraries(loan_application_server_tests
  PRIVATE
    mikado::loan_application_server
    mikado::settings
    catchorg::catch2
)

add_custom_target(run_loan_application_server_tests ALL
  COMMAND mikado_tests::loan_application_server
)

