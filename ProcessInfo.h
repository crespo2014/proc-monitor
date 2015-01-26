/*
 * ProcessInfo.h
 *
 *  Created on: 16 Jan 2015
 *      Author: lester
 */

#ifndef PROCESSINFO_H_
#define PROCESSINFO_H_

#include <list>
#include <vector>
#include <iostream>
#include "Source.h"
#include "Item.h"

class ProcessInfo
{
public:
    ProcessInfo(unsigned pid);
    virtual ~ProcessInfo();
    void addItem(const char* item_name);
    void bindAll();
    void printHeader(std::ostream& os);
    void printItems(std::ostream& os, unsigned long long t);
    void load();

private:
    CPUSource cpu_;
    IOSource io_;
    MemSource mem_; //
    std::vector<std::pair<bool, iSource*> > sources_ { { false, &cpu_ }, { false, &io_ }, { false, &mem_ } };
    std::vector<BaseItem> all_items_;
    std::list<BaseItem*> active_items;

    unsigned pid_;
    constexpr static const char sep_c = ';';
};

#endif /* PROCESSINFO_H_ */
