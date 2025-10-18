Exercise 0 - Group Project

=== Group Members & Workload =======================
Deva Betül Uçar - Nº 23-216-583 (25%)
Ramona Christen - Nº 19-104-405 (25%)
Rodrigo Friaes - Nº 24-219-909 (25%)
Nguyen Chi Manh - Nº 24-107-971 (25%)


=== Exercises ======================================

## Implementing objective functions:

Ex1 - Quadratic Function 2D: f(x,y) = 0.5(x^2 + gamma *y^2)
We implement the evaluation function by getting the coordinates from the 2D vector _x,
and then calculate those coordinates in the function.

Ex2 - Quadratic Function ND: f(x,y) = 0.5 * (x^T A x) + b^T x + c
Explanation:
- first_term: Quadratic component (x^T * A * x)
- second_term: Linear component (b^T * x)
- third_term: Constant (c)
We compute each component separately for clarity.

Ex3 - Non-Convex Function: f(x,y) = (y-x^2)^2+cos^2(4*y)*(1-x)^2+x^2+y^2
We implement this function the same way in the exercise 1, and use pow() functions
to make the code more readable.


## Grid Search:

Ex4 - Grid Search 2D
To evaluate the function over the whole 2D grid, we first calculate the size
of each grid cell (step size for iteration). This is done by taking the
difference between the upper and lower corner (size of the grid), and dividing
by the number of cells. 
Then we use loops to iterate through each grid point, starting from 
the lower corner, and evaluate the function at each of these points, storing
both the minimum value found and its corresponding coordinates throughout the 
search process. 

Ex5 - Grid Search ND
This time to iterate trough the ND grid, we use a index counter for each dimension to 
help us track, which grid point to evaluate.
First we iterate over the first dimension of the grid, and each time we evaluate a point,
we increment the counter. If the counter of any dimension, reaches the max lenght of the
grid, then we reset that dimension's counter and increment the next dimension's counter.
This process continues until all grid points have been evaluated, 
effectively simulating loops without actually writing N loops.
