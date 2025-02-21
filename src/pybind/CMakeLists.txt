# * BUILD
pybind11_add_module(fhmat-hmat hmat.cpp)

# * INSTALLATION
install(TARGETS fhmat-hmat DESTINATION bin)
