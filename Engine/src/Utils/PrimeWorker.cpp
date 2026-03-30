#include "PrimeWorker.h"

/// --------
void PrimeWorker::StartWorker()
{
    if (running) return;
    running = true;
    workerThread = std::thread(WorkerFunction, this);
}

void PrimeWorker::StopWorker()
{
    if (!running) return;
    running = false;
    if (workerThread.joinable()) workerThread.join();
}

std::vector<int> PrimeWorker::PollPrimes()
{
    if (!running) return {};
    
    std::scoped_lock lock(mutex);
    std::vector<int> newPrimes;
    for (size_t i = lastPrimeIndex; i < primes.size(); ++i)
    {
        newPrimes.push_back(primes[i]);
    }
    lastPrimeIndex = primes.size();
    return newPrimes;
}


/// --------
void WorkerFunction(PrimeWorker* worker)
{
    int currentNum = worker->lastSearchedNum;
    while (worker->running)
    {
        if (IsPrime(currentNum))
        {
            std::scoped_lock lock(worker->mutex);
            worker->primes.push_back(currentNum);
        }
        currentNum++;
        
        {
            std::scoped_lock lock(worker->mutex);
            worker->lastSearchedNum = currentNum;
        }
        
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

bool IsPrime(int n)
{
    if (n <= 1)
        return false;
    for (int i = 2; i * i <= n; i++)
    {
        if (n % i == 0)
            return false;
    }
    return true;
}
