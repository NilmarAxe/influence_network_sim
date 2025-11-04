#ifndef EDGE_H
#define EDGE_H

enum class EdgeType {
    ALLIANCE,
    SUBORDINATION,
    CONFLICT,
    NEUTRAL
};

class Edge {
private:
    int source_id;
    int target_id;
    EdgeType type;
    double weight;
    double trust_level;

public:
    Edge(int source, int target, EdgeType type, double weight);
    
    int get_source() const { return source_id; }
    int get_target() const { return target_id; }
    EdgeType get_type() const { return type; }
    double get_weight() const { return weight; }
    double get_trust() const { return trust_level; }
    
    void set_type(EdgeType t) { type = t; }
    void set_weight(double w) { weight = w; }
    void modify_trust(double delta);
    
    double calculate_influence_flow() const;
};

#endif