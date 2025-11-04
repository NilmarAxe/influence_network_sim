#include "simulator.h"
#include <iostream>
#include <iomanip>
#include <random>

Simulator::Simulator(int max_turns) 
    : strategy(network), current_turn(0), max_turns(max_turns) {}

int Simulator::create_agent(const std::string& name, double power) {
    return network.add_node(name, power);
}

void Simulator::create_relationship(int source, int target, EdgeType type) {
    network.add_edge(source, target, type, 1.0);
}

void Simulator::run_simulation() {
    std::cout << "\n========== INFLUENCE NETWORK SIMULATION START ==========\n\n";
    
    print_network_status();
    
    for (current_turn = 1; current_turn <= max_turns; ++current_turn) {
        std::cout << "\n--- TURN " << current_turn << " ---\n";
        
        simulate_natural_growth();
        simulate_random_events();
        
        if (current_turn % 5 == 0) {
            print_network_status();
        }
    }
    
    print_final_analysis();
}

void Simulator::execute_optimal_betrayal_for(int agent_id) {
    auto plans = strategy.find_optimal_betrayals(agent_id, 1);
    
    if (!plans.empty()) {
        const auto& best_plan = plans[0];
        
        auto betrayer = network.get_node(best_plan.betrayer_id);
        auto target = network.get_node(best_plan.target_id);
        
        std::cout << "\n[BETRAYAL EXECUTED]\n";
        std::cout << "  Betrayer: " << betrayer->get_name() << "\n";
        std::cout << "  Target: " << target->get_name() << "\n";
        std::cout << "  Expected Gain: " << std::fixed << std::setprecision(2) 
                  << best_plan.expected_gain << "\n";
        std::cout << "  Success Probability: " 
                  << (best_plan.success_probability * 100) << "%\n";
        std::cout << "  ROI: " << best_plan.calculate_roi() << "\n";
        
        strategy.execute_betrayal(best_plan);
    } else {
        std::cout << "\n[NO VIABLE BETRAYAL OPPORTUNITIES]\n";
    }
}

void Simulator::simulate_natural_growth() {
    for (const auto& pair : network.get_all_nodes()) {
        pair.second->modify_power(0.5);
        pair.second->modify_loyalty(0.02);
    }
    
    network.update_all_influence_radii();
}

void Simulator::simulate_random_events() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> event_dist(1, 100);
    
    if (event_dist(gen) < 30) {
        auto nodes = network.get_all_nodes();
        if (!nodes.empty()) {
            std::uniform_int_distribution<> node_dist(0, nodes.size() - 1);
            auto it = nodes.begin();
            std::advance(it, node_dist(gen));
            
            it->second->modify_power(2.0);
            std::cout << "  [EVENT] " << it->second->get_name() 
                      << " gained unexpected power.\n";
        }
    }
}

void Simulator::print_network_status() const {
    std::cout << "\n=== NETWORK STATUS ===\n";
    std::cout << "Total Network Power: " << std::fixed << std::setprecision(2)
              << network.calculate_total_network_power() << "\n\n";
    
    std::cout << std::left << std::setw(15) << "Agent"
              << std::setw(10) << "Power"
              << std::setw(10) << "Loyalty"
              << std::setw(10) << "Allies"
              << std::setw(12) << "Centrality" << "\n";
    std::cout << std::string(60, '-') << "\n";
    
    for (const auto& pair : network.get_all_nodes()) {
        auto node = pair.second;
        std::cout << std::left << std::setw(15) << node->get_name()
                  << std::setw(10) << std::fixed << std::setprecision(2) 
                  << node->get_power()
                  << std::setw(10) << node->get_loyalty()
                  << std::setw(10) << node->get_allies().size()
                  << std::setw(12) << network.calculate_centrality(pair.first)
                  << "\n";
    }
}

void Simulator::print_betrayal_opportunities(int agent_id) const {
    auto betrayer = network.get_node(agent_id);
    if (!betrayer) return;
    
    std::cout << "\n=== BETRAYAL OPPORTUNITIES FOR " << betrayer->get_name() 
              << " ===\n\n";
    
    auto plans = strategy.find_optimal_betrayals(agent_id, 5);
    
    if (plans.empty()) {
        std::cout << "No viable betrayal opportunities at this time.\n";
        return;
    }
    
    for (size_t i = 0; i < plans.size(); ++i) {
        const auto& plan = plans[i];
        auto target = network.get_node(plan.target_id);
        
        std::cout << (i + 1) << ". Target: " << target->get_name() << "\n";
        std::cout << "   Expected Gain: " << std::fixed << std::setprecision(2)
                  << plan.expected_gain << "\n";
        std::cout << "   Success Rate: " << (plan.success_probability * 100) << "%\n";
        std::cout << "   ROI: " << plan.calculate_roi() << "\n";
        std::cout << "   Required Allies: " << plan.required_allies.size() << "\n";
        std::cout << "   Total Cost: " << plan.total_cost << "\n\n";
    }
}

void Simulator::print_final_analysis() const {
    std::cout << "\n========== FINAL ANALYSIS ==========\n";
    
    auto most_influential = network.find_most_influential_nodes(3);
    std::cout << "\nMost Influential Agents:\n";
    for (size_t i = 0; i < most_influential.size(); ++i) {
        auto node = network.get_node(most_influential[i]);
        std::cout << (i + 1) << ". " << node->get_name() 
                  << " (Power: " << node->get_power() 
                  << ", Control: " << (strategy.calculate_network_control(most_influential[i]) * 100)
                  << "%)\n";
    }
    
    auto vulnerable = network.find_vulnerable_targets();
    std::cout << "\nMost Vulnerable Targets:\n";
    for (size_t i = 0; i < std::min((size_t)3, vulnerable.size()); ++i) {
        auto node = network.get_node(vulnerable[i]);
        std::cout << (i + 1) << ". " << node->get_name()
                  << " (Vulnerability: " << node->calculate_vulnerability() << ")\n";
    }
    
    std::cout << "\n========== SIMULATION COMPLETE ==========\n";
}