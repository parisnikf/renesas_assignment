# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\renesas_assignment_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\renesas_assignment_autogen.dir\\ParseCache.txt"
  "renesas_assignment_autogen"
  )
endif()
