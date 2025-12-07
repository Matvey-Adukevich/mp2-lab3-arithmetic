#
#file(GLOB samples_list RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.cpp)
#
#
#foreach(sample_filename ${samples_list})
#  get_filename_component(sample ${sample_filename} NAME_WE)
#
#  add_executable(${sample} ${sample_filename})
#  target_link_libraries(${sample} ${MP2_LIBRARY})
#  set_target_properties(${sample} PROPERTIES
#    OUTPUT_NAME "${sample}"
#    PROJECT_LABEL "${sample}"
#    RUNTIME_OUTPUT_DIRECTORY "../")
#endforeach()

##set_target_properties(main PROPERTIES
##  RUNTIME_OUTPUT_DIRECTORY "../")
add_executable(sample_main main.cpp)
target_link_libraries(sample_main ${PROJECT_NAME})