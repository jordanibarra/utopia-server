project(datagen LANGUAGES CXX)

option(BUILD_TESTS "Build tests for datagen" ON)

find_package(Boost REQUIRED)

find_library(LMDB_LIB NAMES lmdb REQUIRED)
find_path(LMDB_INCLUDE_DIR NAMES lmdb.h REQUIRED)
find_path(LMDB++_INCLUDE_DIR NAMES lmdb++.h REQUIRED)

add_subdirectory(faker)

add_library(datagen STATIC)
target_sources(datagen PRIVATE src/datagen.cpp src/generation.cpp)
target_include_directories(datagen
        PRIVATE
            ${Boost_INCLUDE_DIRS}
            ${LMDB_INCLUDE_DIR}
            ${LMDB++_INCLUDE_DIR}
        PUBLIC
            ${CMAKE_CURRENT_SOURCE_DIR}/src
)
target_link_libraries(datagen ${Boost_LIBS} ${LMDB_LIB} Faker::Faker)
target_compile_features(datagen PUBLIC cxx_std_17)
set_target_properties(datagen PROPERTIES PUBLIC_HEADER "src/buffer.hpp src/datagen.hpp src/generation.hpp src/model.hpp")

set(CXX_EXTENSIONS OFF)

add_executable(datagen-cli src/main.cpp)
target_link_libraries(datagen-cli datagen)
target_compile_features(datagen-cli PUBLIC cxx_std_17)

if (BUILD_TESTS)
    add_subdirectory(tests)
    enable_testing()
endif()
