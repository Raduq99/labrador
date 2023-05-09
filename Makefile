CXX = g++
NFLlib = /home/radu/nfllib
CXXFLAGS = -g -Wall -Wl,-rpath,$(NFLlib)/lib -I$(NFLlib)/include -L$(NFLlib)/lib -lnfllib
SOURCES = labrador.cpp protocol.cpp types.cpp aggregation.cpp projection.cpp garbage.cpp challenge.cpp verification.cpp
HEADERS = commitment.hpp decompose.hpp garbage.hpp types.hpp protocol.hpp projection.hpp aggregation.hpp challenge.hpp verification.hpp


labrador: $(SOURCES) $(HEADERS)
	$(CXX) -o $@ $(SOURCES) $(CXXFLAGS)