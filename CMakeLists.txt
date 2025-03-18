cmake_minimum_required(VERSION 3.10)
project(VK_cpp_test)

enable_testing()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options(-Wall)
add_compile_options(-Werror)
add_compile_options(-Wextra)
add_compile_options(-Wno-unknown-attributes)

set(COVERAGE_FLAGS --coverage -g -O0)
set(RELEASE_FLAGS -O2)

# Там в целом все файлы используются, вынес по этому их в отдельную переменную
set(
    CPP_FILES_FOR_ALL_VERSION
    ./project/source/exceptions.cpp
    ./project/source/ListGraph.cpp
    ./project/source/GraphTest.cpp
)
set(PATH_TO_INCLUDES ${CMAKE_CURRENT_SOURCE_DIR}/project/include)
separate_arguments(CPP_FILES_FOR_ALL_VERSION)

#### Настройка тестов
function(add_test_executable test_name result_var)
    add_executable(${test_name}.out ./project/tests/${test_name}.cpp ${CPP_FILES_FOR_ALL_VERSION})
    target_include_directories(${test_name}.out PUBLIC ${PATH_TO_INCLUDES})
    target_compile_options(${test_name}.out PRIVATE ${COVERAGE_FLAGS})
    target_link_libraries(${test_name}.out PRIVATE -fprofile-generate)
    set(${result_var} "${${result_var}} ${test_name}.out" PARENT_SCOPE)
    add_test(NAME ${test_name}.out COMMAND ${test_name}.out)
endfunction()

add_test_executable(IGraph_test TEST_NAME_TO_TESTS)
add_test_executable(ListGraph_test TEST_NAME_TO_TESTS)
add_test_executable(exceptions_test TEST_NAME_TO_TESTS)
add_test_executable(GraphTest_test TEST_NAME_TO_TESTS)

message(STATUS "${CPP_FILES_FOR_ALL_VERSION}")
message(STATUS "All files for test: ${TEST_NAME_TO_TESTS}")

#### Релизная версия
add_executable(a.out ./project/source/main.cpp ${CPP_FILES_FOR_ALL_VERSION})
target_include_directories(a.out PUBLIC ${PATH_TO_INCLUDES})
target_compile_options(a.out PRIVATE ${RELEASE_FLAGS})
set_target_properties(a.out PROPERTIES EXCLUDE_FROM_ALL TRUE)

add_custom_target(build_release
    COMMAND ${CMAKE_COMMAND} --build . --target a.out
    COMMENT "Building release version..."
)

#### Настройка анализа тестов
find_program(LCOV lcov)
find_program(GENHTML genhtml)

separate_arguments(TEST_NAME_TO_TESTS)

if (LCOV AND GENHTML)
    add_custom_target(coverage_report
        COMMAND ${LCOV} --ignore-errors format,inconsistent,unsupported --capture --directory ${CMAKE_BINARY_DIR} --output-file coverage.info > /dev/null 2>&1
        COMMAND ${LCOV} --remove coverage.info '/usr/*' '*/tests/*' --output-file coverage.info > /dev/null 2>&1
        COMMAND ${GENHTML} --ignore-errors inconsistent,unsupported,corrupt,category coverage.info --output-directory coverage_report
        COMMAND ${CMAKE_COMMAND} -E echo "Отчет по покрытию составлен и загружен в coverage_report/index.html"
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        DEPENDS ${TEST_NAME_TO_TESTS}
    )
else()
    message(WARNING "!!!> lcov или genhtml не найдены, отчет по покрытию составлен не будет")
endif()

add_custom_target(launchTestAbuildRelease
    COMMAND ${CMAKE_COMMAND} --build . --target ${TEST_NAME_TO_TESTS}
    COMMAND ctest --output-on-failure
    COMMAND ${CMAKE_COMMAND} --build . --target coverage_report
    COMMAND ${CMAKE_COMMAND} --build . --target build_release
    COMMENT "Running all steps..."
)
