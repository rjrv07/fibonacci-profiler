#include <functional>
#include <unordered_map>
#include <utility>
#include <vector>
#include "matrix.h"
using namespace std;
typedef unsigned long long ll;

namespace fib {
struct Vec {
        pair<ll, ll> data;

        Vec(pair<ll, ll> d) {
                data = d;
        }

        ll operator[](int i) {
                return (i ? data.second : data.first);
        }
};

struct Mat {
        vector<ll> data;

        Mat(vector<ll> d) {
                data = d;
        }

        ll operator[](int i) {
                return this->data[i];
        }

        Vec operator*(Vec v) {
                return Vec({
                        data[0] * v[0] + data[1] * v[1],
                        data[2] * v[0] + data[3] * v[1]
                });
        }

        void operator*=(Mat m) {
                data = {
                        data[0] * m[0] + data[1] * m[2],
                        data[0] * m[1] + data[1] * m[3],
                        data[2] * m[0] + data[3] * m[2],
                        data[2] * m[1] + data[3] * m[3]
                }; 
        }
};

inline ll fibBinExp(ll n) {
        Mat M({0, 1, 1, 1});
        Mat F({1, 0, 0, 1});
        Vec v({0, 1});

        for (ll i = 1; i <= n; i <<= 1) {
                if (n&i) F *= M;
                M *= M;
        }

        return (F * v)[0];
}

inline ll fibConstruct(ll n) {
        ll prev = 0, cur = 1;
        while (n--) {
                ll sum = prev + cur;
                prev = cur;
                cur = sum;
        }
        return prev;
}

inline ll fibRec(ll n) {
        if (n <= 1) return n;
        return fibRec(n - 1) + fibRec(n - 2);
}

inline ll fibRecSmart(ll n) {
        if (n <= 1) return n;
        if (n < 5) return fibRecSmart(n - 1) + fibRecSmart(n - 2);
        if (n % 2 == 0) 
                return (fibRecSmart(n/2 - 1) + fibRecSmart(n/2 + 1)) * fibRecSmart(n/2);

        n = (n + 1) / 2;
        return fibRecSmart(n) * fibRecSmart(n) + fibRecSmart(n-1) * fibRecSmart(n-1);
}

inline ll fibRecMemo(ll n) {
        unordered_map<ll, ll> mp;
        function<ll(ll)> f = [&](ll n) -> ll {
                if (mp.count(n)) return mp[n];
                if (n <= 1) return mp[n] = n;
                return mp[n] = f(n - 1) + f(n - 2);
        };
        return f(n);
}

inline ll fibRecSmartMemo(ll n) {
        unordered_map<ll, ll> mp;
        function<ll(ll)> f = [&](ll n) -> ll {
                if (mp.count(n)) return mp[n];
                if (n <= 1) return mp[n] = n;
                if (n < 5) return mp[n] = fibRecSmart(n - 1) + fibRecSmart(n - 2);
                if (n % 2 == 0) 
                        return mp[n] = 
                        (fibRecSmart(n/2 - 1) + fibRecSmart(n/2 + 1)) * fibRecSmart(n/2);

                n = (n + 1) / 2;
                return mp[n] = 
                fibRecSmart(n) * fibRecSmart(n) + fibRecSmart(n-1) * fibRecSmart(n-1);
        };
        return f(n);
}


inline ll fibSimplyCpp(ll n) {
        sc::matrix<ll, 2, 2> fibMat = {0, 1, 1, 1};
        sc::matrix<ll, 2, 1> init = {0, 1};
        return ((fibMat ^ n) * init)[0];
}

const vector<pair<string, ll (*)(ll n)>> fibs = {
        {"Recursive", &fib::fibRec},
        {"Memoised Recursive", &fib::fibRecMemo},
        {"Smart Recursive", &fib::fibRecSmart},
        {"Memoised Smart Recursive", &fib::fibRecSmartMemo},
        {"Constructive", &fib::fibConstruct},
        {"Binary Exponentiation", &fib::fibBinExp},
        {"Simply C++", &fib::fibSimplyCpp},
};
}
