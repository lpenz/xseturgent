
cmake_minimum_required (VERSION 3.0)

project (xseturgent)

if(CMAKE_COMPILER_IS_GNUCXX)
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Werror -W")
	set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -Wall -Werror -W")
endif(CMAKE_COMPILER_IS_GNUCXX)

find_package (PkgConfig REQUIRED)
pkg_check_modules (X11 REQUIRED x11)
link_libraries ("${X11_LIBRARIES}")

add_executable (xseturgent xseturgent.c)

install (TARGETS xseturgent
  RUNTIME DESTINATION bin/
  )
