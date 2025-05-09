set(TEST_FILES qsharp/obj/qsharp/qir-test-random.bc)

#==============================================================================
# This executable target links test code against the dynamic libraries rather than the explicit
# static QIR/RT libs (qir will statically link in the bridge via transitivity of target_link_libraries).
#
add_executable(qir-dynamic-tests qir-driver.cpp)

foreach(file ${TEST_FILES})
  target_source_from_qir(qir-dynamic-tests ${file})
endforeach()

target_link_libraries(qir-dynamic-tests PUBLIC
  "-L${simulator_lib_path}"
  -lMicrosoft.Quantum.Simulator.Runtime
)

target_include_directories(qir-dynamic-tests PUBLIC
  ${test_includes}
)

install(TARGETS qir-dynamic-tests RUNTIME DESTINATION "${CMAKE_BINARY_DIR}/bin")
add_unit_test(qir-dynamic-tests)
