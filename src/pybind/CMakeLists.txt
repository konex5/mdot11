# * BUILD
pybind11_add_module(fhm wrapper.cpp)

# * INSTALLATION
install(TARGETS fhm DESTINATION bin)


