# * BUILD
pybind11_add_module(example example.cpp)

# * INSTALLATION
install(TARGETS example DESTINATION bin)
