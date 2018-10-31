using BenchmarkTools
using Random
using Statistics: minimum
using Printf

f(x1, x2, x3, x4, x5, x6) = @. x1 + x2
g(x1, x2, x3, x4, x5, x6) = @. x1 + x2 - x3
h(x1, x2, x3, x4, x5, x6) = @. x1 + x2 - x3 + x4
i(x1, x2, x3, x4, x5, x6) = @. x1 + x2 - x3 + x4 - x5
j(x1, x2, x3, x4, x5, x6) = @. x1 + x2 - x3 + x4 - x5 + x6

N = 1000000
x = [Array{Float64}(undef, N) for i in 1:6]

function print_result(num, b)
    best = minimum(b)
    # The member "time" is in ns
    @printf("%d\t%8.2f\t%.2f\n", num, best.time / 1e6, best.memory / 1024^2)
end

println("Terms\tSpeed [ms]\tMemory [MB]")
print_result(2, @benchmark f(x...))
print_result(3, @benchmark g(x...))
print_result(4, @benchmark h(x...))
print_result(5, @benchmark i(x...))
print_result(6, @benchmark j(x...))
