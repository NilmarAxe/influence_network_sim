#ifndef SIMULATOR_H
#define SIMULATOR_H

#include "influence_network.h"
#include "betrayal_strategy.h"
#include <string>

class Simulator {
private:
    InfluenceNetwork network;
    BetrayalStrategy strategy;
    int current_turn;
    int max_turns;
    
    void simulate_natural_growth();
    void simulate_random_events();
    void log_state(const std::string& message) const;

public:
    Simulator(int max_turns = 20);
    
    int create_agent(const std::string& name, double power);
    void create_relationship(int source, int target, EdgeType type);
    
    void run_simulation();
    void execute_optimal_betrayal_for(int agent_id);
    
    void print_network_status() const;
    void print_betrayal_opportunities(int agent_id) const;
    void print_final_analysis() const;
};

#endif