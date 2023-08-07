#include <bits/stdc++.h>
#define n_ 100000 + 5
using namespace std;

vector<int> gph[n_];
int chk[n_];
float res = 0;

int dfs(int cur)
{
  chk[cur] += 1;

  for (int nxt : gph[cur])
  {
    if (chk[nxt] == 0)
      chk[cur] += dfs(nxt);
  }

  return chk[cur];
}

int main(void)
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  freopen("input.txt", "r", stdin);

  int n, r, q;
  cin >> n >> r >> q;

  for (int i = 1; i < n; i++)
  {
    int a, b;
    cin >> a >> b;
    gph[a].push_back(b);
    gph[b].push_back(a);
  }

  dfs(r);
  for (int i = 0; i < q; i++)
  {
    int c;
    cin >> c;

    cout << chk[c] << '\n';
  }
}