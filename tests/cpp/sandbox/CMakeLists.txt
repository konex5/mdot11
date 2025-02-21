add_executable(sandbox_exe sandbox.cpp)
target_link_libraries(sandbox_exe ${TBB_TBB_LIBRARY_RELEASE} Boost::system Boost::filesystem)
add_test(run_sandbox sandbox_exe)
