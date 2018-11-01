PYTHON := python3
JULIA := julia
GPP := g++

CXXFLAGS = `gsl-config --cflags` -O3 -march=native -msse3
LOADLIBES = `gsl-config --libs`

.phony: all

all: python-julia-array-speed.pdf \
	c++-speed-results.txt \
	python-speed-results.txt \
	julia-speed-results.txt \
	julia-simd-speed-results.txt

python-julia-array-speed.pdf: c++-speed-results.txt python-speed-results.txt julia-speed-results.txt julia-simd-speed-results.txt
	$(JULIA) plot.jl

c++-speed-results.txt: c++-speed
	./$< | tee $@

python-speed-results.txt: python-speed.py
	$(PYTHON) $< | tee $@

julia-speed-results.txt: julia-speed.jl
	$(JULIA) $< | tee $@

julia-simd-speed-results.txt: julia-simd-speed.jl
	$(JULIA) $< | tee $@

c++-speed: c++-speed.cpp
	$(GPP) -o $@ $< $(CXXFLAGS) $(LDFLAGS) $(LOADLIBES)
