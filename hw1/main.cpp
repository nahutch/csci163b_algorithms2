#include <iostream>
#include <fstream>
#include "graph.h"

using namespace std;

int main(int argc, char *argv[])
{

    ifstream is("g2.txt");
    if (is.fail())
    {
        cout << endl << "Can't open file!" << endl<< endl;
        return 1;
    }
    graph G;

    cout << "Enter a graph: " << endl;
    is >> G;

    cout << "Read graph: " << endl;
    cout << G << endl;

    G.dfs("0");


    std::unordered_set<string> visited;

    for (auto e: G.V())
    {
        if (visited.find(e) == visited.end())
        {
            graph T = G.bfs(e, visited);
            cout << T << endl;
        }
    }

    return 0;
}
