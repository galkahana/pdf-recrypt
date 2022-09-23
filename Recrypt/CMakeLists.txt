Project(Recrypt)
cmake_minimum_required(VERSION 3.10)

add_executable(Recrypt
recrypt-cli.cpp
)

if(PDFHUMMUS_NO_DCT)
	add_definitions(-DPDFHUMMUS_NO_DCT=1)
endif(PDFHUMMUS_NO_DCT)

if(PDFHUMMUS_NO_TIFF)
	add_definitions(-DPDFHUMMUS_NO_TIFF=1)
endif(PDFHUMMUS_NO_TIFF)

if(PDFHUMMUS_NO_PNG)
	add_definitions(-DPDFHUMMUS_NO_PNG=1)
endif(PDFHUMMUS_NO_PNG)

include_directories (${PDFWriter_SOURCE_DIR})
include_directories (${LIBAESGM_INCLUDE_DIRS})
include_directories (${ZLIB_INCLUDE_DIRS})
if(NOT PDFHUMMUS_NO_DCT)
	include_directories (${LIBJPEG_INCLUDE_DIRS})
else(NOT PDFHUMMUS_NO_DCT)
	add_definitions(-DPDFHUMMUS_NO_DCT=1)
endif(NOT PDFHUMMUS_NO_DCT)

if(NOT PDFHUMMUS_NO_TIFF)
	include_directories (${LIBTIFF_INCLUDE_DIRS})
else(NOT PDFHUMMUS_NO_TIFF)
	add_definitions(-DPDFHUMMUS_NO_TIFF=1)
endif(NOT PDFHUMMUS_NO_TIFF)
include_directories (${FREETYPE_INCLUDE_DIRS})

if(NOT PDFHUMMUS_NO_PNG)
	include_directories (${LIBPNG_INCLUDE_DIRS})
else(NOT PDFHUMMUS_NO_PNG)
	add_definitions(-DPDFHUMMUS_NO_PNG=1)
endif(NOT PDFHUMMUS_NO_PNG)

add_dependencies(Recrypt PDFWriter) #add_dependencies makes sure that dependencies are built before main target


target_link_libraries (Recrypt PDFWriter)
target_link_libraries (Recrypt ${LIBAESGM_LDFLAGS})
target_link_libraries (Recrypt ${FREETYPE_LDFLAGS})
if(NOT PDFHUMMUS_NO_DCT)
	target_link_libraries (Recrypt ${LIBJPEG_LDFLAGS})
endif(NOT PDFHUMMUS_NO_DCT)
target_link_libraries (Recrypt ${ZLIB_LDFLAGS})
if(NOT PDFHUMMUS_NO_TIFF)
	target_link_libraries (Recrypt ${LIBTIFF_LDFLAGS})
endif(NOT PDFHUMMUS_NO_TIFF)
if(NOT PDFHUMMUS_NO_PNG)
	target_link_libraries (Recrypt ${LIBPNG_LDFLAGS})
endif(NOT PDFHUMMUS_NO_PNG)

if(APPLE)
	set(CMAKE_EXE_LINKER_FLAGS "-framework CoreFoundation")
endif(APPLE)


install(TARGETS Recrypt
    RUNTIME DESTINATION bin COMPONENT executable
)