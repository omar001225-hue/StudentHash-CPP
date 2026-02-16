# Student Registry - Hash Table Implementation

This repository contains a C++ implementation of a Hash Table system designed for managing student records. The project focuses on demonstrating efficient data storage and retrieval through the application of open addressing and collision resolution algorithms.

## Project Overview
The system manages student data consisting of unique roll numbers and names. It uses a fixed-size hash table and handles index collisions using the Quadratic Probing method, which significantly reduces the issue of primary clustering compared to standard linear probing.

## Core Technical Features
* **Collision Resolution**: Implements Quadratic Probing using the formula:  
  Index = (Hash(key) + attempt^2) % TableSize.
* **Open Addressing**: Utilizes a single array structure with state-tracking flags (isOccupied and isDeleted) to manage data flow.
* **Memory Management**: Features a complete class destructor to clean up dynamically allocated nodes, ensuring zero memory leaks.
* **Input Validation**: Uses buffer clearing and string parsing to handle multi-word names and prevent input stream errors.

## Algorithmic Complexity
| Operation | Average Case | Worst Case |
| :--- | :--- | :--- |
| Insertion | O(1) | O(n) |
| Search | O(1) | O(n) |
| Space Complexity | O(n) | O(n) |

## Implementation Details
* **Language**: C++
* **Table Size**: 15 (Optimized for demonstration)
* **Data Structure**: Array of pointers to custom StudentNode structures.

## Usage Instructions

### Compilation
Use a C++ compiler (such as g++) to compile the source code:
```bash
g++ StudentHashTable.cpp -o StudentDB
