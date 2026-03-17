#pragma once

#include <stack>
#include <new>
#include <assert.h>
#include <cstdlib>
#include <cstddef>
#include <cassert>
#include "../Structs/MemoryPage.h"

template <int NBytes, int NObjects>
class CPageAllocator
{
private:
    void* MemoryPool = nullptr;
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
    MemoryPool = malloc(NBytes * NObjects);
    assert(MemoryPool != nullptr);

#if defined(_MSVC_LANG)
    static_assert(_MSVC_LANG >= 201703L, "Project is not compiling in C++17 or newer");
#endif

    std::byte* memory = reinterpret_cast<std::byte*>(MemoryPool);

    for (int i = 0; i < NObjects; i++)
    {
        Pages[i].Memory = memory + (NBytes * i);
        Pages[i].bUsed = false;
        FreePages.push(i);
    }
}

template <int NBytes, int NObjects>
CPageAllocator<NBytes, NObjects>::~CPageAllocator()
{
#ifdef _DEBUG
    assert(UsedPages == 0 && "PageAllocator destroyed with active allocations");
#endif

    free(MemoryPool);
    MemoryPool = nullptr;

    for (int i = 0; i < NObjects; i++)
    {
        Pages[i].Memory = nullptr;
        Pages[i].bUsed = false;
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
