#include "Event.hpp"
#include <stdexcept>

namespace ptm {

Event::Event(std::vector<bool> mask) : mask_(std::move(mask)) {}

size_t Event::GetSize() const noexcept {
    return mask_.size();
}
    
bool Event::Contains(OutcomeSpace::OutcomeId id) const {
    if (id >= mask_.size()) {
        throw std::out_of_range("OutcomeId out of range");
    }

    return mask_[id];
}
    
const std::vector<bool>& Event::GetMask() const noexcept {
    return mask_;
}
    
Event Event::Empty(std::size_t n) {
    return Event(std::vector<bool>(n, false));
}
    
Event Event::Full(std::size_t n) {
    return Event(std::vector<bool>(n, true));
}
    
Event Event::Complement(const Event& e) {
    std::vector<bool> result = e.mask_;
    for (size_t i = 0; i < result.size(); ++i) {
        result[i] = !result[i];
    }

    return Event(result);
}
    
Event Event::Unite(const Event& a, const Event& b) {
    if (a.mask_.size() != b.mask_.size()) {
        throw std::invalid_argument("Events have different sizes");
    }
    
    std::vector<bool> result(a.mask_.size());
    for (size_t i = 0; i < a.mask_.size(); ++i) {
        result[i] = a.mask_[i] || b.mask_[i];
    }

    return Event(result);
}
    
Event Event::Intersect(const Event& a, const Event& b) {
    if (a.mask_.size() != b.mask_.size()) {
        throw std::invalid_argument("Events have different sizes");
    }
    
    std::vector<bool> result(a.mask_.size());
    for (size_t i = 0; i < a.mask_.size(); ++i) {
        result[i] = a.mask_[i] && b.mask_[i];
    }

    return Event(result);
}
}