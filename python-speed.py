#!/usr/bin/env python3
# -*- encoding: utf-8 -*-

import timeit
import numpy as np


def f(r, x1, x2, x3, x4, x5, x6, x7, x8):
    r = x1 + x2


def g(r, x1, x2, x3, x4, x5, x6, x7, x8):
    r = x1 + x2 - x3


def h(r, x1, x2, x3, x4, x5, x6, x7, x8):
    r = x1 + x2 - x3 + x4


def i(r, x1, x2, x3, x4, x5, x6, x7, x8):
    r = x1 + x2 - x3 + x4 - x5


def j(r, x1, x2, x3, x4, x5, x6, x7, x8):
    r = x1 + x2 - x3 + x4 - x5 + x6


def k(r, x1, x2, x3, x4, x5, x6, x7, x8):
    r = x1 + x2 - x3 + x4 - x5 + x6 - x7


def l(r, x1, x2, x3, x4, x5, x6, x7, x8):
    r = x1 + x2 - x3 + x4 - x5 + x6 - x7 + x8


N = 1000000
x = [np.random.randn(N) for i in range(8)]
result = np.empty(N)


def printtest(num, stmt):
    num_of_calls = 1
    setup = 'from __main__ import f, g, h, i, j, k, l, x, result'

    minval = np.min(timeit.repeat(stmt, repeat=300,
                                  number=num_of_calls, setup=setup))
    print('{0}\t{1:.2f}'.format(num, minval / num_of_calls * 1e3))


print("Terms\tSpeed [ms]")
for idx, fnname in enumerate(['f', 'g', 'h', 'i', 'j', 'k', 'l']):
    printtest(2 + idx, fnname + '(result, *x)')
