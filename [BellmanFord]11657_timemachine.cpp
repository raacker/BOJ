/* 
 *
   1. Is your currentScore not the maximum value? They might not be visited yet.
   2. Total time could be really large
*/

#include <iostream>
#include <queue>
#include <vector>
#include <limits>
#include <sstream>

using namespace std;

typedef std::pair<long, long> WeightIndex;
typedef std::vector<std::vector<WeightIndex>> EdgeMap;
typedef std::vector<long> Scores;

const long MAX_VALUE = std::numeric_limits<long>::max();

bool updateScores(Scores& scores, EdgeMap& edgeMap, bool final)
{
    for (int curIndex = 1; curIndex < scores.size(); curIndex++)
    {
        for (const auto& [weight, index] : edgeMap[curIndex])
        {
            if (scores[curIndex] == MAX_VALUE)
                continue;
                
            long newDist = weight + scores[curIndex];
            long existingDist = scores[index];

            if (newDist < existingDist)
            {
                if (final) return true;
                scores[index] = newDist;
            }
        }
    }
    return false;
}

bool calculateShortestPath(int startingPoint, Scores& scores, EdgeMap& edgeMap)
{
    scores[startingPoint] = 0;

    for (int curIndex = 1; curIndex < scores.size() - 1; curIndex++)
    {
        updateScores(scores, edgeMap, false);
    }

    // Run one more time to detect infinite negative loop
    return updateScores(scores, edgeMap, true);
}

int main()
{
    int cities, edges;
    cin >> cities >> edges;

    Scores scores(cities + 1, MAX_VALUE);

    EdgeMap edgeMap(cities + 1);
    for (int i = 0; i < edges; i++)
    {
        long from, to, weight;
        cin >> from >> to >> weight;

        edgeMap[from].push_back({weight, to});
    }

    bool res = calculateShortestPath(1, scores, edgeMap);
    if (res)
    {
        cout << "-1\n";
        return 0;
    }

    std::stringstream ss;
    for (int i = 2; i < scores.size(); i++)
    {
        if (scores[i] == MAX_VALUE)
            ss << "-1\n";
        else
            ss << scores[i] << "\n";
    }

    cout << ss.str() << "\n";
}