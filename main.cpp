/*
 * main.cpp
 *
 *  Created on: 18 Dec 2014
 *      Author: lester
 */

#include <list>
#include <vector>
#include "strbasic.h"
#include <iostream>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "Source.h"
#include "Item.h"

void loadfile(const char* file, char* buffer, size_t max)
{
    auto fd = ::open("/proc/self/status", O_RDONLY);

    auto len = ::read(fd, buffer, max);
    buffer[len] = 0;
    close(fd);
}

int main()
{
    CPUSource cpu_src;

    std::vector<std::pair<bool, iSource*> > sources { { false, &cpu_src } };
    std::vector<Item> items { { "A", cpu_src } };

    std::list<Item*> active_items;
    std::list<iSource*> active_sources;

    // Initialization
    Item* ni = &items[0];

    for (auto p : sources)
    {
        if (p.second->getType() == ni->getSource().getType())
        {
            if (!p.first)
                active_sources.push_back(p.second);
            p.first = true;
            break;
        }
    }
    active_items.push_back(&items[0]);

    //Pre Running
    cpu_src.bind("self");
    for (auto p : active_sources)
    {
        p->load();
    }
    for (auto i : active_items)
    {
        i->bind();
    }

    //Running
    while (true)
    {
        auto it = active_items.begin();
        if (it != active_items.end())
            std::cout << (*it)->get();

        for (; it != active_items.end(); ++it)
        {
            std::cout << ";" << (*it)->get();   //todo define separator as const
        }
        for (auto p : active_sources)
        {
            p->load();
        }
    }

//    char f[1024];
//
//    auto fd = ::open("/proc/self/status", O_RDONLY);
//
//    auto len = ::read(fd, f, sizeof(f));
//    f[len] = 0;
//    close(fd);
//
//    strRowColumnSplit<15, 2> rc_str(f, ':', '\n');
//
//    strRowSplit<3> str('.', '\n');
//    str.reset(f);
//    while (str.next())
//    {
//        std::cout << str.get(0) << std::endl;
//        std::cout << str.getRemainder() << std::endl;
//    }
}
