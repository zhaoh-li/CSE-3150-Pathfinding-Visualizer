# Owner: E. Add each new .cpp to SOURCES in the week your TODO file schedules it,
# e.g. SOURCES OsmLoader.cpp
# While SOURCES is empty, this folder builds as a header-only library.
pf_library(pf_geo
    SOURCES
    DEPS pf_core nlohmann_json::nlohmann_json
)
