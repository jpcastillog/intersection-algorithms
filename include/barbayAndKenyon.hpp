#include <iostream>
#include <searchAlgorithms.hpp>

using namespace std;
template <typename T>
void barbayKenyon(vector<vector<T>> &sets, uint16_t k, vector<T> &intersection){
    vector<uint64_t> positions(k, 0);
    // eliminator element in [0,0], first element of first set
    uint64_t e = sets[0][0];
    // Set index
    uint64_t i = 1;
    // ocurrences of e
    uint64_t occr = 1;
    // Init actual elements and size of initial set
    uint64_t size = sets[i].size();

    while ( e != -1 ){
        // position of e in ith-set
        uint64_t pos = exponentialSearch<T>(sets[i], e, positions[i]);
        if (sets[i][pos] == e){
            occr ++;
            // sets[i]->pos = pos;
            positions[i] = pos;
            if(occr == k){
                intersection.push_back(e);
            }
        } 
        if(occr == k || sets[i][pos] != e){
            // Position remain and size of next set
            uint64_t next_set_pos = positions[i];
            uint64_t next_set_size = sets[i].size();

            // No elements remain in the smallest set
            if (next_set_pos == next_set_size-1){
            // if (pos + 1 > next_set_size - 1){
                e = -1;
                return;
            }

            // e it's part of intersection      
            if (occr == k){
                e = sets[i][pos+1];
                positions[i] = pos + 1;
            }
            // e is not found in actual set
            else{
                // pos it's a succesor index of e 
                e = sets[i][pos];
                positions[i] = pos;
                
            }
            // restart occurrences
            occr = 1;
        }
        // Cyclical index of sets
        i = (i+1)%k;
        size = sets[i].size();
    }
}