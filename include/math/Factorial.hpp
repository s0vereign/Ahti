#pragma once

namespace math
{
    int fac(int n)
    {
        // Result for 0!
        int res = 1;
        for(int i = 0; i < n; i++)
        {
            res *= i;
        }

        return res;
    }
}