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

void qsort(int start, int end, std::vector<long>& values)
{
    if (start >= end)
        return;

    int mid = (start + end) / 2;
    int midVal = values[mid];
    swap(values[start], values[mid]);

    int left = start + 1, right = end;
    do
    {
        while (values[left] <= midVal) left++;
        while (midVal < values[right]) right--;
        
        if (left < right)
            swap(values[left], values[right]);
    } while (left < right);
    
    int newMid = right;
    swap(values[start], values[newMid]);

    qsort(start, newMid - 1, values);
    qsort(newMid + 1, end, values);
}

int main()
{
    std::vector<long> values;
    generateValues(values, 10);
    qsort(0, values.size() - 1, values);

    for (long& i : values)
    {
        cout << i << " ";
    }
}