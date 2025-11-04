#include "simulator.h"
#include <iostream>

int main() {
    Simulator sim(15);
    
    // Initialize network with agents
    int alpha = sim.create_agent("Alpha", 15.0);
    int beta = sim.create_agent("Beta", 12.0);
    int gamma = sim.create_agent("Gamma", 10.0);
    int delta = sim.create_agent("Delta", 8.0);
    int epsilon = sim.create_agent("Epsilon", 7.0);
    int zeta = sim.create_agent("Zeta", 6.0);
    
    // Establish initial relationships
    sim.create_relationship(alpha, beta, EdgeType::ALLIANCE);
    sim.create_relationship(alpha, gamma, EdgeType::SUBORDINATION);
    sim.create_relationship(beta, delta, EdgeType::ALLIANCE);
    sim.create_relationship(gamma, epsilon, EdgeType::SUBORDINATION);
    sim.create_relationship(delta, zeta, EdgeType::ALLIANCE);
    sim.create_relationship(epsilon, zeta, EdgeType::NEUTRAL);
    sim.create_relationship(beta, gamma, EdgeType::CONFLICT);
    
    std::cout << "Initial network configuration established.\n";
    std::cout << "Agents: 6 | Relationships: 7\n";
    
    // Run base simulation
    sim.run_simulation();
    
    // Analyze betrayal opportunities for key players
    std::cout << "\n\n========== STRATEGIC ANALYSIS ==========\n";
    
    sim.print_betrayal_opportunities(alpha);
    sim.print_betrayal_opportunities(beta);
    
    // Execute optimal betrayals
    std::cout << "\n========== BETRAYAL PHASE ==========\n";
    
    sim.execute_optimal_betrayal_for(alpha);
    sim.execute_optimal_betrayal_for(delta);
    
    // Final state after betrayals
    std::cout << "\n";
    sim.print_network_status();
    
    return 0;
}