#include <iostream>
#include <map>
#include <sstream>
#include <string>

using namespace std;

enum TokenValue {
    NAME,
    NUMBER,
    END,
    PLUS = '+',
    MINUS = '-',
    MUL = '*',
    DIV = '/',
    PRINT = ';',
    ASSIGN = '=',
    LP = '(',
    RP = ')',
};

TokenValue curr_tok = PRINT;
double number_value;
string string_value;
map<string, double> table;
istream* input;

double expr(bool);

int no_of_errors;

double error(const string& s) {
    ++no_of_errors;
    cerr << "error: " << s << endl;
    return 1;
}

TokenValue get_token() {
    char ch;

    do {
        if (!input->get(ch)) return curr_tok = END;
    } while (ch != '\n' && isspace(ch));

    switch (ch) {
        case 0:
            return curr_tok = END;
        case '*':
        case '/':
        case '+':
        case '-':
        case '(':
        case ')':
        case '=':
            return curr_tok = TokenValue(ch);
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
        case '.':
            input->putback(ch);
            cin >> number_value;
            return curr_tok = NUMBER;
        case ';':
        case '\n':
            return curr_tok = PRINT;
        default:
            if (isalpha(ch)) {
                string_value = ch;
                while (input->get(ch) && isalnum(ch))
                    string_value.push_back(ch);
                input->putback(ch);
                return curr_tok = NAME;
            }

            error("bad token");
            return curr_tok = PRINT;
            break;
    }
}

double prim(bool get) {
    if (get) get_token();

    switch (curr_tok) {
        case NUMBER: {
            double v = number_value;
            get_token();
            return v;
        }
        case NAME: {
            double& v = table[string_value];
            if (get_token() == ASSIGN) v = expr(true);
            return v;
        }
        case MINUS: {
            return -prim(true);
        }
        case LP: {
            double e = expr(true);
            if (curr_tok != RP) return error("')' expected");
            get_token();
            return e;
        }
        default:
            return error("primary expected");
    }
}

double term(bool get) {
    double left = prim(get);

    for (;;) {
        switch (curr_tok) {
            case MUL: {
                left *= prim(true);
                break;
            }

            case DIV: {
                if (double d = prim(true)) {
                    left /= d;
                    break;
                }

                return error("divide by zero");
            }
            default:
                return left;
        }
    }
}

double expr(bool get) {
    double left = term(get);

    for (;;) {
        switch (curr_tok) {
            case PLUS: {
                left += term(true);
                break;
            }
            case MINUS: {
                left -= term(true);
                break;
            }
            default:
                return left;
                break;
        }
    }
}

int main(int argc, char* argv[]) {
    switch (argc) {
        case 1: {
            input = &cin;
            break;
        }
        case 2: {
            input = new istringstream(argv[1]);
            break;
        }
        default:
            error("too many arguments");
            return 1;
    }

    table["pi"] = 3.1415926535897932385;
    table["e"] = 2.7182818284590452354;

    while (*input) {
        get_token();
        if (curr_tok == END) break;
        if (curr_tok == PRINT) continue;
        cout << expr(false) << endl;
    }

    if (input != &cin) delete input;

    return no_of_errors;
}
