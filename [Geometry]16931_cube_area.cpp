#include <iostream>
#include <vector>

using namespace std;

int main()
{
    int N, M;
    cin >> N >> M;

    std::vector<std::vector<int>> cube(N);
    for (int i = 0; i < N; i++)
    {
        cube[i].resize(M);
        for (int j = 0; j < M; j++)
        {
            cin >> cube[i][j];
        }
    }

    int totalCount = 0;

    // Row Count
    for (int i = 0; i < N; i++)
    {
        for (int j = 1; j < M; j++)
        {
            int rowDiff = abs(cube[i][j] - cube[i][j - 1]);
            totalCount += rowDiff;
        }
        totalCount += cube[i][0];
        totalCount += cube[i][M - 1];
    }

    // Col count
    for (int j = 0; j < M; j++)
    {
        for (int i = 1; i < N; i++)
        {
            int colDiff = abs(cube[i][j] - cube[i - 1][j]);
            totalCount += colDiff;
        }
        totalCount += cube[0][j];
        totalCount += cube[N - 1][j];
    }

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            totalCount += cube[i][j] == 0 ? 0 : 2;
        }
    }

    cout << totalCount << "\n";
}