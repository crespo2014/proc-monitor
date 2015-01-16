/*
 * Item.h
 *
 *  Created on: 15 Jan 2015
 *      Author: lester
 */

#ifndef ITEM_H_
#define ITEM_H_

#include "memory"

class iSource;

class Item
{
    iSource& source_;
    const char* name_;
    const char* const* v = nullptr;
public:
    Item(const char* name, iSource& source) : source_(source),name_(name)
    {

    }
    /// Get the index of the element in the source
    void bind();
    virtual ~Item() {}
    const char *get()
    {
        return ((v != nullptr) && (*v != nullptr) ? *v : "");
    }
    iSource& getSource() const
    {
        return source_;
    }
    const char* getName() const
    {
        return name_;
    }
};

//class CharItem
//{
//    const char** v = nullptr;
//public:
//    void bind(const char** b)
//    {
//        v = b;
//    }
//
//};

#endif /* ITEM_H_ */
