include(ExternalProject)
include(ragel)
include(boost)
include(pcre)
include(hyperscan)
include(glib)

ExternalProject_Add_StepDependencies(libhs configure ragel libboost libpcre)