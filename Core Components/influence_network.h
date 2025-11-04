#ifndef INFLUENCE_NETWORK_H
#define INFLUENCE_NETWORK_H

#include "node.h"
#include "edge.h"
#include <map>
#include <vector>
#include <memory>

class InfluenceNetwork {
private:
    std::map<int, std::shared_ptr<Node>> nodes;
    std::vector<Edge> edges;
    int next_node_id;
    
    void propagate_power_recursive(int node_id, double amount, 
                                   std::map<int, bool>& visited, int depth);

public:
    InfluenceNetwork();
    
    // Node management
    int add_node(const std::string& name, double initial_power);
    std::shared_ptr<Node> get_node(int id);
    const std::map<int, std::shared_ptr<Node>>& get_all_nodes() const { return nodes; }
    
    // Edge management
    void add_edge(int source, int target, EdgeType type, double weight);
    void remove_edge(int source, int target);
    std::vector<Edge> get_edges_from(int node_id) const;
    
    // Network operations
    void propagate_influence(int source_id, double amount);
    void update_all_influence_radii();
    double calculate_total_network_power() const;
    std::vector<int> find_most_influential_nodes(int count) const;
    
    // Analysis
    double calculate_centrality(int node_id) const;
    std::vector<int> find_vulnerable_targets() const;
};

#endif