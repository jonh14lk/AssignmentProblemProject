#include <bits/stdc++.h>

using namespace std;

int main()
{
  srand(time(NULL));

  ofstream myfile;
  myfile.open("test_case2.in");

  int n, m;

  cout << "Number of applicants" << endl;
  cin >> n;

  cout << endl;

  cout << "Number of jobs" << endl;
  cin >> m;

  myfile << m << " " << m << endl;

  for (int i = 0; i < n; i++)
  {
    int k = (rand() % m) + 1;

    set<int> added; // usar um set pois não teremos elementos repetidos na entrada

    while (added.size() < k)
    {
      int current = (rand() % m) + 1;
      added.insert(current);
    }

    for (auto const &j : added)
    {
      myfile << j << " ";
    }

    myfile << "0" << endl; // final do input do candidato i
  }

  myfile.close();

  cout << endl;

  cout << "Finished!" << endl;

  return 0;
}