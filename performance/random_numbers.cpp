#include "hashing.h"

#include <iostream>
#include <array>
#include <vector>
#include <ctime>
#include <random>
#include <math.h>
#include <numeric>
#include <fstream>

#define Div_Time
#define Mul_Time
#define Univ_Time
#define K_Ind_Time
#define Std_Time
//#define Linear_Probe
//#define Quadratic_Probe
//#define Double_hashing


int main()
{
    int i = 0;
    int j = 0;
    clock_t start;
    clock_t end;
    double seconds;
    std::ofstream fout;
    cout << "========== Testing Chain Hash ==========" << endl << endl;
#ifdef Div_Time
    cout << "============ Division Method ===========" << endl << endl;

    fout.open("../../Results/Random_Numbers/Chain_Hash_Division.xls", std::ios::app);

    for (i = pow(2, 10); i <= pow(2, 25); i *= 2)
    {
        chain_hash::HashTable<int, int, 1> table(i);
        start = clock();
        for (j = 0; j < i; j++)
        {
            table.insert(rand(), j);
        }
        end = clock();
        seconds = (double)(end - start) / CLOCKS_PER_SEC;
        cout << "The time of inserting 2^" << std::log2(i) << " elements is " << seconds << " seconds" << endl;
        fout << i << "\t" << seconds << "\t";

        start = clock();
        for (j = 0; j < i; j++)
        {
            int key = rand() % i;
            auto tmp = table[key];
            (void)tmp;
        }
        end = clock();
        seconds = (double)(end - start) / CLOCKS_PER_SEC;
        cout << "The time of searching 2^" << std::log2(i) << " elements is " << seconds << " seconds" << endl;
        fout << seconds << "\t";

        std::cout << std::endl;
    }
    fout.close();
#endif

    return 0;
}
