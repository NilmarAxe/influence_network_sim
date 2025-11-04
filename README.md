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

6. **AdvancedStrategies** (advanced_strategies.h/cpp) 
   - Coalition formation algorithms
   - Multi-step dominance planning
   - Network manipulation tactics (isolation, divide-and-conquer)
   - Bridge node detection for strategic fragmentation

## Build Instructions

### Basic Build
```bash
# Using Make
make clean && make
make run

# Manual compilation
g++ -std=c++17 -Wall -O2 -o influence_sim \
    main.cpp node.cpp edge.cpp influence_network.cpp \
    betrayal_strategy.cpp simulator.cpp

# Execute
./influence_sim
```

### Advanced Build
```bash
# With advanced strategies
g++ -std=c++17 -Wall -O2 -o influence_sim \
    main.cpp node.cpp edge.cpp influence_network.cpp \
    betrayal_strategy.cpp simulator.cpp advanced_strategies.cpp

# Execute
./influence_sim
```

## Key Features

### Core Features
- **Power Propagation**: Influence flows through network based on relationship types
- **Betrayal Optimization**: Identifies highest ROI betrayal opportunities
- **Dynamic Events**: Random events affect network state
- **Strategic Analysis**: Centrality, vulnerability, and control metrics
- **Relationship Management**: Multiple edge types with different behaviors

### Advanced Features
- **Coalition Formation**: Automatic detection and creation of optimal alliances
- **Multi-Step Planning**: Long-term strategic path calculation for dominance
- **Network Manipulation**: Isolation tactics and divide-and-conquer strategies
- **Bridge Analysis**: Identification of critical nodes for network fragmentation

## Usage Example

### Basic Usage
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

### Advanced Usage
```cpp
#include "advanced_strategies.h"

InfluenceNetwork network;
AdvancedStrategies advanced(network);

// Form optimal coalition
auto coalition = advanced.form_optimal_coalition(agent_id, 4);

// Plan multi-step dominance
auto plan = advanced.plan_dominance_path(agent_id, 10);

// Execute divide and conquer
advanced.execute_divide_and_conquer(agent_id);

// Detect existing coalitions
auto coalitions = advanced.detect_existing_coalitions();
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

### Coalition Compatibility Score
```
compatibility = power * 0.4 
              + loyalty * 0.3 
              + existing_relationship_bonus
```

## Customization

Modify parameters in respective classes:
- Loyalty decay rates (Node)
- Influence flow coefficients (Edge)
- Propagation depth (InfluenceNetwork)
- Success probability weights (BetrayalStrategy)
- Coalition cohesion factors (AdvancedStrategies)

## File Structure
```
influence_network_sim/
├── Core Components
│   ├── node.h
│   ├── node.cpp
│   ├── edge.h
│   ├── edge.cpp
│   ├── influence_network.h
│   └── influence_network.cpp
│
├── Strategic Layer
│   ├── betrayal_strategy.h
│   ├── betrayal_strategy.cpp
│   ├── advanced_strategies.h
│   └── advanced_strategies.cpp
│
├── Simulation
│   ├── simulator.h
│   ├── simulator.cpp
│   └── main.cpp
│
└── Documentation
    ├── Makefile
    ├── README.md
    └── .gitignore
```

## Design Principles

- **Modularity**: Each component has single responsibility
- **Extensibility**: Easy to add new edge types or strategies
- **Performance**: Efficient graph operations with proper data structures
- **Clarity**: Clear separation between data, logic, and presentation
- **Scalability**: Bonus module demonstrates expandable architecture

## Advanced Module Features

### Coalition System
- **Automatic Detection**: Identifies existing power blocs in the network
- **Optimal Formation**: Creates coalitions based on compatibility scores
- **Cohesion Tracking**: Monitors alliance stability over time

### Multi-Step Planning
- **Dominance Paths**: Calculates optimal sequence of betrayals
- **Horizon Analysis**: Simulates future network states
- **Cumulative Gain**: Tracks long-term strategic value

### Network Manipulation
- **Target Isolation**: Systematically removes victim's support structure
- **Bridge Identification**: Finds critical nodes for network control
- **Divide & Conquer**: Fragments opposing coalitions strategically

## Performance Notes

- Network size: Optimized for 5-50 nodes
- Propagation depth: Limited to 3 levels for performance
- Turn complexity: O(N * E) where N=nodes, E=edges
- Memory: Approximately O(N²) for dense networks
- Coalition detection: O(N²) worst case
- Multi-step planning: O(H * N) where H=horizon depth

## Future Enhancements

- Machine learning for strategy optimization
- Parallel coalition negotiations
- Network evolution over extended time horizons
- Visualization with graph rendering libraries
- Persistent state storage and replay system
- Multi-threaded betrayal simulation

## Requirements

- C++17 or later
- Standard library only (no external dependencies)
- Compatible with GCC, Clang, MSVC

## License

This is a simulation framework for educational and research purposes.

## Contributing

Contributions are welcome! Areas of interest:
- New edge types and relationship dynamics
- Alternative betrayal metrics
- Visualization implementations
- Performance optimizations
- Additional strategic patterns
