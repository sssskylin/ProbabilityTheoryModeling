#ifndef PTM_DISCRETERANDOMVARIABLE_HPP_
#define PTM_DISCRETERANDOMVARIABLE_HPP_

#include <optional>
#include <vector>

#include "OutcomeSpace.hpp"
#include "ProbabilityMeasure.hpp"

namespace ptm {

class DiscreteRandomVariable {
public:
  DiscreteRandomVariable(const OutcomeSpace& omega, const ProbabilityMeasure& P, std::vector<double> values);

  std::optional<double> Value(OutcomeSpace::OutcomeId id) const;
  double ExpectedValue() const;

private:
  const OutcomeSpace& omega_;
  const ProbabilityMeasure& P_;
  std::vector<double> values_; // X(ω_i)
};

} // namespace ptm

#endif // PTM_DISCRETERANDOMVARIABLE_HPP_
