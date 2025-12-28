#include "LaplaceDistribution.hpp"

using namespace ptm;

LaplaceDistribution::LaplaceDistribution(double mu, double b) {
  if (mu <= 0) {
    throw std::runtime_error("Scale parameter can not be negative");
  }

  mu_ = mu;
  b_ = b;
}

[[nodiscard]] double LaplaceDistribution::Pdf(double x) const {
  double e_power = -mu_ * std::abs(x - b_);

  return mu_ / 2 * std::pow(std::numbers::e, e_power);
}

[[nodiscard]] double LaplaceDistribution::Cdf(double x) const {
  double e_power = mu_ * (x - b_);

  if (x <= b_) {
    return 0.5 * std::pow(std::numbers::e, e_power);
  } else {
    return 1 - 0.5 * std::pow(std::numbers::e, -e_power);
  }
}

double LaplaceDistribution::Sample(std::mt19937& rng) const {
  std::uniform_real_distribution<> d(0, 1);
  double y = d(rng);
  return InvertedCdf(y);
}

[[nodiscard]] double LaplaceDistribution::TheoreticalMean() const { return b_; }

[[nodiscard]] double LaplaceDistribution::TheoreticalVariance() const {
  return 2.0 / mu_ / mu_;
}

double LaplaceDistribution::InvertedCdf(double x) const {
  if (x < 0.5) {
    return b_ + std::log(2 * x) / mu_;
  } else {
    return b_ - std::log(2 * (1 - x)) / mu_;
  }
}
