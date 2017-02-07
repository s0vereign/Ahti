#pragma once



namespace potential {

    
    struct HarmOsc1D
    {
        double operator()(const double x)
        {
            return x*x/2.0;
        }
    };
}