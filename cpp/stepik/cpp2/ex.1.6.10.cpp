template <typename T, typename U>
bool compare(const T& a, const T& b, U (T::*mptr)() const) {
    return (a.*mptr)() < (b.*mptr)();
}

int main() {}
