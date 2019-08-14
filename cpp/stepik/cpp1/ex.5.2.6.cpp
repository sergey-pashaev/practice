struct Rational {
    Rational(int numerator = 0, int denominator = 1);

    void add(Rational rational);
    void sub(Rational rational);
    void mul(Rational rational);
    void div(Rational rational);

    void neg();
    void inv();
    double to_double() const;

    Rational& operator+=(Rational rational);
    Rational& operator-=(Rational rational);
    Rational& operator*=(Rational rational);
    Rational& operator/=(Rational rational);

    Rational operator-() const;
    Rational operator+() const;

    friend bool operator<(const Rational& lhs, const Rational& rhs);
    friend bool operator==(const Rational& lhs, const Rational& rhs);

   private:
    int numerator_;
    int denominator_;
};

Rational operator+(Rational lhs, Rational rhs);
Rational operator-(Rational lhs, Rational rhs);
Rational operator*(Rational lhs, Rational rhs);
Rational operator/(Rational lhs, Rational rhs);

bool operator<(const Rational& lhs, const Rational& rhs) {
    return lhs.numerator_ * rhs.denominator_ <
           rhs.numerator_ * lhs.denominator_;
}

bool operator==(const Rational& lhs, const Rational& rhs) {
    return !(lhs < rhs) && !(rhs < lhs);
}
bool operator!=(const Rational& lhs, const Rational& rhs) {
    return !(lhs == rhs);
}
bool operator<=(const Rational& lhs, const Rational& rhs) {
    return !(rhs < lhs);
}
bool operator>=(const Rational& lhs, const Rational& rhs) {
    return !(lhs < rhs);
}
bool operator>(const Rational& lhs, const Rational& rhs) { return rhs < lhs; }

int main() {}
