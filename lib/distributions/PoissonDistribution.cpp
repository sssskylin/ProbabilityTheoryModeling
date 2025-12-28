#include "PoissonDistribution.hpp"

using namespace ptm;

[[nodiscard]] double PoissonDistribution::Pdf(double x) const {
  double lambda_divided_by_factorial = 1;

  for (double i = 1; i <= x; ++i) {
    lambda_divided_by_factorial = lambda_ / i;
  }

  return lambda_divided_by_factorial * std::pow(std::numbers::e, -lambda_);
}

[[nodiscard]] double PoissonDistribution::Cdf(double x) const {
  double sum = 0;

  for (double i = 0; i <= x; ++i) {
    sum += Pdf(i);
  }

  return sum;
}

double PoissonDistribution::Sample(std::mt19937& rng) const {
  std::poisson_distribution<> d(lambda_);
  return d(rng);
}

[[nodiscard]] double PoissonDistribution::TheoreticalMean() const {
  return lambda_;
}
[[nodiscard]] double PoissonDistribution::TheoreticalVariance() const {
  return lambda_;
}