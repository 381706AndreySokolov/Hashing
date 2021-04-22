file(GLOB hdrs "*.h*") 
file(GLOB srcs "*.cpp")

add_library(${perfect_hash} ${srcs} ${hdrs}) 
