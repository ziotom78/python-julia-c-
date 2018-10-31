#!/usr/bin/env python3
# -*- encoding: utf-8 -*-

import timeit
import numpy as np


def f(x1, x2, x3, x4, x5, x6):
    return x1 + x2


def g(x1, x2, x3, x4, x5, x6):
    return x1 + x2 - x3


def h(x1, x2, x3, x4, x5, x6):
    return x1 + x2 - x3 + x4


def i(x1, x2, x3, x4, x5, x6):
    return x1 + x2 - x3 + x4 - x5


def j(x1, x2, x3, x4, x5, x6):
    return x1 + x2 - x3 + x4 - x5 + x6


N = 1000000
x = [np.random.randn(N) for i in range(6)]


def printtest(num, stmt):
    num_of_calls = 1
    setup = 'from __main__ import f, g, h, i, j, x'

    minval = np.min(timeit.repeat(stmt, repeat=300,
                                  number=num_of_calls, setup=setup))
    print('{0}\t{1:.2f}'.format(num, minval / num_of_calls * 1e3))


print("Terms\tSpeed [ms]")
printtest(2, 'f(*x)')
printtest(3, 'g(*x)')
printtest(4, 'h(*x)')
printtest(5, 'i(*x)')
printtest(6, 'j(*x)')
