#ifndef BETRAYAL_STRATEGY_H
#define BETRAYAL_STRATEGY_H

#include "influence_network.h"
#include <vector>

struct BetrayalPlan {
    int betrayer_id;
    int target_id;
    double expected_gain;
    double success_probability;
    std::vector<int> required_allies;
    double total_cost;
    
    double calculate_roi() const { return expected_gain / (total_cost + 0.1); }
};

class BetrayalStrategy {
private:
    InfluenceNetwork& network;
    
    double calculate_betrayal_success_probability(int betrayer, int target) const;
    std::vector<int> identify_necessary_allies(int betrayer, int target) const;
    double calculate_execution_cost(const BetrayalPlan& plan) const;

public:
    explicit BetrayalStrategy(InfluenceNetwork& net) : network(net) {}
    
    BetrayalPlan analyze_betrayal_opportunity(int betrayer, int target);
    std::vector<BetrayalPlan> find_optimal_betrayals(int betrayer_id, int top_n);
    void execute_betrayal(const BetrayalPlan& plan);
    
    // Strategic analysis
    double calculate_network_control(int node_id) const;
    std::vector<int> find_critical_targets_for_dominance(int player_id) const;
};

#endif