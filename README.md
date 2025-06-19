 DSA Projects and cods
 1. visualization.py :
    # 🔍 Sorting Algorithm Visualizer

An interactive Python application built using **Pygame** to visually demonstrate the inner workings of popular sorting algorithms. This tool is especially useful for students, educators, and curious developers who want to understand how sorting works step by step.

---

## 🧠 Features

- Visualize four key sorting algorithms:
  - Bubble Sort
  - Selection Sort
  - Merge Sort
  - Quick Sort
- Adjustable:
  - Data size
  - Value range
  - Sorting speed (delay)
- Dynamic UI with:
  - Algorithm selection dropdown
  - Input boxes for custom parameters
  - Real-time animations and highlighting
- Built entirely with **Pygame** and **Python** (no external libraries required)

---

## 🎮 Demo Preview

![screenshot](#) *(Add screenshot or GIF of the UI here)*

---

## ⚙️ Requirements

- Python 3.x
- `pygame` library

Install pygame if not already:
```bash
pip install pygame

2.Contain Max Area:
This C++ program implements a solution to the "Container With Most Water" problem, commonly found on algorithm platforms like LeetCode. The goal is to find two lines in an array of heights such that together with the x-axis, they form a container that holds the most water.

Key Components:
Header Inclusion:
#include<bits/stdc++.h> includes all standard C++ libraries to simplify coding.

Class Solution:
Contains a public method height() which takes a vector of integers (nums) representing the height of vertical lines.

Method height():
Uses the two-pointer approach:

Starts with two pointers at the beginning and end of the array.

Calculates the area between the two pointers.

Moves the pointer pointing to the shorter line inward to try and find a better area.

Repeats until the pointers meet.

Returns the maximum area found.

main() Function:
Creates a sample input vector heights and uses the height() method of the Solution class to compute and print the maximum area.
