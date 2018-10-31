#include <chrono>
#include <iostream>
#include <vector>

#include <gsl/gsl_randist.h>
#include <gsl/gsl_rng.h>

void f(std::vector<double> &result, const std::vector<double> &x1,
       const std::vector<double> &x2, const std::vector<double> &x3,
       const std::vector<double> &x4, const std::vector<double> &x5,
       const std::vector<double> &x6) {
  for (unsigned int i = 0; i < x1.size(); ++i) {
    result[i] = x1[i] + x2[i];
  }
}

void g(std::vector<double> &result, const std::vector<double> &x1,
       const std::vector<double> &x2, const std::vector<double> &x3,
       const std::vector<double> &x4, const std::vector<double> &x5,
       const std::vector<double> &x6) {
  for (unsigned int i = 0; i < x1.size(); ++i) {
    result[i] = x1[i] + x2[i] - x3[i];
  }
}

void h(std::vector<double> &result, const std::vector<double> &x1,
       const std::vector<double> &x2, const std::vector<double> &x3,
       const std::vector<double> &x4, const std::vector<double> &x5,
       const std::vector<double> &x6) {
  for (unsigned int i = 0; i < x1.size(); ++i) {
    result[i] = x1[i] + x2[i] - x3[i] + x4[i];
  }
}

void i(std::vector<double> &result, const std::vector<double> &x1,
       const std::vector<double> &x2, const std::vector<double> &x3,
       const std::vector<double> &x4, const std::vector<double> &x5,
       const std::vector<double> &x6) {
  for (unsigned int i = 0; i < x1.size(); ++i) {
    result[i] = x1[i] + x2[i] - x3[i] + x4[i] - x5[i];
  }
}

void j(std::vector<double> &result, const std::vector<double> &x1,
       const std::vector<double> &x2, const std::vector<double> &x3,
       const std::vector<double> &x4, const std::vector<double> &x5,
       const std::vector<double> &x6) {
  for (unsigned int i = 0; i < x1.size(); ++i) {
    result[i] = x1[i] + x2[i] - x3[i] + x4[i] - x5[i] + x6[i];
  }
}

template <typename F>
double benchmark(F function, int num, std::vector<double> x1,
                 std::vector<double> x2, std::vector<double> x3,
                 std::vector<double> x4, std::vector<double> x5,
                 std::vector<double> x6) {
  std::vector<double> result(x1.size());
  double best_time;
  for (int i = 0; i < num; ++i) {
    auto start = std::chrono::steady_clock::now();
    function(result, x1, x2, x3, x4, x5, x6);
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
  std::vector<double> x1(N);
  std::vector<double> x2(N);
  std::vector<double> x3(N);
  std::vector<double> x4(N);
  std::vector<double> x5(N);
  std::vector<double> x6(N);

  // Fill the vectors with random numbers
  gsl_rng *r = gsl_rng_alloc(gsl_rng_default);
  for (unsigned int i = 0; i < N; ++i) {
    x1[i] = gsl_ran_gaussian(r, 1.0);
    x2[i] = gsl_ran_gaussian(r, 1.0);
    x3[i] = gsl_ran_gaussian(r, 1.0);
    x4[i] = gsl_ran_gaussian(r, 1.0);
    x5[i] = gsl_ran_gaussian(r, 1.0);
    x6[i] = gsl_ran_gaussian(r, 1.0);
  }

  int n = 2;
  std::cout << "Terms\tSpeed [ms]\n";
  std::cout << n++ << '\t' << benchmark(f, 100, x1, x2, x3, x4, x5, x6) << '\n';
  std::cout << n++ << '\t' << benchmark(g, 100, x1, x2, x3, x4, x5, x6) << '\n';
  std::cout << n++ << '\t' << benchmark(h, 100, x1, x2, x3, x4, x5, x6) << '\n';
  std::cout << n++ << '\t' << benchmark(i, 100, x1, x2, x3, x4, x5, x6) << '\n';
  std::cout << n++ << '\t' << benchmark(j, 100, x1, x2, x3, x4, x5, x6) << '\n';
}
