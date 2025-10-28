#include <Utils/OptimalityChecker.hh>
#include <Functions/FunctionQuadraticND.hh>
#include <vector>
#include <iostream>

int main(int _argc, const char* _argv[]) {
    AOPT::FunctionQuadraticND::Mat A(2, 2);
    A.setZero();
    AOPT::FunctionQuadraticND::Vec b(2);
    b.setZero();

    //-------------------------------------------------------------------------------//
    //Todo: set up the optimization problem by populating the various
    //matrices and vectors coefficients
    
    //1. set objective function
    // objective: x1^2 - 2*x2^2
    // A = [[2, 0], [0, -4]] and b = [0, 0], c = 0
    A << 2,  0,
         0, -4;
    AOPT::FunctionQuadraticND obj_func(A, b, 0);

    //2. inequality constraints
    std::vector<AOPT::FunctionBase*> ineq_cons;
    
    // constraint 1: (x1 + 4)^2 - 2 - x2 <= 0
    // x1^2 + 8*x1 - x2 + 14 <= 0
    // A = [[2, 0], [0, 0]], b = [8, -1], c = 14
    A << 2, 0,
         0, 0;
    b << 8, -1;
    AOPT::FunctionQuadraticND qnd1(A, b, 14);
    ineq_cons.push_back(&qnd1);

    // constraint 2: x1 >= -10, so -x1 - 10 <= 0
    // A2 = [[0, 0], [0, 0]], b2 = [-1, 0], c2 = -10
    A.setZero();
    b << -1, 0;
    AOPT::FunctionQuadraticND qnd2(A, b, -10);
    ineq_cons.push_back(&qnd2);

    //3. equality constraints
    std::vector<AOPT::FunctionBase*> eq_cons;
    
    // constraint: x1 - x2 + 4 = 0
    // A3 = [[0, 0], [0, 0]], b3 = [1, -1], c3 = 4
    A.setZero();
    b << 1, -1;
    AOPT::FunctionQuadraticND qnd3(A, b, 4);
    eq_cons.push_back(&qnd3);

    //4. set lambdas and vs
    AOPT::FunctionQuadraticND::Vec lambda(2), nu(1); // 2 inequality constraints
                                                     // 1 equality constraint
    
    lambda << 4.0, 0.0;
    nu << -12.0;
    
    //5. set query point
    AOPT::FunctionQuadraticND::Vec x(2);
    x << -2.0, 2.0;

    //-------------------------------------------------------------------------------//

    //TODO: uncomment this to test your implementation
    //NOTE: you can change the variables name if you want
    //check
    
    AOPT::OptimalityChecker oc;
    if(oc.is_KKT_satisfied(&obj_func, ineq_cons, eq_cons, x, lambda, nu))
        std::cout<<"\nThe query point satisfies the KKT condition."<<std::endl;
    else
        std::cout<<"\nThe query point does NOT satisfy the KKT condition."<<std::endl;

    return 0;
}

