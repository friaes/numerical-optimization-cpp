Exercise 4 - Group Project

=== Group Members & Workload =======================
Deva Betül Uçar - Nº 23-216-583 (25%)
Ramona Christen - Nº 19-104-405 (25%)
Rodrigo Friaes - Nº 24-219-909 (25%)
Nguyen Chi Manh - Nº 24-107-971 (25%)


=== Exercises ======================================

## Theory Exercises
### Lagrange Duality 
1- a) By analyzing the constraint, we got that the the feasible set is [2, 4].
   To find the optimal value and solution, since f0 is convex and is increasing for x > 0,
   the minimum over the feasible set [2, 4] is 2.

b) Calculated the Lagrangian: L(x,λ) = f0 + λf1

   To get the dual function g(λ), minimized the Lagrangian:
   ∂L/∂x = 2x + λ(2x - 6) = 0
   Solving: x = 3λ/(1 + λ) -> assume λ > -1
   And then, replaced x in the function

   Concluding, we can confirm that p*=5 >= g(λ)

c) Since ∇^2g(λ)<=0, we got that the dual function is concave for λ>=0.
   Calculated the dual optimal solution and value, λ=2 and g(2)=5
   Thus, we concluded that strong duality holds. 

### KKT Condition 
2- a) From the sketch we determined that x*= (-2,2)
b) Transformed constraints (primal form),
   Declared the dual constraints of each inequality, λ1>=0 and λ2>=0
   Checked complementary slackness in each inequality,
   From complementary slackness we got λ2=0, thus we had to calcute the other dual variables, λ1 and nu,
   using the Vanishing gradient.

## Programming Exercise

Changed files: 
- FunctionQuadraticND.hh
    Implemented eval_gradient and eval_hessian (straightforward)
    For the gradient: ∇f(x) = A * x + b, and for the hessian: H = A
    
- OptimalityChecker.hh
    Implemented is_KKT_satisfied, by following the todo steps provided of the KKT conditions.
    1) if there are no constraints, just check if (∇f_0(x) = 0) - need to use gradient norm because we compare with epsilon instead of zero
    Then, if there are constraints, check:
    2) Inequality constraints: f_i(x) <= epsilon
    3) Equality constraints: |h_i(x)| <= epsilon
    4) Check Lambda positivity: λ_i > 0 ,i.e. λ_i ≥ -epsilon
    5) Complementary slackness: |λ_i * f_i(x)| ≤ epsilon
    6) Vanishing gradient condition: ||∇f_0(x) + Σλ_i∇f_i(x) + Σν_i∇h_i(x)|| ≤ epsilon
    
- main.cc
    Implemented the minimization problem by taking inspiration from the unit tests structure.
    Used the values calculated in the theory part of the KKT Condition exercise,
    and converted all functions from the KKT Condition exercise into quadratic form.
