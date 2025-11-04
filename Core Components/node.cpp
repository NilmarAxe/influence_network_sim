#include "node.h"
#include <algorithm>
#include <cmath>

Node::Node(int id, const std::string& name, double initial_power)
    : id(id), name(name), power(initial_power), loyalty(1.0), 
      influence_radius(initial_power * 0.5), is_traitor(false) {}

void Node::add_ally(int node_id) {
    if (std::find(allies.begin(), allies.end(), node_id) == allies.end()) {
        allies.push_back(node_id);
    }
}

void Node::remove_ally(int node_id) {
    allies.erase(std::remove(allies.begin(), allies.end(), node_id), allies.end());
}

void Node::add_subordinate(int node_id) {
    if (std::find(subordinates.begin(), subordinates.end(), node_id) == subordinates.end()) {
        subordinates.push_back(node_id);
    }
}

void Node::remove_subordinate(int node_id) {
    subordinates.erase(std::remove(subordinates.begin(), subordinates.end(), node_id), 
                       subordinates.end());
}

double Node::calculate_betrayal_gain(double target_power) const {
    double base_gain = target_power * 0.6;
    double loyalty_penalty = loyalty * target_power * 0.3;
    return base_gain - loyalty_penalty;
}

double Node::calculate_vulnerability() const {
    double base_vulnerability = 1.0 / (power + 1.0);
    double ally_protection = allies.size() * 0.1;
    return std::max(0.0, base_vulnerability - ally_protection);
}

void Node::update_influence_radius() {
    influence_radius = power * 0.5 + subordinates.size() * 0.2;
}