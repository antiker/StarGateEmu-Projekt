# Copyright (C) 2010-2011 Project StarGate

# Need to pass old ${CMAKE_BINARY_DIR} as param because its different at build stage
add_custom_target(revision.h ALL
  COMMAND ${CMAKE_COMMAND} -DBUILDDIR=${CMAKE_BINARY_DIR} -P ${CMAKE_SOURCE_DIR}/cmake/genrev.cmake
  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
)
