struct Expression {
    virtual ~Expression() {}
    virtual double evaluate() const = 0;
};

struct Number : Expression {
    Number(double value) : value(value) {}
    double evaluate() const { return value; }

   private:
    double value;
};

struct BinaryOperation : Expression {
    /*
      Здесь op это один из 4 символов: '+', '-', '*' или '/', соответствующих
      операциям,
      которые вам нужно реализовать.
    */
    BinaryOperation(Expression const* left, char op, Expression const* right)
        : left(left), right(right), op(op) {}
    virtual ~BinaryOperation() {
        if (left) delete left;
        if (right) delete right;
    }

    double evaluate() const {
        switch (op) {
            case '+': {
                return left->evaluate() + right->evaluate();
                break;
            }
            case '-': {
                return left->evaluate() - right->evaluate();
                break;
            }
            case '*': {
                return left->evaluate() * right->evaluate();
                break;
            }
            case '/': {
                return left->evaluate() / right->evaluate();
                break;
            }
        }

        return 0.0;
    }

   private:
    Expression const* left;
    Expression const* right;
    char op;
};

int main() {}
