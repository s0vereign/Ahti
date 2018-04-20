#include "gtest/gtest.h"

#include <boost/math/constants/constants.hpp>
#include "../include/math/CartToSpherical.hpp"
#include <iostream>

TEST(SphericalTest, ThetaTests)
{
    double theta = 0;
    double x = 1.0;
    double y = 0.0;
    double z = 0.0;

    double res = math::theta(x, y, z);

    ASSERT_EQ(res, boost::math::constants::pi<double>()/2.0);


    theta = 0;
    x = 0.0;
    y = 0.0;
    z = 1.0;

    res = math::theta(x, y, z);

    ASSERT_EQ(res, 0);

    theta = boost::math::constants::pi<double>();
    x = 0.0;
    y = 0.0;
    z = -1.0;

    res = math::theta(x,y,z);

    ASSERT_EQ(res, theta);
}

TEST(SpericalTest, PhiTests)
{
    double pi = boost::math::constants::pi<double>();
    std::vector<double> phis = {pi/4.0, 3.0/4.0 * pi, 5.0/4.0 * pi, 7.0/4.0 * pi};
    std::vector<double> thetas = {pi/4.0, 3.0/4.0 * pi};

    double r = 1.0;
    std::vector<double> cart_r(3);
    for(int i = 0; i < 4; i++)
    {
        cart_r = math::sp_to_cart(r, phis[i], thetas[0]);
        double theta = math::theta(cart_r[0], cart_r[1], cart_r[2]);
        double phi = math::phi(cart_r[0], cart_r[1], cart_r[2]);
        ASSERT_DOUBLE_EQ(theta, thetas[0]);
        ASSERT_DOUBLE_EQ(phi, phis[i]);

        cart_r = math::sp_to_cart(r, phis[i], thetas[1]);
        theta = math::theta(cart_r[0], cart_r[1], cart_r[2]);
        phi = math::phi(cart_r[0], cart_r[1], cart_r[2]);
        ASSERT_DOUBLE_EQ(theta, thetas[1]);
        ASSERT_DOUBLE_EQ(phi, phis[i]);
    }
}