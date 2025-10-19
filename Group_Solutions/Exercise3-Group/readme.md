Exercise 3 - Group Project

=== Group Members & Workload =======================
Deva Betül Uçar - Nº 23-216-583 (25%)
Ramona Christen - Nº 19-104-405 (25%)
Rodrigo Friaes - Nº 24-219-909 (25%)
Nguyen Chi Manh - Nº 24-107-971 (25%)


=== Exercises ======================================

## Theory Exercises

### Simple functions
Easy to prove by verifying the second-order condition

### Log-sum-exp
Figure out what the Hessian matrix (H) looks like, then check if it is positive semi-definite by verifying that v^THv >= 0.

### Geometric Mean

Use opposite approach and proof that the geometric mean is concave by showing that the Hessian is negative semi-definite.

## Programming Exercise: Convexity Test

Changed files: 
- ConvexityTest.hh

Straight forward to implement by converting the definition into code. Iterate over max_sampling_points and evaluate n_evals points on the line by using θ=j/n_evals for j=1 to n_evals (excluding 0 and n_evals). 
