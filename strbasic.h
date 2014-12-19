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

template<int C = 2>
class strRowSplit
{
    enum class _chartype
    {
        none, end_col, end_row, end_str,
    };

    const char* col[C + 1];
    char * data_;
    const char end_col_;    // column delimiter
    const char end_row_;    // row delimiter
    _chartype type_ = _chartype::none;    // las character type read
    bool skipspace_ = true;
    bool trimspaces_ = true;

    void clear()
    {
        for (unsigned i = 0; i < C; ++i)
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
            if (*data_ == ' ' && trimspaces_)
                *data_ = 0;
            data_++;
        }
        return _chartype::end_str;
    }
    void skipSpaces()
    {
        while (skipspace_ && *data_ == ' ')
            ++data_;
    }
public:
    strRowSplit(char* data, char endcol, char endrow = '\n') :
            data_(data), end_col_(endcol), end_row_(endrow)
    {
    }
    void setSkipSpaces(bool b)
    {
        skipspace_ = b;
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
        while (pos < C)
        {
            skipSpaces();
            col[pos++] = data_;
            type_ = nextToken();
            if (type_ == _chartype::end_str)
                return true;
            *data_ = 0;
            data_++;
            if (type_ == _chartype::end_row)
                return true;
        }
        col[pos++] = data_;     //remained
        // walk until end of row or end of string
        do
        {
            type_ = nextToken();
            if (type_ == _chartype::end_str) break;
            if (type_ == _chartype::end_row)
                *data_ = 0;
            data_++;
        } while (type_ != _chartype::end_row);
        return true;
    }
    const char* get(unsigned pos)
    {
        if (pos >= C+1)
            return "";
        return col[pos];
    }
    const char* getRemainder() const
    {
        return data_;
    }
};

template<int R, int C>
class strRowColumnSplit
{
    const char* rc_[(R + 1)*(C + 1)];
    void clear()
    {
        for (const char** p = rc_; p < rc_ + (R + 1) * (C + 1); ++p)
            *p = "";
    }
public:
    strRowColumnSplit(char* data, char endcol, char endrow = '\n')
    {
        clear();
        strRowSplit<C> str(data, endcol, endrow);
        unsigned row = 0;
        while (row < R && str.next())
        {
            for (unsigned i = 0; i < C + 1; i++)
                rc_[row*(C+1)+i] = str.get(i);
            row++;
        }
        rc_[row*(C+1)] = str.getRemainder();
    }
    const char* get(unsigned r, unsigned c)
    {
        if ((r >= R + 1) || (c >= C + 1))
            return "";
        return rc_[r*(C+1)+c];
    }

};

#endif /* STRBASIC_H_ */
