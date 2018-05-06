
set(NAME LoanServer)

set(SOURCES
  ApplicationException.cs
  Json.cs
  LoanApplication.cs
  LoanHandler.cs
  LoanRepository.cs
  LoanServer.cs
  Ticket.cs
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
  COMMAND mcs -out:${NAME}.exe ${PKGS} ${source_list}
  DEPENDS ${SOURCES}
  )

