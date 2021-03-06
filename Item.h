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

class iItem
{
public:
    virtual void bind(unsigned long long time) = 0;
    virtual const char *get(unsigned long long time)  = 0;
    virtual iSource& getSource() const = 0;
    virtual const char* getName() const = 0;
    virtual ~iItem() {};
};

class BaseItem : public iItem
{
public:
    BaseItem(const char* name, iSource& source,const char *display_name);

    virtual void bind(unsigned long long time) override ;        ///< Get pointer to value from source, read initial value
    virtual const char *get(unsigned long long time)  override ; ///< get current value as string
    virtual iSource& getSource() const override;
    virtual const char* getName() const override;                ///< get display name
    virtual ~BaseItem();
protected:
    const char* name_;          // name on source
    iSource& source_;
    const char* display_name_;  // name use by user
    const char* const * v = nullptr;
private:
};

// Item that calculate speed, it uses time interval and factor
class SpeedItem : public BaseItem
{
public:
    SpeedItem(const char* name,iSource& src,const char *display_name,unsigned interval = 1,float factor = 1.0);
    virtual const char *get(unsigned long long time)  override ;        ///< tell to item to pick value from source and calculate the new one
    virtual void bind(unsigned long long time) override ;               ///< Get pointer to value from source, read initial value
private:
    char val_[30];
    float factor_;
    unsigned interval_;
    float acumulative_ = 0;
    unsigned long long start_time_ = 0;
};

// This item received acumulative values every time and do calculation of speed
class AcumulativetoSpeedItem : public BaseItem
{
public:
    AcumulativetoSpeedItem(const char* name,iSource& src,const char *display_name,unsigned interval = 1,float factor = 1.0);

    virtual const char *get(unsigned long long time)  override ;    ///< tell to item to pick value from source and calculate the new one
    virtual void bind(unsigned long long time) override ;           ///< Get pointer to value from source, read initial value
private:
    char val_[30];
    float factor_;
    unsigned interval_;
    float acumulative_ = 0; // previous acumulative value
    unsigned long long start_time_ = 0;
};

// create a item that display name is different to name in  name

#endif /* ITEM_H_ */
