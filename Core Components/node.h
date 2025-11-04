#ifndef NODE_H
#define NODE_H

#include <string>
#include <vector>
#include <memory>

class Node {
private:
    int id;
    std::string name;
    double power;
    double loyalty;
    double influence_radius;
    bool is_traitor;
    std::vector<int> allies;
    std::vector<int> subordinates;

public:
    Node(int id, const std::string& name, double initial_power);
    
    // Getters
    int get_id() const { return id; }
    std::string get_name() const { return name; }
    double get_power() const { return power; }
    double get_loyalty() const { return loyalty; }
    double get_influence_radius() const { return influence_radius; }
    bool is_betrayer() const { return is_traitor; }
    const std::vector<int>& get_allies() const { return allies; }
    const std::vector<int>& get_subordinates() const { return subordinates; }
    
    // Setters and modifiers
    void set_power(double p) { power = p; }
    void modify_power(double delta) { power += delta; }
    void set_loyalty(double l) { loyalty = l; }
    void modify_loyalty(double delta) { loyalty += delta; }
    void mark_as_traitor() { is_traitor = true; }
    void clear_traitor_mark() { is_traitor = false; }
    
    // Relationship management
    void add_ally(int node_id);
    void remove_ally(int node_id);
    void add_subordinate(int node_id);
    void remove_subordinate(int node_id);
    
    // Strategic calculations
    double calculate_betrayal_gain(double target_power) const;
    double calculate_vulnerability() const;
    void update_influence_radius();
};

#endif