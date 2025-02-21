# * BUILD
pybind11_add_module(example example.cpp)
pybind11_add_module(operators_mdot operators_mdot.cpp)

# * INSTALLATION
install(TARGETS example DESTINATION bin)
install(TARGETS example DESTINATION lib/python3.9/site-packages)
