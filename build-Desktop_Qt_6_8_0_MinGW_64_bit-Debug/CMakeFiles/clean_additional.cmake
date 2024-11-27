# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "Bibliotheque_de_Contacts_autogen"
  "CMakeFiles\\Bibliotheque_de_Contacts_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\Bibliotheque_de_Contacts_autogen.dir\\ParseCache.txt"
  )
endif()
