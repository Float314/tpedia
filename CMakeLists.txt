#[[
    tpedia
    Copyright (C) 2026, Float314

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.

]]
cmake_minimum_required(VERSION 3.15)
project(tpedia
    DESCRIPTION "Run Wikipedia in the terminal itself!!!"
    LANGUAGES C CXX
    VERSION 1.0.0
)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ------------ CPM -----------------------------------------------
if(NOT EXISTS "${CMAKE_CURRENT_BINARY_DIR}/cmake/CPM.cmake")
    message("-- Downloading CPM v0.42.3")
    file(
        DOWNLOAD
        https://github.com/cpm-cmake/CPM.cmake/releases/download/v0.42.3/CPM.cmake
        ${CMAKE_CURRENT_BINARY_DIR}/cmake/CPM.cmake
    )
    message("-- CPM Successfully fetched!")
else()
    message("-- CPM is already installed")
endif()
include(${CMAKE_CURRENT_BINARY_DIR}/cmake/CPM.cmake)

# ---------------------- CPP-HTTPLIB ------------------------------
set(CXX_HTTPLIB_LIBHDR "${CMAKE_CURRENT_BINARY_DIR}/third_party/httplib.h")

# Check if cpp-httplib is there
if(NOT EXISTS "${CXX_HTTPLIB_LIBHDR}")
    message("-- Downloading cpp-httplib")
    file(DOWNLOAD
        "https://raw.githubusercontent.com/yhirose/cpp-httplib/v0.46.0/httplib.h"
        "${CXX_HTTPLIB_LIBHDR}"
    )
    message("-- Downloaded cpp_httplib!")
else()
    message("-- cpp-httplib is already on the path ${CXX_HTTPLIB_LIBHDR}. Skipping Download")
endif()

# --------------------- Libraries + more ------------------------------------
CPMAddPackage("gh:geode-sdk/json@3.3.0")
CPMAddPackage("gh:ArthurSonzogni/FTXUI@7.0.0")

# --------------------- O-puhh-nSSL --------------------------------------

find_package(OpenSSL REQUIRED)

set(SOURCES
    src/main.cpp
    src/application.cpp
    src/ui/header.cpp
    src/ui/homepage.cpp
    src/ui/search_results.cpp
    src/ui/about.cpp
    src/ui/wiki_text.cpp
    src/ui/scrollbar.cpp
    src/api/wikipedia_client.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})
target_compile_definitions(${PROJECT_NAME} PRIVATE 
    CPP_HTTPLIB_OPENSSL_SUPPORT
)
target_include_directories(${PROJECT_NAME} 
    PRIVATE 
    src
    incl
    "${CMAKE_CURRENT_BINARY_DIR}/third_party"
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    mat-json
    ftxui::ftxui
    OpenSSL::SSL
    OpenSSL::Crypto
)
