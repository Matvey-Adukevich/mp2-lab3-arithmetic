#set(target ${MP2_TESTS})

#file(GLOB hdrs "*.h*")
#file(GLOB srcs "*.cpp")

#include_directories("${CMAKE_CURRENT_SOURCE_DIR}/../3rdparty")

#add_executable(${target} ${srcs} ${hdrs})
#target_link_libraries(${target} gtest ${MP2_LIBRARY})

add_executable(${MP2_TESTS} test_main.cpp)
target_link_libraries(${MP2_TESTS} ${PROJECT_NAME} gtest)
