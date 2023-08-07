#include <bits/stdc++.h>
#define n_ 10000 + 5
using namespace std;

vector<int> gph[n_];
int num[n_];
int dp[n_][2];

void dfs(int cur, int prev)
{
  for (int nxt : gph[cur])
  {
    if (nxt == prev)
      continue;
    dfs(nxt, cur);
  }

  dp[cur][1] = num[cur];
  for (int nxt : gph[cur])
  {
    if (cur == prev)
      continue;
    dp[cur][1] += dp[nxt][0];
  }

  dp[cur][0] = 0;
  for (int nxt : gph[cur])
  {
    if (cur == prev)
      continue;
    dp[cur][0] += max(dp[nxt][0], dp[nxt][1]);
  }
}

int main(void)
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  freopen("input.txt", "r", stdin);

  int n, m;
  cin >> n;

  for (int i = 1; i <= n; i++)
  {
    cin >> num[i];
  }

  for (int i = 1; i < n; i++)
  {
    int a, b;
    cin >> a >> b;
    gph[a].push_back(b);
    gph[b].push_back(a);
  }

  dfs(1, -1);

  cout << max(dp[1][1], dp[1][0]) << endl;
}