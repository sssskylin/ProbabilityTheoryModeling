#include "UniformDistribution.hpp"

using namespace ptm;

UniformDistribution::UniformDistribution(double a, double b) {
  a_ = a;
  b_ = b;
}

[[nodiscard]] double UniformDistribution::Pdf(double x) const {
  if (x < a_) {
    return 0;
  } else if (x > b_) {
    return 1;
  } else {
    return 1.0 / (b_ - a_);
  }
}

[[nodiscard]] double UniformDistribution::Cdf(double x) const {
  if (x < a_) {
    return 0;
  } else if (x > b_) {
    return 1;
  } else {
    return (x - a_) / (b_ - a_);
  }
}

double UniformDistribution::Sample(std::mt19937& rng) const {
  std::uniform_real_distribution<> d(a_, b_);
  return d(rng);
}

[[nodiscard]] double UniformDistribution::TheoreticalMean() const {
  return (a_ + b_) / 2;
}
[[nodiscard]] double UniformDistribution::TheoreticalVariance() const {
  return (b_ - a_) * (b_ - a_) / 12;
}