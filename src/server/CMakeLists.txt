# Copyright (C) 2010-2011 Project StarGate



if(CMAKE_COMPILER_IS_GNUCXX)
  add_definitions(-fno-delete-null-pointer-checks)
endif()

if( SERVERS )
  set(sources_Debugging
    ${CMAKE_SOURCE_DIR}/src/server/shared/Debugging/WheatyExceptionReport.cpp
    ${CMAKE_SOURCE_DIR}/src/server/shared/Debugging/WheatyExceptionReport.h
  )
  add_subdirectory(shared)
  add_subdirectory(game)
  add_subdirectory(collision)
  add_subdirectory(authserver)
  add_subdirectory(scripts)
  add_subdirectory(worldserver)
else()
  if( TOOLS )
    add_subdirectory(collision)
  endif()
endif()
