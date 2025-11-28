Exercise 6 - Group Project

=== Group Members & Workload =======================
Deva Betül Uçar - Nº 23-216-583 (25%)
Ramona Christen - Nº 19-104-405 (25%)
Rodrigo Friaes - Nº 24-219-909 (25%)
Nguyen Chi Manh - Nº 24-107-971 (25%)


=== Exercises ======================================

## Theory Exercises
### Affine Invariance
a) Use chain rule to relate ∇g(y) = A^T ∇f(x) and ∇^2g(y) = A^T ∇^2f(x) A,
    show Newton directions satisfy Δy = A^-1 Δx, so x^k = A y^k + b

b) Because g(y^k + t Δy) = f(x^k + t Δx),
    backtracking gets same step s size and Newton decrements coincide

## Programming Exercise: Mass Spring System

Implement TODOs in all files:

Changed files: 
- NewtonMethods.hh
- SpringElement2DWithLengthPSDHess.hh


### Newton Methods vs Gradient descent
----------|          NewtonMethods       |         GradientDescent      |
Dimension | without length | with length | without length | with length |
----------|----------------|-------------|----------------|-------------|
5x5       | 0.000362s      | 0.001356s   | 0.555721s      | 0.061845s   |
10x10     | 0.000525s      | 0.005293s   | 4.51786s       | 0.365825s   |
20x20     | 0.010596s      | 0.030122s   | 71.4201s       | 4.90668s    |


The table above shows a clear performance advantage for the NewtonMethods solver
 over GradientDescent for the MassSpringProblem.

- NewtonMethods (used standard variant) is greatly faster than GradientDescent on all spring graph sizes.
    For example, on the 20×20 problem without rest length, Newton finishes in 0.01s, while GradientDescent
    takes about 71s
- GradientDescent performs relatively better on the MassSpringProblem with length than the no length problem,
    but it is still much slower than NewtonMethods. Moreover, the NewtonMethods acts in the opposite way,
    where its faster in the without length problem over the with length one

Additional included files:
- screenshots/GradientDescent/gd_*.png
- screenshots/NewtonMethods/newton_std_*.png