#ifndef PTM_GEOMETRICDISTRIBUTION_HPP_
#define PTM_GEOMETRICDISTRIBUTION_HPP_

#include <cmath>
#include <random>
#include <stdexcept>

#include "Distribution.hpp"

namespace ptm {

// Геометрическое Geom(p) на {1, 2, 3, ...}
class GeometricDistribution : public Distribution {
 public:
  explicit GeometricDistribution(double p) {
    if (p < 0 || p > 1) {
      throw std::runtime_error(
          "Probability can't be less than 0 or greater than 1");
    }

    p_ = p;
  }

  [[nodiscard]] double Pdf(double x) const override;
  [[nodiscard]] double Cdf(double x) const override;
  double Sample(std::mt19937& rng) const override;

  [[nodiscard]] double TheoreticalMean() const override;
  [[nodiscard]] double TheoreticalVariance() const override;

 private:
  double p_;
};

}  // namespace ptm

#endif  // PTM_GEOMETRICDISTRIBUTION_HPP_
