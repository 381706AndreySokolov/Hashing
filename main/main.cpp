#ifndef MAIN_MAIN_H_
#define MAIN_MAIN_H_

#include "chain_hash.h"
#include "open_adr_hash.h"

#include <iostream>
#include <array>
#include <vector>
#include <ctime>
#include <random>
#include <math.h>
#include <numeric>
#include <fstream>
#include "windows.h"

#define Div_Time
#define Mul_Time
#define Univ_Time
#define K_Ind_Time
#define Std_Time
//#define Linear_Probe
//#define Quadratic_Probe
//#define Double_hashing

using namespace std;

int main()
{
    int i = 0;
    int j = 0;
    clock_t start;
    clock_t end;
    double seconds;
    ofstream fout;
    cout << "========== Testing Chain Hash ==========" << endl << endl;

    //{
    //    chain_hash::HashTable<> table(100, 4);

    //    table.insert(123232, 6);
    //    table.insert(23, 7);
    //    table.insert(12323432, 6);
    //    table.insert(1, 6);

    //    std::cout << table[123232] << "\n";
    //    std::cout << table[6] << " \n";
    //}
#ifdef Div_Time
    cout << "============ Division Method ===========" << endl << endl;

    fout.open("../../Results/Chain_Hash_Division.xls", ios::app);

    for (i = pow(2, 10); i <= pow(2, 25); i = pow(2, 25))
    {
        chain_hash::HashTable<> table(i, 1);
        start = clock();
        for (j = 0; j < i * 4; j++)
        {
            table.insert(rand(), j);
        }
        end = clock();
        seconds = (double)(end - start) / CLOCKS_PER_SEC;
        cout << "The time of inserting " << i << " elements is " << seconds << " seconds" << endl;
        fout << i << "\t" << seconds << "\t";


        if (i == pow(2, 10))
        {
            auto vector = table.getDistribution();
            for (int idx = 0; idx < vector.size(); ++idx)
            {
                cout << vector[idx] << " ";
            }
            cout << endl;
        }

        start = clock();
        for (j = 0; j < i * 4; j++)
        {
            int key = rand() % i;
            auto tmp = table[key];
        }
        end = clock();
        seconds = (double)(end - start) / CLOCKS_PER_SEC;
        cout << "The time of searching " << i << " elements is " << seconds << " seconds" << endl;
        fout << seconds << "\t";

        start = clock();
        for (j = 0; j < (i - i / 3); j++)
        {
            //int key = rand() % i;
            //table.remove(key);
        }
        end = clock();
        seconds = (double)(end - start) / CLOCKS_PER_SEC;
        cout << "The time of removing " << i <<  " elements is " << seconds << " seconds" << endl;
        fout << seconds << "\t" << endl;

        cout << endl << endl;
    }
    fout.close();
#endif

#ifdef Mul_Time
    cout << "============ Mul Method ===========" << endl << endl;
    fout.open("../../Results/Chain_Hash_Mul.xls", ios::app);

    for (i = pow(2, 10); i <= pow(2, 25); i = pow(2, 25))
    {
        chain_hash::HashTable<> table(i, 2);
        start = clock();
        for (j = 0; j < i * 4; j++)
        {
            table.insert(rand(), j);
        }
        end = clock();
        seconds = (double)(end - start) / CLOCKS_PER_SEC;
        cout << "The time of inserting " << i << " elements is " << seconds << " seconds" << endl;
        fout << i << "\t" << seconds << "\t";

        if (i == pow(2, 10))
        {
            auto vector = table.getDistribution();
            for (int idx = 0; idx < vector.size(); ++idx)
            {
                cout << vector[idx] << " ";
            }
            cout << endl;
        }

        start = clock();
        for (j = 0; j < i * 4; j++)
        {
            int key = rand() % i;
            auto tmp = table[key];
        }
        end = clock();
        seconds = (double)(end - start) / CLOCKS_PER_SEC;
        cout << "The time of searching " << i << " elements is " << seconds << " seconds" << endl;
        fout << seconds << "\t";

        start = clock();
        for (j = 0; j < (i - i / 3); j++)
        {
            //int key = rand() % i;
            //table.remove(key);
        }
        end = clock();
        seconds = (double)(end - start) / CLOCKS_PER_SEC;
        cout << "The time of removing " << i << " elements is " << seconds << " seconds" << endl;
        fout << seconds << "\t" << endl;

        cout << endl << endl;
    }
    fout.close();
#endif

#ifdef Univ_Time
    cout << "=========== Universal Hashing ===========" << endl << endl;
    fout.open("../../Results/Chain_Hash_Universal.xls", ios::app);

    for (i = pow(2, 10); i <= pow(2, 25); i = pow(2, 25))
    {
        //chain_hash::FixedSet fs;
        chain_hash::HashTable<> table(i, 3);
        //fs.setTableSize(i);
        start = clock();
        for (j = 0; j < i * 4; j++)
        {
            table.insert(rand(), j);
        }
        end = clock();
        //fs.Initialize(inputVector);
        
        seconds = (double)(end - start) / CLOCKS_PER_SEC;
        cout << "The time of inserting " << i << " elements is " << seconds << " seconds" << endl;
        fout << i << "\t" << seconds << "\t";

        start = clock();
        for (j = 0; j < i * 4; j++)
        {
            int key = rand() % i;
            auto tmp = table[key];
            // auto tmp = fs.Contains(key);
        }
        end = clock();
        seconds = (double)(end - start) / CLOCKS_PER_SEC;
        cout << "The time of searching " << i << " elements is " << seconds << " seconds" << endl;
        fout << seconds << "\t";

        if (i == pow(2, 10))
        {
            auto vector = table.getDistribution();
            for (int idx = 0; idx < vector.size(); ++idx)
            {
                cout << vector[idx] << " ";
            }
            cout << endl;
        }

        start = clock();
        for (j = 0; j < (i - i / 3); j++)
        {
            int key = rand() % i;
            //table.remove(key);
            //fs.Contains(key);
        }
        end = clock();
        seconds = (double)(end - start) / CLOCKS_PER_SEC;
        cout << "The time of removing " << i << " elements is " << seconds << " seconds" << endl;
        fout << seconds << "\t" << endl;

        cout << endl << endl;
    }
    fout.close();
#endif

#ifdef K_Ind_Time
    cout << "=========== K-Independent Hashing ===========" << endl << endl;
    fout.open("../../Results/Chain_Hash_K_Independent.xls", ios::app);

    for (i = pow(2, 10); i <= pow(2, 25); i = pow(2, 25))
    {
        //chain_hash::FixedSet fs;
        chain_hash::HashTable<> table(i, 4);
        table.generateAVector(4);
        //fs.setTableSize(i);
        start = clock();
        for (j = 0; j < i * 4; j++)
        {
            table.insert(rand(), j);
        }
        end = clock();
        //fs.Initialize(inputVector);

        seconds = (double)(end - start) / CLOCKS_PER_SEC;
        cout << "The time of inserting " << i << " elements is " << seconds << " seconds" << endl;
        fout << i << "\t" << seconds << "\t";

        start = clock();
        for (j = 0; j < (i * 4); j++)
        {
            int key = rand() % i;
            auto tmp = table[key];
            // auto tmp = fs.Contains(key);
        }
        end = clock();
        seconds = (double)(end - start) / CLOCKS_PER_SEC;
        cout << "The time of searching " << i << " elements is " << seconds << " seconds" << endl;
        fout << seconds << "\t";

        if (i == pow(2, 10))
        {
            auto vector = table.getDistribution();
            for (int idx = 0; idx < vector.size(); ++idx)
            {
                cout << vector[idx] << " ";
            }
            cout << endl;
        }

        start = clock();
        for (j = 0; j < (i - i / 3); j++)
        {
            int key = rand() % i;
            //table.remove(key);
            //fs.Contains(key);
        }
        end = clock();
        seconds = (double)(end - start) / CLOCKS_PER_SEC;
        cout << "The time of removing " << i << " elements is " << seconds << " seconds" << endl;
        fout << seconds << "\t" << endl;

        cout << endl << endl;
    }
    fout.close();
#endif

#ifdef Std_Time
    cout << "=========== STD Hashing ===========" << endl << endl;
    fout.open("../../Results/Chain_Hash_std.xls", ios::app);

    //for (i = pow(2, 10); i < pow(2, 25); i *= 2)
    for (i = pow(2, 10); i <= pow(2, 25); i = pow(2, 25))
    {
        //chain_hash::FixedSet fs;
        chain_hash::HashTable<> table(i, 5);
        table.generateAVector(4);
        //fs.setTableSize(i);
        start = clock();
        for (j = 0; j < i * 4; j++)
        {
            table.insert(rand(), j);
        }
        end = clock();
        //fs.Initialize(inputVector);

        seconds = (double)(end - start) / CLOCKS_PER_SEC;
        cout << "The time of inserting " << i << " elements is " << seconds << " seconds" << endl;
        fout << i << "\t" << seconds << "\t";

        start = clock();
        for (j = 0; j < (i * 4); j++)
        {
            int key = rand() % i;
            auto tmp = table[key];
            // auto tmp = fs.Contains(key);
        }
        end = clock();
        seconds = (double)(end - start) / CLOCKS_PER_SEC;
        cout << "The time of searching " << i << " elements is " << seconds << " seconds" << endl;
        fout << seconds << "\t";

        if (i == pow(2, 10))
        {
            auto vector = table.getDistribution();
            for (int idx = 0; idx < vector.size(); ++idx)
            {
                cout << vector[idx] << " ";
            }
            cout << endl;
        }

        start = clock();
        for (j = 0; j < (i - i / 3); j++)
        {
            int key = rand() % i;
            //table.remove(key);
            //fs.Contains(key);
        }
        end = clock();
        seconds = (double)(end - start) / CLOCKS_PER_SEC;
        cout << "The time of removing " << i << " elements is " << seconds << " seconds" << endl;
        fout << seconds << "\t" << endl;

        cout << endl << endl;
    }
    fout.close();
#endif
    cout << "========== End of Testing Chain Hash ==========" << endl << endl;

    //cout << "========== Testing Open Adress Hash ==========" << endl << endl;
#ifdef Linear_Probe
    cout << "============ Linear Probe Method ===========" << endl << endl;

    fout.open("../../Results/Open_Adr_Hash_Linear_Probe.xls", ios::app);

    for (i = pow(2, 10); i < pow(2, 27); i *= 2)
    {
        open_adr::hashTable<> table(i, 1);
        start = clock();
        for (j = 0; j < (i - i / 3); j++)
        {
            table.insert(j, j);
        }
        end = clock();
        seconds = (double)(end - start) / CLOCKS_PER_SEC;
        cout << "The time of inserting " << i << " elements is " << seconds << " seconds" << endl;
        fout << i << "\t" << seconds << "\t";

        start = clock();
        for (j = 0; j < (i - i / 3); j++)
        {
            int key = rand() % i;
            auto tmp = table[key];
        }
        end = clock();
        seconds = (double)(end - start) / CLOCKS_PER_SEC;
        cout << "The time of searching " << i << " elements is " << seconds << " seconds" << endl;

        fout << seconds << "\t" << endl;

        cout << endl << endl;
    }
    fout.close();
#endif

#ifdef Quadratic_Probe
    cout << "============ Quadratic Probe Method ===========" << endl << endl;

    fout.open("../../Results/Open_Adr_Hash_Quadratic_Probe.xls", ios::app);

    for (i = pow(2, 10); i < pow(2, 27); i *= 2)
    {
        open_adr::hashTable<> table(i, 3);
        start = clock();
        for (j = 0; j < (i - i / 3); j++)
        {
            table.insert(j, j);
        }
        end = clock();
        seconds = (double)(end - start) / CLOCKS_PER_SEC;
        cout << "The time of inserting " << i << " elements is " << seconds << " seconds" << endl;
        fout << i << "\t" << seconds << "\t";

        start = clock();
        for (j = 0; j < (i - i / 3); j++)
        {
            int key = rand() % i;
            auto tmp = table[key];
        }
        end = clock();
        seconds = (double)(end - start) / CLOCKS_PER_SEC;
        cout << "The time of searching " << i << " elements is " << seconds << " seconds" << endl;

        fout << seconds << "\t" << endl;

        cout << endl << endl;
    }
    fout.close();
#endif

#ifdef Double_hashing
    cout << "============ Double hashing Method ===========" << endl << endl;

    fout.open("../../Results/Open_Adr_Hash_Double_hashing.xls", ios::app);

    for (i = pow(2, 10); i < pow(2, 27); i *= 2)
    {
        open_adr::hashTable<> table(i, 3);
        start = clock();
        for (j = 0; j < (i - i / 3); j++)
        {
            table.insert(j, j);
        }
        end = clock();
        seconds = (double)(end - start) / CLOCKS_PER_SEC;
        cout << "The time of inserting " << i << " elements is " << seconds << " seconds" << endl;
        fout << i << "\t" << seconds << "\t";

        start = clock();
        for (j = 0; j < (i - i / 3); j++)
        {
            int key = rand() % i;
            auto tmp = table[key];
        }
        end = clock();
        seconds = (double)(end - start) / CLOCKS_PER_SEC;
        cout << "The time of searching " << i << " elements is " << seconds << " seconds" << endl;

        fout << seconds << "\t" << endl;

        cout << endl << endl;
    }
    fout.close();
#endif
    cout << "========== End of Testing Open Adress Hash ==========" << endl << endl;
    return 0;
}

#endif  // MAIN_MAIN_H_