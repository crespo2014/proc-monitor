/*
 * main.cpp
 *
 *  Created on: 18 Dec 2014
 *      Author: lester
 */


#include "strbasic.h"
#include <iostream>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main()
{
    char f[1024];

    auto fd = ::open("/proc/self/status",O_RDONLY);

    auto len = ::read(fd,f,sizeof(f));
    f[len] = 0;
    close(fd);

    strRowColumnSplit<15,2> rc_str(f,':','\n');

    strRowSplit<3> str(f,'.','\n');
    while (str.next())
    {
        std::cout << str.get(0) << std::endl;
        std::cout << str.getRemainder() << std::endl;
    }
}
