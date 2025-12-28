#include "BinomialDistribution.hpp"

using namespace ptm;

BinomialDistribution::BinomialDistribution(unsigned int n, double p) {
  if (n < 0) {
    throw std::runtime_error("There can't be 0 tests in series");
  }
  
  if (p < 0 || p > 1) {
    throw std::runtime_error(
        "Probability can't be less than 0 or greater than 1");
  }

  n_ = n;
  p_ = p;
}

[[nodiscard]] double BinomialDistribution::Pdf(double x) const {
  double binomial_coefficient = 1;

  for (double k = 1; k <= x; ++k) {
    binomial_coefficient *= (n_ - k + 1) / k;
  }

  return binomial_coefficient * std::pow(p_, x) * std::pow(1 - p_, 1 - x);
} 

[[nodiscard]] double BinomialDistribution::Cdf(double x) const {
  double sum = 0;

  for (double i = 0; i <= x; ++i) {
    sum += Pdf(i);
  }

  return sum;
}

double BinomialDistribution::Sample(std::mt19937& rng) const {
  std::binomial_distribution<> d(n_, p_);
  return d(rng);
}

[[nodiscard]] double BinomialDistribution::TheoreticalMean() const {
  return n_ * p_;
}

[[nodiscard]] double BinomialDistribution::TheoreticalVariance() const {
  return n_ * p_ * (1 - p_);
}