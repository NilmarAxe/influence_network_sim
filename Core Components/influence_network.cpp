#include "influence_network.h"
#include <algorithm>
#include <queue>

InfluenceNetwork::InfluenceNetwork() : next_node_id(0) {}

int InfluenceNetwork::add_node(const std::string& name, double initial_power) {
    int id = next_node_id++;
    nodes[id] = std::make_shared<Node>(id, name, initial_power);
    return id;
}

std::shared_ptr<Node> InfluenceNetwork::get_node(int id) {
    auto it = nodes.find(id);
    return (it != nodes.end()) ? it->second : nullptr;
}

void InfluenceNetwork::add_edge(int source, int target, EdgeType type, double weight) {
    edges.emplace_back(source, target, type, weight);
    
    auto source_node = get_node(source);
    auto target_node = get_node(target);
    
    if (source_node && target_node) {
        if (type == EdgeType::ALLIANCE) {
            source_node->add_ally(target);
            target_node->add_ally(source);
        } else if (type == EdgeType::SUBORDINATION) {
            source_node->add_subordinate(target);
        }
    }
}

void InfluenceNetwork::remove_edge(int source, int target) {
    edges.erase(std::remove_if(edges.begin(), edges.end(),
        [source, target](const Edge& e) {
            return e.get_source() == source && e.get_target() == target;
        }), edges.end());
}

std::vector<Edge> InfluenceNetwork::get_edges_from(int node_id) const {
    std::vector<Edge> result;
    for (const auto& edge : edges) {
        if (edge.get_source() == node_id) {
            result.push_back(edge);
        }
    }
    return result;
}

void InfluenceNetwork::propagate_influence(int source_id, double amount) {
    std::map<int, bool> visited;
    propagate_power_recursive(source_id, amount, visited, 0);
}

void InfluenceNetwork::propagate_power_recursive(int node_id, double amount,
                                                 std::map<int, bool>& visited, 
                                                 int depth) {
    if (depth > 3 || visited[node_id] || amount < 0.01) return;
    
    visited[node_id] = true;
    auto node = get_node(node_id);
    if (!node) return;
    
    node->modify_power(amount);
    
    auto outgoing_edges = get_edges_from(node_id);
    for (const auto& edge : outgoing_edges) {
        double flow = edge.calculate_influence_flow();
        double propagated = amount * flow * 0.5;
        propagate_power_recursive(edge.get_target(), propagated, visited, depth + 1);
    }
}

void InfluenceNetwork::update_all_influence_radii() {
    for (auto& pair : nodes) {
        pair.second->update_influence_radius();
    }
}

double InfluenceNetwork::calculate_total_network_power() const {
    double total = 0.0;
    for (const auto& pair : nodes) {
        total += pair.second->get_power();
    }
    return total;
}

std::vector<int> InfluenceNetwork::find_most_influential_nodes(int count) const {
    std::vector<std::pair<int, double>> node_powers;
    
    for (const auto& pair : nodes) {
        node_powers.emplace_back(pair.first, pair.second->get_power());
    }
    
    std::sort(node_powers.begin(), node_powers.end(),
        [](const auto& a, const auto& b) { return a.second > b.second; });
    
    std::vector<int> result;
    for (int i = 0; i < std::min(count, (int)node_powers.size()); ++i) {
        result.push_back(node_powers[i].first);
    }
    return result;
}

double InfluenceNetwork::calculate_centrality(int node_id) const {
    auto node = nodes.find(node_id);
    if (node == nodes.end()) return 0.0;
    
    int incoming = 0, outgoing = 0;
    for (const auto& edge : edges) {
        if (edge.get_target() == node_id) incoming++;
        if (edge.get_source() == node_id) outgoing++;
    }
    
    return (incoming + outgoing) * node->second->get_power();
}

std::vector<int> InfluenceNetwork::find_vulnerable_targets() const {
    std::vector<std::pair<int, double>> vulnerabilities;
    
    for (const auto& pair : nodes) {
        double vuln = pair.second->calculate_vulnerability();
        if (vuln > 0.3) {
            vulnerabilities.emplace_back(pair.first, vuln);
        }
    }
    
    std::sort(vulnerabilities.begin(), vulnerabilities.end(),
        [](const auto& a, const auto& b) { return a.second > b.second; });
    
    std::vector<int> result;
    for (const auto& v : vulnerabilities) {
        result.push_back(v.first);
    }
    return result;
}