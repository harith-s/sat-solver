#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <fstream>
#include <bits/stdc++.h>

struct Clause
{
public:
    std::set<int> clause;
    bool removed;
    int w1;
    int w2;
    int unassigned;

    Clause(std::set<int> c)
    {
        clause = c;
        removed = false;
        unassigned = clause.size();

        std::set<int>::iterator it;
        it = clause.begin();
        if (clause.size() >= 2)
        {
            std::cout << *it;
            w1 = *it;
            it++;
            w2 = *it;
        }
        else
        {
            w1 = *it;
            w2 = 0;
        }
    }
    Clause()
    {
        removed = false;
    }

    void setWatched(std::vector<int> &truth_vals)
    {
        std::set<int>::iterator it;
        it = clause.begin();

        if (unassigned >= 2)
        {
            w1 = *it;
            it++;
            w2 = *it;
        }
        else
        {
            w1 = *it;
            w2 = 0;
        }
    }
};

int chooseVar(std::vector<int> truth_vals, std::vector<Clause> &formula)
{
    std::map<int, int> freq;

    std::set<int>::iterator max = formula[0].clause.begin();

    for (auto cl_clause : formula)
    {
        if (cl_clause.clause.size() == 2)
        {
            int n = cl_clause.w2;
            cl_clause.w2 = 0;
            return n;
        }
        else
        {

            for (std::set<int>::iterator it = cl_clause.clause.begin(); it != cl_clause.clause.end(); it++)
            {
                freq[*it]++;
                if (freq[*max] > freq[*it])
                    max = it;
            }
        }
    }
    return *max;
}

int main()
{
    std::vector<int> truth_vals = {-1, -1, -1, -1, -1, -1, -1};

    std::vector<Clause> formula(4, Clause());
    formula[0].clause.insert(6);
    formula[0].clause.insert(1);
    formula[0].removed = true;
    formula[0].unassigned = 2;
    formula[0].setWatched(truth_vals);
    
    formula[1].clause.insert(2);
    formula[1].clause.insert(3);
    formula[1].clause.insert(4);
    formula[1].clause.insert(5);
    formula[1].clause.insert(6);
    formula[1].setWatched(truth_vals);
    formula[1].unassigned = 5;


    formula[2].clause.insert(6);
    formula[2].clause.insert(3);
    formula[2].setWatched(truth_vals);
    formula[1].unassigned = 2;
    

    std::cout << chooseVar(truth_vals, formula);
}