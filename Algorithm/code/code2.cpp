#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <bits/stdc++.h>

#define CMD_INIT 1
#define CMD_HIRE 2
#define CMD_FIRE 3
#define CMD_UPDATE_SOLDIER 4
#define CMD_UPDATE_TEAM 5
#define CMD_BEST_SOLDIER 6
#define n_ 100000 + 5

extern void init();
extern void hire(int mID, int mTeam, int mScore);    // id 기반
extern void fire(int mID);                           // id 기반
extern void updateSoldier(int mID, int mScore);      // id 기반
extern void updateTeam(int mTeam, int mChangeScore); // 팀 기반...
extern int bestSoldier(int mTeam);                   // 팀 기반...

/////////////////////////////////////////////////////////////////////////
struct Node
{
  int id, team, score;
  Node *left, *right;
};

Node *root;
int node_count = 0;
Node node_pool[n_];

Node *new_node(int mID, int mTeam, int mScore)
{
  node_pool[node_count].id = mID;
  node_pool[node_count].team = mTeam;
  node_pool[node_count].score = mScore;
  node_pool[node_count].left = nullptr;
  node_pool[node_count].right = nullptr;

  return &node_pool[node_count++];
}

extern void init()
{
  root = nullptr;
  node_count = 0;
}

Node *insert(Node *cur, Node *nxt)
{
  if (cur == nullptr)
  {
    return nxt;
  }

  if (nxt->id < cur->id)
  {
    cur->left = insert(cur->left, nxt);
  }
  else
  {
    cur->right = insert(cur->right, nxt);
  }

  return cur;
}

void hire(int mID, int mTeam, int mScore)
{
  Node *nxt = new_node(mID, mTeam, mScore);
  root = insert(root, nxt);
}

Node *find_min_node(Node *cur)
{
  while (cur->left != nullptr)
  {
    cur = cur->left;
  }

  return cur;
}

Node *remove(Node *cur, int mID)
{
  if (mID < cur->id)
  {
    cur->left = remove(cur->left, mID);
  }
  else if (mID > cur->id)
  {
    cur->right = remove(cur->right, mID);
  }
  else
  {
    if (cur->left == nullptr)
    {
      return cur->right;
    }
    else if (cur->right == nullptr)
    {
      return cur->left;
    }

    Node *tmp = find_min_node(cur->right);
    cur->id = tmp->id;
    cur->score = tmp->score;
    cur->team = tmp->team;
    cur->right = remove(cur->right, tmp->id);
  }
  return cur;
}

void fire(int mID)
{
  root = remove(root, mID);
}

void updateSoldier(int mID, int mScore)
{
  Node *cur = root;

  while (cur != nullptr)
  {
    if (cur->id == mID)
    {
      cur->score = mScore;
    }

    cur = mID < cur->id ? cur->left : cur->right;
  }
}

int change_score(int x, int dx)
{
  int cur = x + dx;
  if (cur >= 5)
    return 5;
  else if (cur <= 1)
    return 1;
  else
    return cur;
}

void update(Node *cur, int mTeam, int mChangeScore)
{
  if (cur == nullptr)
    return;

  if (cur->team == mTeam)
  {
    cur->score = change_score(cur->score, mChangeScore);
    // printf("score changed : %d %d\n", cur->id, cur->score);
  }

  update(cur->left, mTeam, mChangeScore);
  update(cur->right, mTeam, mChangeScore);
}

void updateTeam(int mTeam, int mChangeScore)
{
  update(root, mTeam, mChangeScore);
}

Node *best(Node *a, Node *b)
{
  if (a == nullptr)
    return b;
  if (b == nullptr)
    return a;

  if (a->score == b->score)
  {
    return a->id > b->id ? a : b;
  }
  return a->score > b->score ? a : b;
}

Node *search(Node *cur, int mTeam)
{
  if (cur == nullptr)
    return nullptr;

  Node *ret = nullptr;
  Node *tmp = nullptr;

  if (cur->team == mTeam)
  {
    ret = cur;
  }
  tmp = search(cur->left, mTeam);
  ret = best(ret, tmp);
  tmp = search(cur->right, mTeam);
  ret = best(ret, tmp);

  return ret;
}

int bestSoldier(int mTeam)
{
  Node *ret = search(root, mTeam);
  // printf("bestSoldier : %d %d\n", mTeam, ret->id);
  return ret->id;
}

/////////////////////////////////////////////////////////////////////////

static bool
run()
{
  int numQuery;

  int mID, mTeam, mScore, mChangeScore;

  int userAns, ans;

  bool isCorrect = false;

  scanf("%d", &numQuery);

  for (int i = 0; i < numQuery; ++i)
  {
    int cmd;
    scanf("%d", &cmd);
    switch (cmd)
    {
    case CMD_INIT:
      init();
      isCorrect = true;
      break;
    case CMD_HIRE:
      scanf("%d %d %d", &mID, &mTeam, &mScore);
      hire(mID, mTeam, mScore);
      break;
    case CMD_FIRE:
      scanf("%d", &mID);
      fire(mID);
      break;
    case CMD_UPDATE_SOLDIER:
      scanf("%d %d", &mID, &mScore);
      updateSoldier(mID, mScore);
      break;
    case CMD_UPDATE_TEAM:
      scanf("%d %d", &mTeam, &mChangeScore);
      updateTeam(mTeam, mChangeScore);
      break;
    case CMD_BEST_SOLDIER:
      scanf("%d", &mTeam);
      userAns = bestSoldier(mTeam);
      scanf("%d", &ans);
      if (userAns != ans)
      {
        isCorrect = false;
      }
      break;
    default:
      isCorrect = false;
      break;
    }
  }

  return isCorrect;
}

int main()
{
  setbuf(stdout, NULL);
  freopen("input.txt", "r", stdin);

  int T, MARK;
  scanf("%d %d", &T, &MARK);

  for (int tc = 1; tc <= T; tc++)
  {
    int score = run() ? MARK : 0;
    printf("#%d %d\n", tc, score);
  }

  return 0;
}