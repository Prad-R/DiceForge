#include "basicfxn.h"

namespace DiceForge
{
    matrix_t::matrix_t(int r, int c)
        : r(r), c(c)
    {
        m = new real_t*[r];
        for (size_t i = 0; i < r; i++)
        {
            m[i] = new real_t[c];
            for (size_t j = 0; j < c; j++)
            {
                m[i][j] = 0;
            }
        }
    }

    matrix_t::matrix_t(matrix_t& other)
        : r(other.r), c(other.c)
    {
        m = new real_t*[r];
        for (size_t i = 0; i < r; i++)
        {
            m[i] = new real_t[c];
            for (size_t j = 0; j < c; j++)
            {
                m[i][j] = other.m[i][j];
            }
        }
    }

    matrix_t::~matrix_t()
    {
        for (size_t i = 0; i < r; i++)
        {
            delete[] m[i];
        }
        delete[] m;
    }

    const real_t* matrix_t::operator[](int i) const
    {
        return m[i];
    }

    real_t* matrix_t::operator[](int i)
    {
        return m[i];
    }

    matrix_t matrix_t::operator*(const matrix_t& other) const
    {
        matrix_t pdt = matrix_t(r, other.c);
        for (size_t i = 0; i < r; i++)
        {
            for (size_t j = 0; j < other.c; j++)
            {
                pdt[i][j] = 0;

                for (size_t k = 0; k < c; k++)
                {
                    pdt[i][j] += m[i][k] * other.m[k][j];
                }                    
            }
        }            

        return pdt;
    }

    matrix_t matrix_t::operator+(const matrix_t& other) const
    {
        matrix_t sum = matrix_t(r, c);
        for (size_t i = 0; i < r; i++)
        {
            for (size_t j = 0; j < c; j++)
            {
                sum.m[i][j] = m[i][j] + other.m[j][i];
            }
        }
        return sum;
    }

    matrix_t matrix_t::operator-(const matrix_t& other) const
    {
        matrix_t diff = matrix_t(r, c);
        for (size_t i = 0; i < r; i++)
        {
            for (size_t j = 0; j < c; j++)
            {
                diff.m[i][j] = m[i][j] - other.m[j][i];
            }
        }
        return diff;
    }

    matrix_t matrix_t::operator-() const
    {
        matrix_t neg = matrix_t(r, c);
        for (size_t i = 0; i < r; i++)
        {
            for (size_t j = 0; j < c; j++)
            {
                neg.m[i][j] = -m[i][j];
            }
        }
        return neg;
    }
    
    matrix_t matrix_t::transpose() const
    {
        matrix_t t = matrix_t(c, r);
        for (size_t i = 0; i < r; i++)
        {
            for (size_t j = 0; j < c; j++)
            {
                t.m[j][i] = m[i][j];
            }
        }

        return t;
    }
}
