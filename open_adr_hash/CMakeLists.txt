file(GLOB hdrs "*.h*") 
file(GLOB srcs "*.cpp")

add_library(${open_adr_hash} ${srcs} ${hdrs}) 
