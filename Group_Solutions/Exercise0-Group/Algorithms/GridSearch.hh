#pragma once

#include <Functions/FunctionQuadratic2D.hh>
#include <Functions/FunctionQuadraticND.hh>
#include <Functions/FunctionNonConvex2D.hh>
#include <vector>

//== NAMESPACES ===================================================================

namespace AOPT {

    //== CLASS DEFINITION =========================================================
    class GridSearch {
    public:
        using Vec = FunctionBase::Vec;
        using Mat = FunctionBase::Mat;

        GridSearch(const int _n_cells = 10) : n_cells_(_n_cells){}
        ~GridSearch() {}

    public:

        /** Evaluation of a 2D function over the whole grid to find its minimum
         *
         * \param _func a pointer to any 2D function inheriting from FunctionBase
         *              (see include/FunctionBase/FunctionBase.hh)
         * \param _x_l the coordinates of the lower corner of the grid
         * \param _x_u the coordinates of the upper corner of the grid.
         *             _x_l and _x_u together define a square in which the grid lies
         * \return 0 if all went well, -1 if not.*/
        int grid_search_2d(FunctionBase* _func, const Vec& _x_l, const Vec& _x_u, double& _f_min) const {
            std::cout<<"Grid searching the minimum of a 2-D function..."<<std::endl;
            double f = 0., fmin = std::numeric_limits<double>::max();
            
            Vec x_min(2);
            
            //------------------------------------------------------//
            //Todo: implement the 2d version of the grid search
            // algorithm to find minimum value of _func between _x_l and _x_u

            Vec x(2), c(2); // x is the grid point coordinates, c is the unit size of a grid cell
            // calculate c using lower and upper corners and number of cells
            // so we can iterate over the grid
            c = (_x_u - _x_l) / n_cells_; 
            
            for(int i = 0; i <= n_cells_; ++i) {
                x[0] = _x_l[0] + c[0] * i;       // iterate through first dimension of the grid
                for(int j = 0; j <= n_cells_; ++j) {
                    x[1] = _x_l[1] + c[1] * j;   // iterate through second dimension of the grid
                    f = _func->eval_f(x);        // evaluate function at the grid point
                    if(f < fmin) {               // if new minimum found
                        fmin = f;                // update minimum value
                        x_min = x;               // update minimum point
                    }
                }
            }
            //------------------------------------------------------//
            _f_min = fmin;
            std::cout<<"Minimum value of the function is: "<<fmin<<" at x:\n"<<x_min<<std::endl;
            return 0;
        }



        /** Evaluation of an ND function over the whole grid to find its minimum
         *  using an iterative approach
         *
         * \param _func a pointer to any ND function inheriting from FunctionBase
         *              (see include/FunctionBase/FunctionBase.hh)
         * \param _x_l the coordinates of the lower corner of the grid
         * \param _x_u the coordinates of the upper corner of the grid.
         *             _x_l and _x_u together define an ND cuboid in which the grid lies
         * \return 0 if all went well, -1 if not.*/
        int grid_search_nd(FunctionBase* _func, const Vec& _x_l, const Vec& _x_u, double& _f_min) const {
            int n = _func->n_unknowns();
            if (_x_l.size() != n || _x_u.size() != n) {
                std::cout << "Error: input limits are not of correct dimension!" << std::endl;
                return -1;
            }
            std::cout << "Grid searching the minimum of a " << n << "-D function..." << std::endl;

            double f = 0., f_min = std::numeric_limits<double>::max();
            Vec x_min(n);
            //------------------------------------------------------//
            //Todo: implement the nd version of the grid search
            // algorithm to find minimum value of a nd quadratic function
            // set f_min with the minimum, which is then stored in the referenced argument _f_min

            Vec x(n), c(n);
            c = (_x_u - _x_l) / n_cells_;
            std::vector<int> index(n, 0); // index counter for each dimension

            x = _x_l; // start at lower corner
            int total_points = pow(n_cells_ + 1, n); // total number of grid points
            for (int i = 0; i < total_points; ++i) {
                f = _func->eval_f(x);
                if (f < f_min) {
                    f_min = f;
                    x_min = x;
                }
                ++(index[0]); // increment first dimension
                x[0] += c[0]; // update first dimension of x (current grid point)

                if (index[0] > n_cells_) { // if the index exceeds the number of cells in the first dimension
                    for (int j = 0; j < n - 1; ++j) {
                        if (index[j] > n_cells_) { // the index exceeds the number of cells in this dimension
                            index[j] = 0;          // reset index
                            x[j] = _x_l[j];        // reset grid coordinate in this dimension
                            ++(index[j + 1]);      // increment the next dimension
                            x[j + 1] += c[j + 1];  // update the next dimension
                        }
                    }
                }
            }
            //------------------------------------------------------//
            _f_min = f_min;
            std::cout << "Minimum value of the function is: " << f_min << " at x:\n" << x_min << std::endl;

            return 0;
        }



    private:
        int n_cells_;
    };

    //=============================================================================
}




