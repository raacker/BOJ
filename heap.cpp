#include <iostream>
#include <random>
#include <vector>

using namespace std;

void generateRandomVector(std::vector<int>& arr, int size)
{
    srand(time(NULL));
    arr.resize(size);
    for (int& value : arr)
    {
        value = rand() % 1000;
    }
}

int getLeftChild(int parent)
{
    return parent * 2;
}

int getRightChild(int parent)
{
    return parent * 2 + 1;
}

int getParent(int child)
{
    return child / 2;
}

bool comp(const int& a, const int& b)
{
    return a > b;
}

std::vector<int> heapify(const std::vector<int>& inputs)
{
    // start index from 1 for easier calculation
    std::vector<int> heap(1);
    heap.reserve(inputs.size() + 1);

    for (const int& input : inputs)
    {
        heap.emplace_back();

        int newIndex = heap.size() - 1;
        int parentIndex = getParent(newIndex);
        while (parentIndex >= 1 && comp(heap[parentIndex], input))
        {
            heap[newIndex] = heap[parentIndex];
            newIndex = parentIndex;
            parentIndex = getParent(newIndex);
        }
        heap[newIndex] = input;
    }
    return heap;
}

bool empty(const std::vector<int>& heap)
{
    return heap.size() == 1;
}

int top(const std::vector<int>& heap)
{
    if (empty(heap)) return -1;

    return heap[1];
}

void pop(std::vector<int>& heap)
{
    if (empty(heap)) return;

    int rootIndex = 1;
    int newValue = heap.back();
    heap.pop_back();

    int maxIndex = heap.size() - 1;
    while (rootIndex <= maxIndex)
    {
        int children = getLeftChild(rootIndex);
        if (children > maxIndex)
            break;
        
        if (children + 1 <= maxIndex && comp(heap[children], heap[children + 1]))
            children++;
        
        if (comp(heap[children], newValue))
            break;

        heap[rootIndex] = heap[children];
        rootIndex = children;
    }
    heap[rootIndex] = newValue;
}

int main()
{
    std::vector<int> data;
    generateRandomVector(data, 15000);

    std::vector<int> heap = heapify(data);

    std::sort(data.begin(), data.end(), std::greater<int>());
    std::vector<int> res;
    while (empty(heap) == false)
    {
        res.push_back(top(heap));
        pop(heap);
    }

    for (int i = 0; i < res.size(); i++)
    {
        if (res[i] != data[i])
            cout << "Wrong!" << "\n";
    }

    cout << "Correct :) " << "\n";
}