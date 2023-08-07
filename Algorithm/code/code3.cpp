#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#define MAX_NODE 10000

enum
{
  ADD_HEAD = 1,
  ADD_TAIL,
  ADD_NUM,
  FIND,
  REMOVE,
  PRINT,
  PRINT_REVERSE,
  END = 99
};

struct Node
{
  int data;
  Node *prev;
  Node *next;
};

Node node[MAX_NODE];
int nodeCnt;
Node *head;

Node *getNode(int data)
{
  node[nodeCnt].data = data;
  node[nodeCnt].prev = nullptr;
  node[nodeCnt].next = nullptr;
  return &node[nodeCnt++];
}

extern void init()
{
  head = getNode(-1);
}
extern void addNode2Head(int data)
{
  Node *ne = getNode(data);

  if (head->next != nullptr)
  {
    head->next->prev = ne;
    ne->next = head->next;
  }
  ne->prev = head;
  head->next = ne;

  return;
}
extern void addNode2Tail(int data)
{
  Node *ne = getNode(data);

  Node *tail = head;
  while (tail->next != nullptr)
  {
    tail = tail->next;
  }

  tail->next = ne;
  ne->prev = tail;

  return;
}
extern void addNode2Num(int data, int num)
{
  Node *idx = head;
  while (num--)
  {
    idx = idx->next;
  }

  if (idx == nullptr)
  {
    addNode2Tail(data);
    return;
  }

  Node *ne = getNode(data);
  idx->prev->next = ne;
  ne->prev = idx->prev;
  ne->next = idx;
  idx->prev = ne;
}
extern int findNode(int data)
{
  int idx = 1;
  Node *iter = head->next;

  while (iter->data != data)
  {
    idx++;
    iter = iter->next;
  }

  return idx;
}
extern void removeNode(int data)
{
  Node *idx = head->next;
  while (idx != nullptr && idx->data != data)
  {
    idx = idx->next;
  }

  if (idx != nullptr)
  {
    if (idx->next != nullptr)
    {
      idx->next->prev = idx->prev;
    }
    idx->prev->next = idx->next;
  }
}
extern int getList(int output[MAX_NODE])
{
  int idx = 0;
  Node *iter = head->next;

  while (iter != nullptr)
  {
    output[idx++] = iter->data;
    iter = iter->next;
  }

  return idx;
}
extern int getReversedList(int output[MAX_NODE])
{
  int idx = 0;
  Node *iter = head->next;
  while (iter->next != nullptr)
  {
    iter = iter->next;
  }

  while (iter != head)
  {
    output[idx++] = iter->data;
    iter = iter->prev;
  }

  return idx;
}

static void run()
{
  while (1)
  {
    int cmd, data, num, cnt, i = 0;
    int output[MAX_NODE] = {0};

    scanf("%d", &cmd);
    switch (cmd)
    {
    case ADD_HEAD: // 1
      scanf("%d", &data);
      addNode2Head(data);
      break;
    case ADD_TAIL: // 2
      scanf("%d", &data);
      addNode2Tail(data);
      break;
    case ADD_NUM: // 3
      scanf("%d %d", &data, &num);
      addNode2Num(data, num);
      break;
    case FIND: // 4
      scanf("%d", &data);
      num = findNode(data);
      printf("%d\n", num);
      break;
    case REMOVE: // 5
      scanf("%d", &data);
      removeNode(data);
      break;
    case PRINT: // 6
      cnt = getList(output);
      while (cnt--)
        printf("%d ", output[i++]);
      printf("\n");
      break;
    case PRINT_REVERSE: // 7
      cnt = getReversedList(output);
      while (cnt--)
        printf("%d ", output[i++]);
      printf("\n");
      break;
    case END:
      return;
    }
  }
}

int main(void)
{
  // setbuf(stdout, NULL);
  // freopen("dll_input.txt", "r", stdin);

  int T;
  scanf("%d", &T);
  for (int t = 1; t <= T; t++)
  {
    printf("#%d\n", t);
    init();
    run();
    printf("\n");
  }

  return 0;
}