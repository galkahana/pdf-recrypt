cmake_minimum_required (VERSION 3.15)
project(Recrypt)

# hummus dependency
include(FetchContent)
FetchContent_Declare(
  PDFHummus
  GIT_REPOSITORY https://github.com/galkahana/PDF-Writer.git
  GIT_TAG        v4.7.0
  FIND_PACKAGE_ARGS
)
FetchContent_MakeAvailable(PDFHummus)

ADD_SUBDIRECTORY(Recrypt)
