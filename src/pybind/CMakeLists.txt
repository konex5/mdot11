# * BUILD
pybind11_add_module(fmd_operators fmd_operators.cpp)
pybind11_add_module(cool_example cool_example.cpp)

# * INSTALLATION
# install(TARGETS fmd_operators DESTINATION bin)
install(TARGETS fmd_operators DESTINATION ${CMAKE_INSTALL_PYTHON_SITE_PACKAGE})
