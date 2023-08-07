#include <bits/stdc++.h>
#define n_ 32000 + 5
using namespace std;

vector<int> gph[n_];
bool chk[n_];

void dfs(int cur)
{
  chk[cur] = true;

  for (int nxt : gph[cur])
  {
    if (!chk[nxt])
      dfs(nxt);
  }

  cout << cur << " ";
}

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
    if (!chk[i])
      dfs(i);
  }
}