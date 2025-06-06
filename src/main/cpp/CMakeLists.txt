cmake_minimum_required(VERSION 3.22.1)

project("librtlsdr")

# Clave: Busca headers en 'include' Y en el directorio actual (cpp, representado por '.')
include_directories(include .)

# Recoge automáticamente todos los archivos .c (incluidos los tuners)
file(GLOB NATIVE_SOURCES "*.c")

# Agrega la librería precompilada libusb.so
add_library(usb SHARED IMPORTED)
set_target_properties(usb PROPERTIES IMPORTED_LOCATION
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/${ANDROID_ABI}/libusb.so)

# Crea nuestra librería rtlsdr compartida a partir de todos los fuentes .c
add_library(rtlsdr SHARED ${NATIVE_SOURCES})

# Enlaza rtlsdr con la librería usb y con la librería de log de Android
target_link_libraries(rtlsdr usb log)
