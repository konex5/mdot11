# * BUILD
pybind11_add_module(example example.cpp)

# * INSTALLATION
install(TARGETS example DESTINATION bin)
install(TARGETS example DESTINATION lib/python3.9/site-packages)
