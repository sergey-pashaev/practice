/* ex.4.2 */

/* Extend atof to handle scientific notation of the form 123.45e-6 */
/* where a floating-point number may be followed by e or E and an */
/* optionally signed exponent. */

#include <assert.h>
#include <ctype.h>
#include <float.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

double atof(const char s[]) {
    double val, power;
    int i, sign, exp, esign;

    /* skip whitespace */
    for (i = 0; isspace(s[i]); ++i)
        ;

    /* store sign */
    sign = (s[i] == '-') ? -1 : 1;
    if (s[i] == '-' || s[i] == '+') ++i;

    /* read until point */
    for (val = 0.0; isdigit(s[i]); ++i) {
        val = 10.0 * val + (s[i] - '0');
    }

    /* skip point */
    if (s[i] == '.') ++i;

    /* read after point */
    for (power = 1.0; isdigit(s[i]); ++i) {
        val = 10.0 * val + (s[i] - '0');
        power *= 10.0;
    }

    val = sign * val / power;

    /* skip exponent char */
    if (s[i] == 'e' || s[i] == 'E') ++i;

    /* store exponent sign */
    esign = (s[i] == '-') ? -1 : 1;
    if (s[i] == '-' || s[i] == '+') ++i;

    /* read exponent */
    for (exp = 0; isdigit(s[i]); ++i) {
        exp = 10 * exp + (s[i] - '0');
    }

    /*  val = 10^(exp) */
    for (i = 0; i < exp; ++i) {
        val = (esign > 0) ? (val * 10.0) : (val / 10.0);
    }

    return val;
}

int approx_equal(double x, double y) {
    return fabs(x - y) < (DBL_EPSILON * fabs(x + y));
}

int tests() {
    assert(approx_equal(1.0, atof("1.0")));
    assert(approx_equal(123.456, atof("+123.456")));
    assert(approx_equal(-123.456, atof("-123.456")));
    assert(approx_equal(-123.456e+02, atof("-123.456E2")));
    assert(approx_equal(-123.456e-02, atof("-123.456e-2")));
    assert(approx_equal(123.456e+12, atof("123.456E+12")));
    return 0;
}

int usage(const char* bin) {
    printf("Usage: %s <float as string>\n", bin);
    return 1;
}

int main(int argc, char** argv) {
    if (argc < 2) {
        usage(argv[0]);
        return tests();
    }

    double v = atof(argv[1]);
    printf("atof(%s) == %e\n", argv[1], v);
    return 0;
}
