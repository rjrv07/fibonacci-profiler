#include <iostream>
#include "fib.h"
#include "include/timer.h"
#include "matplotlibcpp.h"
namespace plt = matplotlibcpp;
using namespace std;
typedef unsigned long long ll;

int main(int argc, char* argv[]) {
        if (argc != 2 && argc != 3) {
                cerr << "Invalid usage!\n";
                cerr << argv[0] << "[-ll] <max ms>" << endl;
                return 1;
        }

        bool loglog;
        ll maxMicro;
        for (int i = 0; i < argc; i++ ) {
                string arg = argv[i];

                if (arg == "--loglog") {
                        loglog = true;
                        continue;
                }

                try {
                        maxMicro = stoi(argv[1]) * 1000;
                } catch (exception) {
                        cerr << "Error: <max ms> must be a positive integer!";
                        return 1;
                }
        }

        ll maxX = 1;
        for (auto [name, fib] : fib::fibs) {
                vector<ll> x, y;
                ll totalT = 0;
                ll n = 1;
                while (totalT < maxMicro) {
                        sc::timer t;
                        fib(n);
                        t.stop();
                        totalT += t.micros();
                        x.push_back(n);
                        y.push_back(totalT);
                        maxX = max(maxX, n);
                        n++;
                }
                plt::named_plot(name, x, y);
        }

        if (loglog) PyRun_SimpleString(
                "import matplotlib.pyplot as plt; plt.xscale('log'); plt.yscale('log')"
        );

        plt::xlim(1ULL, maxX);
        plt::ylim(1ULL, maxMicro);
        plt::xlabel("n");
        plt::ylabel("Cumulative time (µs)");
        plt::title("Fibonacci implementations");
        plt::legend();
        plt::show();

        return 0;
}
