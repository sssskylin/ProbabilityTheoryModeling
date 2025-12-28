#ifndef PTM_EXPONENTIALDISTRIBUTION_HPP_
#define PTM_EXPONENTIALDISTRIBUTION_HPP_

#include <cmath>
#include <numbers>
#include <stdexcept>

#include "Distribution.hpp"

namespace ptm {

class ExponentialDistribution : public Distribution {
 public:
  explicit ExponentialDistribution(double lambda) {
    if (lambda <= 0) {
      throw std::runtime_error(
          "Exponetial distribution parameter should be positive");
    }
    lambda_ = lambda;
  }

  [[nodiscard]] double Pdf(double x) const override;
  [[nodiscard]] double Cdf(double x) const override;
  double Sample(std::mt19937& rng) const override;

  [[nodiscard]] double TheoreticalMean() const override;
  [[nodiscard]] double TheoreticalVariance() const override;

 private:
  double lambda_;
};

}  // namespace ptm

#endif  // PTM_EXPONENTIALDISTRIBUTION_HPP_
