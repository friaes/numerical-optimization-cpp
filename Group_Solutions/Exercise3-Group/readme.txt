Exercise 3 - Group Project

=== Group Members & Workload =======================
Deva Betül Uçar - Nº 23-216-583 (25%)
Ramona Christen - Nº 19-104-405 (25%)
Rodrigo Friaes - Nº 24-219-909 (25%)
Nguyen Chi Manh - Nº 24-107-971 (25%)


=== Exercises ======================================

## Theory Exercises
### QCQP to SOCP
1) Expand the L2 Norm, then do some basic math to show the equality
2) Turn the quadratic terms into norms

### Linear Programming
Transform problem such that it fits the definition of LP
For general LP: The general linear program is converted to standard form by introducing slack variables for inequalities and splitting unrestricted variables into positive and negative parts. 
This ensures all variables are nonnegative and all constraints are equalities.

The transformation preserves feasibility and optimality: 
- every feasible solution in the general form corresponds uniquely to one in the standard form, and both have the same optimal solutions and identical objective values apart from a constant shift.

## Programming Exercise: Mass Spring System

Changed files: 
- SpringElement2D.hh
- SpringElement2DWithLength.hh
    Transform the basic objective function to code (straigtht forward). 
    For the gradient and Hessian matrix we first did the derivatives on paper and then added the code. 
    The one with length was a bit more of a challenge due to the more complicated derivatives
- MassSpringProblem2DDense.hh
- MassSpringProblem2DSparse.hh
    Just combine the derivatives/hessian as described well in the exercise.
    For the sparse representation store the solutions to triplets instead of directly into a matrix to then create a sparse matrix in the end.
- MassSpringSystemT_impl.hh
    Create a connected graph. Most challenging is to consider all edge cases. The visualization helped to debug.


Additional included files:
- Test_edges.csv
- Test_nodes.csv
- screenshot.png
    The screenshot shows a visualization of the final graph with the edges and nodes.