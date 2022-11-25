#include <cstring>
#include <iostream>
using namespace std;

typedef struct HTNode {
  int weight;
  int parent, lchild, rchild;
} HTNode, *HuffmanTree; // 定义结构体

typedef char **HuffmanCode;

void Select(HuffmanTree HT, int len, int &s1, int &s2) {
  // s1最小，s2次小
  int i, min1 = 0x3f3f3f3f, min2 = 0x3f3f3f3f;
  for (i = 1; i <= len; i++) {
    if (HT[i].weight < min1 && HT[i].parent == 0) {
      min1 = HT[i].weight;
      s1 = i;
    } // 找s1
  }
  for (i = 1; i <= len; i++) {
    if (HT[i].weight < min2 && HT[i].parent == 0 && i != s1) {
      min2 = HT[i].weight;
      s2 = i;
    } // 找s2
  }
  cout << "s1:" << s1 << ";"
       << "s2:" << s2 << ";" << endl;
}; // 找两个最小权值结点的函数

void CreateHuffmanTree(HuffmanTree &HT, int n, int num[]) {
  if (n <= 1) {
    return;
  }
  int i, s1, s2, m; // m:所有结点数量
  m = 2 * n - 1;
  HT = new HTNode[m + 1];
  for (i = 1; i < m; i++) {
    HT[i].parent = 0;
    HT[i].lchild = 0;
    HT[i].rchild = 0;
  }
  for (i = 1; i <= n; i++) {
    HT[i].weight = num[i];
  }
  for (i = n + 1; i <= m; i++) {
    Select(HT, i - 1, s1, s2);
    cout << "HT[s1]:" << HT[s1].weight << ";"
         << "HT[s2]:" << HT[s2].weight << ";" << endl;
    HT[s1].parent = i;
    HT[s2].parent = i;
    HT[i].lchild = s1;
    HT[i].rchild = s2;
    HT[i].weight = HT[s1].weight + HT[s2].weight;
  }
}
void CreatHuffmanCode(HuffmanTree HT, HuffmanCode &HC, int n) {
  int i, start, c, f;
  HC = new char *[n + 1];
  char *cd = new char[n];
  cd[n - 1] = '\0';
  for (i = 1; i <= n; ++i) {
    start = n - 1;
    c = i;
    f = HT[i].parent;
    while (f != 0) {
      --start;
      if (HT[f].lchild == c)
        cd[start] = '0';
      else
        cd[start] = '1';
      c = f;
      f = HT[f].parent;
    }
    HC[i] = new char[n - start];
    strcpy(HC[i], &cd[start]);
  }
  delete[] cd;
}
//==============  ================
void show(HuffmanTree HT, HuffmanCode HC) {
  for (int i = 1; i <= sizeof(HC) + 1; i++) {
    cout << "权值为" << HT[i].weight << "的结点编码为：" << HC[i] << endl;
  }
}
//==============  ================
void Printe(HuffmanCode &HC, int l) {
  string str = HC[l];
  cout << str;
}
void change() {
  cin.ignore();
  char a[100];
  cin.getline(a, 100);
  int len = strlen(a);
  for (int i = 0; i < len; i++) {
    int l = a[i];
    if (a[i] == ' ')
      l = 27;
    else if (l >= 97) {
      l -= 96;
    } else if (l < 97 && l >= 65) {
      l -= 64;
    }
  }
}
//============== TODO================

//============== decoding ================
void decoding(HuffmanCode &HC, int n, string s) {
  string temp = "";
  char str[1000];
  for (int i = 0; i < 1000; i++) {
    str[i] =
  }
}
//============== main ================
int main(int argc, char *argv[]) {
  HuffmanTree HT;
  HuffmanCode HC;
  int n;
  int num[100] = {0};
  cout << "请输入叶子结点的个数" << endl;
  cin >> n;
  CreateHuffmanTree(HT, n, num);
  CreatHuffmanCode(HT, HC, n);
  show(HT, HC);
  return 0;
}
