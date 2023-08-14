#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>
#include <sstream>

using namespace std;

typedef vector<vector<int>> EdgeMap;

void dfs(int startIndex, std::vector<int>& visitOrder, const EdgeMap& edgeMap)
{
    stack<int> visitStack;
    visitStack.push(startIndex);
    int visitCount = 1;

    while (visitStack.empty() == false)
    {
        int currVisit = visitStack.top();
        visitStack.pop();

        if (visitOrder[currVisit] != 0) continue;
        visitOrder[currVisit] = visitCount;
        visitCount++;

        for (const int& edgeIndex : edgeMap[currVisit])
        {
            visitStack.push(edgeIndex);
        }
    }
}

int main()
{
    int N, M, R;
    cin >> N >> M >> R;
    
    EdgeMap edgeMap(N + 1);

    for (int i = 0; i < M; i++)
    {
        int u, v;
        cin >> u >> v;
        edgeMap[u].push_back(v);
        edgeMap[v].push_back(u);
    }

    for (int i = 1; i < N + 1; i++)
    {
        std::sort(edgeMap[i].begin(), edgeMap[i].end(), std::greater<>());
    }
    
    std::vector<int> visitOrder(N + 1, 0);
    dfs(R, visitOrder, edgeMap);

    std::stringstream ss;
    for (int i = 1; i < N + 1; i++)
    {
        ss << visitOrder[i] << "\n";
    }
    
    cout << ss.str() << "\n";
}