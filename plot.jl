using PyPlot
using DelimitedFiles

filenames = [
    ("G++ 7.3.0, flags -O3 -march", "c++-speed-results.txt"),
    ("Python 3.6.6 + NumPy 1.15.1", "python-speed-results.txt"),
    ("Julia 1.0.1", "julia-speed-results.txt"),
]

for (language, filename) in filenames
    data, header = readdlm(filename, header=true)

    plot(data[:, 1], data[:, 2], "o-", label=language)
end

xlabel("Number of terms in the expression")
ylabel("Best speed (100 runs) [ms]")
legend()
xticks(2:8)

savefig("python-julia-array-speed.pdf", dpi=600, bbox_inches="tight")
