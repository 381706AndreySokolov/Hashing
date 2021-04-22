file(GLOB hdrs "*.h*") 
file(GLOB srcs "*.cpp")

add_executable(${main} ${srcs} ${hdrs}) 

target_link_libraries(${main} ${graph_hash})
