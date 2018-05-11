find_package(Threads REQUIRED)

add_library(loan_application_server
  source/LoanApplication.cc
  source/LoanHandler.cc
  source/LoanRepository.cc
  source/Server.cc
  source/Ticket.cc
)
add_library(mikado::loan_application_server ALIAS loan_application_server)
target_link_libraries(loan_application_server
  PRIVATE
    cesanta::mongoose
    nlohmann::json
    mikado::settings
    Threads::Threads
)
target_include_directories(loan_application_server
  PUBLIC include
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

