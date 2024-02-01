#pragma GCC optimize("O3")
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

signed main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  int n, m;
  cin >> n >> m;
  vector<vector<int>> mat(n, vector<int>(m));
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      cin >> mat[i][j];
    }
  }
  ll s;
  cin >> s;
  const int MASKS_N = 1 << n; // Битмаски по строкам
  const int HALF1 = m / 2; // Первая половина по столбцам
  const int HALF2 = (m + 1) / 2; // Вторая половина по столбцам
  const int MASKS_M1 = 1 << HALF1; // Битмаски первой половины столбцов
  const int MASKS_M2 = 1 << HALF2; // Битмаски второй половины столбцов

  // Ответ
  bool ans = false;
  vector<pair<int, int>> cert;

  vector<ll> costs(MASKS_M1); // Стоимости масок
  vector<int> masks(MASKS_M1); // Сами битмаски
  vector<ll> have(m); // Текущие стоимости столбцов
  for (int mask1 = 0; mask1 < MASKS_N; ++mask1) {
    fill(have.begin(), have.end(), 0LL);
    // Применяем битмаску строк. То есть выбираем некоторые
    // строки с которыми будем работать.
    for (int i = 0; i < n; ++i) {
      if ((mask1 >> i) & 1) {
        // Если i-й бит равен единице, то мы выбрали эту строку
        for (int j = 0; j < m; ++j) {
          have[j] += mat[i][j];
        }
      }
    }
    // Вычисляем маски для первой половины получившегося массива have
    for (int mask2 = 0; mask2 < MASKS_M1 && !ans; ++mask2) {
      costs[mask2] = 0;
      for (int j = 0; j < HALF1; ++j) {
        if ((mask2 >> j) & 1) {
          costs[mask2] += have[j];
        }
      }
    }
    // Заполняем сами маски
    iota(masks.begin(), masks.end(), 0);
    // Сортируем маски по стоимости
    sort(masks.begin(), masks.end(), [&](const int &i, const int &j) {
      return costs[i] < costs[j];
    });
    // Перебираем вторую половину масок
    for (int mask2 = 0; mask2 < MASKS_M2 && !ans; ++mask2) {
      ll sum = 0;
      // Считаем стоимость второй половины маски
      for (int j = 0; j < HALF2; ++j) {
        if ((mask2 >> j) & 1) {
          sum += have[HALF1 + j];
        }
      }
      ll need = s - sum;
      if (costs[masks[0]] > need) {
        continue;
      }
      int l = 0; // Какая маска точно <= нужной сумме
      int r = MASKS_M1; // Какая точно больше
      // Сужаем границы бинарным поиском
      while (r - l > 1) {
        int mid = l + (r - l) / 2;
        if (costs[masks[mid]] <= need) {
          l = mid;
        } else {
          r = mid;
        }
      }
      if (costs[masks[l]] == need) {
        // Если нашли маску, которая равна необходимой сумме
        ans = true;
        // Удаляем строки
        for (int i = n - 1; i >= 0; --i) {
          if (((mask1 >> i) & 1) == 0) {
            cert.emplace_back(1, i + 1);
          }
        }
        // Удаляем вторую половину столбцов
        for (int j = HALF2 - 1; j >= 0; --j) {
          if (((mask2 >> j) & 1) == 0) {
            cert.emplace_back(2, HALF1 + j + 1);
          }
        }
        int mask = masks[l];
        // Теперь для первой половины
        for (int j = HALF1 - 1; j >= 0; --j) {
          if (((mask >> j) & 1) == 0) {
            cert.emplace_back(2, j + 1);
          }
        }
        // Выйдем из циклов потому что ans = true
      }
    }
  }
  if (ans) {
    cout << "YES" << '\n';
    cout << cert.size() << '\n';
    for (int i = 0; i < (int)cert.size(); ++i) {
      cout << cert[i].first << ' ' << cert[i].second << '\n';
    }
  } else {
    cout << "NO" << '\n';
  }
  return 0;
}
