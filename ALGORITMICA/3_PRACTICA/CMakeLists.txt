CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
PROJECT(practica3)
#Required for uco thinstation. May not be required in your own pc
OPTION(THINSTATION	"Set to OFF at home" ON)

IF(THINSTATION)
  SET(CMAKE_CXX_FLAGS " -D_GLIBCXX_USE_CXX11_ABI=0 -m32")
  SET(XRAND Xrandr)
  link_directories(/usr/local/X11R7/lib)
  MESSAGE( STATUS "USING THINSTATION OPTIONS" )
ENDIF()
set(CMAKE_CXX_STANDARD 11) # C+11...


LINK_LIBRARIES(${OpenCV_LIBS} ${XRAND})

add_executable(main menu.cpp funciones.cpp operadoresExternos.cpp)