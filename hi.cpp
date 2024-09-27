#include <iostream>
#include <vector>

// assuming that indicies are the literal names
class Literal
{

public:
    int type;
    int value;
    Literal()
    {
        type = -1;
        // value = -1;
    }
    Literal(int tp)
    {
        type = tp;
        // value = -1;
    }
    void operator=(Literal l)
    {
        type = l.type;
        // value = l.value;
    }
};

class Clause
{
public:
    int num_unassigned;
    std::vector<Literal> c;
    int sat;
    Clause(std::vector<Literal> v)
    {
        for (int i = 0; i < v.size(); i++)
        {
            c.push_back(v[i]);
        }
        num_unassigned = (int)(v.size());
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
int UP(std::vector<Clause> formula, std::vector<int> &truth_vals);
bool DPLL(std::vector<Clause> formula, std::vector<int> truth_vals)
{
    int sat = UP(formula, truth_vals);
    if (sat == 0)
        return false;
    if (sat == 1)
        return true;
    int literal_type = chooseVar(truth_vals);
    truth_vals[literal_type] = 0;
    // for (auto& clause : formula){
    //     for(auto& literal : clause.c){
    //         literal.value = truth_vals[abs(literal.type)];
    //     }
    // }
    bool litTrue = DPLL(formula, truth_vals);
    if (litTrue)
        return true;
    truth_vals[literal_type] = 0;
    bool litFalse = DPLL(formula, truth_vals);
    return litFalse;
}

int UP(std::vector<Clause> formula, std::vector<int> &truth_vals)
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
                Literal to_assign;
                for (auto literal : clause.c)
                {
                    if (truth_vals[abs(literal.type)] == -1)
                    {
                        num_ua++;
                        to_assign = literal;
                    }
                }
                if (num_ua == 1)
                {
                    if (to_assign.type > 0)
                    {
                        if (truth_vals[to_assign.type] == 0)
                            return 0;
                        truth_vals[to_assign.type] = 1;
                        clause.sat = 1;
                        hasChanged = true;
                    }
                    else
                    {
                        if (truth_vals[-(to_assign.type)] == 1)
                            return 0;
                        truth_vals[-(to_assign.type)] = 0;
                        clause.sat = 1;
                        hasChanged = true;
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

int unit_prop(std::vector<Clause> formula, std::vector<int> &truth_vals)
{

    for (int iclause = 0; iclause < formula.size(); iclause++)
    {
        if (!formula[iclause].sat && formula[iclause].num_unassigned == 1)
        {
            formula[iclause].num_unassigned = 0;
            for (int i = 0; i < formula[iclause].c.size(); i++)
            {
                if (formula[iclause].c[i].value == -1)
                {
                    formula[iclause].c[i].value = 1;
                    if (formula[iclause].c[i].type > 0)
                    {
                        if (truth_vals[formula[iclause].c[i].type] == 0)
                            return -1;
                        truth_vals[formula[iclause].c[i].type] = 1;
                    }
                    else
                    {
                        if (truth_vals[formula[iclause].c[i].type] == 1)
                            return -1;
                        truth_vals[-formula[iclause].c[i].type] = 0;
                    }
                }
            }
        }
    }
    return 0;
}

int main()
{
    std::vector<Clause> formula = getFormula();
    int n;
    std::cout << "Input number of variables: ";
    std::cin >> n;
    std::vector<int> v(n + 1, -1);
    std::cout << DPLL(formula, v);
}