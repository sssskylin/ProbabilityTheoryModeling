#include "MarkovChain.hpp"

namespace ptm {

void MarkovChain::Train(const std::vector<State>& sequence) {
    if (sequence.size() < 2) {
        return;
    }

    for (size_t i = 0; i < sequence.size() - 1; ++i) {
        size_t from_index = ensureState(sequence[i]);
        size_t to_index = ensureState(sequence[i + 1]);

        ++counts_[from_index][to_index];
        ++row_sums_[from_index];
    }
}

[[nodiscard]] std::unordered_map<MarkovChain::State, double> MarkovChain::NextDistribution(const State& current) const {
    std::unordered_map<MarkovChain::State, double> distribution = std::unordered_map<MarkovChain::State, double>();

    size_t current_index = state_to_index_.at(current);
    int sum = row_sums_[current_index];

    if (sum == 0) {
        return distribution;
    }

    for (size_t i = 0; i < counts_[current_index].size(); ++i) {
        double probability = (double)counts_[current_index][i]/sum;

        if (probability == 0){
            continue;
        }

        distribution[index_to_state_[i]] = probability;
    }

    return distribution;
}

double MarkovChain::TransitionProbability(const State& from, const State& to) const {
    size_t from_index = state_to_index_.at(from);
    size_t to_index = state_to_index_.at(to);

    int to_cnt = counts_[from_index][to_index];
    int from_row_sum = row_sums_[from_index];

    if (from_row_sum == 0) {
        return 0;
    }

    return (double)to_cnt/from_row_sum;
}

std::optional<MarkovChain::State> MarkovChain::SampleNext(const State& current, std::mt19937& rng) const {
    if (state_to_index_.find(current) == state_to_index_.end()) {
        return std::nullopt;
    }

    size_t current_index = state_to_index_.at(current);

    if (row_sums_[current_index] == 0) {
        return std::nullopt;
    }

    std::discrete_distribution<size_t> dist(
        counts_[current_index].begin(),
        counts_[current_index].end()
    );
    size_t next_index = dist(rng);

    return index_to_state_[next_index];
}

std::vector<MarkovChain::State> MarkovChain::Generate(const State& start, size_t length, std::mt19937& rng) const {
    std::vector<MarkovChain::State> states = std::vector<MarkovChain::State>();

    if (state_to_index_.find(start) == state_to_index_.end()) {
        return states;
    }

    states.push_back(start);

    for(int i = 0; i < length - 1; ++i){
        std::optional<MarkovChain::State> next_state = SampleNext(states[states.size() - 1], rng);

        if(next_state == std::nullopt){
            return states;
        } 
        
        states.push_back(next_state.value());
    }

    return states;
}

std::vector<MarkovChain::State> MarkovChain::States() const {
    return index_to_state_;
}

size_t MarkovChain::ensureState(const State& s) {
    if(state_to_index_.find(s) != state_to_index_.end()){
        return state_to_index_.at(s);
    }

    state_to_index_[s] = index_to_state_.size();
    index_to_state_.push_back(s);

    for(auto& row : counts_) {
        row.push_back(0);
    }
    counts_.push_back(std::vector<size_t>(index_to_state_.size(), 0));
    row_sums_.push_back(0);

    return index_to_state_.size() - 1;
}
}
