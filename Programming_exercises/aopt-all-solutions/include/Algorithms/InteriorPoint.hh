#pragma once

#include <FunctionBase/FunctionBaseSparse.hh>
#include <Functions/InteriorPointProblem.hh>
#include <Algorithms/NewtonMethods.hh>
#include <Utils/OptimizationStatistic.hh>

//== NAMESPACES ===============================================================

namespace AOPT {

    //== CLASS DEFINITION =========================================================
    class InteriorPoint {
    public:
        // LA typedefs
        using Vec = FunctionBaseSparse::Vec;

        static Vec solve(FunctionBaseSparse *_obj, const Vec& _initial_x, const std::vector<FunctionBaseSparse*>& _constraints,
                const double _eps = 1e-4, const double _mu = 10.0, const int _max_iters = 1000) {
            std::cerr << "******** Interior Point ********" << std::endl;

            // construct log-barrier problem
            InteriorPointProblem problem(_obj, _constraints);
            auto opt_st = std::make_unique<AOPT::OptimizationStatistic>(&problem);

            // count number of iterations
            int iter(0);

            // current barrier parameter
            double t = 1;

            // number of constraints
            double m = _constraints.size();

            // points
            Vec x = _initial_x;

            //------------------------------------------------------//
            //TODO: implement the interior point method
            //Hint: Use projected newton method to solve for an approximated x.
            bool converged = false;

            while (iter < _max_iters) {
                problem.t() = t;

                // centering step
                x = NewtonMethods::solve_with_projected_hessian(opt_st.get(), converged, x, 10., _eps, 100000);

                // stopping criterion
                if (m / t < _eps)
                    break;

                // print status
                std::cerr << "----------> IP iter: " << iter <<
                          "   obj = " << opt_st->eval_f(x) <<
                          "   t = " << t << std::endl << std::endl;

                // increase t
                t *= _mu;


                ++iter;
            }
            //------------------------------------------------------//

            opt_st->print_statistics();

            return x;
        }
    };
    //=============================================================================

}





