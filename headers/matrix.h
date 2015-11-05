#pragma once
#include <assert.h>


// WARNING!!
// Note that there occurs error when operate {type T} / {type T}

template <typename T>
class Matrix {
private:
    int m, n;
    bool allocated;
public:
    T** a;
    Matrix() {
        this->allocated = false;
    }
    Matrix(int m, int n) {
        assert(m >0 && n>0);
        this->m = m;
        this->n = n;

        newDoublePointer();

    }
    Matrix(int m, int n, T** a) {
        assert(m >0 && n>0);
        this->m = m;
        this->n = n;
        this->a = a;
        this->allocated = false;
    }
    
    //Identity Matrix
    Matrix(int n) {
        
        assert( n >0);
        this->m = m;
        this->n = n;
        
        this->m = n;
        this->n = n;
        newDoublePointer();
        
        int i, j;
        for (i=0; i<n; i++) {
            for (j=0; j<n; j++) this->a[i][j] = 0;
            this->a[i][i] = 1;
        }
    }
    ~Matrix() {
        if (allocated) deleteDoublePointer();
    }
    void newDoublePointer() {
        int i;
        this->a = new T*[this->m];
        for (i=0; i<this->m; i++) {
            a[i] = new T[this->n];
        }
        this->allocated = true;
    }
    void deleteDoublePointer() {
        int i;
        for (i=0; i<this->m; i++) {
            delete this->a[i];
        }
        delete this->a;
    }
    
    Matrix operator+ (const Matrix other) const {
        assert(this->m == other.m && this->n == other.n);
        Matrix ret = Matrix(this->m, this->n);
        
        int i,j;
        for (i=0; i<m; i++) {
            for (j=0; j<n; j++) {
                ret.a[i][j] = this->a[i][j] + other.a[i][j];
            }
        }
        return ret;
    }
    Matrix operator- (const Matrix other) const {
        assert(this->m == other.m && this->n == other.n);
        Matrix ret = Matrix(this->m, this->n);
        
        int i,j;
        for (i=0; i<m; i++) {
            for (j=0; j<n; j++) {
                ret.a[i][j] = this->a[i][j] - other.a[i][j];
            }
        }
        return ret;
    }
    Matrix operator* (const Matrix other) const {
        assert(this->n == other.m);
        Matrix ret = Matrix(this->m, other.n);
        
        int i, j, k;
        for (i=0; i<this->m; i++) {
            for (j=0; j<other.n; j++) {
                ret.a[i][j] = 0;
                for (k=0; k<this->n; k++) {
                    ret.a[i][j] += this->a[i][k] * other.a[k][j];
                }
            }
        }
        return ret;
    }
    Matrix Inverse() {
        
    }
    T det() {
        assert(this->m == this->n);
        bool sign = true; //true : +, false : -
        Matrix tm = (*this);
        
        int i,j, k;
        for (i=0; i<tm.m; i++) {
            if (tm.a[i][i] == 0) {
            
                bool flag = false;
                for (j=i; j<tm.m; j++) {
                    if (tm.a[j][i] != 0) {
                        //switch i-th row and j-th row. starts with i since the previous elements are all zero.
                        for (k=j; k<this->m; k++) {
                            T t = tm.a[i][k]; tm.a[i][k] = tm.a[j][k]; tm.a[j][k] = t;
                            flag = true;
                            sign = !sign;
                            break;
                        }
                    }
                }
                
                if (!flag) return 0;
            }
            //pivot row is i-th row
            for (j=i+1; j<tm.m; j++) {
                T val_i = tm.a[i][i];
                T val_j = tm.a[j][i];
                T co = val_j  / val_i;
                
                for (k=i; k<tm.m; k++) {
                    tm.a[j][k] -= co * tm.a[i][k];
                }
            }
        }
        T ret= T(1);
        for (i=0; i<tm.m; i++) {
            ret *= tm.a[i][i];
        }
        return ret * ( sign? 1:-1);
    }
};