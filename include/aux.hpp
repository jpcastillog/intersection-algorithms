#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <map>

using namespace std;

template <typename T>
vector<vector<T>> loadQueryLog(string queryPath){
    vector<vector<T>> queries;
    ifstream in(queryPath);
    if (!in.is_open()){
        cerr << "Can't open file: " << queryPath << "\n";
        return queries;
    }
    string line;
    while(getline(in, line)) {
        vector<T> query;
        istringstream iss(line);
        for (string s; iss >> s;) {
            T id = (T)stoi(s);
            // cout << id << " ";
            query.push_back(id);
        }
        // cout << endl;
        queries.push_back(query);
    }
    in.close();
    return queries;
}

template<typename T> 
map<T, vector<T>> 
loadSequences(string sequencesPath, 
            vector<vector<T>> &queries){

    vector<T> setIndexes;
    for(auto q: queries)
        setIndexes.insert(setIndexes.end(), q.begin(), q.end());
    sort(setIndexes.begin(), setIndexes.end());
    setIndexes.erase(unique(setIndexes.begin(), setIndexes.end()), setIndexes.end());
    std::ifstream input_stream;
    input_stream.open(sequencesPath, std::ios::binary | std::ios::in);
    map<T, vector<T>> sequences;
    if (!input_stream.is_open()) {
        cout << "Can't open file:  " << sequencesPath << endl;
        return sequences;
    }

    uint32_t nIl = 0;
    uint32_t _1, u, n;
    input_stream.read(reinterpret_cast<char*>(&_1), sizeof(_1));
    input_stream.read(reinterpret_cast<char*>(&u), sizeof(u));
    // std::cout << "Num. of sets: " << n << std::endl;
    std::cout << "_1: " << _1 << std::endl;
    std::cout << "Universe: "<< u << std::endl;
    uint32_t np = 0;
    uint32_t i = 0;
    while (true) {
        input_stream.read(reinterpret_cast<char*>(&n), sizeof(n));
        if (input_stream.eof()){
            break;
        }
        else if (i == setIndexes[np]){
            vector<T> S(n);
            for (uint32_t j=0; j < n; ++j) {
                T x;
                input_stream.read(reinterpret_cast<char*>(&x), sizeof(x));
                S[j] = (T)x;
            }
            sequences.insert({i, S});
            np++;
            if (np == setIndexes.size()) break;
        }
        else {
            input_stream.seekg(4*n, ios::cur);
        }
        
        ++i;
    }
    return sequences;
}