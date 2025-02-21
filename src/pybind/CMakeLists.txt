# * BUILD
pybind11_add_module(fmd_operators fmd_operators.cpp)

# * INSTALLATION
install(TARGETS fmd_operators DESTINATION bin)
install(TARGETS fmd_operators DESTINATION lib/python3.9/site-packages)
