# Copyright (c) Microsoft Corporation.
# Licensed under the MIT License.
cmake_minimum_required(VERSION 3.14)
include(FetchContent)

file(GLOB SRC CONFIGURE_DEPENDS *.cpp)
file(GLOB INC ../include/*.h ../include/*.hpp ../interface/*.h *.h *.hpp)
file(GLOB INL ../include/*.inl *.inl)

file(GLOB_RECURSE EXTERNAL_INC ../external/*.h ../external/*.hpp)

add_library(d3d11on12 SHARED ${SRC} ${INC} ${INL} ${EXTERNAL_INC} d3d11on12.rc d3d11on12.def)

if("${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang")
target_compile_options(d3d11on12 PUBLIC -fpermissive -Wno-error -Wno-switch -Wno-nonportable-include-path -Wno-c++11-narrowing -Wno-unused-command-line-argument -Wno-deprecated-enum-compare -Wno-defaulted-function-deleted)
else("${CMAKE_CXX_COMPILER_ID}" MATCHES "GNU")
target_compile_options(d3d11on12 PUBLIC -fpermissive -Wno-template-body -Wno-non-template-friend -Wno-subobject-linkage -Wno-extra -Wno-error)
endif()

set_target_properties(d3d11on12 PROPERTIES PREFIX "")

#if (CMAKE_VERSION VERSION_GREATER 3.16)
#	target_precompile_headers(d3d11onvkd3d PRIVATE ../include/pch.hpp)
#endif()

FetchContent_Declare(
    d3d12translationlayer
    SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../D3D12TranslationLayer
)
FetchContent_MakeAvailable(d3d12translationlayer)

target_link_libraries(d3d11on12 d3d12translationlayer_wdk)
target_include_directories(d3d11on12
    PRIVATE ../include
    PRIVATE ../external
    PUBLIC ../interface
    PRIVATE ./)
source_group(Inlines FILES ${INL})
source_group("Header Files\\External" FILES ${EXTERNAL_INC})
