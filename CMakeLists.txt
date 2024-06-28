cmake_minimum_required(VERSION 3.28)

project(v3tool LANGUAGES CXX VERSION 0.1.0.0)

include(cmake/get_cpm.cmake)

CPMAddPackage(
    NAME              traypp
    GIT_TAG           698db7d58dd450cc9e30dc12d3bd0c5ca4d6a5b1
    GITHUB_REPOSITORY Soundux/traypp
)

add_executable(v3tool WIN32
    src/v3tool.cc
    res/v3tool.rc
)

target_compile_features(v3tool PUBLIC cxx_std_23)

target_link_libraries(v3tool tray minisforum)
target_link_directories(v3tool PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/lib)
target_link_options(v3tool PRIVATE "/MANIFESTUAC:level='requireAdministrator' uiAccess='false'")