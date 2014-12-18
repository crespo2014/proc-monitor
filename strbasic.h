/*
 * strbasic.h
 *  String basic manipulation.
 *  Created on: 18 Dec 2014
 *      Author: lester
 */

#ifndef STRBASIC_H_
#define STRBASIC_H_

#include <cctype>
#include <cstring>

/**
 * String Iterator use to extract information in column mode
 * template using max number of columns
 */

template<int N = 2>
class strRowSplit
{
    enum class _chartype
    {
        none, end_col, end_row, end_str,
    };
    char* col[N];
    const char end_col_;    //column delimiter
    const char end_row_;    // row delimiter
    char * data_;
    _chartype type_ = _chartype::none;    // las character type read

    void clear()
    {
        for (unsigned i = 0; i < N; ++i)
            col[i] = "";
    }
    _chartype nextToken()
    {
        while (*data_)
        {
            if (*data_ == end_col_)
                return _chartype::end_col;
            if (*data_ == end_row_)
                return _chartype::end_row;
            data_++;
        }
        return _chartype::end_str;
    }
public:
    strRowSplit(char* data, char endcol, char endrow = '\n') :
            data_(data), end_col_(endcol), end_row_(endrow)
    {
    }

    /**
     * go to next column
     * @return false y there is not more
     */
    bool next()
    {
        // test end of string
        if ((type_ == _chartype::end_str) || (*data_ == 0))
            return false;
        clear();
        unsigned pos = 0;
        // walk until eos or max columns
        while (pos < N)
        {
            col[pos++] = data_;
            type_ = nextToken();
            if (type_ == _chartype::end_str)
                return true;
            *data_ = 0;
            data_++;
            if (type_ == _chartype::end_row)
                return true;
        }
        // walk until end of row or end of string
        do
        {
            type_ = nextToken();
            if (type_ == _chartype::end_row)
                *data_ = 0;
            data_++;
        } while (type_ != _chartype::end_str);
        return true;
    }
    char* get(unsigned pos)
    {
        if (pos >= N)
            return "";
        return col[pos];
    }
};

#endif /* STRBASIC_H_ */
