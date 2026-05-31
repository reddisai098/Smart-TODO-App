# Smart Todo Application (CLI)

A robust Command Line Interface (CLI) task management system built in C++ that introduces optimized data structures for tracking, updating, and maintaining productivity logs.

## 🚀 Features
* **Efficient Lookups:** Utilizes C++ STL `std::map` to achieve $O(\log N)$ time complexity for adding, completing, and deleting tasks.
* **Task Prioritization:** Supports categorization of tasks by priority levels (High, Medium, Low).
* **Data Persistence:** Seamlessly serializes and deserializes tasks to a local data file upon exit and startup.
* **Input Hardening:** Robust validation loops preventing menu crashes from malformed terminal inputs.

## 🛠️ Concepts Practiced
* Associative Containers (`std::map`)
* File Stream Serialization (`<fstream>`)
* Input Buffer Maintenance (`std::cin.ignore`)
* Object-Oriented Data Structuring

## 💻 How to Run
1. Compile the code: `g++ main.cpp -o todoapp`
2. Run the executable: `./todoapp`
