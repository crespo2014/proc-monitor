/*
 * main.cpp
 *
 *  Created on: 18 Dec 2014
 *      Author: lester
 */


#include "strbasic.h"
#include <iostream>

int main()
{
    char str1[] = "   isasdjs  .     slkdlsl   .sds .....\n1 .2 .3 .4......\n5.6.7.8.9........";

    strRowColumnSplit<2,3> rc_str(str1,'.','\n');

    strRowSplit<3> str(str1,'.','\n');
    while (str.next())
    {
        std::cout << str.get(0) << std::endl;
        std::cout << str.getRemainder() << std::endl;
    }
}
