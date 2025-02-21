
add_executable(bench_dgemm bench_dgemm.cpp)
add_test(
  bench_dgemm
  hyperfine
  --warmup
  2
  --min-runs
  4
  --show-output
  ${CMAKE_CURRENT_BINARY_DIR}/bench_dgemm)
# < ${CMAKE_SOURCE_DIR}/benchmark_input > ${CMAKE_SOURCE_DIR}/benchmark_output"
