#pragma GCC optimize("O3")
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
#define int ll

int calc(vector<int> &arr, vector<int> &brr, int time) {
  // 2^30 будет точно больше любого m
  const int B = 30;
  int have = 0;
  for (int i = 0; i < (int)arr.size(); ++i) {
    // Если бактерию поместят в чашку и она успеет созреть
    if (time >= arr[i] + brr[i]) {
      // То она каждую секунду будет делиться на две
      // Берём минимум с числом B, потому что больше 2^30
      // бактерий уже не имеет смысла считать. И так понятно,
      // что их будет слишком много
      have += 1 << min(B, time - (arr[i] + brr[i]) + 1);
    } else if (time >= arr[i]) {
      // Если успели только поместить в чашку
      have += 1;
    }
  }
  return have;
};

signed main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);

  int n, m;
  cin >> n >> m;
  vector<int> arr(n), brr(n);
  for (int i = 0; i < n; ++i) {
    cin >> arr[i];
  }
  for (int i = 0; i < n; ++i) {
    cin >> brr[i];
  }

  // За это время количество бактерий будет строго меньше m
  int l = 0;
  // За это время будет больше или равно m
  int r = 2e9 + 30;
  while (r - l > 1) {
    int mid = l + (r - l) / 2;
    if (calc(arr, brr, mid) < m) {
      l = mid;
    } else {
      r = mid;
    }
  }
  // Проверяем, что за время r их стало в точности m
  if (calc(arr, brr, r) == m) {
    cout << r << endl;
  } else {
    cout << -1 << endl;
  }

  return 0;
}
