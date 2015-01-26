/*
 * main.cpp
 *
 *  Created on: 18 Dec 2014
 *      Author: lester
 */

#include <list>
#include <vector>
#include <chrono>
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
    ProcessInfo self(2879);
    std::vector<const char*> names { "utime", "VmPeak","stime","rchar","wchar","read_bytes","write_bytes","syscr","syscr"};
    for (auto nm : names)
    {
        self.addItem(nm);
    }
    auto start = std::chrono::high_resolution_clock::now();
    self.bindAll();
    self.printHeader(std::cout);
    //Running
    while (true)
    {
        auto diff_ms = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - start);
        self.load();
        std::cout << diff_ms.count() << ';';
        self.printItems(std::cout,diff_ms.count());
    }
}
