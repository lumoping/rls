#ifndef RLS_MATRIX_H
#define RLS_MATRIX_H

#include <stdlib.h>
#include <printf.h>

typedef struct {
    int row;
    int column;
    float *data;
} Matrix;

Matrix *Matrix_gen(int row, int column, const float *data);

Matrix *Matrix_copy(Matrix *_m_source);

Matrix *zeros(int row, int column);

Matrix *eye(int row, int column);

Matrix *ones(int row, int column);

Matrix *mtimes(Matrix *_m_left, Matrix *_m_right);

Matrix *times(Matrix *_matrix, float num);

Matrix *plus(Matrix *_matrix, float num);

Matrix *r_divide(Matrix *_m_left, Matrix *_m_right);

Matrix *transpose(Matrix *_matrix);

_Bool compatible(Matrix *_m_left, Matrix *_m_right);

int M_free(Matrix *_matrix);

Matrix *M_Cut(Matrix *_matrix, int row_head, int row_tail, int column_head, int column_tail);

void replace(Matrix *_matrix, int row, int column, const float data[]);

Matrix *Matrix_gen(int row, int column, const float *data) {
    Matrix *_mat = (Matrix *) malloc(sizeof(Matrix));
    _mat->row = row;
    _mat->column = column;
    int size = _mat->row * _mat->column;
    _mat->data = (float *) malloc((size) * sizeof(float));
    int i;
    for (i = 0; i < size; i++) {
        _mat->data[i] = data[i];
    }
    return _mat;
}

Matrix *Matrix_copy(Matrix *_m_source) {
    Matrix *_m_copy = Matrix_gen(_m_source->row, _m_source->column, _m_source->data);
    return _m_copy;
}

Matrix *zeros(int row, int column) {
    Matrix *matrix = (Matrix *) malloc(sizeof(Matrix));
    matrix->column = column;
    matrix->row = row;
    int size = row * column, i;
    float *data = (float *) malloc((size) * sizeof(float));
    for (i = 0; i < size; i++) {
        data[i] = 0;
    }
    matrix->data = data;
    return matrix;
}

Matrix *eye(int row, int column) {
    Matrix *matrix = (Matrix *) malloc(sizeof(Matrix));
    matrix->column = column;
    matrix->row = row;
    int size = row * column, min_side_len, i;
    min_side_len = row < column ? row : column;
    float *data = (float *) malloc((size) * sizeof(float));
    for (i = 0; i < min_side_len; ++i) {
        data[column * i + i] = 1;
    }
    matrix->data = data;
    return matrix;
}

Matrix *ones(int row, int column) {
    Matrix *matrix = (Matrix *) malloc(sizeof(Matrix));
    matrix->column = column;
    matrix->row = row;
    int size = row * column, i;
    float *data = (float *) malloc((size) * sizeof(float));
    for (i = 0; i < size; i++) {
        data[i] = 1;
    }
    matrix->data = data;
    return matrix;
}

Matrix *mtimes(Matrix *_m_left, Matrix *_m_right) {
    Matrix *_m_result = NULL;
    if (_m_left->column != _m_right->row) {
        //error
    } else {
        _m_result = (Matrix *) malloc(sizeof(Matrix));
        int row = _m_left->row;
        int mid = _m_left->column;
        int column = _m_right->column;
        int i, j, k;
        float *_data = (float *) malloc((row * column) * sizeof(float));
        float temp;
        for (i = 0; i < row; i++) {
            for (j = 0; j < column; j++) {
                temp = 0;
                for (k = 0; k < mid; k++) {
                    temp += (_m_left->data[i * mid + k]) * (_m_right->data[k * column + j]);
                }
                _data[i * column + j] = temp;
            }
        }
        _m_result->row = row;
        _m_result->column = column;
        _m_result->data = _data;
    }
    return _m_result;
}

Matrix *times(Matrix *_matrix, float num) {
    Matrix *_m_result;
    _m_result = Matrix_copy(_matrix);
    int i, size;
    size = _m_result->row * _m_result->column;
    for (i = 0; i < size; ++i) {
        _m_result->data[i] *= num;
    }
}

Matrix *plus(Matrix *_matrix, float num) {
    Matrix *_m_result;
    _m_result = Matrix_copy(_matrix);
    int i, size;
    size = _m_result->row * _m_result->column;
    for (i = 0; i < size; ++i) {
        _m_result->data[i] += num;
    }
}

Matrix *r_divide(Matrix *_m_left, Matrix *_m_right) {
    Matrix *_m_result = NULL;
    if (compatible(_m_left, _m_right)) {
        _m_result = (Matrix *) malloc(sizeof(Matrix));
        int row = _m_left->row > _m_right->row ? _m_left->row : _m_right->row;
        int column = _m_left->column > _m_right->column ? _m_left->column : _m_right->column;
        float *_data = (float *) malloc((row * column) * sizeof(float));
        int i, size;
        size = row * column;
        for (i = 0; i < size; ++i) {
            int result_row, result_col;
            result_row = i / column;
            result_col = i % column;
            int l_row, l_col, r_row, r_col;
            l_row = result_row < _m_left->row ? result_row : 0;
            l_col = result_col < _m_left->column ? result_col : 0;
            r_row = result_row < _m_right->row ? result_row : 0;
            r_col = result_col < _m_right->column ? result_col : 0;
            _data[i] =
                    _m_left->data[l_row * _m_left->column + l_col] / _m_right->data[r_row * _m_right->column + r_col];
        }
        _m_result->row = row;
        _m_result->column = column;
        _m_result->data = _data;
    }
    return _m_result;
}


Matrix *transpose(Matrix *_matrix) {
    Matrix *_result = (Matrix *) malloc(sizeof(Matrix));
    _result->column = _matrix->row;
    _result->row = _matrix->column;
    float *data = (float *) malloc(sizeof(float) * (_result->column) * (_result->row));
    _result->data = data;
    int i, j;
    for (i = 0; i < (_result->row); i++) {
        for (j = 0; j < _result->column; j++) {
            data[i * (_result->column) + j] = _matrix->data[j * (_matrix->column) + i];
        }
    }
    return _result;
}

_Bool compatible(Matrix *_m_left, Matrix *_m_right) {

    return 1;
}


int M_free(Matrix *_matrix) {
    free(_matrix->data);
    free(_matrix);
    return 0;
}

Matrix *M_Cut(Matrix *_matrix, int row_head, int row_tail, int column_head, int column_tail) {
    Matrix *mat_result = NULL;
    if (row_tail < 0) {
        row_tail = _matrix->row;
    }

    if (row_head < 0) {
        row_head = _matrix->row;
    }

    if (column_tail < 0) {
        column_tail = _matrix->column;
    }

    if (column_head < 0) {
        column_head = _matrix->column;
    }

    if ((row_tail > _matrix->row) || (column_tail > _matrix->column)) {
        //
    } else {
        if ((row_head > row_tail) || (column_head > column_tail)) {
            //
        } else {
            row_head = row_head - 1;
            column_head = column_head - 1;
            mat_result = (Matrix *) malloc(sizeof(Matrix));
            mat_result->row = row_tail - row_head;
            mat_result->column = column_tail - column_head;
            mat_result->data = (float *) malloc(sizeof(float) * (mat_result->row) * (mat_result->column));
            int i, j;
            for (i = 0; i < (row_tail - row_head); i++) {
                for (j = 0; j < (column_tail - column_head); j++) {
                    mat_result->data[i * (mat_result->column) + j] = _matrix->data[(i + row_head) * (_matrix->column) +
                                                                                   (j + column_head)];
                }
            }
        }
    }
    return mat_result;
}

void replace(Matrix *_matrix, int row, int column, const float data[]) {
    if (row <= 0 && column <= 0) { return; }
    if (row > 0 && column > 0) {
        _matrix->data[(row - 1) * _matrix->column + column] = data[0];
    } else {
        if (row < 0) {
            int i;
            for (i = 0; i < _matrix->row; i++) {
                _matrix->data[i * _matrix->column + (column - 1)] = data[i];
            }
        }
        if (column < 0) {
            int i;
            for (i = 0; i < _matrix->column; i++) {
                _matrix->data[(row - 1) * _matrix->column + i] = data[i];
            }
        }
    }

}

#endif //RLS_MATRIX_H



