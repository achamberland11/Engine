#pragma once

#include <stack>
#include <new>
#include <assert.h>
#include "../Structs/MemoryPage.h"

template <int NBytes, int NObjects>
class CPageAllocator
{
private:
    FMemoryPage Pages[NObjects];
    std::stack<int> FreePages;
    int UsedPages;

public:
    CPageAllocator();
    ~CPageAllocator();

    // Enlever copy operations pour empecher du double-free
    CPageAllocator(const CPageAllocator&) = delete;
    CPageAllocator& operator=(const CPageAllocator&) = delete;

    template <typename T>
    T* NewObject();

    template <typename T>
    void FreeObject(T* InObject);

    int GetUsedPages() const;
    int GetAvailablePages() const;
};

template <int NBytes, int NObjects>
CPageAllocator<NBytes, NObjects>::CPageAllocator() : UsedPages(0)
{
    // Implementation simple
    for (int i = 0; i < NObjects; i++)
    {
        Pages[i].Memory = malloc(NBytes);
        Pages[i].bUsed = false;
        FreePages.push(i);
    }

    // Implementation safe avec alignement de memoire
    /*for (int i = 0; i < NObjects; i++)
    {
        constexpr size_t maxAlignment = 64;
        Pages[i].Memory = _aligned_malloc(NBytes, maxAlignment);

        if (Pages[i].Memory == nullptr)
            Pages[i].Memory = malloc(NBytes);

        Pages[i].bUsed = false;
        FreePages.push(i);
    }*/
}

template <int NBytes, int NObjects>
CPageAllocator<NBytes, NObjects>::~CPageAllocator()
{
#ifdef _DEBUG
    assert(UsedPages == 0 && "PageAllocator destroyed with active allocations");
#endif

    for (int i = 0; i < NObjects; i++)
    {
        if (Pages[i].Memory == nullptr) break;

        free(Pages[i].Memory);
        Pages[i].Memory = nullptr;
    }
}

template <int NBytes, int NObjects>
template <typename T>
T* CPageAllocator<NBytes, NObjects>::NewObject()
{
    if (sizeof(T) > NBytes)
    {
        assert(false && "Object size exceeds memory page size");
        return nullptr;
    }

    if (FreePages.empty())
        return nullptr;

    int pageIndex = FreePages.top();
    FreePages.pop();

    Pages[pageIndex].bUsed = true;
    UsedPages++;

/*#ifdef _DEBUG
    void* memory = Pages[pageIndex].Memory;
    if (reinterpret_cast<uintptr_t>(memory) % alignof(T) != 0)
        assert(false && "Memory page not aligned");
#endif*/

    T* nObject = new(Pages[pageIndex].Memory) T();
    return nObject;
}

template <int NBytes, int NObjects>
template <typename T>
void CPageAllocator<NBytes, NObjects>::FreeObject(T* InObject)
{
    InObject->~T();

    int pageIndex = -1;
    for (int i = 0; i < NObjects; i++)
    {
        if (Pages[i].Memory == InObject)
        {
            pageIndex = i;
            break;
        }
    }

    if (pageIndex == -1)
    {
        assert(false && "Object not found in any page");
        return;
    }

    Pages[pageIndex].bUsed = false;
    FreePages.push(pageIndex);
    UsedPages--;
}

template <int NBytes, int NObjects>
int CPageAllocator<NBytes, NObjects>::GetUsedPages() const
{
    return UsedPages;
}

template <int NBytes, int NObjects>
int CPageAllocator<NBytes, NObjects>::GetAvailablePages() const
{
    return NObjects - UsedPages;
}
