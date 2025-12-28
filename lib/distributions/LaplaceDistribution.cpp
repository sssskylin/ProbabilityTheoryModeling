#include "LaplaceDistribution.hpp"

using namespace ptm;

LaplaceDistribution::LaplaceDistribution(double mu, double b) {
  if (b <= 0) {
    throw std::runtime_error("Scale parameter can not be negative");
  }

  mu_ = mu;
  b_ = b;
}

[[nodiscard]] double LaplaceDistribution::Pdf(double x) const {
  return 1.0 / (2.0 * b_) * std::exp(-std::abs(x - mu_) / b_);
}

[[nodiscard]] double LaplaceDistribution::Cdf(double x) const {
  if (x <= mu_) {
    return 0.5 * std::exp((x - mu_) / b_);
  } else {
    return 1 - 0.5 * std::exp(-(x - mu_) / b_);
  }
}

double LaplaceDistribution::Sample(std::mt19937& rng) const {
  std::uniform_real_distribution<> d(0, 1);
  double y = d(rng);
  return InvertedCdf(y);
}

[[nodiscard]] double LaplaceDistribution::TheoreticalMean() const { return mu_; }

[[nodiscard]] double LaplaceDistribution::TheoreticalVariance() const {
  return 2.0 * b_ * b_;
}

double LaplaceDistribution::InvertedCdf(double x) const {
  if (x < 0.5) {
    return mu_ + b_ * std::log(2 * x);
  } else {
    return mu_ - b_ * std::log(2 * (1 - x));
  }
}
