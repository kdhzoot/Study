#include <bits/stdc++.h>
#define n_ 50 + 5
using namespace std;

vector<int> gph[n_];
float val[n_];
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
    gph[a].push_back(b);
  }

  val[1] = 100;
  for (int i = 1; i <= n; i++)
  {
    int way = gph[i].size();
    if (way == 0)
    {
      res = max(res, val[i]);
    }

    float flow = val[i] / way;
    for (int nxt : gph[i])
    {
      val[nxt] += flow;
    }
  }

  cout << res << endl;
}