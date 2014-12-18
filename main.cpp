/*
 * main.cpp
 *
 *  Created on: 18 Dec 2014
 *      Author: lester
 */


#include "strbasic.h"

int main()
{
    char str1[] = "isasdjs. slkdlsl. sds .....\n.........\n............";
    strRowSplit<10> str(str1,'.','\n');
    while (str.next())
    {

    }
}
