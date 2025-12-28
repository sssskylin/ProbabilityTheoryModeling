#include "CauchyDistribution.hpp"
#include <stdexcept>

using namespace ptm;

CauchyDistribution::CauchyDistribution(double x0, double gamma) {
  if (gamma <= 0) {
    throw std::runtime_error("Scale parameter cannot be negative");
  }

  x0_ = x0;
  gamma_ = gamma;
}

[[nodiscard]] double CauchyDistribution::Pdf(double x) const {
  double denominator = (x - x0_) * (x - x0_) + gamma_ * gamma_;

  return (1.0 / std::numbers::pi) * (gamma_ / denominator);
}

[[nodiscard]] double CauchyDistribution::Cdf(double x) const {
  double arctg = std::atan((x - x0_) / gamma_);

  return (1.0 / std::numbers::pi) * arctg + 0.5;
}

double CauchyDistribution::Sample(std::mt19937& rng) const {
  std::cauchy_distribution<double> d(x0_, gamma_);
  return d(rng);
}

[[nodiscard]] double CauchyDistribution::TheoreticalMean() const {
  return std::nan("");
}

[[nodiscard]] double CauchyDistribution::TheoreticalVariance() const {
  return std::nan("");
}