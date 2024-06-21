#include <iostream>
#include <vector>

using namespace std;

template<typename T>
vector<T> forceBruteIntersection(vector<vector<T>> &S){
    sort(S.begin(), S.end(),
         [](const vector<T> &a, const vector<T> &b){
            return a.size() < b.size();
         }
    ); 
    uint64_t k = S.size();
    vector<T> intersection = S[0];
    vector<T>aux_intersection;
    for (uint16_t i = 1; i<k; ++i){
        aux_intersection.clear();
        set_intersection(intersection.begin(), intersection.end(),
                        S[i].begin(), S[i].end(),
                        back_inserter(aux_intersection));
        intersection = aux_intersection;
    }
    return intersection;
}