#include <iostream>
#include <vector>
#include <ctime>
#include <random>

using namespace std;

void generateValues(std::vector<long>& arr, int N)
{
    srand(time(NULL));
    arr.resize(N);
    for (int i = 0; i < N; i++)
    {
        arr[i] = rand() % 100000;
    }
}

class Heap
{
public:
    Heap()
    {
        heap.resize(1);
        heap.shrink_to_fit();
    }
    
    void push(int v)
    {
        heap.push_back(v);
        int index = heap.size() - 1;
        while (1 < index)
        {
            int parentIndex = parent(index);
            if (heap[parentIndex] > heap[index])
            {
                swap(heap[parentIndex], heap[index]);
                index = parentIndex;
            }
            else
            {
                break;
            }
        }
    }

    int top()
    {
        return heap[1];
    }

    void pop()
    {
        heap[1] = heap.back();
        heap.pop_back();
        
        int index = 1;
        while (index < heap.size())
        {
            int existingIndex = index;
            
            int leftIndex = leftChild(existingIndex);
            if (leftIndex < heap.size())
            {
                if (heap[existingIndex] > heap[leftIndex])
                {
                    swap(heap[existingIndex], heap[leftIndex]);
                    index = leftIndex;
                }
            }

            int rightIndex = rightChild(existingIndex);
            if (rightIndex < heap.size())
            {
                if (heap[existingIndex] > heap[rightIndex])
                {
                    swap(heap[existingIndex], heap[rightIndex]);
                    index = rightIndex;
                }
            }

            if (existingIndex == index)
                break;
        }
    }

    bool empty()
    {
        return heap.size() == 1;
    }

private:
    int parent(int idx)
    {
        return idx / 2;
    }

    int leftChild(int idx)
    {
        return idx * 2;
    }

    int rightChild(int idx)
    {
        return idx * 2 + 1;
    }

    int reorderChild(int parentIndex, int childIndex)
    {
        int result = parentIndex;
        if (childIndex < heap.size())
        {
            if (heap[parentIndex] < heap[childIndex])
            {
                swap(heap[parentIndex], heap[childIndex]);
                result = childIndex;
            }
        }
        return result;
    }

    std::vector<int> heap;
};



int main()
{
    int size = 10;
    Heap heap;
    heap.push(10);
    heap.push(20);
    heap.push(30);
    heap.push(40);
    heap.push(50);
    heap.push(60);
    heap.push(10);
    
    while (heap.empty() == false)
    {
        cout << heap.top() << endl;
        heap.pop();
    }
}