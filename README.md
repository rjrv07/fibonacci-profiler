# fibonacci-profiler

Benchmarking and visualisation of various techniques for computing Fibonacci numbers in C++20.

Seven implementations are compared — from naïve recursion to matrix exponentiation — across three executables: a timing benchmark, a correctness verifier, and a matplotlib plot.

---

## Implementations

| Name | Strategy | Complexity |
|---|---|---|
| Recursive | Naïve double-recursion | O(2ⁿ) |
| Memoised Recursive | Recursive + hash-map cache | O(n) |
| Smart Recursive | Halving identities (no cache) | O(n) |
| Memoised Smart Recursive | Halving identities + hash-map cache | O(log n) |
| Constructive | Iterative, O(1) space | O(n) |
| Binary Exponentiation | 2×2 matrix fast-power (hand-rolled) | O(log n) |
| Simply C++ | 2×2 matrix fast-power via `sc::matrix` | O(log n) |

All implementations live in `fib.h`. The matrix helpers used by the last two are defined in `matrix.h` and pulled in as a dependency via the [simply-cpp](https://github.com/roelofrossouw/simply-cpp) library.

---

## Prerequisites

- CMake ≥ 3.20
- A C++20-capable compiler (Clang or GCC)
- Python 3 with **NumPy** and **matplotlib** (required only for the `plot` target)

---

## Building

```bash
cmake -B build
cmake --build build
```

CMake fetches two dependencies automatically at configure time:

- **simply-cpp** — provides `sc::timer` and `sc::matrix`
- **matplotlib-cpp** — header-only Python/C++ bridge (plot target only)

> **macOS note:** the build patches two `long long` specialisations out of `matplotlibcpp.h` that conflict with Apple's libc++. This happens automatically via `sed` in `CMakeLists.txt`.

---

## Executables

### `benchmark` — timing comparison

Runs every implementation and reports either:

- **How far it got** in a fixed time budget, or
- **How long it took** to compute a specific term.

```
benchmark <max_ms> [n]
```

| Argument | Description |
|---|---|
| `<max_ms>` | Time budget in milliseconds |
| `[n]` | *(optional)* Specific term to compute |

**Examples:**

```bash
# How many terms can each method compute in 500 ms?
./build/benchmark 500

# How long does each method take to compute fib(40)?
./build/benchmark 500 40
```

---

### `verify` — correctness checker

Runs all implementations in lockstep and prints any term where the results disagree, then reports total elapsed time and how many terms were checked.

```
verify <max_ms> [n]
```

| Argument | Description |
|---|---|
| `<max_ms>` | Time budget in milliseconds |
| `[n]` | *(optional)* Stop after this many terms |

**Example:**

```bash
# Cross-check all methods for up to 2 seconds
./build/verify 2000
```

If all implementations agree, only a summary line is printed. Any divergence prints the term index and each method's result.

---

### `plot` — cumulative-time graph

Plots cumulative compute time (µs) vs term index for every implementation using matplotlib.

```
plot [--loglog] <max_ms>
```

| Argument | Description |
|---|---|
| `<max_ms>` | Time budget per implementation |
| `--loglog` | *(optional)* Render both axes on a log scale |

**Examples:**

```bash
./build/plot 1000
./build/plot --loglog 1000
```

A window opens showing a labelled line per implementation. The log-log view makes the O(2ⁿ) curve of naïve recursion especially clear.

---

## Project structure

```
.
├── CMakeLists.txt      # Build config; fetches simply-cpp and matplotlib-cpp
├── fib.h               # All seven Fibonacci implementations
├── matrix.h            # sc::matrix template (2×2 fast-power helpers)
├── benchmark.cpp       # Timing benchmark executable
├── verify.cpp          # Cross-implementation correctness checker
└── plot.cpp            # matplotlib-cpp visualisation
```

---

## Notes on overflow

All implementations use `unsigned long long` (64-bit). Fibonacci numbers overflow `uint64` at n = 94 (fib(93) = 12 200 160 415 121 876 738, fib(94) wraps around). The benchmark and verifier do not guard against this — keep `[n]` below 94 for meaningful results.
