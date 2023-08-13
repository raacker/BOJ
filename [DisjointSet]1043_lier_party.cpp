/*
 *  Mergin parent in every findParent() might give you a chance of losing deep information.
 * 
 *  
    int findParent(int index, std::vector<int>& set)
    {
        if (index == set[index]) return index;
        return findParent(set[index], set);
    }

    int findParent(int index, std::vector<int>& set)
    {
        if (index == set[index]) return index;
        return (set[index] = findParent(set[index], set));
    }


example:
6 5
1 6
2 4 5
2 1 2
2 2 3
2 3 4
2 5 6

Expected Output -> 0
 */

#include <iostream>
#include <vector>
#include <numeric>

using namespace std;

int findParent(int index, std::vector<int>& set)
{
    if (index == set[index]) return index;
    return findParent(set[index], set);
}

void unionParent(int indexA, int indexB, std::vector<int>& set)
{
    int parentA = findParent(indexA, set);
    int parentB = findParent(indexB, set);

    if (parentA < parentB) set[parentB] = parentA;
    else set[parentA] = parentB;
}

int main()
{
    int N, M;
    cin >> N >> M;

    int truthCount;
    cin >> truthCount;

    std::vector<int> truths(N + 1);
    std::iota(truths.begin(), truths.end(), 0);
    
    int truthGroup = 0;
    for (int i = 0; i < truthCount; i++)
    {
        int truth;
        cin >> truth;
        unionParent(truthGroup, truth, truths);
    }

    std::vector<std::vector<int>> parties;
    for (int i = 0; i < M; i++)
    {
        int partyMemberCount;
        cin >> partyMemberCount;

        std::vector<int> partyMembers;
        for (int j = 0; j < partyMemberCount; j++)
        {
            int personID;
            cin >> personID;
            partyMembers.push_back(personID);
            if (j == 0) continue;

            unionParent(partyMembers[0], personID, truths);
        }
        parties.push_back(partyMembers);
    }
    
    int availableParty = 0;
    for (int i = 0; i < parties.size(); i++)
    {
        bool foundTruth = false;
        for (int j = 0; j < parties[i].size(); j++)
        {
            foundTruth |= (findParent(parties[i][j], truths) == truthGroup);
        }
        
        if (foundTruth == false)
            availableParty++;
    }
    
    cout << availableParty << "\n";
}