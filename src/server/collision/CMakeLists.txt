 # Copyright (C) 2010-2011 Project StarGate

if( USE_COREPCH )
  include_directories(${CMAKE_CURRENT_BINARY_DIR})
endif()

file(GLOB_RECURSE sources_Management Management/*.cpp Management/*.h)
file(GLOB_RECURSE sources_Maps Maps/*.cpp Maps/*.h)
file(GLOB_RECURSE sources_Models Models/*.cpp Models/*.h)
file(GLOB sources_localdir *.cpp *.h)

if( USE_COREPCH AND MSVC )
  set(collision_STAT_SRCS
    PrecompiledHeaders/collisionPCH.cpp
    PrecompiledHeaders/collisionPCH.h
  )
endif()

set(collision_STAT_SRCS
  ${collision_STAT_SRCS}
  ${sources_Management}
  ${sources_Maps}
  ${sources_Models}
  ${sources_localdir}
)

include_directories(
  ${CMAKE_SOURCE_DIR}/dep/g3dlite/include
  ${CMAKE_SOURCE_DIR}/src/server/shared
  ${CMAKE_SOURCE_DIR}/src/server/shared/Debugging
  ${CMAKE_SOURCE_DIR}/src/server/shared/Database
  ${CMAKE_SOURCE_DIR}/src/server/shared/Debugging
  ${CMAKE_SOURCE_DIR}/src/server/shared/Dynamic
  ${CMAKE_SOURCE_DIR}/src/server/shared/Logging
  ${CMAKE_SOURCE_DIR}/src/server/shared/Threading
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}/Management
  ${CMAKE_CURRENT_SOURCE_DIR}/Maps
  ${CMAKE_CURRENT_SOURCE_DIR}/Models
  ${CMAKE_BINARY_DIR}
  ${ACE_INCLUDE_DIR}
  ${MYSQL_INCLUDE_DIR}
  ${OPENSSL_INCLUDE_DIR}
)

add_library(collision STATIC ${collision_STAT_SRCS})

# Generate precompiled header
if( USE_COREPCH )
  if(CMAKE_COMPILER_IS_GNUCXX)
    add_precompiled_header(collision ${CMAKE_CURRENT_SOURCE_DIR}/PrecompiledHeaders/collisionPCH.h)
  elseif(MSVC)
    add_native_precompiled_header(collision ${CMAKE_CURRENT_SOURCE_DIR}/PrecompiledHeaders/collisionPCH)
  endif()
endif()

