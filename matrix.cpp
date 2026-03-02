/**
 * @file matrix.cpp
 * @author Cameren Rowlette (crowlet6@ut.utm.edu)
 * @brief 
 * @version 0.1
 * @date 2026-02-26
 * 
 * @copyright Copyright (c) 2026
 * 
 */
#include "matrix.h"
#include <sstream>
#include <iomanip>

using namespace std;
 
Matrix::Matrix(unsigned int rows, unsigned int cols){
    m = rows;
    n = cols;
    ar = nullptr;

    if(m > 0 && n > 0){
        ar = new double*[m];
        for(int i = 0; i < m; ++i){
            ar[i] = new double[n];
            for(int j = 0; j < n; ++j){
                ar[i][j] = 0.0;
            }
        }
    }
}

Matrix::Matrix(const Matrix& rhs){
    m = rhs.m;
    n = rhs.n;
    ar = nullptr;

    if(m > 0 && n > 0){
        ar = new double*[m];
        for(int i = 0; i < m; ++i){
            ar[i] = new double[n];
            for(int j = 0; j < n; ++j){
                ar[i][j] = rhs.ar[i][j];
            }
        }
    }
}

Matrix::~Matrix(){
        for(int i = 0; i < m; ++i){
            delete[] ar[i];
        }
        delete[] ar;
        ar = nullptr;
}

int Matrix::getRows() const{
    return m;
}

int Matrix::getCols() const{
    return n;
}

double& Matrix::at(unsigned int row, unsigned int col){
    return ar[row][col];
}

const double& Matrix::at(unsigned int row, unsigned int col) const{
    return ar[row][col];
}

Matrix& Matrix::operator=(const Matrix& rhs){
    //a=b
    for(int i = 0; i < m; ++i){
            delete[] ar[i];
        }
    delete[] ar;
    m = rhs.m;
    n = rhs.n;
    
    if (m > 0 && n > 0) {
        ar = new double*[m];
        for (int i = 0; i < m; ++i) {
            ar[i] = new double[n];
            for (int j = 0; j < n; ++j) {
                ar[i][j] = rhs.ar[i][j];
            }
        }
    } else {
        ar = nullptr;
    }

    return *this;
}

Matrix operator+(const Matrix& m1, const Matrix& m2){
    Matrix result(m1.getRows(), m1.getCols());
    for(int i = 0; i < m1.getRows(); ++i){
        for(int j = 0; j < m1.getCols(); ++j){
            result.at(i, j) = m1.at(i, j) + m2.at(i, j);
        }
    }
    return result;
}

Matrix operator-(const Matrix& m1, const Matrix& m2){
    Matrix result(m1.getRows(), m1.getCols());
    for(int i = 0; i < m1.getRows(); ++i){
        for(int j = 0; j < m1.getCols(); ++j){
            result.at(i, j) = m1.at(i, j) - m2.at(i, j);
        }
    }
    return result;
}

Matrix operator*(const Matrix& m1, const Matrix& m2){
    Matrix result(m1.getRows(), m1.getCols());

    for(int i = 0; i < m1.getRows(); ++i){
        for(int j = 0; j < m2.getCols(); ++j){
            double sum = 0.0;
            for(int k = 0; k < m1.getCols(); ++k){
               sum += m1.at(i, k) * m2.at(k, j);
            }
            result.at(i, j) = sum;
        }
    }
    return result;
}

Matrix operator*(double scalar, const Matrix& m){
    Matrix result(m.getRows(), m.getCols());
    for(int i = 0; i < m.getRows(); ++i){
        for(int j = 0; j < m.getCols(); ++j){
            result.at(i, j) = m.at(i, j) * scalar;
        }
    }
    return result;
}

Matrix operator*(const Matrix& m, double scalar){
    Matrix result(m.getRows(), m.getCols());
    for(int i = 0; i < m.getRows(); ++i){
        for(int j = 0; j < m.getCols(); ++j){
            result.at(i, j) = m.at(i, j) * scalar;
        }
    }
    return result;
}

std::ostream& operator<<(std::ostream& os, const Matrix& m){

    for(int i = 0; i < m.getRows(); ++i){
        for(int j = 0; j < m.getCols(); ++j){
            os << std::setw(10) << m.at(i,j) << " ";
        }
        os << '\n';
    }
    os << '\n';
    return os;
}

std::istream& operator>>(std::istream& is, Matrix& m){
    for(int i = 0; i < m.getRows(); ++i){
        for(int j = 0; j < m.getCols(); ++j){
            is >> m.at(i,j);
        }
    }
    return is;
}