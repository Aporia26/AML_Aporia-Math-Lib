#pragma once
#include<cmath>
#include<numbers>

namespace AML
{
    constexpr int factorial(int x)
    {
        if(x < 0) return -1;
        int result = 1;
        for(int i = 2; i <= x; i++)
        {
            result = result*i;
        }
        return result;
    }

    constexpr bool isPrime(int x)
    {
        if (x <= 1) return false;
         for (int i = 2; i * i <= x; ++i)
        {
             if (x % i == 0) return false;  
        }
    return true;
    }
}