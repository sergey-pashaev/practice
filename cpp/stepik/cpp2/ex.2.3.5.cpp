// определение структуры Point уже подключено
struct Point {
    constexpr Point(double x, double y) : x(x), y(y) {}

    double x = 0;
    double y = 0;
};

// сложение
constexpr Point operator+(const Point& lhs, const Point& rhs) {
    return Point(lhs.x + rhs.x, lhs.y + rhs.y);
}

// вычитание
constexpr Point operator-(const Point& lhs, const Point& rhs) {
    return Point(lhs.x - rhs.x, lhs.y - rhs.y);
}

// скалярное произведение
constexpr double operator*(const Point& lhs, const Point& rhs) {
    return lhs.x * rhs.x + lhs.y * rhs.y;
}

int main() {}
