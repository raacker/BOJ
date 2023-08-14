#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;

int danji[25][25];
bool visited[25][25];

int dx[] = { -1, 1, 0, 0};
int dy[] = { 0, 0, -1, 1};

int dfsSearch(int row, int col, const int maxSize)
{
    if (row < 0 || row >= maxSize || col < 0 || col >= maxSize)
        return 0;
    
    if (visited[row][col])
        return 0;
    
    visited[row][col] = true;

    if (danji[row][col] == 0)
        return 0;

    int res = 1;
    for (int i = 0; i < 4; i++)
    {
        res += dfsSearch(row + dx[i], col + dy[i], maxSize);
    }
    return res;
}

int main()
{
    memset(danji, 0, sizeof(int) * 25 * 25);
    memset(visited, false, sizeof(bool) * 25 * 25);

    int N;
    cin >> N;

    for (int r = 0; r < N; r++)
    {
        std::string s;
        cin >> s;
        for (int c = 0; c < N; c++)
        {
            danji[r][c] = s[c] - '0';
        }
    }

    std::vector<int> danjiCount;
    for (int r = 0; r < N; r++)
    {
        for (int c = 0; c < N; c++)
        {
            int result = dfsSearch(r, c, N);
            if (result != 0)
            {
                danjiCount.push_back(result);
            }
        }
    }
    cout << danjiCount.size() << "\n";
    std::sort(danjiCount.begin(), danjiCount.end());
    for (int& count : danjiCount)
    {
        cout << count << "\n";
    }
}