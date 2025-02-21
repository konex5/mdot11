set(VALIDATION_NAMES apply_gate)

foreach(VALIDATION_NAME ${VALIDATION_NAMES})
  add_executable(validate_${VALIDATION_NAME} validate_${VALIDATION_NAME}.cpp)
  target_link_libraries(
    validate_${VALIDATION_NAME}
    ${Boost_FILESYSTEM_LIBRARY}
    ${Boost_SYSTEM_LIBRARY}
    ${TBB_IMPORTED_TARGETS}
    ${TBB_LIBRARIES}
    ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
    apply_gate)
  add_test(validate_${VALIDATION_NAME} validate_${VALIDATION_NAME})
endforeach()
