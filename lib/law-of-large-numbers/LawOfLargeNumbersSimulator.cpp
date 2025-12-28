#include "LawOfLargeNumbersSimulator.hpp"


namespace ptm {

LawOfLargeNumbersSimulator::LawOfLargeNumbersSimulator(std::shared_ptr<Distribution> dist) : dist_(dist) {}

LLNPathResult LawOfLargeNumbersSimulator::Simulate(std::mt19937& rng, size_t max_n, size_t step) const {
    if (step == 0) return {};

    LLNPathResult result;
    result.entries.reserve(max_n / step);
    double sum = 0;

    for (size_t i = 1; i < max_n; ++i) {
        double sample = dist_->Sample(rng);
        sum += sample;

        if (i % step == 0) {
            double sample_mean = sum / i;
            LLNPathEntry entry = LLNPathEntry{
                .n = i,
                .sample_mean = sample_mean,
                .abs_error = std::abs(sample_mean - dist_->TheoreticalMean())
            };
            result.entries.push_back(entry);
        }
    }
    return result;
}

[[nodiscard]] std::shared_ptr<Distribution> LawOfLargeNumbersSimulator::GetDistribution() const noexcept {
    return dist_;
}


}