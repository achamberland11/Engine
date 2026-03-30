#pragma once
#include <mutex>
#include <vector>
#include <thread>
#include <atomic>

struct PrimeWorker
{
    PrimeWorker() : lastPrimeIndex(0) {}

    std::mutex mutex;
    std::vector<int> primes;
    size_t lastPrimeIndex = 0;

    std::atomic<bool> running{ false };
    std::thread workerThread;

    void StartWorker();
    void StopWorker();
    std::vector<int> PollPrimes();
};

bool IsPrime(int n);
void WorkerFunction(PrimeWorker* worker);