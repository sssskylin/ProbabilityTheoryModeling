#include "BernoulliDistribution.hpp"

using namespace ptm;

[[nodiscard]] double BernoulliDistribution::Pdf(double x) const {
  if (x == 1) {
    return p_;
  } else if (x == 0) {
    return 1 - p_;
  } else {
    return 0;
  }
}

[[nodiscard]] double BernoulliDistribution::Cdf(double x) const {
  if (x > 1) {
    return 1;
  } else if (x > 0 && x <= 1) {
    return 1 - p_;
  } else {
    return 0;
  }
}

double BernoulliDistribution::Sample(std::mt19937& rng) const {
  std::bernoulli_distribution d(p_);
  return d(rng);
}

[[nodiscard]] double BernoulliDistribution::TheoreticalMean() const {
  return p_;
}

[[nodiscard]] double BernoulliDistribution::TheoreticalVariance() const {
  return p_ * (1 - p_);
}