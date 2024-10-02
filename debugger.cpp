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
    // int w1;
    // int w2;

    Clause(std::set<int> c)
    {
        clause = c;
        removed = false;
        std::set<int>::iterator it = clause.begin();

        // if (clause.size() >= 2)
        // {
        //     w1 = *it;
        //     it++;
        //     w2 = *it;
        // }
        // else
        // {
        //     w1 = *it;
        //     w2 = 0;
        // }
    }
    Clause()
    {
        removed = false;
    }

    // void setWatched(std::vector<int> &truth_vals)
    // {
    //     std::set<int>::iterator it = clause.begin();

    //     if (clause.size() >= 2)
    //     {
    //         w1 = *it;
    //         it++;
    //         w2 = *it;
    //     }
    //     else
    //     {
    //         w1 = *it;
    //         w2 = 0;
    //     }
    // }
};

void numInfo(std::string s, int &nC, int &nV, std::ofstream &debugFile)
{
    std::stringstream ss(s);
    std::string word;
    ss >> word;
    ss >> word;
    ss >> word;
    nV = stoi(word);
    ss >> word;
    nC = stoi(word);
    // debugFile << "Number of Variables: " << nV << ", Number of Clauses: " << nC << std::endl;
}

int numLiterals(std::string s, std::ofstream &debugFile)
{
    std::stringstream ss(s);
    std::string word;
    int count = 0;
    while (ss >> word)
    {
        if (word != "0")
            count++;
    }
    // debugFile << "Number of Literals: " << count << std::endl;
    return count;
}

void putLiterals(std::string s, std::set<int> &clause, std::ofstream &debugFile)
{
    std::stringstream ss(s);
    std::string word;
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
            clause.insert(tp);
        }
    }
    // debugFile << "Literals inserted: ";
    // for (const int &lit : clause)
    // {
    //     debugFile << lit << " ";
    // }
    // debugFile << std::endl;
}

// Other functions remain the same...
int chooseVar(std::vector<int> truth_vals, std::vector<Clause> &formula)

{
    std::vector<int> unassigned;

    for (int i = 1; i < truth_vals.size(); i++)
    {
        if (truth_vals[i] == -1)
            unassigned.push_back(i);
    }
    // std::cout << "count " << unassigned.size() << std::endl;
    return unassigned[0];
}

void removeNegUP(std::vector<Clause> &formula, int assign_type)
{
    std::set<int>::iterator it;
    for (auto &C : formula)
    {
        it = C.clause.find(-assign_type);
        if (it != C.clause.end())
            C.clause.erase(it);
    }
}

std::vector<Clause> removeNeg(std::vector<Clause> formula, int assign_type)
{
    std::set<int>::iterator it;
    for (auto &C : formula)
    {
        it = C.clause.find(-assign_type);
        if (it != C.clause.end())
            C.clause.erase(it);
    }
    return formula;
}

std::vector<Clause> removePos(std::vector<Clause> formula, int assign_type)
{
    std::set<int>::iterator it;
    for (auto &C : formula)
    {
        it = C.clause.find(assign_type);
        if (it != C.clause.end())
            C.clause.erase(it);
    }
    return formula;
}

void removePosUP(std::vector<Clause> &formula, int assign_type)
{
    std::set<int>::iterator it;
    for (auto &C : formula)
    {
        it = C.clause.find(assign_type);
        if (it != C.clause.end())
            C.clause.erase(it);
    }
}
std::vector<Clause> setSat(std::vector<Clause> formula, int assign_type)
{

    // here we send in the sign as well

    for (auto &C : formula)
    {
        if (C.clause.find(assign_type) != C.clause.end())
        {
            C.removed = true;
        }
    }
    return formula;
}

void setSatUP(std::vector<Clause> &formula, int assign_type)
{

    // here we send in the sign as well

    for (auto &C : formula)
    {
        if (C.clause.find(assign_type) != C.clause.end())
        {
            C.removed = true;
        }
    }
    return;
}

std::vector<int> unitPropogation(std::vector<Clause> &formula, std::vector<int> truth_vals, std::ofstream &debugFile)
{
    bool hasChanged = true;
    bool isFormulaSat = false;
    bool nothing = true;

    while (hasChanged)
    {
        isFormulaSat = true;
        hasChanged = false;
        for (auto &C : formula)
        {
            isFormulaSat = isFormulaSat && C.removed;
            if (!C.removed)
            {
                if (C.clause.size() == 0)
                {
                    // debugFile << "Conflict found in unit propagation." << std::endl;
                    truth_vals[0] = 0;
                    return truth_vals;
                }

                int assign_type = *(C.clause.begin());

                if (C.clause.size() == 1 && truth_vals[abs(assign_type)] == -1)
                {
                    // debugFile << "Unit clause found: " << assign_type << std::endl;
                    if (assign_type > 0)
                    {
                        truth_vals[assign_type] = 1;
                        removeNegUP(formula, assign_type);
                        C.removed = true;
                        setSatUP(formula, assign_type);
                    }
                    else
                    {
                        truth_vals[-assign_type] = 0;
                        removePosUP(formula, -assign_type);
                        C.removed = true;
                        setSatUP(formula, assign_type);
                    }
                    hasChanged = true;
                    nothing = false;
                    break;
                }
            }
        }
    }

    if (nothing)
    {
        // debugFile << "Nothing happened" << std::endl;
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

std::vector<int> DPLL(std::vector<Clause> formula, std::vector<int> truth_vals, std::ofstream &debugFile)
{
    int count = 0;
    for (int i = 1; i < truth_vals.size(); i++)
    {
        if (truth_vals[i] == -1)
            count++;
    }
    // debugFile << "Before UP: " << count << std::endl;

    std::vector<int> assignment = unitPropogation(formula, truth_vals, debugFile);

    if (assignment[0] != -1)
    {
        return assignment;
    }
    truth_vals = assignment;

    count = 0;
    for (int i = 1; i < truth_vals.size(); i++)
    {
        if (truth_vals[i] == -1)
            count++;
    }

    // debugFile << "After UP: " << count << std::endl;

    int lit_chosen = chooseVar(truth_vals, formula);

    assert(lit_chosen != 0);
    // debugFile << "Chosen literal: " << lit_chosen << std::endl;
    // std::cout << "Chosen literal: " << lit_chosen << std::endl;

    truth_vals[lit_chosen] = 1;

    assignment = DPLL(setSat(removeNeg(formula, lit_chosen), lit_chosen), truth_vals, debugFile);

    if (assignment[0] == 1)
        return assignment;
    // debugFile << "Trying the other assignment...: " << -lit_chosen << std::endl;

    truth_vals[lit_chosen] = 0;
    return DPLL(setSat(removePos(formula, lit_chosen), -lit_chosen), truth_vals, debugFile);
}

int main()
{
    std::ofstream debugFile("debug_output.txt"); // Open debug file
    if (!debugFile.is_open())
    {
        std::cerr << "Error opening the debug file!" << std::endl;
        return 1;
    }

    int num_files = 2;
    for (int file_no = 1; file_no < num_files; file_no++)
    {
        std::string file = "sat_testcase/uf20-0" + std::to_string(file_no) + ".cnf";
        file = "sudoku.cnf"; // Use your desired input file
        // file = "naive.txt"; // Use your desired input file


        std::ifstream inputFile(file);
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
        numInfo(line, nClauses, nVar, debugFile);

        std::vector<Clause> formula(nClauses, Clause());
        int index = 0;
        while (getline(inputFile, line) && line[0] != '%')
        {
            int n = numLiterals(line, debugFile);
            std::set<int> clause;
            putLiterals(line, clause, debugFile);
            formula[index].clause = clause;
            index++;
        }

        inputFile.close();

        std::vector<int> ttable(nVar + 1, -1);
        std::vector<int> assignment = DPLL(formula, ttable, debugFile);
        if (assignment[0] == 1)
        {
            debugFile << "SAT\n";
            for (int i = 1; i < assignment.size(); i++)
            {
                debugFile << i << " : " << assignment[i] << std::endl;
            }
        }
        else
            debugFile << "UNSAT\n";

        // printSudoku(assignment);
    }

    debugFile.close(); // Close debug file
    return 0;
}
