#include <chrono>
#include <iostream>
#include <vector>

#include <gsl/gsl_randist.h>
#include <gsl/gsl_rng.h>

typedef std::vector<double> Vect;

void f(Vect &result, const Vect &x1, const Vect &x2, const Vect &x3,
       const Vect &x4, const Vect &x5, const Vect &x6, const Vect &x7,
       const Vect &x8) {
  for (size_t i = 0; i < x1.size(); ++i) {
    result[i] = x1[i] + x2[i];
  }
}

void g(Vect &result, const Vect &x1, const Vect &x2, const Vect &x3,
       const Vect &x4, const Vect &x5, const Vect &x6, const Vect &x7,
       const Vect &x8) {
  for (size_t i = 0; i < x1.size(); ++i) {
    result[i] = x1[i] + x2[i] - x3[i];
  }
}

void h(Vect &result, const Vect &x1, const Vect &x2, const Vect &x3,
       const Vect &x4, const Vect &x5, const Vect &x6, const Vect &x7,
       const Vect &x8) {
  for (size_t i = 0; i < x1.size(); ++i) {
    result[i] = x1[i] + x2[i] - x3[i] + x4[i];
  }
}

void i(Vect &result, const Vect &x1, const Vect &x2, const Vect &x3,
       const Vect &x4, const Vect &x5, const Vect &x6, const Vect &x7,
       const Vect &x8) {
  for (size_t i = 0; i < x1.size(); ++i) {
    result[i] = x1[i] + x2[i] - x3[i] + x4[i] - x5[i];
  }
}

void j(Vect &result, const Vect &x1, const Vect &x2, const Vect &x3,
       const Vect &x4, const Vect &x5, const Vect &x6, const Vect &x7,
       const Vect &x8) {
  for (size_t i = 0; i < x1.size(); ++i) {
    result[i] = x1[i] + x2[i] - x3[i] + x4[i] - x5[i] + x6[i];
  }
}

void k(Vect &result, const Vect &x1, const Vect &x2, const Vect &x3,
       const Vect &x4, const Vect &x5, const Vect &x6, const Vect &x7,
       const Vect &x8) {
  for (size_t i = 0; i < x1.size(); ++i) {
    result[i] = x1[i] + x2[i] - x3[i] + x4[i] - x5[i] + x6[i] - x7[i];
  }
}

void l(Vect &result, const Vect &x1, const Vect &x2, const Vect &x3,
       const Vect &x4, const Vect &x5, const Vect &x6, const Vect &x7,
       const Vect &x8) {
  for (size_t i = 0; i < x1.size(); ++i) {
    result[i] = x1[i] + x2[i] - x3[i] + x4[i] - x5[i] + x6[i] - x7[i] + x8[i];
  }
}

template <typename F>
double benchmark(F function, int num, const Vect &x1, const Vect &x2,
                 const Vect &x3, const Vect &x4, const Vect &x5, const Vect &x6,
                 const Vect &x7, const Vect &x8) {
  Vect result(x1.size());
  double best_time;
  for (int i = 0; i < num; ++i) {
    auto start = std::chrono::steady_clock::now();
    function(result, x1, x2, x3, x4, x5, x6, x7, x8);
    auto end = std::chrono::steady_clock::now();
    auto diff = end - start;

    double cur_time = std::chrono::duration<double, std::milli>(diff).count();
    if (i == 0)
      best_time = cur_time;
    else {
      if (cur_time < best_time)
        best_time = cur_time;
    }
  }

  return best_time;
}

int main() {
  constexpr int N = 1000000;
  Vect x1(N);
  Vect x2(N);
  Vect x3(N);
  Vect x4(N);
  Vect x5(N);
  Vect x6(N);
  Vect x7(N);
  Vect x8(N);

  // Fill the vectors with random numbers
  gsl_rng *r = gsl_rng_alloc(gsl_rng_default);
  for (size_t i = 0; i < N; ++i) {
    x1[i] = gsl_ran_gaussian(r, 1.0);
    x2[i] = gsl_ran_gaussian(r, 1.0);
    x3[i] = gsl_ran_gaussian(r, 1.0);
    x4[i] = gsl_ran_gaussian(r, 1.0);
    x5[i] = gsl_ran_gaussian(r, 1.0);
    x6[i] = gsl_ran_gaussian(r, 1.0);
    x7[i] = gsl_ran_gaussian(r, 1.0);
    x8[i] = gsl_ran_gaussian(r, 1.0);
  }

  int n = 2;
  std::cout << "Terms\tSpeed [ms]\n";
  std::cout << n++ << '\t' << benchmark(f, 100, x1, x2, x3, x4, x5, x6, x7, x8)
            << '\n';
  std::cout << n++ << '\t' << benchmark(g, 100, x1, x2, x3, x4, x5, x6, x7, x8)
            << '\n';
  std::cout << n++ << '\t' << benchmark(h, 100, x1, x2, x3, x4, x5, x6, x7, x8)
            << '\n';
  std::cout << n++ << '\t' << benchmark(i, 100, x1, x2, x3, x4, x5, x6, x7, x8)
            << '\n';
  std::cout << n++ << '\t' << benchmark(j, 100, x1, x2, x3, x4, x5, x6, x7, x8)
            << '\n';
  std::cout << n++ << '\t' << benchmark(k, 100, x1, x2, x3, x4, x5, x6, x7, x8)
            << '\n';
  std::cout << n++ << '\t' << benchmark(l, 100, x1, x2, x3, x4, x5, x6, x7, x8)
            << '\n';
}
