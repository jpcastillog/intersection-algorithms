#include <iostream>
#include <vector>
#include <fstream>
#include <barbayAndKenyon.hpp>
#include <aux.hpp>

using namespace std;

template<typename T>
void performIntersections(string sequencesPath, string queryPath) {

    vector<vector<uint32_t>> queries = loadQueryLog<uint32_t>(queryPath);

    cout << "Computing queries...\n";
    uint64_t nq = 0;
    long unsigned int total_time = 0;
    for (auto q: queries) {
        vector<vector<T>> Qseq = loadOneSequence<T>(sequencesPath, q);
        vector<T> intersection;
        if (Qseq.size() <= 16){
            auto start = std::chrono::high_resolution_clock::now();
            barbayKenyon<T>(Qseq, Qseq.size(), intersection);
            auto end = std::chrono::high_resolution_clock::now();
            auto elapsed = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
            auto time = elapsed.count();
            total_time += time;
            ++nq;
            if (nq % 1== 0) {
                std::cout << nq << " correct queries processed" << std::endl;
            }
        }
    }

    std::cout << "Number of queries: " << nq << std::endl;
    std::cout <<"Avg time execution: " << (double)(total_time*1e-3)/(nq) << "[ms]" << std::endl;
}

int main(int argc, char const *argv[]) {
    int mandatory = 3;
    bool sdsl_int_v = false;
    // (*) mandatory parameters
    if (argc < mandatory){
        std::cout   << "collection filename " // (*)
                        "query log" // (*)
                    << "\n";
        return 1;
    }
    for (int i = 2; i < argc; ++i){
        if(std::string(argv[i]) == "--int_vector")
            sdsl_int_v = true;

    } 
    std::string sequences_filename = std::string(argv[1]);
    std::string querylog_filename   = std::string(argv[2]);
    performIntersections<uint32_t>(sequences_filename, querylog_filename);
    
    return 0;
}