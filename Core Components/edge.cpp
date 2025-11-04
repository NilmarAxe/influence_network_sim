#include "edge.h"
#include <algorithm>

Edge::Edge(int source, int target, EdgeType type, double weight)
    : source_id(source), target_id(target), type(type), 
      weight(weight), trust_level(0.8) {}

void Edge::modify_trust(double delta) {
    trust_level = std::max(0.0, std::min(1.0, trust_level + delta));
}

double Edge::calculate_influence_flow() const {
    switch (type) {
        case EdgeType::ALLIANCE:
            return weight * trust_level * 0.8;
        case EdgeType::SUBORDINATION:
            return weight * 1.2;
        case EdgeType::CONFLICT:
            return -weight * 0.5;
        case EdgeType::NEUTRAL:
            return weight * 0.3;
        default:
            return 0.0;
    }
}