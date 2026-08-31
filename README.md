# Advanced Object-Oriented Programming in C++ (C++17)

A collection of modular C++ applications demonstrating core object-oriented programming concepts, manual memory management, template programming, and standard library (STL) algorithms.

---

## Projects Overview

### 01. Dictionary & Performance Profiler
* Implemented dynamic memory allocation and custom array resizing without standard library containers.
* Designed move semantics (`std::move`) to optimize memory transfers and evaluated performance using `std::chrono`.
* Utilized file stream I/O (`std::ifstream`) to parse and populate structured tokenized datasets.

### 02. RPG Combat Simulation Engine
* Implemented class hierarchies using pure virtual interfaces and abstract base classes.
* Applied C++ template classes to handle dynamic data types and attributes.
* Managed deep copies and resource lifecycles following the **Rule of 5** (Copy/Move constructors and assignment operators).
* Designed distinct relationship architectures: **Composition** (Team lifecycle management) and **Aggregation** (Guild membership management).

### 03. Multimedia Management System
* Managed object collections using STL containers (`std::vector`, `std::list`) and function objects (Functors).
* Processed data using STL algorithms (`std::for_each`, `std::copy_if`, `std::sort`) paired with lambda expressions.
* Integrated the **Observer Pattern** via callback function pointers to trigger updates upon collection modifications.

### 04. Factory Assembly Line Simulation
* Simulated a multi-station industrial assembly line managing order queues and inventory fulfillment.
* Designed station-to-station order dispatching workflows using double-ended queues (`std::deque`).
* Implemented line configuration, topological linkage, and station reordering within `LineManager`.
* Validated dynamic memory allocations and verified zero memory leaks using `valgrind`.

---

## Technical Concepts Applied

* **Language Standard:** C++17
* **Memory Management:** Pointers, dynamic arrays, Rule of 5, Valgrind leak checking
* **OOP Paradigms:** Encapsulation, inheritance, polymorphism, abstract classes, operator overloading
* **Modern C++ Features:** Class templates, move semantics, lambda expressions, STL algorithms (`<algorithm>`, `<chrono>`)

---

## Compilation & Verification

Each subproject includes a test harness (`tester_1.cpp`, `tester_2.cpp`, or `tester_3.cpp`) and sample output.

