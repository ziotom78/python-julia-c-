PYTHON := python3
JULIA := julia
GPP := g++

CXXFLAGS = `gsl-config --cflags` -O3
LDFLAGS = -O3
LOADLIBES = `gsl-config --libs`

.phony: all

all: c++-speed-results.txt python-speed-results.txt julia-speed-results.txt

c++-speed-results.txt: c++-speed
	./$< > $@

python-speed-results.txt: python-speed.py
	$(PYTHON) $< > $@

julia-speed-results.txt: julia-speed.jl
	$(JULIA) $< > $@

c++-speed: c++-speed.cpp
	$(GPP) -o $@ $< $(CXXFLAGS) $(LDFLAGS) $(LOADLIBES)
