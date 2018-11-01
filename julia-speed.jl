using BenchmarkTools
using Random
using Statistics: minimum
using Printf

f(r, x1, x2, x3, x4, x5, x6, x7, x8) = @. r = x1 + x2
g(r, x1, x2, x3, x4, x5, x6, x7, x8) = @. r = x1 + x2 - x3
h(r, x1, x2, x3, x4, x5, x6, x7, x8) = @. r = x1 + x2 - x3 + x4
i(r, x1, x2, x3, x4, x5, x6, x7, x8) = @. r = x1 + x2 - x3 + x4 - x5
j(r, x1, x2, x3, x4, x5, x6, x7, x8) = @. r = x1 + x2 - x3 + x4 - x5 + x6
k(r, x1, x2, x3, x4, x5, x6, x7, x8) = @. r = x1 + x2 - x3 + x4 - x5 + x6 - x7
l(r, x1, x2, x3, x4, x5, x6, x7, x8) = @. r = x1 + x2 - x3 + x4 - x5 + x6 - x7 + x8

N = 1000000
rng = MersenneTwister(1234)
x = [Random.randn(rng, N) for i in 1:8]
function print_result(num, b)
    best = minimum(b)
    # The member "time" is in ns
    @printf("%d\t%8.2f\t%.2f\n", num, best.time / 1e6, best.memory / 1024^2)
end

result = Array{Float64}(undef, N)

println("Terms\tSpeed [ms]\tMemory [MB]")
print_result(2, @benchmark f(result, x...))
print_result(3, @benchmark g(result, x...))
print_result(4, @benchmark h(result, x...))
print_result(5, @benchmark i(result, x...))
print_result(6, @benchmark j(result, x...))
print_result(7, @benchmark k(result, x...))
print_result(8, @benchmark l(result, x...))
