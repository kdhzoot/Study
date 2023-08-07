#include <bits/stdc++.h>
#define n_ 1000 + 5
using namespace std;

vector<int> gph[n_];
int chk[n_];
float res = 0;

int main(void)
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  freopen("input.txt", "r", stdin);

  int n, m;
  cin >> n >> m;

  for (int i = 0; i < m; i++)
  {
    int a, b;
    cin >> a >> b;
    gph[b].push_back(a);
  }

  for (int i = 1; i <= n; i++)
  {
    if (gph[i].size() == 0)
    {
      chk[i] = 1;
    }

    for (int nxt : gph[i])
    {
      chk[i] = max(chk[nxt] + 1, chk[i]);
    }

    cout << chk[i] << " ";
  }
  cout << endl;
}