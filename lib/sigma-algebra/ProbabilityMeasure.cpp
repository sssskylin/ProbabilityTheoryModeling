#include "ProbabilityMeasure.hpp"
#include <stdexcept>
#include <cmath>

namespace ptm {

ProbabilityMeasure::ProbabilityMeasure(const OutcomeSpace& omega) 
    : omega_(omega), atom_probs_(omega.GetSize(), 0.0) {}

void ProbabilityMeasure::SetAtomicProbability(OutcomeSpace::OutcomeId id, double p) {
    if (id >= atom_probs_.size()) {
        throw std::out_of_range("OutcomeId out of range");
    }

    if (p < 0.0 || p > 1.0) {
        throw std::invalid_argument("Probability must be in [0, 1]");
    }

    atom_probs_[id] = p;
}

double ProbabilityMeasure::GetAtomicProbability(OutcomeSpace::OutcomeId id) const {
    if (id >= atom_probs_.size()) {
        throw std::out_of_range("OutcomeId out of range");
    }

    return atom_probs_[id];
}

bool ProbabilityMeasure::IsValid(double eps) const {
    double sum = 0.0;
    for (double p : atom_probs_) {
        if (p < 0.0) return false;
        sum += p;
    }

    return std::abs(sum - 1.0) < eps;
}

double ProbabilityMeasure::Probability(const Event& event) const {
    if (event.GetSize() != atom_probs_.size()) {
        throw std::invalid_argument("Event size doesn't match outcome space size");
    }
  
    double prob = 0.0;
    const auto& mask = event.GetMask();
    for (size_t i = 0; i < mask.size(); ++i) {
        if (mask[i]) {
            prob += atom_probs_[i];
        }
    }

    return prob;
}
}