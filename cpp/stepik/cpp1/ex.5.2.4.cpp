struct Rational {
    Rational(int numerator = 0, int denominator = 1);

    void add(Rational rational);
    void sub(Rational rational);
    void mul(Rational rational);
    void div(Rational rational);

    void neg();
    void inv();
    double to_double() const;

    Rational& operator+=(Rational rational) { return *this; }
    Rational& operator-=(Rational rational) { return *this; }
    Rational& operator*=(Rational rational) { return *this; }
    Rational& operator/=(Rational rational) { return *this; }

    Rational operator-() const;
    Rational operator+() const;

   private:
    int numerator_;
    int denominator_;
};

Rational operator+(Rational a, const Rational& b) { return a += b; }
Rational operator-(Rational a, const Rational& b) { return a -= b; }
Rational operator*(Rational a, const Rational& b) { return a *= b; }
Rational operator/(Rational a, const Rational& b) { return a /= b; }

int main() {}
