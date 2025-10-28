#pragma once

#include <FunctionBase/FunctionBase.hh>
#include <vector>
//== NAMESPACES ===============================================================

namespace AOPT {

//== CLASS DEFINITION =========================================================
    class OptimalityChecker {
    public:
        using Vec = Eigen::VectorXd;

        OptimalityChecker(const double _epsilon = 1e-13) : eps_(_epsilon) {}


        /** Checks whether a particular optimization problem satisfies the KKT conditions
         *
         * \param _objective pointer to the objective function, which should be any function
         *        inheriting from FunctionBase
         *
         * \param _inequality_constraints an array containing the inequalities,
         *        each representend as a function inheriting from FunctionBase,
         *        such that _inequality_constraints[i].eval_f(x) <= 0 for all i
         *        if x is in the feasible set
         *
         * \param _equality_constraints an array containing the equalities,
         *        each representend as a function inheriting from FunctionBase,
         *        such that _equality_constraints[i].eval_f(x) == 0 for all i
         *        if x is in the feasible set
         *
         * \param _query_point the point at which the KKT conditions should be checked
         *
         * \param _lambda the lambda coefficients of the dual problem.
         *        It should be of the same dimension as _inequality_constraints since
         *        there is one lambda factor per inequality in the dual problem
         * \param _nu the nu coefficients of the dual problem.
         *        It should be of the same dimension as _equality_constraints since
         *        there is one nu factor per equality in the dual problem
         * */
        bool is_KKT_satisfied(FunctionBase *_objective, const std::vector<FunctionBase *>& _inequality_constraints,
                              const std::vector<FunctionBase *>& _equality_constraints,
                              const Vec& _query_point, const Vec& _lambda, const Vec& _nu) {
            //------------------------------------------------------//
            //Todo:

            //1. check only condition 4 in case there are no constraints
            Vec gradient;
            _objective->eval_gradient(_query_point, gradient);

            if(_equality_constraints.empty() && _inequality_constraints.empty()) {
                // eps_ > |gradient|, i.e., approximately zero (∇f_0(x) = 0)
                if(gradient.norm() <= eps_)
                    return true;
                return false;
            }

            //2. check inequality constraints (cond. 1.)
            for(auto constraint : _inequality_constraints){
                double fx_i = constraint->eval_f(_query_point);
                // f_i(x*) <= 0
                if(!(fx_i <= eps_))
                    return false;
            }

            //3. check equality constraints (cond. 1.)
            for(auto constraint : _equality_constraints) {
                double hx_i = constraint->eval_f(_query_point);
                // h_i(x*) = 0
                if(!(std::abs(hx_i) <= eps_))
                    return false;
            }

            //4. check lambda (cond. 2.)
            for(int i = 0; i < _lambda.size(); ++i) {
                // lambda must be positive
                if (_lambda[i] <= -eps_)
                    return false;
            }

            //5. check complementary slackness (cond. 3.)
            for(int i = 0; i < _lambda.size(); ++i) {
                double fx_i = _inequality_constraints[i]->eval_f(_query_point);
                // lambda_i* * f_i(x*) = 0
                if(!(std::abs(_lambda[i] * fx_i) <= eps_))
                    return false;
            }

            //6. check gradient (cond. 4.)
            Vec temp_g(_objective->n_unknowns());
            Vec λf_i(_objective->n_unknowns());
            Vec vh_i(_objective->n_unknowns());

            // get all inequality constraints gradients
            int i = 0;
            for(auto constraint : _inequality_constraints) {
                constraint->eval_gradient(_query_point, temp_g);
                λf_i += _lambda[i] * temp_g;
                i++;
            }
            // and equality constraints gradients
            i = 0;
            for(auto constraint : _equality_constraints) {
                constraint->eval_gradient(_query_point, temp_g);
                vh_i += _nu[i] * temp_g;
                i++;
            }

            // check vanishing gradient of Lagrangian: ∇L(x, λ, ν) = 0
            if(!((gradient + λf_i + vh_i).norm() <= eps_))
                return false;
            return true;
            //------------------------------------------------------//
        }

    private:
        double eps_;
    };
//=============================================================================
}



