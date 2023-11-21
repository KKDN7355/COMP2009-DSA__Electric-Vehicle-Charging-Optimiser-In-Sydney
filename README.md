# EV Charging Solutions in Sydney

## Overview
This repository contains a solution to challenges related to Electric Vehicle (EV) charging in Sydney, Australia. The solution aims to address issues such as identifying charging stations, finding optimal routes considering charging costs, and extending the functionality for multiple scenarios involving EV charging.

## Programming Tasks
### Task Completion Summary
1. **Task 1**: Code review and execution to understand base functionality.
2. **Task 2**: Addition of three new locations to the network.
3. **Task 3**: Sorting charging stations based on ascending charging prices.
4. **Task 4**: Retrieval of adjacent locations with charging stations.
5. **Task 5**: Determining adjacent location with the lowest charging cost.
6. **Task 6**: Finding the nearest charging station from a given location.
7. **Task 7**: Locating the lowest total cost location for travel and charging.
8. **Task 8**: Pathfinding with minimal charging and travel costs (single charge).
9. **Task 9**: Pathfinding allowing multiple charges for a single trip.
10. **Task 10**: Bonus - Insertion and deletion functions for dynamic updates.

### Implementation Details
- Utilized C++ to develop the solution, focusing on scalability and efficiency.
- Expanded the base code to incorporate additional functionalities.
- Ensured seamless integration with extended data files (Locations.txt and Weights.txt).
- Demonstrated various scenarios related to EV charging in Sydney metropolitan area.

## Complexity Analysis
### Document Overview
- Detailed analysis of data structures and algorithms used in the program.
- Assessment of the chosen algorithms for Tasks 3-9, illustrating their implementation.
- Estimation of the complexity for these algorithms in terms of worst-case or average-case scenarios.

## File Structure
- **EVChargingApp.cpp**: Driver program for EV charging functionalities.
- **Location.h**: Class defining location information.
- **WeightedGraph.h**: Implementation of weighted graph data structure.
- **EVCharging.h**: Class encapsulating road network and charging infrastructure.
- **Locations.txt**: Data file containing location information.
- **Weights.txt**: Data file storing distance information between locations.

## How to Use
1. Clone the repository: `git clone <repository_url>`
2. Compile the code (if necessary): `g++ EVChargingApp.cpp -o EVChargingApp`
3. Run the executable: `./EVChargingApp`

## Demonstration

The project includes a demonstration of the program, showcasing its functionalities and adherence to the assignment requirements. The demonstration involves showcasing the implemented features, running the program, and explaining the codebase and design choices.

Final Grade: 100/100
