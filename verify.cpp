#include <iostream>
#include <iomanip>
#include "fib.h"
#include "include/timer.h"
using namespace std;
typedef unsigned long long ll;

int main(int argc, char* argv[]) {
        if (argc != 2 && argc != 3) {
                cerr << "Invalid usage!\n";
                cerr << argv[0] << " <max ms> [num to calc]" << endl;
                return 1;
        }

        ll maxMicro;
        try {
                maxMicro = stoi(argv[1]) * 1000;
        } catch (exception) {
                cerr << "Error: <max ms> must be a positive integer!";
                return 1;
        }

        ll num = LLONG_MAX;
        if (argc == 3) {
                try {
                        num = stoi(argv[2]);
                } catch (exception) {
                        cerr << "Error: [num to calc] must be a non-negative integer!";
                        return 1;
                }
        }

        int maxw = 0;
        for (auto [name, _] : fib::fibs) maxw = max(maxw, static_cast<int>(name.size()));

        sc::timer t;
        ll n = 0;
        while (t.micros() < maxMicro && n < num) {
                vector<ll> fs(fib::fibs.size());
                for (int i = 0; i < fib::fibs.size(); i++) {
                        auto [_, fib] = fib::fibs[i];
                        fs[i] = fib(n);
                }
                bool valid = true;
                for (int i = 1; i < fs.size() && valid; i++)
                        valid = fs[i] == fs[i - 1];
                if (!valid) {
                        cout << n << ":\n";
                        for (int i = 0; i < fs.size(); i++)
                                cout << left << setw(maxw + 2)
                                        << fib::fibs[i].first + ": "
                                        << fs[i] << "\n";
                        cout << endl;
                }
                n++;
        }
        cout << "Time: " << t << endl;
        cout << "N: " << n << endl;

        return 0;
}
