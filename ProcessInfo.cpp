/*
 * ProcessInfo.cpp
 *
 *  Created on: 16 Jan 2015
 *      Author: lester
 */

#include "ProcessInfo.h"

ProcessInfo::ProcessInfo(unsigned pid) :
        pid_(pid)
{
    for (auto & src : sources_)
    {
        src.second->bind(pid);
        src.second->getItems(all_items_);
    }
}

ProcessInfo::~ProcessInfo()
{
    // TODO Auto-generated destructor stub
}

void ProcessInfo::addItem(const char* item_name)
{
    BaseItem* ni = nullptr;
    for (auto &it : all_items_)
    {
        if (strcmp(it.getName(), item_name) == 0)
        {
            ni = &it;
            for (auto& p : sources_)
            {
                if (p.second->getType() == ni->getSource().getType())
                {
                    p.first = true;
                    break;
                }
            }
            active_items.push_back(ni);
            return;
        }
    }
    throw std::bad_alloc();
}

void ProcessInfo::bindAll()
{
    for (auto& p : sources_)
    {
        if (p.first)
            p.second->load();
    }
    for (auto i : active_items)
    {
        i->bind();
    }
}

void ProcessInfo::printHeader(std::ostream& os)
{
    bindAll();
    auto it = active_items.begin();
    if (it != active_items.end())
        os << (*it)->getName();
    ++it;
    for (; it != active_items.end(); ++it)
    {
        os << sep_c << (*it)->getName();   //todo define separator as const
    }
    os << std::endl;
}

void ProcessInfo::printItems(std::ostream& os)
{
    auto it = active_items.begin();
    if (it != active_items.end())
        os << (*it)->get(0);
    ++it;
    for (; it != active_items.end(); ++it)
    {
        os << sep_c << (*it)->get(0);   //todo define separator as const
    }
    os << std::endl;
}

void ProcessInfo::load()
{
    for (auto& p : sources_)
    {
        if (p.first)
            p.second->load();
    }
}
