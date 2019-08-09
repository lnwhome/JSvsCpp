#include <iostream>
#include <cstdlib>
#include <chrono>
#include <vector>
#include <numeric>

int main();
#ifdef WASM
#include "emscripten.h"
extern "C"
{
    EMSCRIPTEN_KEEPALIVE void entryPoint()
    {
        main();
    }
}
#endif

int ackermann(int m, int n)
{
    return m == 0 ? n + 1 : ackermann(m - 1, n == 0  ? 1 : ackermann(m, n - 1));
}

int main ()
{
    using namespace std;
    const size_t arraySize = 50 * 1000000;
    vector<double> array;


    auto t0 = chrono::high_resolution_clock::now();

    srand(time(NULL));
    for (auto i = 0u;i < arraySize; ++i)
    {
        array.push_back((double)rand() / RAND_MAX);
    }
    cout << "array size " << array.size() << "\n";

    auto t1 = chrono::high_resolution_clock::now();

    cout << "mean value " << accumulate(array.begin(), array.end(), (double)0) / array.size() << "\n";

    auto t2 = chrono::high_resolution_clock::now();

    cout << "ackermann value " << ackermann(4,1) << "\n";

    auto t3 = chrono::high_resolution_clock::now();
  
    cout << "array generation time    " << chrono::duration_cast<chrono::microseconds>(t1-t0).count() / 1000.0 << "ms\n";
    cout << "mean calculation time    " << chrono::duration_cast<chrono::microseconds>(t2-t1).count() / 1000.0 << "ms\n";
    cout << "ackermann execution time " << chrono::duration_cast<chrono::microseconds>(t3-t2).count() / 1000.0 << "ms\n";
}
/*
c++ -O3 --std=c++17 ./main.cpp && ./a.out
em++ -O3 --std=c++17 -DWASM=1 -s ALLOW_MEMORY_GROWTH=1 -s "EXTRA_EXPORTED_RUNTIME_METHODS=['cwrap', 'ccall']" ./main.cpp
cp a.out.* /var/www/html/jsvscpp/
cp ../html/index.html /var/www/html/jsvscpp/
*/

