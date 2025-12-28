#include "GeometricDistribution.hpp"

using namespace ptm;

GeometricDistribution::GeometricDistribution(double p) {
  if (p < 0 || p > 1) {
    throw std::runtime_error(
        "Probability can't be less than 0 or greater than 1");
  }

  p_ = p;
}

[[nodiscard]] double GeometricDistribution::Pdf(double x) const {
  return std::pow(1 - p_, x - 1) * p_;
}

[[nodiscard]] double GeometricDistribution::Cdf(double x) const {
  return 1 - std::pow(1 - p_, x);
}

double GeometricDistribution::Sample(std::mt19937& rng) const {
  std::geometric_distribution<> d(p_);
  return d(rng);
}

[[nodiscard]] double GeometricDistribution::TheoreticalMean() const {
  return 1.0 / p_;
}

[[nodiscard]] double GeometricDistribution::TheoreticalVariance() const {
  return (1 - p_) / p_ / p_;
}