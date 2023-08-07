#include <bits/stdc++.h>
#define n_ 512 + 5
using namespace std;

int n;
float dp[n_][n_];
int arr[n_];
int brr[n_];

float dist(int from, int to)
{
  int dx = arr[from] - arr[to];
  int dy = brr[from] - brr[to];

  return sqrt(dx * dx + dy * dy);
}

float solve(int tom, int bob, int nxt)
{
  if (dp[tom][bob])
    return dp[tom][bob];

  float &ret = dp[tom][bob];
  if (nxt == n && tom == n - 1)
  {
    return ret = dist(bob, n - 1);
  }
  if (nxt == n && bob == n - 1)
  {
    return ret = dist(tom, n - 1);
  }

  return ret = min(solve(tom, nxt, nxt + 1) + dist(bob, nxt), solve(nxt, bob, nxt + 1) + dist(tom, nxt));
}

int main(void)
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  freopen("input.txt", "r", stdin);

  int T;

  cin >> T;

  while (T--)
  {

    cin >> n;
    for (int i = 0; i < n; i++)
    {
      int a, b;
      cin >> arr[i] >> brr[i];
    }
    for (int i = 0; i <= 512; i++)
      for (int j = 0; j <= 512; j++)
        dp[i][j] = 0;

    solve(0, 0, 1);
    cout << dp[0][0] << endl;
  }
}