cmake_minimum_required(VERSION 3.16)

project(svg2b2d LANGUAGES CXX)

add_library(${PROJECT_NAME} STATIC)

target_sources(${PROJECT_NAME}
  PRIVATE
    src/svg.cpp
)

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)


target_include_directories(${PROJECT_NAME} 
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
  PUBLIC 
      # where top-level project will look for the library's public headers
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    # where external projects will look for the library's public headers
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

target_link_libraries(${PROJECT_NAME}
  PUBLIC
  Blend2D::Blend2D
)


