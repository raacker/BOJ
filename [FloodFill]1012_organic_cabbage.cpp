#include <iostream>
#include <cstring>

using namespace std;

int bat[50][50];
bool visited[50][50];

int dx[] = { -1, 1, 0, 0};
int dy[] = { 0, 0, -1, 1};

int dfsSearch(int row, int col, const int maxRow, const int maxCol)
{
    if (row < 0 || row >= maxRow || col < 0 || col >= maxCol)
        return 0;
    
    if (visited[row][col])
        return 0;
    
    visited[row][col] = true;

    if (bat[row][col] == 0)
        return 0;

    int res = 1;
    for (int i = 0; i < 4; i++)
    {
        res += dfsSearch(row + dx[i], col + dy[i], maxRow, maxCol);
    }
    return res;
}

int main()
{
    int testCase;
    cin >> testCase;

    for (int t = 0; t < testCase; t++)
    {
        memset(bat, 0, sizeof(int) * 2500);
        memset(visited, false, sizeof(bool) * 2500);

        int col, row, K;
        cin >> col >> row >> K;

        for (int k = 0; k < K; k++)
        {
            int r, c;
            cin >> c >> r;

            bat[r][c] = 1;
        }

        int count = 0;
        for (int r = 0; r < row; r++)
        {
            for (int c = 0; c < col; c++)
            {
                int result = dfsSearch(r, c, row, col);
                if (result != 0)
                {
                    count++;
                }
            }
        }
        cout << count << "\n";
    }
}