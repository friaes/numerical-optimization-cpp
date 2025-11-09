#pragma once

#include <FunctionBase/FunctionBaseSparse.hh>
#include "LineSearch.hh"

//== NAMESPACES ===============================================================

namespace AOPT {

    /* Performs a gradient descent on a given problem.
     * This can work with any Problem with a FunctionBase-style interface since
     * the gradient descent method is rather generic mathematically */
    class GradientDescent {
    public:
        typedef FunctionBaseSparse::Vec Vec; ///< Eigen::VectorXd


        /**
         * \param _problem a pointer to a specific Problem, which can be any type that
         *        has the same interface as FunctionBase's (i.e. with eval_f, eval_gradient, etc.)
         * \param _initial_x  the x starting point
         * \param _eps the stopping criterion below which we consider the method
         *             to be done
         * \param _max_iters a capping number of iterations in case you would end-up with a
         *             bad configuration where the successive attemps of finding the
         *             minimum kind of oscillate around the actual minimum without
         *             finding it
         *
         * \return the minimum found by the method. */
        template <class Problem>
        static Vec solve(Problem *_problem, const Vec& _initial_x, const double _eps = 1e-4, const int _max_iters = 1000000) {
            std::cout << "******** Gradient Descent ********" << std::endl;

            // squared epsilon for stopping criterion
            double e2 = _eps * _eps;

            // get starting point
            Vec x = _initial_x;

            // allocate gradient storage
            Vec g(_problem->n_unknowns());
            int iter(0);

            //------------------------------------------------------//
            //TODO: implement the gradient descent
            double f = _problem->eval_f(x);

            while (iter < _max_iters) {
                // gradient
                _problem->eval_gradient(x, g);
                const double g2 = g.squaredNorm();
                if (g2 <= e2) break;  // gradient small enough

                // steepest descent direction
                Vec dx = -g;

                // backtracking line search (with a safe initial step)
                double t = LineSearch::backtracking_line_search(_problem, x, g, dx, 1.0, 0.5, 0.75);
                if (t <= 0.0 || !std::isfinite(t)) {
                    // could not find a valid step — stop to avoid NaNs/oscillation
                    break;
                }

                // update
                Vec x_new = x + t * dx;
                double f_new = _problem->eval_f(x_new);
                if (!std::isfinite(f_new)) break;      // keep things robust
                if (f_new > f && std::abs(f_new - f) > 1e-14) {
                    // should not happen with Armijo, but guard anyway
                    t *= 0.5;
                    if (t <= 0.0) break;
                    x_new = x + t * dx;
                    f_new = _problem->eval_f(x_new);
                    if (!std::isfinite(f_new)) break;
                }

                x = x_new;
                f = f_new;
                ++iter;
            }

            //------------------------------------------------------//

            return x;
        }
    };
}



