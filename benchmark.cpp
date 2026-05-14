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
                maxMicro = stoll(argv[1]) * 1000;
        } catch (exception) {
                cerr << "Error: <max ms> must be a positive integer!" << endl;
                return 1;
        }

        ll num;
        if (argc == 3) {
                try {
                        num = stoll(argv[2]);
                } catch (exception) {
                        cerr << "Error: [num to calc] must be a non-negative integer!";
                        return 1;
                }
        }

        int maxw = 0;
        for (auto [name, _] : fib::fibs) maxw = max(maxw, static_cast<int>(name.size()));

        sc::timer t;
        for (auto [name, fib] : fib::fibs) {
                t.stop();
                t.reset();
                if (argc == 3) {
                        t.start();
                        fib(num);
                        t.stop();
                        cout << left << setw(maxw + 2) << (name + ": ") << t << endl;
                } else {
                        ll n = 0;
                        while (t.micros() < maxMicro) {
                                t.start();
                                fib(n);
                                t.stop();
                                n++;
                        }
                        cout << left << setw(maxw + 2) 
                                << (name + ": ") 
                                << right << setw(20) 
                                << n - 1 
                                << endl;
                }
        }

        return 0;
}
