#include <iostream>
#include <vector>
#include <fstream>
#include <barbayAndKenyon.hpp>
#include <aux.hpp>
#include <chrono>

using namespace std;

template<typename T>
void performIntersections(string sequencesPath, string queryPath, uint64_t batch_size) {
    uint64_t trep = 10;
    vector<vector<uint32_t>> queries;
    // map<T, vector<T>> sequences;
    
    queries = loadQueryLog<uint32_t>(queryPath);
    
    
    // ifstream inSeq;
    // inSeq.open(sequencesPath, ios::binary | ios::in);

    cout << "Computing queries...\n";
    uint64_t nq = 0;
    long unsigned int total_time = 0;
    uint16_t i_batch = 1;
    for(uint64_t b = 0; b < queries.size(); b+=batch_size) {
        cout << "Batch i: "<< i_batch << "\n";
        vector<vector<uint32_t>> Qbatch;
        Qbatch.assign(&queries[b], &queries[min(b+batch_size, queries.size())]);
        map<uint32_t, vector<T>> sequences = loadSequences<T>(sequencesPath, Qbatch);
        cout << "Sequences loaded succefully, Total: " << sequences.size() << endl;
        for (auto q: Qbatch) {
            vector<vector<T>> Qseq;
            for (auto i: q){
                Qseq.push_back(sequences[i]);
            }
            // vector<vector<T>> Qseq = loadOneSequence<T>(inSeq, q);
            // inSeq.seekg(0, ios::beg);
            vector<T> intersection;
            if (Qseq.size() <= 16){
                uint64_t time_10 = 0;
                for(uint32_t rep = 0; rep < trep; ++rep){
                    auto start = std::chrono::high_resolution_clock::now();
                    barbayKenyon<T>(Qseq, Qseq.size(), intersection);
                    auto end = std::chrono::high_resolution_clock::now();
                    auto elapsed = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
                    auto time = elapsed.count();

                    time_10 += time;
                    total_time += time;
                    if (rep != trep-1)
                        intersection.clear();  
                }
                // total_time += time;
                ++nq;
                if (nq % 1000 == 0) {
                    std::cout << nq << " correct queries processed" << std::endl;
                }
            }
        }
        ++i_batch;
    }
    // inSeq.close();

    std::cout << "Number of queries: " << nq << std::endl;
    std::cout <<"Total time execution: " << total_time*1e-3 << "[ms]" << std::endl;
    std::cout <<"Avg time execution: " << (double)(total_time*1e-3)/(nq*trep) << "[ms]" << std::endl;
}

int main(int argc, char const *argv[]) {
    int mandatory = 3;
    bool sdsl_int_v = false;
    bool batches = false;
    uint64_t batch_size = -1;
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
        if (std::string(argv[i]) == "--batch_size"){
            batches = true;
            ++i;
            batch_size = std::stoull(argv[i]);
        }

    } 
    cout << "-> Batch size: " << batch_size << "\n";
    std::string sequences_filename = std::string(argv[1]);
    std::string querylog_filename   = std::string(argv[2]);
    performIntersections<uint32_t>(sequences_filename, querylog_filename, batch_size);
    
    return 0;
}