# * BUILD
pybind11_add_module(mdot_operators mdot_operators.cpp)
pybind11_add_module(mdot_routine mdot_routine.cpp)
# pybind11_add_module(cool_example cool_example.cpp)

target_link_libraries(mdot_routine PUBLIC  ${TBB_TBB_LIBRARY_RELEASE} lapack)

# * INSTALLATION
# install(TARGETS mdot_operators DESTINATION bin)
install(TARGETS mdot_operators DESTINATION ${CMAKE_INSTALL_PYTHON_SITE_PACKAGE})
