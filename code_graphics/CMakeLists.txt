# CMake build for console graphics samples (BGI/winbgim)
cmake_minimum_required(VERSION 3.16)

# Create an interface target for include paths
add_library(graphics_includes INTERFACE)
target_include_directories(graphics_includes INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/includs
    ${CMAKE_CURRENT_SOURCE_DIR}/Graphics
)

# Import the prebuilt BGI library
set(BGI_LIB ${CMAKE_CURRENT_SOURCE_DIR}/Graphics/libbgi.a)
if(NOT EXISTS ${BGI_LIB})
    message(FATAL_ERROR "BGI static library not found at ${BGI_LIB}")
endif()

add_library(bgi STATIC IMPORTED GLOBAL)
set_target_properties(bgi PROPERTIES IMPORTED_LOCATION ${BGI_LIB})

# Helper function to add console executables linked with BGI
function(add_bgi_exe name src)
    add_executable(${name} ${src})
    target_link_libraries(${name} PRIVATE graphics_includes bgi gdi32 comdlg32 uuid oleaut32 ole32)
    target_compile_features(${name} PRIVATE cxx_std_17)
    if (WIN32)
        # Force console subsystem so linker expects main(), not WinMain()
        target_link_options(${name} PRIVATE -Wl,-subsystem,console)
    endif()
endfunction()

# Ajuster sample
add_bgi_exe(ajuster ${CMAKE_CURRENT_SOURCE_DIR}/src_graphics/ajuster/ajuster.cpp)
