#include "SigmaAlgebra.hpp"
#include <algorithm>
#include <stdexcept>

namespace ptm {

SigmaAlgebra::SigmaAlgebra(const OutcomeSpace& omega, std::vector<Event> events)
    : omega_(omega), events_(std::move(events)) {}

const OutcomeSpace& SigmaAlgebra::GetOutcomeSpace() const noexcept {
    return omega_;
}

const std::vector<Event>& SigmaAlgebra::GetEvents() const noexcept {
    return events_;
}

bool SigmaAlgebra::IsSigmaAlgebra() const {
    if (events_.empty()) return false;
  
    size_t n = omega_.GetSize();
    Event empty = Event::Empty(n);
    Event full = Event::Full(n);
  
    bool has_empty = std::any_of(events_.begin(), events_.end(),
        [&empty](const Event& e) { return e.GetMask() == empty.GetMask(); });
    if (!has_empty) return false;
  
    bool has_full = std::any_of(events_.begin(), events_.end(),
        [&full](const Event& e) { return e.GetMask() == full.GetMask(); });
    if (!has_full) return false;
  
  
    for (const auto& event : events_) {
        Event complement = Event::Complement(event);
        bool found = std::any_of(events_.begin(), events_.end(),
        [&complement](const Event& e) { return e.GetMask() == complement.GetMask(); });
        if (!found) return false;
    }
  
    for (size_t i = 0; i < events_.size(); ++i) {
        for (size_t j = i; j < events_.size(); ++j) {
        Event united = Event::Unite(events_[i], events_[j]);
        bool found = std::any_of(events_.begin(), events_.end(),
            [&united](const Event& e) { return e.GetMask() == united.GetMask(); });
        if (!found) return false;
        }
    }
  
    return true;
}

SigmaAlgebra SigmaAlgebra::Generate(const OutcomeSpace& omega, 
                                   const std::vector<Event>& generators) {
    if (generators.empty()) {
        std::vector<Event> events;
        events.push_back(Event::Empty(omega.GetSize()));
        events.push_back(Event::Full(omega.GetSize()));
        return SigmaAlgebra(omega, events);
    }
  
    size_t n = omega.GetSize();
    std::vector<Event> events;
    
    events = generators;
    
    events.push_back(Event::Empty(n));
    events.push_back(Event::Full(n));
  
    size_t current_size;
    do {
        current_size = events.size();
        
        for (size_t i = 0; i < current_size; ++i) {
        Event complement = Event::Complement(events[i]);
        if (std::find_if(events.begin(), events.end(),
            [&complement](const Event& e) { 
                return e.GetMask() == complement.GetMask(); 
            }) == events.end()) {
            events.push_back(complement);
        }
        }
    
        for (size_t i = 0; i < events.size(); ++i) {
        for (size_t j = 0; j < events.size(); ++j) {
            Event united = Event::Unite(events[i], events[j]);
            if (std::find_if(events.begin(), events.end(),
                [&united](const Event& e) { 
                return e.GetMask() == united.GetMask(); 
                }) == events.end()) {
            events.push_back(united);
            }
        }
        }
        
        for (size_t i = 0; i < events.size(); ++i) {
        for (size_t j = 0; j < events.size(); ++j) {
            Event intersected = Event::Intersect(events[i], events[j]);
            if (std::find_if(events.begin(), events.end(),
                [&intersected](const Event& e) { 
                return e.GetMask() == intersected.GetMask(); 
                }) == events.end()) {
            events.push_back(intersected);
            }
        }
        }
    } while (events.size() > current_size);
    
    return SigmaAlgebra(omega, events);
}
}