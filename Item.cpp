/*
 * Item.cpp
 *
 *  Created on: 15 Jan 2015
 *      Author: lester
 */

#include <cstdio>
#include "Item.h"
#include "Source.h"

void BaseItem::bind(unsigned long long time)
{
    v = source_.get(name_);
}

BaseItem::BaseItem(const char* name, iSource& source) :
        name_(name), source_(source)
{
}

iSource& BaseItem::getSource() const
{
    return source_;
}
const char* BaseItem::getName() const
{
    return name_;
}

const char* BaseItem::get(unsigned long long time)
{
    return ((v != nullptr) && (*v != nullptr) ? *v : "");
}

BaseItem::~BaseItem()
{
}

SpeedItem::SpeedItem(const char* name, iSource& src, unsigned interval, float factor) : BaseItem(name,src),factor_(factor),interval_(interval)
{
}

const char* SpeedItem::get(unsigned long long time)
{
    float f;
    if (sscanf(BaseItem::get(time), "%f", &f) == 1)
    {
        acumulative_ += f;
        if (time - start_time_ > interval_)
        {
            float v = acumulative_ / (time - start_time_);
            snprintf(val_, sizeof(val_) - 1, "%f", v);
            acumulative_ = 0;
            start_time_ = time;
        }
    }
    return val_;
}

AcumulativetoSpeedItem::AcumulativetoSpeedItem(const char* name, iSource& src, unsigned interval, float factor) : BaseItem(name,src),factor_(factor),interval_(interval)
{
}

const char* AcumulativetoSpeedItem::get(unsigned long long time)
{
    float f;
    if (sscanf(BaseItem::get(time), "%f", &f) == 1)
    {
        if (time - start_time_ > interval_)
        {
            float v = (f - acumulative_) / (time - start_time_);
            snprintf(val_, sizeof(val_) - 1, "%f", v);
            acumulative_ = f;
            start_time_ = time;
        }
    }
    return val_;
}

void SpeedItem::bind(unsigned long long time)
{
    BaseItem::bind(time);
    start_time_ = time;
}

void AcumulativetoSpeedItem::bind(unsigned long long time)
{
    BaseItem::bind(time);
    start_time_ = time;
}
