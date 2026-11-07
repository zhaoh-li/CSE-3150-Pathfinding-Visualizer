# Owner: D. Add each new .cpp to SOURCES in the week your TODO file schedules it,
# e.g. SOURCES Map.cpp Generator.cpp
# While SOURCES is empty, this folder builds as a header-only library.
pf_library(pf_gen
    SOURCES
    DEPS pf_core
)
