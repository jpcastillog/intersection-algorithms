#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <map>
#include <chrono>
#include <barbayAndKenyon.hpp>
#include <bruteForceIntersection.hpp>
#include <aux.hpp>
using namespace std;


template<typename T>
void performIntersections(string sequencesPath, string queryPath) {
    vector<vector<T>> queries;
    map<T, vector<T>> sequences;

    queries = loadQueryLog<T>(queryPath);
    cout << "Queries loaded succefully, Total: " << queries.size() << "" << endl;
    sequences = loadSequences<T>(sequencesPath, queries);
    cout << "Sequences loaded succefully, Total: " << sequences.size() << endl;

    cout << "Computing queries...\n";
    uint64_t nq = 0;
    long unsigned int total_time = 0;
    for (auto q: queries) {
        vector<vector<T>> Qseq;
        for (auto i: q){
            Qseq.push_back(sequences[i]);
        }
        vector<T> intersection;
        vector<T> BFintersection;
        if (Qseq.size() <= 16){
            auto start = std::chrono::high_resolution_clock::now();
            barbayKenyon<T>(Qseq, Qseq.size(), intersection);
            auto end = std::chrono::high_resolution_clock::now();
            auto elapsed = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
            auto time = elapsed.count();
            total_time += time;
            BFintersection = forceBruteIntersection(Qseq);
            // Check equality of intersection (forcebrute and trie-intersection)
            if (intersection != BFintersection){
                cout << "Trie intersection size: " << intersection.size() << "\n";
                cout << "Set intersection size: " << BFintersection.size() << "\n";
                uint64_t c = 0;
                for (uint64_t i = 0; i<intersection.size(); ++i){
                    if (intersection[i] != BFintersection[i]){
                        cout << "i: " << i << " " << intersection[i] << " " << BFintersection[i] << "\n";
                        c++;
                        if (c == 10) break;
                    }
                }
                cout << "Query " << nq << " not match with force brute intersection" << endl;
                break;
            }
            ++nq;
            if (nq % 1 == 0) {
                std::cout << nq << " correct queries processed" << std::endl;
            }
        }
    }

    std::cout << "Number of queries: " << nq << std::endl;
    std::cout <<"Avg time execution: " << (double)(total_time*1e-3)/(nq) << "[ms]" << std::endl;
    std::cout << "Total time execution: " << total_time << "micro seconds\n";
}

int main(int argc, char const *argv[]) {
    int mandatory = 3;
    // (*) mandatory parameters
    if (argc < mandatory){
        std::cout   << "collection filename " // (*)
                        "query log" // (*)
                    << "\n";
        return 1;
    }
    std::string sequences_filename = std::string(argv[1]);
    std::string querylog_filename   = std::string(argv[2]);
    performIntersections<uint32_t>(sequences_filename, querylog_filename);
    
    return 0;
}