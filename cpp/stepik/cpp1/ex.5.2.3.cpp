struct Rational {
    Rational(int numerator = 0, int denominator = 1);

    void add(Rational) {}
    void sub(Rational) {}
    void mul(Rational) {}
    void div(Rational) {}

    void neg() {}
    void inv() {}
    double to_double() const;

    Rational& operator+=(const Rational& b) {
        add(b);
        return *this;
    }
    Rational& operator-=(const Rational& b) {
        sub(b);
        return *this;
    }
    Rational& operator*=(const Rational& b) {
        mul(b);
        return *this;
    }
    Rational& operator/=(const Rational& b) {
        div(b);
        return *this;
    }

   private:
    int numerator_;
    int denominator_;
};

Rational operator-(const Rational& other) {
    Rational ret = other;
    ret.neg();
    return ret;
}
Rational operator+(const Rational& other) { return other; }
Rational operator+(Rational a, const Rational& b) {
    a += b;
    return a;
}

int main() {}
