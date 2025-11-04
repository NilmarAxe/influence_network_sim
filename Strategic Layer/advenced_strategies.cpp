#include "advanced_strategies.h"
#include <algorithm>
#include <set>
#include <cmath>

AdvancedStrategies::Coalition 
AdvancedStrategies::form_optimal_coalition(int initiator, int target_size) {
    Coalition coalition;
    coalition.leader_id = initiator;
    coalition.members.push_back(initiator);
    
    auto initiator_node = network.get_node(initiator);
    if (!initiator_node) return coalition;
    
    std::vector<std::pair<int, double>> candidates;
    
    for (const auto& pair : network.get_all_nodes()) {
        if (pair.first == initiator) continue;
        
        double compatibility = 0.0;
        auto candidate = pair.second;
        
        // Calculate compatibility score
        compatibility += candidate->get_power() * 0.4;
        compatibility += candidate->get_loyalty() * 0.3;
        
        // Check for existing relationships
        const auto& allies = initiator_node->get_allies();
        if (std::find(allies.begin(), allies.end(), pair.first) != allies.end()) {
            compatibility += 5.0;
        }
        
        candidates.emplace_back(pair.first, compatibility);
    }
    
    std::sort(candidates.begin(), candidates.end(),
        [](const auto& a, const auto& b) { return a.second > b.second; });
    
    coalition.combined_power = initiator_node->get_power();
    
    for (size_t i = 0; i < std::min((size_t)(target_size - 1), candidates.size()); ++i) {
        coalition.members.push_back(candidates[i].first);
        auto member = network.get_node(candidates[i].first);
        if (member) {
            coalition.combined_power += member->get_power();
        }
    }
    
    coalition.cohesion = 0.8 - (coalition.members.size() * 0.05);
    
    return coalition;
}

std::vector<AdvancedStrategies::Coalition> 
AdvancedStrategies::detect_existing_coalitions() {
    std::vector<Coalition> coalitions;
    std::set<int> processed;
    
    for (const auto& pair : network.get_all_nodes()) {
        if (processed.count(pair.first)) continue;
        
        Coalition coalition;
        coalition.leader_id = pair.first;
        coalition.members.push_back(pair.first);
        coalition.combined_power = pair.second->get_power();
        
        // Add allies to coalition
        for (int ally_id : pair.second->get_allies()) {
            if (!processed.count(ally_id)) {
                coalition.members.push_back(ally_id);
                auto ally = network.get_node(ally_id);
                if (ally) {
                    coalition.combined_power += ally->get_power();
                }
            }
        }
        
        // Add subordinates
        for (int sub_id : pair.second->get_subordinates()) {
            if (!processed.count(sub_id)) {
                coalition.members.push_back(sub_id);
                auto sub = network.get_node(sub_id);
                if (sub) {
                    coalition.combined_power += sub->get_power();
                }
            }
        }
        
        if (coalition.members.size() > 1) {
            coalition.cohesion = 0.7;
            coalitions.push_back(coalition);
            
            for (int member : coalition.members) {
                processed.insert(member);
            }
        }
    }
    
    return coalitions;
}

AdvancedStrategies::MultiStepPlan 
AdvancedStrategies::plan_dominance_path(int agent_id, int horizon) {
    MultiStepPlan plan;
    plan.cumulative_gain = 0.0;
    plan.required_turns = 0;
    
    BetrayalStrategy strategy(network);
    
    // Simulate multiple betrayals
    InfluenceNetwork temp_network = network;
    BetrayalStrategy temp_strategy(temp_network);
    
    for (int turn = 0; turn < horizon; ++turn) {
        auto opportunities = temp_strategy.find_optimal_betrayals(agent_id, 1);
        
        if (opportunities.empty()) break;
        
        plan.sequence.push_back(opportunities[0]);
        plan.cumulative_gain += opportunities[0].expected_gain;
        plan.required_turns++;
        
        // Simulate execution on temp network
        temp_strategy.execute_betrayal(opportunities[0]);
    }
    
    return plan;
}

void AdvancedStrategies::isolate_target(int target_id, int aggressor_id) {
    auto target = network.get_node(target_id);
    if (!target) return;
    
    // Remove all alliances targeting the victim
    for (int ally_id : target->get_allies()) {
        network.remove_edge(ally_id, target_id);
        network.remove_edge(target_id, ally_id);
        
        // Create conflict with aggressor
        network.add_edge(aggressor_id, ally_id, EdgeType::ALLIANCE, 1.0);
    }
    
    target->modify_loyalty(-0.5);
}

std::vector<int> AdvancedStrategies::find_bridge_nodes() const {
    std::vector<int> bridges;
    
    // Simplified bridge detection: nodes with high betweenness
    for (const auto& pair : network.get_all_nodes()) {
        double centrality = network.calculate_centrality(pair.first);
        
        if (centrality > 50.0) {
            bridges.push_back(pair.first);
        }
    }
    
    return bridges;
}

void AdvancedStrategies::execute_divide_and_conquer(int agent_id) {
    auto bridges = find_bridge_nodes();
    
    for (int bridge_id : bridges) {
        if (bridge_id == agent_id) continue;
        
        auto bridge = network.get_node(bridge_id);
        if (!bridge) continue;
        
        // Target bridge nodes to fragment the network
        if (bridge->calculate_vulnerability() > 0.3) {
            BetrayalStrategy strategy(network);
            auto plan = strategy.analyze_betrayal_opportunity(agent_id, bridge_id);
            
            if (plan.success_probability > 0.5) {
                strategy.execute_betrayal(plan);
                break;
            }
        }
    }
}