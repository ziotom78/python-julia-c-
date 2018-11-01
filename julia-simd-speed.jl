using BenchmarkTools
using Random
using Statistics: minimum
using Printf

function f(r, x1, x2, x3, x4, x5, x6, x7, x8)
    @inbounds @simd for i in eachindex(x1)
        r[i] = x1[i] + x2[i]
    end
end

function g(r, x1, x2, x3, x4, x5, x6, x7, x8)
    @inbounds @simd for i in eachindex(x1)
        r[i] = x1[i] + x2[i] - x3[i]
    end
end

function h(r, x1, x2, x3, x4, x5, x6, x7, x8)
    @inbounds @simd for i in eachindex(x1)
        r[i] = x1[i] + x2[i] - x3[i] + x4[i]
    end
end

function i(r, x1, x2, x3, x4, x5, x6, x7, x8)
    @inbounds @simd for i in eachindex(x1)
        r[i] = x1[i] + x2[i] - x3[i] + x4[i] - x5[i]
    end
end

function j(r, x1, x2, x3, x4, x5, x6, x7, x8)
    @inbounds @simd for i in eachindex(x1)
        r[i] = x1[i] + x2[i] - x3[i] + x4[i] - x5[i] + x6[i]
    end
end

function k(r, x1, x2, x3, x4, x5, x6, x7, x8)
    @inbounds @simd for i in eachindex(x1)
        r[i] = x1[i] + x2[i] - x3[i] + x4[i] - x5[i] + x6[i] - x7[i]
    end
end

function l(r, x1, x2, x3, x4, x5, x6, x7, x8)
    @inbounds @simd for i in eachindex(x1)
        r[i] = x1[i] + x2[i] - x3[i] + x4[i] - x5[i] + x6[i] - x7[i] + x8[i]
    end
end

N = 1000000
rng = MersenneTwister(1234)
x = [Random.randn(rng, N) for i in 1:8]
function print_result(num, b)
    best = minimum(b)
    # The member "time" is in ns
    @printf("%d\t%8.2f\n", num, best.time / 1e6)
end

result = Array{Float64}(undef, N)

println("Terms\tSpeed [ms]")
print_result(2, @benchmark f(result, x...))
print_result(3, @benchmark g(result, x...))
print_result(4, @benchmark h(result, x...))
print_result(5, @benchmark i(result, x...))
print_result(6, @benchmark j(result, x...))
print_result(7, @benchmark k(result, x...))
print_result(8, @benchmark l(result, x...))
