#include <iostream>
#include <vector>
#include <fstream>
#include <string>
// #include <algorithm>
#include <bits/stdc++.h>
#include <queue>
#include <map>
using namespace std;
// assuming that indicies are the literal names

// GLOBAL vbles

vector<int> vble_order;
int num_decisions = 0;

// class for Literal - its name and whether it is a positive literal or negative
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

// class containing a vector of literals and sat of the clause

class Clause
{
public:
    std::vector<int> c;
    int sat;
    Clause(std::vector<int> v)
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

// checks for the number of variables and clauses

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

// this is to put literals given a string containing the literals

void putLiterals(string s, vector<int> &clause, map<int, int> &vble_freq)
{
    stringstream ss(s);
    string word;
    int tp;

    // first position for unsat/sat/unassigned

    clause.push_back(-1);

    while (ss >> word)
    {
        tp = stoi(word);
        if (tp == 0)
        {
            return;
        }
        else
        {
            clause.push_back(tp);
            vble_freq[abs(tp)] = vble_freq[abs(tp)] + 1;
        }
    }
}

// checking the number of literals in the string

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

// to manually take in the formula

std::vector<Clause> getFormula()
{
    std::vector<Clause> formula;
    int num_clauses;
    std::cout << "Input number of Clauses: ";

    std::cin >> num_clauses;
    for (int i = 0; i < num_clauses; i++)
    {
        std::vector<int> clause;
        int num_lit;
        std::cout << "Input number of literals in this clause: ";

        std::cin >> num_lit;
        std::cout << "Input the literals in this clause: ";
        for (int j = 0; j < num_lit; j++)
        {
            int k = 0;

            std::cin >> k;

            clause.push_back(k);
        }
        formula.push_back(Clause(clause));
    }
    return formula;
}

// heuristics for choosing the variable (right now its the most occuring vble)
// int chooseVar(std::vector<int> &truth_vals, vector<Clause> formula){
//     int type = 0; int max = 0;
//     for (auto & clause : formula){
//         if (clause.c.size() == 2){

//         }
//     }
// }
int chooseVar(std::vector<int> truth_vals, vector<vector<int>> formula)
{
    num_decisions++;
    cout << num_decisions << endl;
    std::vector<int> unassigned;
    for (int i = 1; i < truth_vals.size(); i++)
    {
        if (truth_vals[i] == -1)
            unassigned.push_back(i);
    }
    return unassigned[rand() % unassigned.size()];
}
// unit prop and decision put into a function

vector<vector<int>> removeSat(std::vector<vector<int>> formula)
{
    int sz = formula.size();
    priority_queue<int> to_remove;
    for (int i = 0; i < sz; i++)
    {
        if (formula[i][0] == 1)
        {
            to_remove.push(i);
        }
    }
    while (not(to_remove.empty()))
    {
        formula.erase(formula.begin() + to_remove.top());
        to_remove.pop();
    }
    return formula;
}

void removeSatClausesUP(vector<vector<int>> &formula, int assign_type)
{
    int sz = formula.size();
    priority_queue<int> to_remove;
    for (int i = 0; i < sz; i++)
    {
        for (int j = 1; j < formula[i].size(); j++)
        {
            if (formula[i][j] == assign_type)
            {
                to_remove.push(i);
                break;
            }
        }
    }
    while (not(to_remove.empty()))
    {
        formula.erase(formula.begin() + to_remove.top());
        to_remove.pop();
    }
    return;
}
vector<vector<int>> removeSat(vector<vector<int>> formula, int assign_type)
{
    int sz = formula.size();
    priority_queue<int> to_remove;
    for (int i = 0; i < sz; i++)
    {
        for (int j = 1; j < formula[i].size(); j++)
        {
            if (formula[i][j] == assign_type)

            {
                to_remove.push(i);
                break;
            }
        }
    }
    while (not(to_remove.empty()))
    {
        formula.erase(formula.begin() + to_remove.top());
        to_remove.pop();
    }
    return formula;
}

vector<vector<int>> setSat(std::vector<vector<int>> formula, int chosen, int val)
{
    for (auto &clause : formula)
    {
        for (int j = 1; j < clause.size(); j++)
        {
            if ((clause[j] == chosen && val == 1) || (clause[j] == -chosen && val == 0))
            {
                clause[0] = 1;
                break;
            }
            else
            {
                clause[0] = -1;
            }
        }
    }
    return formula;
}


vector<vector<int>> removePos(vector<vector<int>> formula, int type)
{

    // called when we assign 0 to a variable
    // the first value of -1 won't cause an issue as the type removed here is positive

    for (auto &clause : formula)
    {
        clause.erase(std::remove(clause.begin(), clause.end(), type), clause.end());
    }
    return formula;
}

vector<vector<int>> removeNeg(vector<vector<int>> formula, int type)
{

    // called when we assign 0 to a variable
    // the first value of -1 causes an issue as we denote sat by -1
    // we don't do anything in case type == 1 slight innefficiency, but can live with it

    if (type != 1)
    {
        for (auto &clause : formula)
        {
            clause.erase(std::remove(clause.begin(), clause.end(), -type), clause.end());
        }
    }
    else{
        for (auto & clause : formula){
            vector<int> temp = clause;
            temp.erase(std::remove(temp.begin(), temp.end(), -1), temp.end());
            clause.clear();
            clause.push_back(-1);
            for(int i = 0; i < temp.size(); i++){
                clause.push_back(temp[i]);
            }
        }
    }
    return formula;
}

// Does unit propgation returns -1 if decisions can be made; 0 if formula is unsat and 1 if formula sat

vector<int> UnitProp(std::vector<vector<int>> formula, std::vector<int> truth_vals)
{
    // this boolean checks whether the formula has changed, exits loop if no change has happen
    // loop exit happens - any clause is unsat

    bool hasChanged = true;
    while (hasChanged)
    {
        hasChanged = false;
        for (auto &clause : formula)
        {
            // I don't even need this condition now but let it be
            if (clause[0] == -1)
            {
                int assign_type = 0;

                // no more variables left to assign

                if (clause.size() == 1)
                {
                    truth_vals[0] = 0;
                    return truth_vals;
                }
                if (clause.size() == 2)
                {
                    assign_type = clause[1];

                    if (assign_type > 0)
                    {
                        truth_vals[assign_type] = 1;
                        formula = removeNeg(formula, assign_type);
                        removeSatClausesUP(formula, assign_type);
                    }
                    else
                    {
                        truth_vals[-assign_type] = 0;
                        formula = removePos(formula, -assign_type);
                        removeSatClausesUP(formula, assign_type);
                    }
                    // clause[0] = 1;
                    hasChanged = true;

                    // break;
                }
                // for (index = 1; index < sz; index++)
                // {
                //     int literal_type = clause[index];
                //     if (truth_vals[abs(clause[index])] == -1)
                //     {
                //         ua++;
                //         assign_type = clause[index];
                //     }
                //     else
                //     {
                //         if ((literal_type > 0 && truth_vals[abs(literal_type)] == 1) || (literal_type < 0 && truth_vals[abs(literal_type)] == 0))
                //         {
                //             clause[0] = 1;
                //             break; // clause is sat
                //         }
                //     }
                // }

                // if at least one of the literals has a bool val of 1, clause.sat = 1; and there are no unassigned vbles
                // so no scope for this clause to be sat -> conflict

                // if (ua == 0 && clause[0] != 1)
                // {
                //     truth_vals[0] = 0;
                //     return truth_vals;
                // }

                // assigns values if number of unassigned variables is 1 and the clause is still unassigned

                // else if (ua == 1 && clause[0] == -1)
                // {
                //     // doing what would make the clause true

                //     if (assign_type > 0)
                //     {
                //         truth_vals[assign_type] = 1;
                //         formula = removeNeg(formula, assign_type);
                //         removeSatClauses(formula, assign_type);
                //     }
                //     else
                //     {
                //         truth_vals[-assign_type] = 0;
                //         formula = removePos(formula, assign_type);
                //         removeSatClauses(formula, assign_type);

                //     }
                //     clause[0] = 1;
                //     hasChanged = true;

                //     break;
                // }
            }
        }
    }
    for (int i = 1; i < truth_vals.size(); i++)
    {
        if (truth_vals[i] == -1)
        {
            truth_vals[0] = -1;
            return truth_vals;
        }
    }
    truth_vals[0] = 1;
    return truth_vals;
}

vector<int> DPLL(std::vector<vector<int>> formula, std::vector<int> truth_vals)
{
    // sat = -1 means that the formula is neither sat nor unsat
    // sat = 0 means that there is a conflict
    // sat = 1 means that the formula is true

    vector<int> sat = UnitProp(formula, truth_vals);

    if (sat[0] != -1)
        return sat;

    // control goes here if the formula is neither sat or unsat

    int literal_type = chooseVar(truth_vals, formula);

    // cout << literal_type << endl;

    truth_vals[literal_type] = 1;

    // removeNeg(formula, literal_type);

    // setSat(formula, literal_type, 1);

    // run DPLL on the updated truth_table

    sat = DPLL(removeNeg(removeSat(formula, literal_type), literal_type), truth_vals);

    if (sat[0] == 1)
        return sat;

    truth_vals[literal_type] = 0;

    // removePos(formula, literal_type);

    // setSat(formula, literal_type, 0);

    return DPLL(removePos(removeSat(formula, -literal_type), literal_type), truth_vals);
}

void printSudoku(vector<int> assignments)
{
    vector<int> sudoku;
    int index = 0;
    int grid_sz = 4;
    for (int i = 0; i < assignments.size(); i++)
    {
        if (assignments[i] == 1 && i != 0)
        {
            sudoku.push_back((i % grid_sz) + 1);
        }
    }
    for (int i = 0; i < sudoku.size(); i++)
    {

        if (i % grid_sz == 0 && i != 0)
            cout << endl;
        cout << sudoku[i] << " ";
    }
}
int main()
{
    int num_files = 2;
    for (int file_no = 1; file_no < num_files; file_no++)
    {
        string file = "sat_testcase/uf20-0" + to_string(file_no) + ".cnf";
        // cout << file_no << endl;

        file = "sudoku.cnf";
        file = "naive.txt";

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

        vector<vector<int>> formula;
        // int i = 0;

        map<int, int> vble_freq;
        for (int index = 1; index <= nVar; index++)
        {
            vble_freq[index] = 0;
        }

        while (getline(inputFile, line) && line[0] != '%')
        {
            int n = numLiterals(line);
            vector<int> clause;
            putLiterals(line, clause, vble_freq);
            formula.push_back(clause);
            // i++;
        }
        vector<pair<int, int>> pairs;

        for (auto &it : vble_freq)
        {
            pairs.push_back(it);
        }
        sort(pairs.begin(), pairs.end(), [](auto &a, auto &b)

             { return a.second > b.second; });

        inputFile.close();

        for_each(pairs.begin(), pairs.end(), [](const auto &pair)
                 { vble_order.push_back(pair.first); });

        std::vector<int> ttable(nVar + 1, -1);

        vector<int> assignment = DPLL(formula, ttable);
        if (assignment[0] == 1)
        {
            cout << "SAT\n";
            for (int i = 1; i < assignment.size(); i++)
            {
                cout << i << " : " << assignment[i] << endl;
            }
        }
        else
            cout << "UNSAT\n";
        // cout << endl;
        // printSudoku(assignment);
    }
}