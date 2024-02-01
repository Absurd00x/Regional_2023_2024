#pragma GCC optimize("O3")
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
#define int ll

signed main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  const int COLS = 6;
  int n, m;
  cin >> n >> m;
  vector<string> mat(n);
  for (int i = 0; i < n; ++i) {
    cin >> mat[i];
  }
  /*
  Если для крестика существует зеркальный крестик, то
  ничего не нужно и нельзя делать.
  Если для крестика существует зеркальная точка, то мы
  обязаны посадить туда пассажира.
  Если для точки существует зеркальная точка, то мы можем
  посадить пару пассажиров в эти точки.
  */
  int have = 0; // Сколько есть свободных мест
  int need = 0; // Сколько пассажиров обязаны добавить
  bool ans = true; // Ответ
  vector<string> cert = mat; // Рассадка
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < COLS; ++j) {
      // Если для крестика зеркальная точка
      if (mat[i][j] == 'X' && mat[i][COLS - j - 1] == '.') {
        // В ответе обязательно нужно заменить точку
        cert[i][COLS - j - 1] = 'X';
        ++need;
      // Если для точки зеркальная точка и мы в первых 3х местах
      // Считаем только первую половину, чтобы не считать одно и то же дважды
      } else if (cert[i][j] == '.' && cert[i][COLS - j - 1] == '.' && j < COLS / 2) {
        // Есть 2 свободных места
        have += 2;
      }
    }
  }
  // Если обязаны рассадить больше пассажиров, чем есть, то ответ "нет"
  if (need > m) {
    ans = false;
  // После того, как рассадили "обязательных" пассажиров
  // должно остаться чётное количество, чтобы было симметрично.
  } else if ((m - need) % 2 == 0 && m - need <= have) {
    ans = true;
    int rem = m - need; // Сколько осталось рассадить
    for (int i = 0; i < n && rem > 0; ++i) {
      for (int j = 0; j < COLS && rem > 0; ++j) {
        // Если тут две точки, то сажаем
        if (cert[i][j] == '.' && cert[i][COLS - j - 1] == '.') {
          cert[i][j] = cert[i][COLS - j - 1] = 'X';
          rem -= 2;
        }
      }
    }
  } else {
    ans = false;
  }
  if (ans) {
    for (int i = 0; i < n; ++i) {
      cout << cert[i] << '\n';
    }
  } else {
    cout << "Impossible" << '\n';
  }
  return 0;
}
