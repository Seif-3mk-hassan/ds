cmake_minimum_required(VERSION 3.30)
project(DSproject)

set(CMAKE_CXX_STANDARD 23)

# Add all source files
file(GLOB SOURCES 
    "source/*.cpp"
    "main.cpp"
)

# Add all header directories
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/headers
    ${CMAKE_CURRENT_SOURCE_DIR}/lib
)
add_executable(DSproject ${SOURCES})
find_package(folly CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)
target_link_libraries(DSproject PRIVATE nlohmann_json::nlohmann_json folly)