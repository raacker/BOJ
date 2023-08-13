/* 
 * If you can start from any vertex, every vertex should be zero at the start.
*/


#include <iostream>
#include <vector>
#include <limits>

using namespace std;

typedef pair<long, long> WeightIndex;
typedef vector<long> Scores;
typedef vector<std::vector<WeightIndex>> EdgeMap;

const long MAX_VALUE = std::numeric_limits<long>::max();

bool updateScores(Scores& scores, EdgeMap& edgeMap, bool final = false)
{
    for (int curIndex = 1; curIndex < scores.size(); curIndex++)
    {
        for (const auto& [weight, index] : edgeMap[curIndex])
        {
            if (scores[curIndex] == MAX_VALUE) continue;
            
            long newScore = weight + scores[curIndex];
            long existingScore = scores[index];
            if (newScore < existingScore)
            {
                if (final) return true;
                scores[index] = newScore;
            }
        }
    }
    return false;
}

bool calculateShortestPath(int startingIndex, Scores& scores, EdgeMap& edgeMap)
{
    scores[startingIndex] = 0;

    for (int i = 1; i < scores.size() - 1; i++)
    {
        updateScores(scores, edgeMap);
    }
    return updateScores(scores, edgeMap, true);
}

int main()
{
    int TestCase;
    cin >> TestCase;

    for (int tc = 0; tc < TestCase; tc++)
    {
        int N, M, W;
        cin >> N >> M >> W;

        Scores scores(N + 1, 0);
        EdgeMap edgeMap(N + 1);
        for (int i = 0; i < M; i++)
        {
            long S, E, T;
            cin >> S >> E >> T;

            edgeMap[S].push_back({T, E});
            edgeMap[E].push_back({T, S});
        }
        for (int i = 0; i < W; i++)
        {
            long S, E, T;
            cin >> S >> E >> T;

            edgeMap[S].push_back({-T, E});
        }

        bool res = calculateShortestPath(1, scores, edgeMap);
        if (res)
            cout << "YES" << "\n";
        else
            cout << "NO" << "\n";
    }
}