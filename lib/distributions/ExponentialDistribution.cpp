#include "ExponentialDistribution.hpp"

using namespace ptm;

explicit ExponentialDistribution::ExponentialDistribution(double lambda) {
  if (lambda <= 0) {
    throw std::runtime_error(
        "Exponetial distribution parameter should be positive");
  }
  lambda_ = lambda;
}

[[nodiscard]] double ExponentialDistribution::Pdf(double x) const {
  if (x < 0) {
    return 0;
  } else {
    return lambda_ * std::pow(std::numbers::e, -lambda_ * x);
  }
}

[[nodiscard]] double ExponentialDistribution::Cdf(double x) const {
  if (x < 0) {
    return 0;
  } else {
    return 1 - std::pow(std::numbers::e, -lambda_ * x);
  }
}

double ExponentialDistribution::Sample(std::mt19937& rng) const {
  std::exponential_distribution<> d(lambda_);
  return d(rng);
}

[[nodiscard]] double ExponentialDistribution::TheoreticalMean() const {
  return 1.0 / lambda_;
}

[[nodiscard]] double ExponentialDistribution::TheoreticalVariance() const {
  return 1.0 / lambda_ / lambda_;
}