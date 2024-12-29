# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles/lookOutside_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/lookOutside_autogen.dir/ParseCache.txt"
  "lookOutside_autogen"
  )
endif()
