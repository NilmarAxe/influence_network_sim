#ifndef ADVANCED_STRATEGIES_H
#define ADVANCED_STRATEGIES_H

#include "influence_network.h"
#include "betrayal_strategy.h"
#include <vector>
#include <map>

class AdvancedStrategies {
private:
    InfluenceNetwork& network;
    
public:
    explicit AdvancedStrategies(InfluenceNetwork& net) : network(net) {}
    
    // Coalition formation
    struct Coalition {
        std::vector<int> members;
        double combined_power;
        int leader_id;
        double cohesion;
    };
    
    Coalition form_optimal_coalition(int initiator, int target_size);
    std::vector<Coalition> detect_existing_coalitions();
    
    // Long-term planning
    struct MultiStepPlan {
        std::vector<BetrayalPlan> sequence;
        double cumulative_gain;
        int required_turns;
    };
    
    MultiStepPlan plan_dominance_path(int agent_id, int horizon);
    
    // Network manipulation
    void isolate_target(int target_id, int aggressor_id);
    std::vector<int> find_bridge_nodes() const;
    void execute_divide_and_conquer(int agent_id);
};

#endif