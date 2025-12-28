#ifndef PTM_BERNOULLIDISTRIBUTION_HPP_
#define PTM_BERNOULLIDISTRIBUTION_HPP_

#include <cmath>
#include <random>

#include "Distribution.hpp"

namespace ptm {

// Бернулли Bernoulli(p)
class BernoulliDistribution : public Distribution {
 public:
  explicit BernoulliDistribution(double p) {
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

#endif  // PTM_BERNOULLIDISTRIBUTION_HPP_
