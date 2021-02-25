idf_component_register(
    SRCS
    "main.cpp" "packet.cpp"
    "configure_wifi.c"
    INCLUDE_DIRS
    "."
)
target_link_libraries(${COMPONENT_LIB} -Wl,-zmuldefs)