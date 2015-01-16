/*
 * procstat.h
 *
 * Process status data and type
 *
 *  Created on: 19 Dec 2014
 *      Author: lester
 */

#ifndef PROCSTAT_H_
#define PROCSTAT_H_

#include <vector>



enum class data_type
{

};

// todo make item auto read from source.
// make source be able to read itself
// prebuild lookat table for items.

class procStat
{
    std::vector<data_source> srcs_;
    // active inputs
    // actived items
public:
    procStat(): srcs_(5) {}
    void addSource(data_source s)
    {
        for (auto v : srcs_)
        {
            if (v == s) return;
        }
        srcs_.push_back(s);
    }
    void addItem();
};



#endif /* PROCSTAT_H_ */
