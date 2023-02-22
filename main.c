#include "matrix.h"


int main() {
    int N = 3000;
    Matrix *x = NULL;

    int n = 30;
    float o = 1;
    Matrix *Cxx, *g, *h, *y, *e;
    Matrix *Cxx_eye = eye(n, n);
    Matrix *Cxx_10000 = Matrix_gen(1, 1, (float *) 10000);
    Cxx = mtimes(Cxx_10000, Cxx_eye);
    M_free(Cxx_eye);
    M_free(Cxx_10000);
    g = zeros(N, n);
    h = zeros(N, n);
    y = zeros(1, N);
    e = zeros(1, N);
    int i;
    for (i = n + 1; i <= N; ++i) {
        //    g(i,:)=(Cxx*x(i-n+1:i)'./(o+x(i-n+1:i)*Cxx*x(i-n+1:i)'))';
        Matrix *cut = M_Cut(x, i - n + 1, i, 1, 1);
        Matrix *trans = transpose(cut);
        Matrix *left = mtimes(Cxx, trans);
        Matrix *mtimes1 = mtimes(cut, trans);
        Matrix *right = plus(mtimes1, o);
        Matrix *divide = r_divide(left, right);
        Matrix *transpose1 = transpose(divide);
        replace(g, i, -1, transpose1->data);

    }
}

//

