# Applied Optimization — A C++ Numerical Optimization Library

Coursework for the **Applied Optimization** course at the **University of Bern**, taken as part of my Master's in Computer Science. Over a series of exercises the course builds up, from scratch, a **C++ numerical-optimization library** on top of [Eigen](https://eigen.tuxfamily.org/), progressing from brute-force search all the way to constrained interior-point methods — and applies it to a 2D **mass–spring energy-minimisation** problem.

The material follows the standard convex/continuous-optimization curriculum (in the spirit of Boyd & Vandenberghe and Nocedal & Wright): first-order methods, second-order (Newton) methods, quasi-Newton, and constrained optimization.

## What's in the library

The heart of the repository is a clean, generic optimization framework under `include/`, organised into four layers.

### Function interface (`include/FunctionBase/`)
An abstract `FunctionBase` interface that any objective function implements by providing `eval_f` (value), `eval_gradient`, and `eval_hessian`. Because every algorithm is written against this interface, the same solver works on *any* function — a textbook use of abstraction. There are dense and sparse variants (`FunctionBaseSparse`), a parametric-function base for constrained problems, and wrappers.

### Algorithms (`include/Algorithms/`)
The optimization methods, built up in order of sophistication:

- **Grid search** — a brute-force baseline that evaluates the function over a grid.
- **Convexity test** — sampling-based check of whether a function is convex.
- **Line search** — backtracking / Armijo (and Wolfe) step-size selection, used by the descent methods.
- **Gradient descent** — first-order steepest descent.
- **Newton's method** — second-order method solving `H·Δx = −g` via a sparse Cholesky factorisation (`SimplicialLLT`), with a Newton-decrement stopping criterion, plus a **projected-Hessian** variant that regularises the Hessian to stay positive-definite on non-convex problems.
- **L-BFGS** — limited-memory quasi-Newton, approximating curvature from past gradients without forming the Hessian.
- **Gauss–Newton** — for nonlinear least-squares problems.
- **Equality-constrained Newton** — the KKT system for linear equality constraints, including an **infeasible-start** version.
- **Augmented Lagrangian** — constrained optimization by penalising constraint violation and updating multipliers.
- **Interior point** — constrained optimization via a log-barrier / central-path method.

### Objective & constraint functions (`include/Functions/`)
Concrete problems the solvers are tested on: 2D and N-D quadratics, a non-convex 2D function, several **spring-element energies** (plain, with rest length, least-squares and PSD-Hessian variants), the assembled **mass–spring problem** (dense, sparse, and least-squares forms), and constraints (circle, area) plus the augmented-Lagrangian and interior-point problem wrappers.

### Utilities (`include/Utils/`)
Supporting tools including a **derivative checker** (finite-difference verification of gradients/Hessians — invaluable for catching bugs in hand-derived derivatives), an **optimality checker** (KKT conditions), an optimization-statistics collector, a CSV exporter for plotting convergence, a stopwatch, and a random-number generator.

## The application: mass–spring systems

The `MassSpringSystem` module ties it together: a 2D network of point masses connected by springs, whose equilibrium configuration is the minimum of the system's total spring energy. Each optimizer can be pointed at this problem to watch it settle into equilibrium, which makes a great, visual benchmark for comparing convergence speed and robustness across the methods (gradient descent vs. Newton vs. L-BFGS, etc.). This is the same energy-minimisation idea that underlies physical simulation and geometry processing.

## Repository structure

```
.
├── Programming_exercises/
│   ├── aopt-all-solutions/                # the cumulative final library
│   │   ├── include/{FunctionBase,Algorithms,Functions,Utils}
│   │   ├── GridSearch/ GradientDescent/ NewtonMethods/ LBFGS/
│   │   ├── GaussNewton/ EqualityConstrainedNewton[InfeasibleStart]/
│   │   ├── AugmentedLagrangian/ InteriorPoint/ ConvexityTests/ …
│   │   │       (each: main.cc + unit_tests.cc + CMakeLists.txt)
│   │   ├── MassSpringSystem/               # the mass-spring application
│   │   └── external/eigen                  # vendored Eigen (third-party)
│   └── aopt-eigen-tutorial/                # intro Eigen exercises
├── Group_Solutions/                        # written/theory exercise solutions
├── Exercise_Instructions/                  # assignment briefs
├── Exams/
└── README.md
```

Each exercise vendors its own copy of Eigen and uses GoogleTest (fetched by CMake) for the `unit_tests.cc` in every component.

## Requirements

- A C++17 compiler (g++/clang)
- CMake
- Eigen (vendored in each exercise under `external/eigen`)
- Internet access on first configure (CMake fetches GoogleTest for the unit tests)

## Building & running

Each exercise builds with CMake:

```bash
cd Programming_exercises/aopt-exercise10   # or aopt-all-solutions
mkdir build && cd build
cmake ..
make
```

The compiled executables land in `Build/bin/`. For example, grid-searching the minimum of a 2D quadratic on `[-10, 10]` with a 20-point grid:

```bash
./Build/bin/GridSearch 1 -10 10 20
# Minimum value of the function is: -50 at x: (0, -10)
```

Each algorithm's `main.cc` prints usage when run without arguments, and each component ships a GoogleTest suite (`unit_tests.cc`).

## Notes

The algorithm bodies were the graded work: the course provided the framework (the `FunctionBase` interface, problem definitions, CMake, and test harnesses) with the optimization methods left to implement — marked by `//TODO: implement …` blocks inside each algorithm.
