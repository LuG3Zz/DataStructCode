#include <fstream>
#include <iostream>
#include <string>
#define ERROR 0
using namespace std;
typedef struct PNode {
  float coef; // 系数
  int expn;   // 指数
  struct PNode *next;
} PNode, *Polynomial;
string head_1, head_2;
int temp;
char st = 'A';
void CreatPolyn(Polynomial &P, int m) // 算法2.18 多项式的创建
{
  // 输入m项的系数和指数，建立表示一个多项式的有序链表P
  Polynomial q, pre, s;
  int i;
  P = new PNode;
  P->next = NULL; // 先建立一个带头结点的单链表
  string filename;
  cout << "请输入有关多项式p" << char(st + 32)
       << "系数和指数的数据文件名称（文件名+“.txt”，如Poly" << st << ".txt）："
       << endl;
  ++st;
  getline(cin, filename);
  fstream file;
  file.open(filename);
  if (!file) {
    cout << "未找到相关文件，无法打开！" << endl;
    exit(ERROR);
  }
  file >> head_1 >> head_2;
  while (!file.eof()) {
    s = new PNode;              // 生成新结点
    file >> s->coef >> s->expn; // 输入元素值
    pre = P; // pre用于保存q的前驱，初值为头结点
    q = P->next;
    while (q && q->expn < s->expn) // 通过比较指数找到第一个大于输入项指数的项q
    {
      pre = q;
      q = q->next;
    }            // while
    s->next = q; // 将输入项s插入到q和其前驱结点pre之间
    pre->next = s;
  } // for
  file.close();
} // CreatPolyn
void AddPolyn(Polynomial &Pa, Polynomial &Pb) // 算法2.19 多项式的相加
{
  // 多项式加法：Pa=Pa+Pb，利用两个多项式的结点构成“和多项式”
  Polynomial r, p1, p2, p3;
  float sum;
  p1 = Pa->next;
  p2 = Pb->next;   // p1和p2初值分别指向Pa和Pb的第一个结点
  p3 = Pa;         // p3指向和多项式的当前结点，初值为Pa
  while (p1 && p2) // p1和p2均非空
  {
    if (p1->expn == p2->expn) // 指数相等
    {
      sum = p1->coef + p2->coef; // sum保存两项的系数和
      if (sum != 0)              // 系数和不为0
      {
        p1->coef = sum; // 修改Pa当前结点p1的系数值为两项系数的和
        p3->next = p1;
        p3 = p1; // 将修改后的Pa当前结点p1链在p3之后，p3指向p1
        p1 = p1->next; // p1指向后一项
        r = p2;
        p2 = p2->next;
        delete r; // 删除Pb当前结点r
      } else      // 系数和为0
      {
        r = p1;
        p1 = p1->next;
        delete r; // 删除Pb当前结点p1
        r = p2;
        p2 = p2->next;
        delete r; // 删除Pb当前结点p2
      }
    } else if (p1->expn < p2->expn) // Pa当前结点p1的指数值小
    {
      p3->next = p1; // 将p1链在p3之后
      p3 = p1;       // p3指向p1
      p1 = p1->next; // p1指向后一项
    } else           // Pa当前结点p2的指数值小
    {
      p3->next = p2; // 将p2链在p3之后
      p3 = p2;       // p3指向p2
      p2 = p2->next; // p2指向后一项
    }
  }                        // while
  p3->next = p1 ? p1 : p2; // 插入非空多项式的剩余段
  delete Pb;               // 释放Pb的头结点
} // AddPolyn
void SubPolyn(Polynomial &Pa, Polynomial &Pb) // 算法2.19 多项式的相加
{
  // 多项式加法：Pa=Pa+Pb，利用两个多项式的结点构成“和多项式”
  Polynomial r, p1, p2, p3;
  float sub;
  p1 = Pa->next;
  p2 = Pb->next;   // p1和p2初值分别指向Pa和Pb的第一个结点
  p3 = Pa;         // p3指向和多项式的当前结点，初值为Pa
  while (p1 && p2) // p1和p2均非空
  {
    if (p1->expn == p2->expn) // 指数相等
    {
      sub = p1->coef - p2->coef; // sub保存两项的系数差
      if (sub != 0)              // 系数差不为0
      {
        p1->coef = sub; // 修改Pa当前结点p1的系数值为两项系数的差
        p3->next = p1;
        p3 = p1; // 将修改后的Pa当前结点p1链在p3之后，p3指向p1
        p1 = p1->next; // p1指向后一项
        r = p2;
        p2 = p2->next;
        delete r; // 删除Pb当前结点r
      } else      // 系数差为0
      {
        r = p1;
        p1 = p1->next;
        delete r; // 删除Pb当前结点p1
        r = p2;
        p2 = p2->next;
        delete r; // 删除Pb当前结点p2
      }
    } else if (p1->expn < p2->expn) // Pa当前结点p1的指数值小
    {
      p3->next = p1; // 将p1链在p3之后
      p3 = p1;       // p3指向p1
      p1 = p1->next; // p1指向后一项
    } else           // Pa当前结点p2的指数值小
    {
      p3->next = p2; // 将p2链在p3之后
      p3 = p2;       // p3指向p2
      p2 = p2->next; // p2指向后一项
    }
  }                        // while
  p3->next = p1 ? p1 : p2; // 插入非空多项式的剩余段
  delete Pb;               // 释放Pb的头结点
} // AddPolyn

void ShowMenu() {
  cout << "============   多项式运算================" << endl;
  cout << "============1. 创建多项式================" << endl;
  cout << "============2. 多项式加法================" << endl;
  cout << "============3. 多项式减法================" << endl;
  cout << "============4.   退出    ================" << endl;
}
void ShowPoly(Polynomial Pa) {

  Polynomial p;
  int i;
  cout << "多项式的值为：\n";
  p = Pa->next;
  i = 0;
  while (p) // 输出相加后的结果，每一项以x^n表示
  {
    if (i)
      cout << " + ";
    cout << "(" << p->coef << ") * x^" << p->expn;
    p = p->next;
    i = 1;
  }
  cout << endl;
}
int main(int argc, char *argv[]) {
  int i, temp;
  Polynomial a = NULL;
  Polynomial b = NULL;
  while (1) {
    ShowMenu();
    cin >> i;
    cin.ignore(); // 丢弃回车
    switch (i) {
    case 1:
      CreatPolyn(a, temp);
      CreatPolyn(b, temp);
      cout << "创建成功" << endl;
      ShowPoly(a);
      ShowPoly(b);
      break;
    case 2:
      if (a == NULL) {
        cout << "未创建多项式，请创建后重试" << endl;
        break;
      }
      AddPolyn(a, b);
      cout << "==多项式相加==" << endl;
      ShowPoly(a);
      return 0;
    case 3:
      if (b == NULL) {
        cout << "未创建多项式，请创建后重试" << endl;
        break;
      }
      cout << "==多项式相减==" << endl;
      SubPolyn(a, b);
      ShowPoly(a);
      return 0;
    case 4:
      return 0;
    }
  }
}
