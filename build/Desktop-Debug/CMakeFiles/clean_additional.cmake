# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles/appQuantToolSuite_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/appQuantToolSuite_autogen.dir/ParseCache.txt"
  "appQuantToolSuite_autogen"
  )
endif()
