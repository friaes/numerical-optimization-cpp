#pragma once

#include <Utils/RandomNumberGenerator.hh>
#include <FunctionBase/FunctionBase.hh>

//== NAMESPACES ===================================================================

namespace AOPT {

    //== CLASS DEFINITION =========================================================

    class ConvexityTest {
    public:
        using Vec = FunctionBase::Vec; ///< Eigen::VectorXd
        using Mat = FunctionBase::Mat; ///< Eigen::MatrixXd

        ConvexityTest() {}

        ~ConvexityTest() {}

    public:

        /** Checks whether the function given as argument is convex or not.
         * If it is not, it should output a point not satisfying the convexity property
         * before returning false.
         * \param _function a function pointer that should be any class inheriting
         * from FunctionBase, e.g. FunctionQuadraticND
         * \param min the minimum value of all tested points' coordinate
         * \param max the maximum value of all tested points' coordinate
         * \param n_evals the number of evaluations/samples tested on the
         *        line between the two points on the function */
        static bool isConvex(FunctionBase* _function, const double min = -1000., const double max = 1000., const int n_evals = 10) {
            const int n = _function->n_unknowns();
            //randomly generate number from min to max
            RandomNumberGenerator rng(min, max);
            
            const int max_sampling_points(1000000);

            //------------------------------------------------------//
            //Todo: Add your code here
            for (int i = 0; i < max_sampling_points; i++) {
                Vec x = rng.get_random_nd_vector(n);
                Vec y = rng.get_random_nd_vector(n);

                auto f = [_function](const Vec& point) { return _function->eval_f(point); };

                for (int j = 1; j < n_evals; j++) {
                    double θ = (double) j/n_evals; // θ in [0,1], θ = {0.1,0.2,...,0.9}

                    // is convex if: f((1 - θ) * x + θ * y) <= (1 - θ) * f(x) + θ * f(y)
                    if ((f((1.0 - θ) * x + θ * y)) > ((1.0 - θ) * f(x) + θ * f(y)))
                        return false;
                }
            }
            //------------------------------------------------------//
            return true;
        }


    private:
        static void printPathInfo(FunctionBase::Vec p1, FunctionBase::Vec p2, FunctionBase::Vec p, double t) {
            std::cout << "path: p(t) = (1 - t) * p1 + t * p2; \nwith:\n"
                      << "  p1 = (" << p1.transpose() << ")\n"
                      << "  p2 = (" << p2.transpose() << ")\n"
                      << "  p (t = " << t << ") = (" << p.transpose() << ")" << std::endl;
        }

    };




}
