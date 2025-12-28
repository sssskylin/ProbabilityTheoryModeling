#include "DistributionExperiment.hpp"
#include <stdexcept>

using namespace ptm;

DistributionExperiment::DistributionExperiment(
    std::shared_ptr<Distribution> dist, size_t sample_size) {
  if (dist == nullptr) {
    throw std::runtime_error("Distribution should not be null");
  }

  dist_ = dist;
  sample_size_ = sample_size;
}

ExperimentStats DistributionExperiment::Run(std::mt19937& rng) {
  ExperimentStats results;

  std::vector<double> samples(sample_size_);

  for (size_t i = 0; i < sample_size_; ++i) {
    samples[i] = dist_->Sample(rng);
  }

  double sample_mean = std::accumulate(samples.begin(), samples.end(), 0.0) * 1.0 / sample_size_;
  double sample_variance = 0.0;

  for (int j = 0; j < sample_size_; ++j) {
    double deviation = (samples[j] - sample_mean);
    sample_variance += deviation * deviation;
  }

  results.empirical_mean = sample_mean;
  results.empirical_variance = sample_variance / (sample_size_ - 1);
  results.mean_error = std::abs(sample_mean - dist_->TheoreticalMean());
  results.variance_error =
      std::abs(results.empirical_variance - dist_->TheoreticalVariance());

  return results;
}

std::vector<double> DistributionExperiment::EmpiricalCdf(
    const std::vector<double>& grid, std::mt19937& rng,
    std::size_t sample_size) {
  std::vector<double> samples(sample_size);

  for (size_t i = 0; i < sample_size; ++i) {
    samples[i] = dist_->Sample(rng);
  }

  std::sort(samples.begin(), samples.end());
  std::vector<double> results;

  for (double x : grid) {
    auto it = std::upper_bound(samples.begin(), samples.end(), x);
    double fx = it - samples.begin();
    results.emplace_back(fx / sample_size);
  }

  return results;
}

[[nodiscard]] double DistributionExperiment::KolmogorovDistance(
    const std::vector<double>& grid,
    const std::vector<double>& empirical_cdf) const {
  if (grid.size() != empirical_cdf.size()) {
    throw std::runtime_error(
        "grid and empirical_cdf vector must be same size...");
  }

  size_t size = grid.size();
  double Kolmogorov_distance = 0.0;
  for (size_t i = 0; i < size; ++i) {
    double theory_cdf = dist_->Cdf(grid[i]);
    double distance = std::abs(theory_cdf - empirical_cdf[i]);

    if (Kolmogorov_distance < distance) {
      Kolmogorov_distance = distance;
    }
  }

  return Kolmogorov_distance;
}