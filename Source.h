/*
 * Source.h
 *
 *  Created on: 15 Jan 2015
 *      Author: lester
 */

#ifndef SOURCE_H_
#define SOURCE_H_

#include <sstream>
#include <string>
#include <vector>
#include "strbasic.h"
#include "Item.h"

class iSource
{
public:
    // source of data
    enum class source_e
    {
        none, io,     // io status
        cpu,   // cpu
        mem  // memory
    };
    iSource(source_e type, const char* proc_file) :
            type_(type), proc_file_name_(proc_file)
    {

    }
    virtual const char* const * get(const char* name) = 0;
    virtual void load() = 0;
    virtual void getItems(std::vector<Item>& v) = 0;

    template<class T>
    void bind(T pid)
    {
        std::stringstream ss;
        ss << "/proc/" << pid << "/" << proc_file_name_;
        file_path_ = ss.str();
    }
    source_e getType() const
    {
        return type_;
    }
protected:
    ~iSource()
    {
    }
    void setFilePath(const std::string& fp)
    {
        file_path_ = fp;
    }
    char* loadFile();
    std::string file_path_;
    source_e type_;
    char raw_[2 * 1024];
private:
    const char* proc_file_name_;
};

/**
 *     proc/self/status
 *     (1) pid  %d
 *     (2) comm  %s
 *     (3) state  %c
 *     (4) ppid  %d
 *     (5) pgrp  %d
 *     (6) session  %d
 *     (7) tty_nr  %d
 *     (8) tpgid  %d
 *     (9) flags  %u
 *     (10) minflt  %lu
 *     (11) cminflt  %lu
 *     (12) majflt  %lu
 *     (13) cmajflt  %lu
 *     (14) utime  %lu
 *     (15) stime  %lu
 *     (16) cutime  %ld
 *     (17) cstime  %ld
 *     (18) priority  %ld
 *     (19) nice  %ld
 *     (20) num_threads  %ld
 *     (21) itrealvalue  %ld
 *     (22) starttime  %llu
 *     (23) vsize  %lu
 *     (24) rss  %ld
 *     (25) rsslim  %lu
 *     (26) startcode  %lu
 *     (27) endcode  %lu
 *     (28) startstack  %lu
 *     (29) kstkesp  %lu
 *     (30) kstkeip  %lu
 *     (31) signal  %lu
 *     (32) blocked  %lu
 *     (33) sigignore  %lu
 *     (34) sigcatch  %lu
 *     (35) wchan  %lu
 *     (36) nswap  %lu
 *     (37) cnswap  %lu
 *     (38) exit_signal  %d  (since Linux 2.1.22)
 *     (39) processor  %d  (since Linux 2.2.8)
 *     (40) rt_priority  %u  (since Linux 2.5.19)
 *     (41) policy  %u  (since Linux 2.5.19)
 *     (42) delayacct_blkio_ticks  %llu  (since Linux 2.6.18)
 *     (43) guest_time  %lu  (since Linux 2.6.24)
 *     (44) cguest_time  %ld  (since Linux 2.6.24)
 *     (45) start_data  %lu  (since Linux 3.3)
 *     (46) end_data  %lu  (since Linux 3.3)
 *     (47) start_brk  %lu  (since Linux 3.3)
 *     (48) arg_start  %lu  (since Linux 3.5)
 *     (49) arg_end  %lu  (since Linux 3.5)
 *     (50) env_start  %lu  (since Linux 3.5)
 *     (51) env_end  %lu  (since Linux 3.5)
 *     (52) exit_code  %d  (since Linux 3.5)
 */
class CPUSource: public iSource
{
    static const unsigned item_count = 52;
    const char* proc_file_s = "stat";
    strRowSplit<item_count + 1> data_;
    static const char* items_[item_count + 1];
public:
    CPUSource();
    virtual const char* const * get(const char* name);
    virtual void getItems(std::vector<Item>& v);
    virtual void load();
    virtual ~CPUSource()
    {
    }
};

class MemSource: public iSource
{
    static const unsigned item_count = 50;
    static const char* items_[item_count];
    const char* proc_file_s = "status";
    strRowColumnSplit<item_count, 3> data_;
public:
    MemSource();
    virtual const char* const * get(const char* name);
    virtual void getItems(std::vector<Item>& v);
    virtual void load();
    virtual ~MemSource(){}
};
/*
 * rchar: 1299
 wchar: 0
 syscr: 7
 syscw: 0
 read_bytes: 0
 write_bytes: 0
 cancelled_write_bytes: 0
 */
class IOSource: public iSource
{
    static const unsigned item_count = 10;
    const char* proc_file_s = "io";
    strRowColumnSplit<item_count, 3> data_;
    static const char* items_[item_count];
public:
    IOSource();
    virtual const char* const * get(const char* name);
    virtual void getItems(std::vector<Item>& v);
    virtual void load();
    virtual ~IOSource(){}
};

#endif /* SOURCE_H_ */
