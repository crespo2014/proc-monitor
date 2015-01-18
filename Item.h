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
    virtual void bind() = 0;
    virtual const char *get() const = 0;
    virtual iSource& getSource() const = 0;
    virtual const char* getName() const = 0;
    virtual ~iItem() {};
};

class BaseItem : public iItem
{
public:
    BaseItem(const char* name, iSource& source);
    /// Get pointer to value from source, read initial value
    void bind() override ;
    /// get current value as string
    const char *get() const override ;
    iSource& getSource() const override;
    const char* getName() const override;
    virtual ~BaseItem();
protected:

    const char* name_;
    iSource& source_;
    const char* const * v = nullptr;
private:
};


#endif /* ITEM_H_ */
