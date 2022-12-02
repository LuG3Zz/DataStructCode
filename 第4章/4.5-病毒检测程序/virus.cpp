#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
using namespace std;

void get_next(string t, int next[]) {
  // TODO
  int tlen = t.length();
  int j = 0, k = -1;
  next[0] = -1;
  while (j < tlen) {
    if (k == -1 || t[k] == t[j]) { // k=-1是第一个字符不等的情况
      next[++j] = ++k;
    } else
      k = next[k];
  }
}
void get_nexval(string t, int nextval[]) {
  // TODO
  int tlen = t.length();
  int j = 0, k = -1;
  nextval[0] = -1;
  while (j < tlen) {
    if (k == -1 || t[k] == t[j]) {
      if (t[++k] == t[++j])
        nextval[j] = nextval[k];
      else
        nextval[j] = k;
    } else
      k = nextval[k];
  }
}
int Index_KMP(string s, string t, int pos = 0) {
  // 比较第pos+1个字符后的串
  int tlen = t.length();
  int slen = s.length();

  int i = pos, j = 0, sum = 0;
  int *next = new int[slen];
  get_next(t, next);
  while (i < slen && j < tlen) {
    sum++;
    if (j == -1 || s[i] == t[j])
      i++, j++;
    else
      j = next[j];
  }
  if (j >= tlen) {
    return i - tlen + 1;
  } else
    return -1;
}
void Virus_detection(string filename) {
  // TODO
  int num, m, flag;
  string Virus, person, temp;
  ifstream inFile(filename);
  ofstream outFile("VirusOutputData.txt");
  inFile >> num;
  while (num--) {
    inFile >> Virus;
    inFile >> person;
    m = Virus.length();
    string Vir = Virus + Virus;
    for (int i = 0; i < m; i++) {
      for (int j = 0; j < m; j++) {
        temp += Vir[i + j];
      }

      flag = Index_KMP(person, temp);
      temp = "";
      if (flag != -1)
        break;
    }
    if (flag == -1) {
      outFile << Virus << " " << person << " "
              << "No" << endl;
    } else
      outFile << Virus << " " << person << " "
              << "Yes" << endl;

  } // while
}
int main(int argc, char *argv[]) {
  string filename;
  cout << "请输入病毒和人的基因序列文件：" << endl;
  getline(cin, filename);
  if (filename.empty()) {
    cout << "输入文件不能为空" << endl;
    exit(-1);
  } else {
    Virus_detection(filename);
    cout << "检测完成！结果已输出至文件VirusOutputData.txt" << endl;
  }
  return 0;
}
