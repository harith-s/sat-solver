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

    // if 1, it is sat; 0 if unassigned; unsat if size of the clause is 0

    bool removed;
    int w1;
    int w2;

    Clause(std::set<int> c)
    {
        clause = c;
        removed = false;

        std::set<int>::iterator it;
        it = clause.begin();

        if (clause.size() >= 2)
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
    Clause()
    {
        removed = false;
    }

    void setWatched(std::vector<int> &truth_vals)
    {
        std::set<int>::iterator it;
        it = clause.begin();

        if (clause.size() >= 2)
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

void numInfo(std::string s, int &nC, int &nV)
{
    std::stringstream ss(s);
    std::string word;
    ss >> word;
    ss >> word;
    ss >> word;
    nV = stoi(word);
    ss >> word;
    nC = stoi(word);
    return;
}
int numLiterals(std::string s)
{
    std::stringstream ss(s);
    std::string word;
    int count = 0;
    while (ss >> word)
    {
        if (word != "0")
            count++;
    }
    return count;
}

void putLiterals(std::string s, std::set<int> &clause)
{
    std::stringstream ss(s);
    std::string word;
    int tp;

    // first position for unsat/sat/unassigned

    while (ss >> word)
    {
        tp = stoi(word);
        if (tp == 0)
        {
            return;
        }
        else
        {
            clause.insert(tp);
        }
    }
}

int chooseVarWatched(std::vector<int> truth_vals, std::vector<Clause> &formula)
{
    std::map<int, int> freq;

    std::set<int>::iterator max = formula[0].clause.begin();

    for (auto cl_clause : formula)
    {
        if (cl_clause.clause.size() == 2)
        {
            cl_clause.w2 = 0;
            return cl_clause.w2;
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
void num_ones(std::vector<int>& truth_vals){
    int count = 0;
    for (int i = 1; i < truth_vals.size(); i++){
        if(truth_vals[i] == -1) count++;
    }
    std::cout << "Count " << count << std::endl;
}

// int chooseVar(std::vector<int> truth_vals, std::vector<Clause> &formula)
// {
//     std::map<int, int> frequency;
//     num_ones(truth_vals);
//     for (const auto& clause : formula) {
//         if (!clause.removed) {
//             for (int literal : clause.clause) {
//                 int var = abs(literal);
//                 if (truth_vals[var] == -1) {
//                     frequency[var]++;
//                 }
//             }
//         }
//     }

//     // Find the variable with the highest frequency
//     int chosenVar = 0;
//     int maxFrequency = 0;

//     for (const auto& entry : frequency) {
//         if (entry.second > maxFrequency) {
//             maxFrequency = entry.second;
//             chosenVar = entry.first;
//         }
//     }
//     // std::cout << "Chosen variable: " << chosenVar << ", frequency: " << frequency[chosenVar] << std::endl;

//     return chosenVar;
// }

int chooseVar(std::vector<int> truth_vals, std::vector<Clause> &formula)

{
    std::vector<int> unassigned;

    for (int i = 1; i < truth_vals.size(); i++)
    {
        if (truth_vals[i] == -1)
            unassigned.push_back(i);
    }
    std::cout << "count " << unassigned.size() << std::endl;
    return unassigned[rand() % unassigned.size()];
}

void removeNegUP(std::vector<Clause> &formula, int assign_type)
{
    std::set<int>::iterator it;
    for (auto& C : formula)
    {
        it = C.clause.find(-assign_type);
        if (it != C.clause.end()) C.clause.erase(it);
    }
}

std::vector<Clause> removeNeg(std::vector<Clause> formula, int assign_type)
{
    std::set<int>::iterator it;
    for (auto& C : formula)
    {
        it = C.clause.find(-assign_type);
        if (it != C.clause.end()) C.clause.erase(it);
    }
    return formula;
}

std::vector<Clause> removePos(std::vector<Clause> formula, int assign_type)
{
    std::set<int>::iterator it;
    for (auto& C : formula)
    {   it = C.clause.find(assign_type);
        if (it != C.clause.end()) C.clause.erase(it);
    }
    return formula;
}

void removePosUP(std::vector<Clause> &formula, int assign_type)
{
    std::set<int>::iterator it;
    for (auto& C : formula)
    {
        it = C.clause.find(assign_type);
        if (it != C.clause.end()) C.clause.erase(it);
    }
}
std::vector<Clause> setSat(std::vector<Clause> formula, int assign_type)
{

    // here we send in the sign as well

    for (auto& C : formula)
    {
        if (C.clause.find(assign_type) != C.clause.end())
        {
            C.removed = true;
        }
    }
    return formula;
}
std::vector<int> unitPropogation(std::vector<Clause> &formula, std::vector<int> truth_vals)
{

    bool hasChanged = true;
    bool isFormulaSat = false;

    while (hasChanged)
    {
        isFormulaSat = true;
        hasChanged = false;

        for (auto& C : formula)
        {
            isFormulaSat = isFormulaSat && C.removed;
            if (not(C.removed))
            {
                // unsat clause

                if (C.clause.size() == 0)
                {
                    // std::cout << "Conflict\n";
                    truth_vals[0] = 0;
                    return truth_vals;
                }

                // unit clauser
                int assign_type = *(C.clause.begin());

                if (C.clause.size() == 1 && truth_vals[assign_type] != 1)
                {
                    if (assign_type > 0)
                    {
                        truth_vals[assign_type] = 1;
                        removeNegUP(formula, assign_type);
                        C.removed = true;
                    }

                    else
                    {
                        truth_vals[-assign_type] = 0;
                        removePosUP(formula, -assign_type);
                        C.removed = true;
                    }
                    hasChanged = true;
                    // break;
                }
            }
        }
    }

    if (isFormulaSat)
    {
        truth_vals[0] = 1;
        return truth_vals;
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

std::vector<int> DPLL(std::vector<Clause> formula, std::vector<int> truth_vals)
{

    std::vector<int> assignment = unitPropogation(formula, truth_vals);

    // first value is the truth value of the formula

    if (assignment[0] != -1)
    {
        return assignment;
    }
    truth_vals = assignment;

    int lit_chosen = chooseVar(truth_vals, formula);

    assert(lit_chosen != 0);
    // std::cerr << lit_chosen << " 1" << std::endl;

    // add a heuristic to choose the value based on the number of pos literals or neg literals

    truth_vals[lit_chosen] = 1;

    assignment = DPLL(setSat(removeNeg(formula, lit_chosen), lit_chosen), truth_vals);

    if (assignment[0] == 1)
        return assignment;

    truth_vals[lit_chosen] = 0;
    // std::cout << lit_chosen << " 0" << std::endl;


    return DPLL(setSat(removePos(formula, lit_chosen), -lit_chosen), truth_vals);
}
void printSudoku(std::vector<int> assignments)
{
    std::vector<int> sudoku;
    int index = 0;
    int grid_sz = 9;
    for (int i = 1; i < assignments.size(); i++)
    {
        if (assignments[i] == 1 && i != 0)
        {
            sudoku.push_back(((i - 1) % grid_sz) + 1);
        }
    }
    for (int i = 0; i < sudoku.size(); i++)
    {

        if (i % grid_sz == 0 && i != 0)
            std::cout << std::endl;
        std::cout << sudoku[i] << " ";
    }
}

int main()
{
    int num_files = 2;
    for (int file_no = 1; file_no < num_files; file_no++)
    {
        std::string file = "sat_testcase/uf20-0" + std::to_string(file_no) + ".cnf";
        // cout << file_no << endl;

        file = "sudoku.cnf";
        // file = "input.txt";

        std::ifstream inputFile(file);

        // Check if the file is successfully opened
        if (!inputFile.is_open())
        {
            std::cerr << "Error opening the file!" << std::endl;
            return 1;
        }

        std::string line;
        int nClauses = 0;
        int nVar = 0;
        getline(inputFile, line);
        while (!line.empty() && line[0] != 'p')
        {
            std::getline(inputFile, line);
        }
        numInfo(line, nClauses, nVar);

        std::vector<Clause> formula(nClauses, Clause());
        // int i = 0;

        int index = 0;
        while (getline(inputFile, line) && line[0] != '%')
        {
            int n = numLiterals(line);
            std::set<int> clause;
            putLiterals(line, clause);
            formula[index].clause = clause;
            index++;
        }

        inputFile.close();

        std::vector<int> ttable(nVar + 1, -1);

        std::vector<int> assignment = DPLL(formula, ttable);
        if (assignment[0] == 1)
        {
            std::cout << "SAT\n";
            for (int i = 1; i < assignment.size(); i++)
            {
                std::cout << i << " : " << assignment[i] << std::endl;
            }
        }
        else
            std::cout << "UNSAT\n";
        // cout << endl;
        // printSudoku(assignment);
    }
}