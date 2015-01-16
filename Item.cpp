/*
 * Item.cpp
 *
 *  Created on: 15 Jan 2015
 *      Author: lester
 */

#include "Item.h"
#include "Source.h"


void Item::bind()
{
    v = source_.get(name_);
}

//Item::~Item()
//{
//    // TODO Auto-generated destructor stub
//}

