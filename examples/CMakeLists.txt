
add_executable(universal_hash ${CMAKE_CURRENT_SOURCE_DIR}/universal_hash.cpp) 

target_link_libraries(universal_hash hashing_lib)
