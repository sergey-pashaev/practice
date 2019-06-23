// ex.1.8

// Переключение потоков

#include <fstream>
#include <iostream>

using namespace std;

template <typename In, typename Out>
void process(In& in, Out& out) {
    out << in.rdbuf();
}

int main(int argc, char* argv[]) {
    fstream in, out;
    if (argc > 1) in.open(argv[1], ios::in | ios::binary);
    if (argc > 2) out.open(argv[2], ios::in | ios::binary);

    process(in.is_open() ? in : cin, out.is_open() ? out : cout);
    return 0;
}
