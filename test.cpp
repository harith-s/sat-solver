
// C++ code to demonstrate the working of
// iterator, begin() and end()
#include <iostream>
#include <iterator> // for iterators
#include <vector>   // for vectors
#include <string>

using namespace std;
int main()
{
   for (int i = 1; i < 100; i++)
    {
        string file = "uf20-0" + to_string(i) + ".cnf";
        cout << file << endl;
    }
}


// int UP(std::vector<Clause> formula, std::vector<int> truth_vals)
// {
//     bool hasChanged = true;
//     while (hasChanged)
//     {
//         hasChanged = false;
//         for (auto &clause : formula)
//         {
//             if (clause.sat == 0)
//                 return 0;
//             else if (clause.sat == -1)
//             {
//                 int num_ua = 0;
//                 int assign_type = 0;
//                 for (auto literal : clause.c)
//                 {
//                     if (truth_vals[abs(literal.type)] == -1)
//                     {
//                         num_ua++;
//                         assign_type = literal.type;
//                     }
//                 }
//                 if (num_ua == 0)
//                     return 0;
//                 if (num_ua == 1)
//                 {
//                     int sz = clause.c.size();
//                     int index;
//                     for (index = 0; index < sz; index++)
//                     {
//                         if (clause.c[index].type == assign_type)
//                             break;
//                     }
//                     Literal &to_assign = clause.c[index];
//                     if (to_assign.type > 0)
//                     {
//                         if (truth_vals[to_assign.type] == 0)
//                             return 0;
//                         truth_vals[to_assign.type] = 1;
//                         to_assign.value = 1;
//                         clause.sat = 1;
//                         hasChanged = true;
//                         break;
//                     }
//                     else
//                     {
//                         if (truth_vals[-(to_assign.type)] == 1)
//                             return 0;
//                         truth_vals[-(to_assign.type)] = 0;
//                         to_assign.value = 1;
//                         clause.sat = 1;
//                         hasChanged = true;
//                         break;
//                     }
//                 }
//             }
//         }
//     }
//     for (int i = 1; i < truth_vals.size(); i++)
//     {
//         if (truth_vals[i] == -1)
//             return -1;
//     }
//     return 1;
// }

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



// if (literal.type > 0 && truth_vals[literal.type] == 1 || (literal.type < 0 && truth_vals[literal_type] == 0)){
//                 clause.sat = 1;
//                 break;
//             }
//             if (literal.type > 0) literal.value = truth_vals[literal.type] == -1 ? -1 : 1;
//             else literal.value = truth_vals[-literal.type] == -1 ? -1 : 1;

// bool DPLL(std::vector<Clause> formula, std::vector<int> truth_vals)
// {
//     int sat = UnitProp(formula, truth_vals);
//     if (sat == 0)
//         return false;
//     if (sat == 1)
//         return true;
//     int literal_type = chooseVar(truth_vals);
//     truth_vals[literal_type] = 0;

//     for (auto &clause : formula)
//     {
//         clause.sat = -1;
//         bool unsat = true;
//         for (auto &literal : clause.c)
//         {
//             // (literal.type > 0 && truth_vals[literal.type] == 1 || (literal.type < 0 && truth_vals[literal_type] == 0))
//             int val = truth_vals[abs(literal.type)];
//             if (val == -1)
//                 literal.value = -1;
//             else
//                 literal.value = literal.type > 0 ? val : (val == 1 ? 0 : 1);

//             if (literal.value == -1 || literal.value == 1)
//             {
//                 unsat = false;
//                 if (literal.value == 1)
//                     clause.sat = 1;
//             }
//         }
//         if (unsat)
//             clause.sat = 0;
//     }

//     bool isSatFalse = DPLL(formula, truth_vals);
//     if (isSatFalse)
//         return true;

//     truth_vals[literal_type] = 1;

//     for (auto &clause : formula)
//     {
//         clause.sat = -1;
//         bool unsat = true;
//         for (auto &literal : clause.c)
//         {
//             // (literal.type > 0 && truth_vals[literal.type] == 1 || (literal.type < 0 && truth_vals[literal_type] == 0))
//             int val = truth_vals[abs(literal.type)];
//             if (val == -1)
//                 literal.value = -1;
//             else
//                 literal.value = literal.type > 0 ? val : (val == 1 ? 0 : 1);

//             if (literal.value == -1 || literal.value == 1)
//             {
//                 unsat = false;
//                 if (literal.value == 1)
//                     clause.sat = 1;
//             }
//         }
//         if (unsat)
//             clause.sat = 0;
//     }
//     return DPLL(formula, truth_vals);
// }
// int UP(std::vector<Clause> formula, std::vector<int> truth_vals);
// 