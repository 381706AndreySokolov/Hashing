file(GLOB hdrs "*.h*") 
file(GLOB srcs "*.cpp")

add_library(${graph_hash} ${srcs} ${hdrs}) 
