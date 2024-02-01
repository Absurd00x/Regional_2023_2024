#pragma GCC optimize("O3")
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
#define int ll

signed main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);

  // Вычисляем простые до 10^6 решетом Эратосфена
  const int A = 1e6;
  vector<int> primes;
  vector<bool> sieve(A + 1, true);
  sieve[0] = sieve[1] = false;
  for (int i = 2; i <= A; ++i) {
    if (sieve[i]) {
      primes.push_back(i);
      for (int j = i + i; j <= A; j += i) {
        sieve[j] = false;
      }
    }
  }
  // Заранее считаем в какой части должно быть каждое число
  vector<int> part(A + 1, 1);
  for (int i = 1; i <= A; ++i) {
    if (part[i] == 1) {
      for (int j = 0; j < (int)primes.size(); ++j) {
        if (i * primes[j] > A) {
          break;
        }
        part[i * primes[j]] = 2;
      }
    }
  }

  int n;
  cin >> n;
  for (int i = 0; i < n; ++i) {
    int num;
    cin >> num;
    cout << part[num] << ' ';
  }
  cout << endl;

  return 0;
}
