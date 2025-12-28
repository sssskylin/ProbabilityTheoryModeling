#include "NormalDistribution.hpp"

using namespace ptm;

NormalDistribution::NormalDistribution(double mean, double stddev) {
  if (stddev <= 0) {
    throw std::runtime_error("Standard deviation must be positive");
  }
  mean_ = mean;
  stddev_ = stddev;
}

[[nodiscard]] double NormalDistribution::Pdf(double x) const {
  double e_power = -(x - mean_) * (x - mean_) / (2 * stddev_ * stddev_);

  return 1.0 / (stddev_ * sqrt(2 * std::numbers::pi)) *
         std::pow(std::numbers::e, e_power);
}

[[nodiscard]] double NormalDistribution::Cdf(double x) const {
  double z = (x - mean_) / (stddev_ * std::sqrt(2.0));

  return 0.5 * (1.0 + std::erf(z));
}
double NormalDistribution::Sample(std::mt19937& rng) const {
  std::normal_distribution d(mean_, stddev_);
  return d(rng);
}

[[nodiscard]] double NormalDistribution::TheoreticalMean() const {
  return mean_;
}

[[nodiscard]] double NormalDistribution::TheoreticalVariance() const {
  return stddev_ * stddev_;
}

[[nodiscard]] double NormalDistribution::GetMean() const {
  return mean_;
}

[[nodiscard]] double NormalDistribution::GetStddev() const {
  return stddev_;
}