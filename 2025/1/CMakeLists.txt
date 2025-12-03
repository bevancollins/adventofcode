add_executable(day1
  day1.cpp
)

add_test(
  NAME day1_run1
  COMMAND
    day1 $<SHELL_PATH:${CMAKE_CURRENT_SOURCE_DIR}/tests/test1.txt> $<SHELL_PATH:${CMAKE_CURRENT_BINARY_DIR}/result1.txt>
)

add_test(
  NAME day1_test1
  COMMAND
    ${CMAKE_COMMAND} -E compare_files --ignore-eol ${CMAKE_CURRENT_BINARY_DIR}/result1.txt ${CMAKE_CURRENT_SOURCE_DIR}/tests/expected1.txt
)

add_test(
  NAME day1_run2
  COMMAND
    day1 $<SHELL_PATH:${CMAKE_CURRENT_SOURCE_DIR}/tests/test2.txt> $<SHELL_PATH:${CMAKE_CURRENT_BINARY_DIR}/result2.txt>
)

add_test(
  NAME day1_test2
  COMMAND
    ${CMAKE_COMMAND} -E compare_files --ignore-eol ${CMAKE_CURRENT_BINARY_DIR}/result2.txt ${CMAKE_CURRENT_SOURCE_DIR}/tests/expected2.txt
)

add_test(
  NAME day1_run3
  COMMAND
    day1 $<SHELL_PATH:${CMAKE_CURRENT_SOURCE_DIR}/tests/test3.txt> $<SHELL_PATH:${CMAKE_CURRENT_BINARY_DIR}/result3.txt>
)

add_test(
  NAME day1_test3
  COMMAND
    ${CMAKE_COMMAND} -E compare_files --ignore-eol ${CMAKE_CURRENT_BINARY_DIR}/result3.txt ${CMAKE_CURRENT_SOURCE_DIR}/tests/expected3.txt
)

add_test(
  NAME day1_run4
  COMMAND
    day1 $<SHELL_PATH:${CMAKE_CURRENT_SOURCE_DIR}/tests/test4.txt> $<SHELL_PATH:${CMAKE_CURRENT_BINARY_DIR}/result4.txt>
)

add_test(
  NAME day1_test4
  COMMAND
    ${CMAKE_COMMAND} -E compare_files --ignore-eol ${CMAKE_CURRENT_BINARY_DIR}/result4.txt ${CMAKE_CURRENT_SOURCE_DIR}/tests/expected4.txt
)

add_test(
  NAME day1_run5
  COMMAND
    day1 $<SHELL_PATH:${CMAKE_CURRENT_SOURCE_DIR}/tests/test5.txt> $<SHELL_PATH:${CMAKE_CURRENT_BINARY_DIR}/result5.txt>
)

add_test(
  NAME day1_test5
  COMMAND
    ${CMAKE_COMMAND} -E compare_files --ignore-eol ${CMAKE_CURRENT_BINARY_DIR}/result5.txt ${CMAKE_CURRENT_SOURCE_DIR}/tests/expected5.txt
)

add_test(
  NAME day1_run6
  COMMAND
    day1 $<SHELL_PATH:${CMAKE_CURRENT_SOURCE_DIR}/tests/test6.txt> $<SHELL_PATH:${CMAKE_CURRENT_BINARY_DIR}/result6.txt>
)

add_test(
  NAME day1_test6
  COMMAND
    ${CMAKE_COMMAND} -E compare_files --ignore-eol ${CMAKE_CURRENT_BINARY_DIR}/result6.txt ${CMAKE_CURRENT_SOURCE_DIR}/tests/expected6.txt
)

add_test(
  NAME day1_run7
  COMMAND
    day1 $<SHELL_PATH:${CMAKE_CURRENT_SOURCE_DIR}/tests/test7.txt> $<SHELL_PATH:${CMAKE_CURRENT_BINARY_DIR}/result7.txt>
)

add_test(
  NAME day1_test7
  COMMAND
    ${CMAKE_COMMAND} -E compare_files --ignore-eol ${CMAKE_CURRENT_BINARY_DIR}/result7.txt ${CMAKE_CURRENT_SOURCE_DIR}/tests/expected7.txt
)

add_test(
  NAME day1_run8
  COMMAND
    day1 $<SHELL_PATH:${CMAKE_CURRENT_SOURCE_DIR}/tests/test8.txt> $<SHELL_PATH:${CMAKE_CURRENT_BINARY_DIR}/result8.txt>
)

add_test(
  NAME day1_test8
  COMMAND
    ${CMAKE_COMMAND} -E compare_files --ignore-eol ${CMAKE_CURRENT_BINARY_DIR}/result8.txt ${CMAKE_CURRENT_SOURCE_DIR}/tests/expected8.txt
)

add_test(
  NAME day1_run9
  COMMAND
    day1 $<SHELL_PATH:${CMAKE_CURRENT_SOURCE_DIR}/tests/test9.txt> $<SHELL_PATH:${CMAKE_CURRENT_BINARY_DIR}/result9.txt>
)

add_test(
  NAME day1_test9
  COMMAND
    ${CMAKE_COMMAND} -E compare_files --ignore-eol ${CMAKE_CURRENT_BINARY_DIR}/result9.txt ${CMAKE_CURRENT_SOURCE_DIR}/tests/expected9.txt
)
