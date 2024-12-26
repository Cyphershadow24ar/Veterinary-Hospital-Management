# Veterinary-Hospital-Management

This C program implements Dijkstra's algorithm to find the shortest path between veterinary clinics in a network. It generates a visual representation of the network and the optimal route using DOT graph notation.

# Features

1. Finds the shortest path between CVRGU (source) and any veterinary clinic in the network
2. Generates a visual graph representation using DOT format
3. Calculates and displays:
  Shortest distance between clinics
  Complete path from source to destination
  Visit sequence of nodes
4. Interactive command-line interface for destination selection
5. Visual output with highlighted shortest path

# Prerequisites

1. C compiler (GCC recommended)
2. Graphviz (for visualizing the DOT file output)

# Installation

1. Clone the repository or download the source files:
main.c or Explain.c (they contain the same implementation)

2. Install Graphviz:
On Ubuntu/Debian: sudo apt-get install graphviz
On macOS: brew install graphviz
On Windows: Download from Graphviz website

# Compilation
Compile the program using GCC:
bash
gcc -o clinic_navigator main.c

# Usage
1. Run the compiled program:
bash
./clinic_navigator

3. When prompted, enter the name of the destination clinic exactly as shown in the list:
Example: "Hello Pet Cares" or "Govt. Veterinary Hospital"

4. The program will output:
The shortest distance from CVRGU to the destination
The complete path through the network
The sequence number of the destination in the visit order
A DOT file named graph.dot containing the network visualization

5. To generate a visual graph from the DOT file:
bash
dot -Tpng graph.dot -o network.png

# Network Structure
The program includes 13 veterinary clinics:

1. CVRGU (Source)
2. Hello Pet Cares
3. Anisha Pet Care Clinic
4. Petvetcure
5. Govt. Veterinary Hospital
6. Vet Surgery Dept. OUAT
7. Bhubaneswar Pet Clinic
8. Aashrey Pet Clinic
9. Royal Pet Clinic
10. VetCare Pet Clinic
11. Blue Cross Vet Clinic
12. Petland Veterinary Clinic
13. Dr. Panda's Pet Clinic

# Implementation Details

1. Uses adjacency matrix representation for the network
2. Implements Dijkstra's algorithm for shortest path finding
3. Distances between clinics are measured in kilometers
4. INF (99999) represents no direct connection between clinics
5. The source node is fixed as CVRGU (index 0)

# Output Format
The program generates two types of output:

1. Console Output:
Source: [Starting Clinic]
Destination: [Selected Clinic]
Shortest Distance: [X] km
Path: Clinic1 -> Clinic2 -> ... -> ClinicN
Visit Sequence: [Number]

2. Visual Output (graph.dot):
Black lines: All possible connections
Red lines: Shortest path
Labels: Distance in kilometers
Nodes: Clinic names

# Error Handling

1. Validates destination clinic name input
2. Handles file opening errors for DOT file generation
3. Manages unreachable destinations through INF value checks

# Contributing
Feel free to submit issues, fork the repository, and create pull requests for any improvements.
