#pragma GCC optimize("O3")
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
#define int ll

signed main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  int n;
  cin >> n;
  vector<int> arr(n);
  for (int i = 0; i < n; ++i) {
    cin >> arr[i];
  }
  // Считаем заранее все отрезки длины 1
  int ans = n;
  for (int i = 0; i < n; ++i) {
    // Если i-ый элемент больше своих соседей
    // Считаем что на позициях -1 и n стоят нули
    if ((i == 0 || arr[i - 1] <= arr[i]) && (i + 1 == n || arr[i] >= arr[i + 1])) {
      int start = i;
      // Если слева есть элемент и он строго меньше нас
      if (i > 0 && arr[i - 1] < arr[i]) {
        // Смотрим как долго продолжается "уменьшение"
        for (int j = start - 1; j >= 0 && arr[j] < arr[j + 1]; --j) {
          start = j;
        }
      }
      int finish = i;
      // Если справа есть элемент и он строго меньше нас
      if (i + 1 < n && arr[i] > arr[i + 1]) {
        for (int j = finish + 1; j < n && arr[j - 1] > arr[j]; ++j) {
          finish = j;
        }
      }
      // Можно выбрать любой подотрезок отрезка [start, finish]
      // Считаем количество подотрезков через длину
      int len = finish - start + 1;
      ans += len * (len - 1) / 2;
    }
  }
  cout << ans << endl;
  return 0;
}
