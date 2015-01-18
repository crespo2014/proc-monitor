/*
 * Item.cpp
 *
 *  Created on: 15 Jan 2015
 *      Author: lester
 */

#include "Item.h"
#include "Source.h"

void BaseItem::bind()
{
    v = source_.get(name_);
}

BaseItem::BaseItem(const char* name, iSource& source) :
        name_(name), source_(source)
{
}

const char *BaseItem::get() const
{
    return ((v != nullptr) && (*v != nullptr) ? *v : "");
}
iSource& BaseItem::getSource() const
{
    return source_;
}
const char* BaseItem::getName() const
{
    return name_;
}

BaseItem::~BaseItem()
{
}
