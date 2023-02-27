add_executable(Recrypt
recrypt-cli.cpp
)

target_link_libraries (Recrypt PDFHummus::PDFWriter)

if(APPLE)
	set(CMAKE_EXE_LINKER_FLAGS "-framework CoreFoundation")
endif(APPLE)


install(TARGETS Recrypt
    RUNTIME DESTINATION bin COMPONENT executable
)