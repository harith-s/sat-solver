#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <bits/stdc++.h>

using namespace std;
// assuming that indicies are the literal names
class Literal
{

public:
    int type;
    int value;
    Literal()
    {
        type = -1;
        value = -1;
    }
    Literal(int tp)
    {
        type = tp;
        value = -1;
    }
    void operator=(Literal l)
    {
        type = l.type;
        value = l.value;
    }
};

class Clause
{
public:
    std::vector<Literal> c;
    int sat;
    Clause(std::vector<Literal> v)
    {
        for (int i = 0; i < v.size(); i++)
        {
            c.push_back(v[i]);
        }
        // num_unassigned = (int)(v.size());
        sat = -1;
    }
    Clause()
    {
        sat = -1;
    }
};

std::vector<Clause> getFormula()
{
    std::vector<Clause> formula;
    int num_clauses;
    std::cout << "Input number of Clauses: ";

    std::cin >> num_clauses;
    for (int i = 0; i < num_clauses; i++)
    {
        std::vector<Literal> clause;
        int num_lit;
        std::cout << "Input number of literals in this clause: ";

        std::cin >> num_lit;
        std::cout << "Input the literals in this clause: ";
        for (int j = 0; j < num_lit; j++)
        {
            int k = 0;

            std::cin >> k;

            clause.push_back(Literal(k));
        }
        formula.push_back(Clause(clause));
    }
    return formula;
}
int chooseVar(std::vector<int> truth_vals)
{
    std::vector<int> unassigned;
    for (int i = 1; i < truth_vals.size(); i++)
    {
        if (truth_vals[i] == -1)
            unassigned.push_back(i);
    }
    return unassigned[rand() % unassigned.size()];
}
int UP(std::vector<Clause> formula, std::vector<int> truth_vals);

// if (literal.type > 0 && truth_vals[literal.type] == 1 || (literal.type < 0 && truth_vals[literal_type] == 0)){
//                 clause.sat = 1;
//                 break;
//             }
//             if (literal.type > 0) literal.value = truth_vals[literal.type] == -1 ? -1 : 1;
//             else literal.value = truth_vals[-literal.type] == -1 ? -1 : 1;

bool DPLL(std::vector<Clause> formula, std::vector<int> truth_vals)
{
    int sat = UP(formula, truth_vals);
    if (sat == 0)
        return false;
    if (sat == 1)
        return true;
    int literal_type = chooseVar(truth_vals);
    truth_vals[literal_type] = 0;

    for (auto &clause : formula)
    {
        clause.sat = -1;
        bool unsat = true;
        for (auto &literal : clause.c)
        {
            // (literal.type > 0 && truth_vals[literal.type] == 1 || (literal.type < 0 && truth_vals[literal_type] == 0))
            int val = truth_vals[abs(literal.type)];
            if (val == -1)
                literal.value = -1;
            else
                literal.value = literal.type > 0 ? val : (val == 1 ? 0 : 1);

            if (literal.value == -1 || literal.value == 1)
            {
                unsat = false;
                if (literal.value == 1)
                    clause.sat = 1;
            }
        }
        if (unsat)
            clause.sat = 0;
    }

    bool isSatFalse = DPLL(formula, truth_vals);
    if (isSatFalse)
        return true;

    truth_vals[literal_type] = 1;

    for (auto &clause : formula)
    {
        clause.sat = -1;
        bool unsat = true;
        for (auto &literal : clause.c)
        {
            // (literal.type > 0 && truth_vals[literal.type] == 1 || (literal.type < 0 && truth_vals[literal_type] == 0))
            int val = truth_vals[abs(literal.type)];
            if (val == -1)
                literal.value = -1;
            else
                literal.value = literal.type > 0 ? val : (val == 1 ? 0 : 1);

            if (literal.value == -1 || literal.value == 1)
            {
                unsat = false;
                if (literal.value == 1)
                    clause.sat = 1;
            }
            
        }
        if (unsat)
                clause.sat = 0;
    }
    return DPLL(formula, truth_vals);
}

int UP(std::vector<Clause> formula, std::vector<int> truth_vals)
{
    bool hasChanged = true;
    while (hasChanged)
    {
        hasChanged = false;
        for (auto &clause : formula)
        {
            if (clause.sat == 0)
                return 0;
            else if (clause.sat == -1)
            {
                int num_ua = 0;
                Literal * assignPtr;
                for (auto literal : clause.c)
                {
                    if ((literal.value) == -1)
                    {
                        num_ua++;
                        assignPtr = &literal;
                    }
                }
                Literal to_assign = *assignPtr;
                if (num_ua == 1)
                {
                    if (to_assign.type > 0)
                    {
                        if (truth_vals[to_assign.type] == 0)
                            return 0;
                        truth_vals[to_assign.type] = 1;
                        to_assign.value = 1;
                        clause.sat = 1;
                        hasChanged = true;
                        break;
                    }
                    else
                    {
                        if (truth_vals[-(to_assign.type)] == 1)
                            return 0;
                        truth_vals[-(to_assign.type)] = 0;
                        to_assign.value = 1;
                        clause.sat = 1;
                        hasChanged = true;
                        break;
                    }
                }
            }
        }
    }
    for (int i = 1; i < truth_vals.size(); i++)
    {
        if (truth_vals[i] == -1)
            return -1;
    }
    return 1;
}

// int unit_prop(std::vector<Clause> formula, std::vector<int> &truth_vals){

//     for (int iclause = 0; iclause < formula.size(); iclause++)
//     {
//         if (!formula[iclause].sat && formula[iclause].num_unassigned == 1)
//         {
//             formula[iclause].num_unassigned = 0;
//             for (int i = 0; i < formula[iclause].c.size(); i++)
//             {
//                 if (formula[iclause].c[i].value == -1)
//                 {
//                     formula[iclause].c[i].value = 1;
//                     if (formula[iclause].c[i].type > 0)
//                     {
//                         if (truth_vals[formula[iclause].c[i].type] == 0)
//                             return -1;
//                         truth_vals[formula[iclause].c[i].type] = 1;
//                     }
//                     else
//                     {
//                         if (truth_vals[formula[iclause].c[i].type] == 1)
//                             return -1;
//                         truth_vals[-formula[iclause].c[i].type] = 0;
//                     }
//                 }
//             }
//         }
//     }
//     return 0;
// }

void putLiterals(string s, vector<Literal> &clause)
{
    stringstream ss(s);
    string word;
    int i = 0;
    int tp;
    while (ss >> word)
    {
        tp = stoi(word);
        if (tp == 0)
        {
            return;
        }
        else
        {
            clause[i].type = tp;
            i++;
        }
    }
}
int numLiterals(string s)
{
    stringstream ss(s);
    string word;
    int count = 0;
    while (ss >> word)
    {
        if (word != "0")
            count++;
    }
    return count;
}

void numInfo(string s, int &nC, int &nV)
{
    stringstream ss(s);
    string word;
    ss >> word;
    nC = stoi(word);
    ss >> word;
    nV = stoi(word);
    return;
}
int main()
{
    ifstream inputFile("input.txt");

    // Check if the file is successfully opened
    if (!inputFile.is_open())
    {
        cerr << "Error opening the file!" << endl;
        return 1;
    }

    string line;
    int nClauses = 0;
    int nVar = 0;
    getline(inputFile, line);
    numInfo(line, nClauses, nVar);

    vector<Clause> formula(nClauses, Clause());
    int i = 0;

    while (getline(inputFile, line))
    {
        int n = numLiterals(line);
        vector<Literal> clause(n, Literal(0));
        putLiterals(line, clause);
        formula[i].c = clause;
        i++;
    }

    inputFile.close();

    std::vector<int> ttable(nVar + 1, -1);
    std::cout << DPLL(formula, ttable);
}