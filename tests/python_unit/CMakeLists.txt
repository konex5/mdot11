add_custom_target(
  python_interface_msg ALL
  COMMAND
    echo && echo
    "# You may want to import the pybind11 library during development." && echo
    "export PYTHONPATH=$<TARGET_FILE_DIR:mdot_operators>:$PYTHONPATH" && echo
  COMMENT "look for python interface"
  VERBATIM)
add_dependencies(python_interface_msg mdot_operators)

add_test(
  NAME pytest_interface
  COMMAND pytest -vv ${CMAKE_SOURCE_DIR}
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
set_tests_properties(
  pytest_interface
  PROPERTIES ENVIRONMENT PYTHONPATH=$<TARGET_FILE_DIR:mdot_operators>:$ENV{PYTHONPATH})
