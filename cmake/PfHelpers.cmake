# Helpers so each folder's CMakeLists.txt stays a few lines long.
# Owner: C.

# Warnings required by Conventions.md in the team plan, applied only to our own code.
function(pf_warnings target)
    if(MSVC)
        target_compile_options(${target} PRIVATE /W4)
    else()
        target_compile_options(${target} PRIVATE -Wall -Wextra)
    endif()
endfunction()

# pf_library(<name> SOURCES <files...> DEPS <targets...>)
#
# One library per folder. While a folder still has only headers (week 1, before
# the owner adds a .cpp), it becomes a header-only (INTERFACE) library. As soon as
# SOURCES lists a .cpp, it becomes a normal library. Owners only ever edit SOURCES
# (and DEPS when they start using another folder).
function(pf_library name)
    cmake_parse_arguments(PF "" "" "SOURCES;DEPS" ${ARGN})
    if(PF_SOURCES)
        add_library(${name} STATIC ${PF_SOURCES})
        target_include_directories(${name} PUBLIC ${PROJECT_SOURCE_DIR}/src)
        target_link_libraries(${name} PUBLIC ${PF_DEPS})
        pf_warnings(${name})
    else()
        add_library(${name} INTERFACE)
        target_include_directories(${name} INTERFACE ${PROJECT_SOURCE_DIR}/src)
        target_link_libraries(${name} INTERFACE ${PF_DEPS})
    endif()
endfunction()

# pf_test(<name> SOURCES <files...> DEPS <targets...>)
# A console test program that `ctest` (and CI) runs.
function(pf_test name)
    cmake_parse_arguments(PF "" "" "SOURCES;DEPS" ${ARGN})
    add_executable(${name} ${PF_SOURCES})
    target_link_libraries(${name} PRIVATE ${PF_DEPS})
    pf_warnings(${name})
    add_test(NAME ${name} COMMAND ${name})
endfunction()
