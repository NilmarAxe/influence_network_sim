# Influence Network Simulator

A strategic simulation framework for modeling power dynamics, influence propagation, 
and betrayal optimization in hierarchical networks.

## Architecture Overview

### Core Components

1. **Node** (node.h/cpp)
   - Represents individual agents with power, loyalty, and influence metrics
   - Manages relationships (allies, subordinates)
   - Calculates strategic values (vulnerability, betrayal gains)

2. **Edge** (edge.h/cpp)
   - Models connections between nodes
   - Types: Alliance, Subordination, Conflict, Neutral
   - Computes influence flow based on relationship type and trust

3. **InfluenceNetwork** (influence_network.h/cpp)
   - Core graph structure managing all nodes and edges
   - Implements power propagation algorithms
   - Provides network analysis (centrality, vulnerability detection)

4. **BetrayalStrategy** (betrayal_strategy.h/cpp)
   - Strategic decision engine for optimal betrayal planning
   - Calculates success probabilities and ROI
   - Identifies critical targets for network dominance

5. **Simulator** (simulator.h/cpp)
   - Main orchestration layer
   - Manages simulation lifecycle and events
   - Provides visualization and analysis output

## Build Instructions
```bash
# Using Make
make
make run

# Manual compilation
g++ -std=c++17 -Wall -O2 main.cpp node.cpp edge.cpp \
    influence_network.cpp betrayal_strategy.cpp simulator.cpp \
    -o influence_network_sim

# Execute
./influence_network_sim
```

## Key Features

- **Power Propagation**: Influence flows through network based on relationship types
- **Betrayal Optimization**: Identifies highest ROI betrayal opportunities
- **Dynamic Events**: Random events affect network state
- **Strategic Analysis**: Centrality, vulnerability, and control metrics
- **Relationship Management**: Multiple edge types with different behaviors

## Usage Example
```cpp
Simulator sim(20);  // 20 turns

// Create agents
int leader = sim.create_agent("Leader", 20.0);
int deputy = sim.create_agent("Deputy", 15.0);

// Establish relationships
sim.create_relationship(leader, deputy, EdgeType::SUBORDINATION);

// Run simulation
sim.run_simulation();

// Analyze and execute betrayals
sim.print_betrayal_opportunities(deputy);
sim.execute_optimal_betrayal_for(deputy);
```

## Algorithm Details

### Power Propagation
- Recursive traversal up to depth 3
- Flow calculated per edge type and trust level
- Diminishing returns with distance

### Betrayal Success Probability
```
P(success) = 0.5 * (betrayer_power / target_power) 
           + 0.1 * ally_count 
           + 0.3 * target_vulnerability
```

### ROI Calculation
```
ROI = expected_gain / (base_cost + ally_cost + risk_cost)
```

## Customization

Modify parameters in respective classes:
- Loyalty decay rates (Node)
- Influence flow coefficients (Edge)
- Propagation depth (InfluenceNetwork)
- Success probability weights (BetrayalStrategy)

## File Structure
```
influence_network_sim/
├── node.h
├── node.cpp
├── edge.h
├── edge.cpp
├── influence_network.h
├── influence_network.cpp
├── betrayal_strategy.h
├── betrayal_strategy.cpp
├── simulator.h
├── simulator.cpp
├── main.cpp
├── Makefile
└── README.md
```

## Design Principles

- **Modularity**: Each component has single responsibility
- **Extensibility**: Easy to add new edge types or strategies
- **Performance**: Efficient graph operations with proper data structures
- **Clarity**: Clear separation between data, logic, and presentation

## Future Enhancements

- Coalition formation algorithms
- Multi-agent simultaneous betrayals
- Network evolution over long time horizons
- Machine learning for strategy optimization
- Visualization with graph rendering

## License

This is a simulation framework for educational and research purposes.
