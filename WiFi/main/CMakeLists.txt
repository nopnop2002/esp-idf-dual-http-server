set(srcs "main.c" "http_server.c")

idf_component_register(SRCS "${srcs}" INCLUDE_DIRS ".")

