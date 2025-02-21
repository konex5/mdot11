# * BUILD
pybind11_add_module(mdot_operators mdot_operators.cpp)

# * INSTALLATION
install(TARGETS mdot_operators DESTINATION bin)
install(TARGETS mdot_operators DESTINATION lib/python3.9/site-packages)
