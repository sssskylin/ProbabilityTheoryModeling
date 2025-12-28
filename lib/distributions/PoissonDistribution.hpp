#ifndef PTM_POISSONDISTRIBUTION_HPP_
#define PTM_POISSONDISTRIBUTION_HPP_

#include <cmath>
#include <numbers>
#include <random>
#include <stdexcept>

#include "Distribution.hpp"

namespace ptm {

// Пуассоновское Poisson(lambda)
class PoissonDistribution : public Distribution {
 public:
  explicit PoissonDistribution(double lambda) {
    if (lambda < 0) {
      throw std::runtime_error("Amount of events can't be negative");
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

#endif  // PTM_POISSONDISTRIBUTION_HPP_
