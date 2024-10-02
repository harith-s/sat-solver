#include <bits/stdc++.h>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
int main(){
   int n = 1;
   int& m = n;
   n = 2;
   cout << m << endl;
   int k = 10;
   m = k;
   k = 100;
   cout << m << endl;
   cout << n << endl;
   vector<int> vec = {1,2,3,8,4,5,6,7,8,8};
   vec.erase(std::remove(vec.begin(), vec.end(), 8), vec.end());
   for (int i = 0; i < vec.size(); i++){
    cout << vec[i] << endl;
   }

}