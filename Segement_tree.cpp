// C++ Program to Create RMQ Segment Tree
#include <bits/stdc++.h>
using namespace std;
  
// Returns true if it is possible to construct
// a range minimum segment tree from given array.
bool createTree(int arr[], int N)
{
    // Store the height of the final tree
    const int height = log2(N) + 1;
  
    // Container to sort and store occurrences of elements
    map<int, int> multi;
  
    // Insert elements into the container
    for (int i = 0; i < 2 * N - 1; ++i)
        ++multi[arr[i]];
  
    // Used to store new subtrees created
    set<int> Q[height];
  
    // Insert root into set
    Q[height - 1].emplace(0);
  
    // Iterate through each unique element in set
    for (map<int, int>::iterator it = multi.begin();
        it != multi.end(); ++it)
    {
        // Number of occurrences is greater than height
        // Or, no subtree exists that can accommodate it
        if (it->second > height || Q[it->second - 1].empty())
            return false;
  
        // Get the appropriate subtree
        int node = *Q[it->second - 1].begin();
  
        // Delete the subtree we grabbed
        Q[it->second - 1].erase(Q[it->second - 1].begin());
  
        int level = 1;
        for (int i = node; i < 2 * N - 1;
            i = 2 * i + 1, ++level)
        {
            // Insert new subtree created into root
            if (2 * i + 2 < 2 * N - 1)
                Q[it->second - level - 1].emplace(2 * i + 2);
  
            // Insert element into array at position
            arr[i] = it->first;
        }
    }
    return true;
}
  
// Driver program
int main()
{
    int N = 8;
    int arr[2 * N - 1] = {1, 1, 1, 1, 2, 2,
                 3, 3, 3, 4, 4, 5, 6, 7, 8};
    if (createTree(arr, N))
    {
        cout << "YES\n";
        for (int i = 0; i < 2 * N - 1; ++i)
            cout << arr[i] << " ";
    }
    else
        cout << "NO\n";
    return 0;
}