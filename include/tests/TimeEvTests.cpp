#include <iostream>
#include <complex>
#include <vector>
#include <math.h>
#include <mpi.h>

#include "grid/Localgrid.hpp"
#include "timeconf/Timeconf.hpp"
#include "math/FourierCoeff.hpp"
#include "math/CoeffEv.hpp"
#include "math/ValsEv.hpp"
#include "testfunctors/Gaussian.hpp"
#include "config/Config1D.hpp"
#include "worker/TimeEv.hpp"

#include "math/CoeffEv.hpp"
#include "math/ValsEv.hpp"

#define PI 3.141592653589793

#define BOOST_TEST_MODULE "TimeEvTest"

#include "boost/test/included/unit_test.hpp"



BOOST_AUTO_TEST_CASE(COEFF_EV)
{
    using std::cout; 
    using std::endl;
    using std::complex;
    using std::exp;
    using math::fourier_1D_serial;
    using std::vector;
    cout << "Running 1D Coefficient Evolution" << endl;

    int nx = 5;
    const int gnx = 10.0;
    const double l = 1.0;
    const double dt = 2.0;
    
    const complex<double> j(0.0, 1.0);
    vector<complex<double>> analytical = {1.0, 2.0, 3.0, 4.0, 5.0};
    vector<complex<double>> numerical(analytical);

    int xmin = 4;
    int xmax = xmin + nx;

    Grid::Localgrid1D* l = Grid::create_Localgrid1D(nx, xmax, xmin);

    int n = xmin - gnx/2;
    for(auto& it : analytical)
    {
        it *= it * exp( -j * 4*PI*PI*n*n);
        
    }
}
