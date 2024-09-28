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
    int abs_type;
    // int value;
    Literal()
    {
        type = 0;
        abs_type = abs(type);
        // value = -1;
    }
    Literal(int tp)
    {
        type = tp;
        abs_type = abs(type);
        // value = -1;
    }
    void operator=(Literal l)
    {
        type = l.type;
        abs_type = abs(type);
        // value = l.value;
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
int UnitProp(std::vector<Clause> formula, std::vector<int> truth_vals);

bool modDPLL(std::vector<Clause> formula, std::vector<int> truth_vals)
{
    // sat = -1 means that the formula is neither sat nor unsat
    // sat = 0 means that there is a conflict
    // sat = 1 means that the formula is true

    int sat = UnitProp(formula, truth_vals);

    if (sat == 0)
        return false;
    if (sat == 1)
        return true;

    // control goes here if the formula is neither sat or unsat

    int literal_type = chooseVar(truth_vals);

    truth_vals[literal_type] = 0;

    // run DPLL on the updated truth_table

    bool isSatFalse = modDPLL(formula, truth_vals);

    if (isSatFalse)
        return true;

    truth_vals[literal_type] = 1;

    return modDPLL(formula, truth_vals);
}

int UnitProp(std::vector<Clause> formula, std::vector<int> truth_vals)
{
    // this boolean checks whether the formula has changed, exits loop if no change has happen
    // loop exit happens - any clause is unsat

    bool hasChanged = true;
    while (hasChanged)
    {
        hasChanged = false;
        for (auto &clause : formula)
        {
            if (clause.sat == -1)
            {
                int ua = 0;
                int sz = clause.c.size();
                int index = 0;
                int assign_type = 0;

                for (index = 0; index < sz; index++)
                {
                    if (truth_vals[clause.c[index].abs_type] == -1)
                    {
                        ua++;
                        assign_type = clause.c[index].type;
                    }
                    else
                    {
                        Literal literal = clause.c[index];
                        if ((literal.type > 0 && truth_vals[literal.abs_type] == 1) || (literal.type < 0 && truth_vals[literal.abs_type] == 0))
                        {
                            clause.sat = 1;
                            break; // clause is sat
                        }
                    }
                }

                // if at least one of the literals has a bool val of 1, clause.sat = 1; and there are no unassigned vbles
                // so no scope for this clause to be sat -> conflict

                if (ua == 0 && clause.sat != 1)
                    return 0;

                // assigns values if number of unassigned variables is 1 and the clause is still unassigned

                else if (ua == 1 && clause.sat == -1)
                {
                    // finding the clause to be assigned

                    for (index = 0; index < sz; index++)
                    {
                        if (clause.c[index].type == assign_type)
                            break;
                    }

                    Literal &to_assign = clause.c[index];

                    // doing what would make the clause true

                    if (to_assign.type > 0)
                        truth_vals[to_assign.abs_type] = 1;
                    else
                        truth_vals[to_assign.abs_type] = 0;
                    clause.sat = 1;
                    hasChanged = true;
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
            clause[i].abs_type = abs(tp);
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
    ss >> word;
    ss >> word;
    nV = stoi(word);
    ss >> word;
    nC = stoi(word);
    return;
}

int main()
{
    int num_files = 2;
    for (int file_no = 1; file_no < num_files; file_no++)
    {
        string file = "sat_testcase/uf20-0" + to_string(file_no) + ".cnf";
        
        file = "input.txt";
        
        ifstream inputFile(file);

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
        while (!line.empty() && line[0] != 'p')
        {
            std::getline(inputFile, line);
        }
        numInfo(line, nClauses, nVar);

        vector<Clause> formula(nClauses, Clause());
        int i = 0;

        while (getline(inputFile, line) && line[0] != '%')
        {
            int n = numLiterals(line);
            vector<Literal> clause(n, Literal(0));
            putLiterals(line, clause);
            formula[i].c = clause;
            i++;
        }

        inputFile.close();

        std::vector<int> ttable(nVar + 1, -1);
        if (not(modDPLL(formula, ttable))) cout << "Error!";
    }
}