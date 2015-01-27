/*
 * Source.cpp
 *
 *  Created on: 15 Jan 2015
 *      Author: lester
 */

#include <sstream>

#include "memory.h"
#include "Source.h"

using namespace std;

CPUSource::CPUSource() :
        iSource(source_e::cpu, proc_file_s), data_(' ')
{
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
    data_.reset(loadFile());
    do
    {
    } while (data_.next());
}

void CPUSource::getItems(std::vector<std::shared_ptr<BaseItem> >& v)
{
    for (const char** it = items_; *it != nullptr; ++it)
    {
        v.push_back(std::make_shared<BaseItem>(*it, *this,*it));
    }
}

char* iSource::loadFile()
{
    auto fd = ::open(file_path_.c_str(), O_RDONLY);
    auto len = ::read(fd, raw_, sizeof(raw_) - 1);
    close(fd);
    raw_[len] = 0;
    return raw_;
}

const char* MemSource::items_[] = { "FDSize", "VmPeak", "VmSize", "VmLck", "VmPin", "VmHWM", "VmRSS", "VmData", "VmStk", "VmExe", "VmLib", "VmPTE", "VmSwap", "Threads", "nonvoluntary_ctxt_switches",
        "voluntary_ctxt_switches", "Mems_allowed_list", "Mems_allowed", "Cpus_allowed_list", "Cpus_allowed", nullptr };

MemSource::MemSource() :
        iSource(source_e::mem, proc_file_s), data_(':')
{

}

const char* const * MemSource::get(const char* name)
{
    for (unsigned i = 0; i < item_count; ++i)
    {
        if (strcmp(data_.get(i, 0), name) == 0)
            return data_.getRawPointer(i, 1);
    }
    return nullptr;
}

void MemSource::getItems(std::vector<std::shared_ptr<BaseItem> >& v)
{
    for (const char** it = items_; *it != nullptr; ++it)
    {
        v.push_back(std::make_shared<BaseItem>(*it, *this,*it));
    }
}

void MemSource::load()
{
    data_.reset(loadFile());
    do
    {
    } while (data_.next());
}

const char* IOSource::items_[] = { "rchar", "wchar", "syscr", "syscw", "read_bytes", "write_bytes", "cancelled_write_bytes", nullptr };
IOSource::IOSource() :
        iSource(source_e::io, proc_file_s), data_(':')
{
}

const char* const * IOSource::get(const char* name)
{
    for (unsigned i = 0; i < item_count; ++i)
    {
        if (strcmp(data_.get(i, 0), name) == 0)
            return data_.getRawPointer(i, 1);
    }
    return nullptr;
}

void IOSource::getItems(std::vector<std::shared_ptr<BaseItem> >& v)
{
    for (const char** it = items_; *it != nullptr; ++it)
    {
        v.push_back(make_shared<AcumulativetoSpeedItem>(*it, *this,*it,1000));       // clock is millisecond base
    }
}

void IOSource::load()
{
    data_.reset(loadFile());
    do
    {
    } while (data_.next());
}

