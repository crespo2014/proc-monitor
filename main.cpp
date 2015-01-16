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

#include "ProcessInfo.h"

int main()
{
    ProcessInfo self(getpid());

    std::vector<const char*> names { "utime", "VmPeak" };
    for (auto nm : names)
    {
        self.addItem(nm);
    }
    self.printHeader(std::cout);
    //Running
    while (true)
    {
        self.load();
        self.printItems(std::cout);
    }
}
