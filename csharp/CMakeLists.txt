cmake_minimum_required(VERSION 3.10)
project(LoanServerCSharp LANGUAGES NONE)

set(NAME LoanServer.exe)

set(SOURCES
  LoanServer/ApplicationException.cs
  LoanServer/Json.cs
  LoanServer/LoanApplication.cs
  LoanServer/LoanHandler.cs
  LoanServer/LoanRepository.cs
  LoanServer/LoanServer.cs
  LoanServer/Ticket.cs
  )

set(source_list "")
foreach(source ${SOURCES})
  list(APPEND source_list "${CMAKE_CURRENT_SOURCE_DIR}/${source}")
endforeach()

set(PKGS
  -r:System.Web.Http
  -r:System.Net.Http
  -r:System.Json
  -r:System.Runtime.Serialization
  )

add_custom_target(${NAME} ALL
  COMMAND mcs -out:${NAME} ${PKGS} ${source_list}
  DEPENDS ${SOURCES}
  )

