file(GLOB hdrs "*.h*") 
file(GLOB srcs "*.cpp")

add_library(${chain_hash} ${srcs} ${hdrs}) 
