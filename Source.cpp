/*
 * Source.cpp
 *
 *  Created on: 15 Jan 2015
 *      Author: lester
 */

#include <sstream>

#include "memory.h"
#include "Source.h"

CPUSource::CPUSource() :
        iSource(source_e::cpu), data_(' ')
{
}

void CPUSource::bindPid(unsigned pid)
{
    std::stringstream ss;
    ss << "/proc/" << pid << "/stat";
    file_ = ss.str();
}

const char* const * CPUSource::get(const char* name)
{
    const char** it = items_;
    unsigned idx = 0;
    while (*it != nullptr)
    {
        if (strcmp(name, *it) == 0)
            return data_.getRawData() + idx;
        ++it;
        ++idx;
    }
    return nullptr;
}

const char* CPUSource::items_[] = { "pid", "name", "state", "ppid", "pgrp", "session", "tty_nr", "tpgid", "flags", "minflt", "cminflt", "majflt", "cmajflt", "utime", "stime", "cutime", "cstime",
        "priority", "nice", "num_threads", "itrealvalue", "starttime", "vsize", "rss", "rsslim", nullptr };

void CPUSource::load()
{
    auto fd = ::open(file_.c_str(), O_RDONLY);
    auto len = ::read(fd, raw_, sizeof(raw_));
    raw_[len] = 0;
    close(fd);
    data_.reset(raw_);
    do
    {
    } while (data_.next());
}

void CPUSource::getItems(std::vector<Item>& v)
{
    for (const char** it = items_; *it != nullptr; ++it)
    {
        v.push_back(Item(*it, *this));
    }
}
