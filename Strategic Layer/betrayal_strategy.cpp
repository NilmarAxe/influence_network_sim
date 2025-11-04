#include "betrayal_strategy.h"
#include <algorithm>
#include <cmath>

BetrayalPlan BetrayalStrategy::analyze_betrayal_opportunity(int betrayer, int target) {
    BetrayalPlan plan;
    plan.betrayer_id = betrayer;
    plan.target_id = target;
    
    auto betrayer_node = network.get_node(betrayer);
    auto target_node = network.get_node(target);
    
    if (!betrayer_node || !target_node) {
        plan.expected_gain = 0;
        plan.success_probability = 0;
        return plan;
    }
    
    plan.expected_gain = betrayer_node->calculate_betrayal_gain(target_node->get_power());
    plan.success_probability = calculate_betrayal_success_probability(betrayer, target);
    plan.required_allies = identify_necessary_allies(betrayer, target);
    plan.total_cost = calculate_execution_cost(plan);
    
    return plan;
}

std::vector<BetrayalPlan> BetrayalStrategy::find_optimal_betrayals(int betrayer_id, 
                                                                    int top_n) {
    std::vector<BetrayalPlan> plans;
    
    auto betrayer = network.get_node(betrayer_id);
    if (!betrayer) return plans;
    
    for (const auto& pair : network.get_all_nodes()) {
        if (pair.first == betrayer_id) continue;
        
        BetrayalPlan plan = analyze_betrayal_opportunity(betrayer_id, pair.first);
        if (plan.expected_gain > 0 && plan.success_probability > 0.3) {
            plans.push_back(plan);
        }
    }
    
    std::sort(plans.begin(), plans.end(),
        [](const BetrayalPlan& a, const BetrayalPlan& b) {
            return a.calculate_roi() > b.calculate_roi();
        });
    
    if (plans.size() > (size_t)top_n) {
        plans.resize(top_n);
    }
    
    return plans;
}

void BetrayalStrategy::execute_betrayal(const BetrayalPlan& plan) {
    auto betrayer = network.get_node(plan.betrayer_id);
    auto target = network.get_node(plan.target_id);
    
    if (!betrayer || !target) return;
    
    betrayer->mark_as_traitor();
    
    double power_stolen = target->get_power() * 0.6;
    target->modify_power(-power_stolen);
    betrayer->modify_power(power_stolen);
    
    target->modify_loyalty(-0.4);
    
    for (int ally_id : plan.required_allies) {
        auto ally = network.get_node(ally_id);
        if (ally) {
            ally->modify_loyalty(-0.2);
        }
    }
    
    network.remove_edge(plan.betrayer_id, plan.target_id);
    network.add_edge(plan.betrayer_id, plan.target_id, EdgeType::CONFLICT, 1.0);
    
    network.propagate_influence(plan.betrayer_id, power_stolen * 0.3);
}

double BetrayalStrategy::calculate_betrayal_success_probability(int betrayer, 
                                                                int target) const {
    auto betrayer_node = network.get_node(betrayer);
    auto target_node = network.get_node(target);
    
    if (!betrayer_node || !target_node) return 0.0;
    
    double power_ratio = betrayer_node->get_power() / (target_node->get_power() + 1.0);
    double ally_advantage = betrayer_node->get_allies().size() * 0.1;
    double target_vulnerability = target_node->calculate_vulnerability();
    
    double probability = (power_ratio * 0.5 + ally_advantage + target_vulnerability * 0.3);
    return std::min(0.95, std::max(0.05, probability));
}

std::vector<int> BetrayalStrategy::identify_necessary_allies(int betrayer, 
                                                             int target) const {
    auto betrayer_node = network.get_node(betrayer);
    auto target_node = network.get_node(target);
    
    if (!betrayer_node || !target_node) return {};
    
    std::vector<int> necessary_allies;
    
    if (target_node->get_power() > betrayer_node->get_power() * 1.5) {
        for (int ally_id : betrayer_node->get_allies()) {
            auto ally = network.get_node(ally_id);
            if (ally && ally->get_power() > 5.0) {
                necessary_allies.push_back(ally_id);
                if (necessary_allies.size() >= 2) break;
            }
        }
    }
    
    return necessary_allies;
}

double BetrayalStrategy::calculate_execution_cost(const BetrayalPlan& plan) const {
    double base_cost = 2.0;
    double ally_cost = plan.required_allies.size() * 1.5;
    double risk_cost = (1.0 - plan.success_probability) * 5.0;
    
    return base_cost + ally_cost + risk_cost;
}

double BetrayalStrategy::calculate_network_control(int node_id) const {
    auto node = network.get_node(node_id);
    if (!node) return 0.0;
    
    double total_power = network.calculate_total_network_power();
    double node_power = node->get_power();
    double centrality = network.calculate_centrality(node_id);
    
    return (node_power / total_power) * 0.6 + (centrality / 100.0) * 0.4;
}

std::vector<int> BetrayalStrategy::find_critical_targets_for_dominance(int player_id) const {
    std::vector<std::pair<int, double>> target_values;
    
    for (const auto& pair : network.get_all_nodes()) {
        if (pair.first == player_id) continue;
        
        double strategic_value = pair.second->get_power() * 0.5 +
                                network.calculate_centrality(pair.first) * 0.3 +
                                pair.second->calculate_vulnerability() * 0.2;
        
        target_values.emplace_back(pair.first, strategic_value);
    }
    
    std::sort(target_values.begin(), target_values.end(),
        [](const auto& a, const auto& b) { return a.second > b.second; });
    
    std::vector<int> result;
    for (size_t i = 0; i < std::min((size_t)5, target_values.size()); ++i) {
        result.push_back(target_values[i].first);
    }
    return result;
}