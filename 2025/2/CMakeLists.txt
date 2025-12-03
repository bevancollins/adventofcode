add_executable(day2
  day2.cpp
)

add_test(
  NAME day2_run1
  COMMAND
    day2 $<SHELL_PATH:${CMAKE_CURRENT_SOURCE_DIR}/tests/test1.txt> $<SHELL_PATH:${CMAKE_CURRENT_BINARY_DIR}/result1.txt>
)

add_test(
  NAME day2_test1
  COMMAND
    ${CMAKE_COMMAND} -E compare_files --ignore-eol ${CMAKE_CURRENT_BINARY_DIR}/result1.txt ${CMAKE_CURRENT_SOURCE_DIR}/tests/expected1.txt
)
