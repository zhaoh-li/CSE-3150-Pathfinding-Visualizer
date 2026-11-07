# Test programs. `ctest` runs all of them, and so does CI on every pull request.
# Tests always build in Debug-style mode for asserts: don't define NDEBUG here.

# Contract tests (owner: A). Every contracts_X.cpp is built in automatically.
pf_test(test_contracts
    SOURCES test_contracts.cpp
            contracts/contracts_A.cpp contracts/contracts_B.cpp contracts/contracts_C.cpp
            contracts/contracts_D.cpp contracts/contracts_E.cpp
    DEPS pf_core pf_problems pf_gen pf_editor pf_geo pf_io
)

# Each owner uncomments their own line in week 1, once their test file exists.
# pf_test(test_core     SOURCES test_core.cpp     DEPS pf_core)                    # A
# pf_test(test_problems SOURCES test_problems.cpp DEPS pf_problems)                # B
# pf_test(test_gen      SOURCES test_gen.cpp      DEPS pf_gen pf_editor)           # D
# pf_test(test_geo      SOURCES test_geo.cpp      DEPS pf_geo pf_io)               # E
# console_demo is a program to run by hand, not a test (A + D start it in week 1):
# add_executable(console_demo console_demo.cpp)
# target_link_libraries(console_demo PRIVATE pf_core pf_gen pf_problems)
