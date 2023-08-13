/* 
 * priority_queue is defined as 

   std::priority_queue<T, std::vector<T>, std::less<T>>

   as default which is descending order (largest at the top)

   Is this correct expectation of your algorithm?
*/

#include <iostream>
#include <queue>
#include <vector>
#include <limits>
#include <sstream>

using namespace std;

typedef std::pair<int, int> WeightIndex;
typedef std::vector<std::vector<WeightIndex>> EdgeMap;
typedef std::vector<int> Scores;
typedef std::vector<bool> VisitMap;

void calculateShortestPath(int startingPoint, Scores& scores, VisitMap& visited, EdgeMap& edges)
{
    std::priority_queue<WeightIndex, vector<WeightIndex>, greater<WeightIndex>> pq;
    
    scores[startingPoint] = 0;
    
    pq.push({0, startingPoint});

    while (pq.empty() == false)
    {
        int curDist = pq.top().first;
        int curIndex = pq.top().second;
        pq.pop();

        if (visited[curIndex])
            continue;
        visited[curIndex] = true;

        for (const auto& [weight, index] : edges[curIndex])
        {
            int newDist = weight + curDist;
            int existingDist = scores[index];

            if (newDist < existingDist)
            {
                scores[index] = newDist;
                pq.push({newDist, index});
            }
        }
    }
}

int main()
{
    int V, E;
    cin >> V >> E;

    int startingPoint;
    cin >> startingPoint;

    Scores scores(V + 1, std::numeric_limits<int>::max());
    VisitMap visited(V + 1, false);

    EdgeMap edges(V + 1);
    for (int i = 0; i < E; i++)
    {
        int from, to, weight;
        cin >> from >> to >> weight;

        edges[from].push_back({weight, to});
    }

    calculateShortestPath(startingPoint, scores, visited, edges);
    
    std::stringstream ss;
    for (int i = 1; i < scores.size(); i++)
    {
        if (scores[i] == std::numeric_limits<int>::max())
            ss << "INF\n";
        else
            ss << scores[i] << "\n";
    }

    cout << ss.str() << "\n";
}