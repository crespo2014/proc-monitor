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
    iSource(source_e type) :
            type_(type)
    {

    }
    virtual const char* const* get(const char* name) = 0;
    virtual void load() = 0;
    virtual void getItems(std::vector<Item>& v) = 0;
    source_e getType() const
    {
        return type_;
    }
protected:
    ~iSource()
    {
    }
    ;
    source_e type_;
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
 The bitmap of pending signals, displayed as a
 decimal number.  Obsolete, because it does not
 provide information on real-time signals; use
 /proc/[pid]/status instead.

 (32) blocked  %lu
 The bitmap of blocked signals, displayed as a
 decimal number.  Obsolete, because it does not
 provide information on real-time signals; use
 /proc/[pid]/status instead.

 (33) sigignore  %lu
 The bitmap of ignored signals, displayed as a
 decimal number.  Obsolete, because it does not
 provide information on real-time signals; use
 /proc/[pid]/status instead.

 (34) sigcatch  %lu
 The bitmap of caught signals, displayed as a decimal
 number.  Obsolete, because it does not provide
 information on real-time signals; use
 /proc/[pid]/status instead.

 (35) wchan  %lu
 This is the "channel" in which the process is
 waiting.  It is the address of a location in the
 kernel where the process is sleeping.  The
 corresponding symbolic name can be found in
 /proc/[pid]/wchan.

 (36) nswap  %lu
 Number of pages swapped (not maintained).

 (37) cnswap  %lu
 Cumulative nswap for child processes (not
 maintained).

 (38) exit_signal  %d  (since Linux 2.1.22)
 Signal to be sent to parent when we die.

 (39) processor  %d  (since Linux 2.2.8)
 CPU number last executed on.

 (40) rt_priority  %u  (since Linux 2.5.19)
 Real-time scheduling priority, a number in the range
 1 to 99 for processes scheduled under a real-time
 policy, or 0, for non-real-time processes (see
 sched_setscheduler(2)).

 (41) policy  %u  (since Linux 2.5.19)
 Scheduling policy (see sched_setscheduler(2)).
 Decode using the SCHED_* constants in linux/sched.h.

 The format for this field was %lu before Linux
 2.6.22.

 (42) delayacct_blkio_ticks  %llu  (since Linux 2.6.18)
 Aggregated block I/O delays, measured in clock ticks
 (centiseconds).

 (43) guest_time  %lu  (since Linux 2.6.24)
 Guest time of the process (time spent running a
 virtual CPU for a guest operating system), measured
 in clock ticks (divide by sysconf(_SC_CLK_TCK)).

 (44) cguest_time  %ld  (since Linux 2.6.24)
 Guest time of the process's children, measured in
 clock ticks (divide by sysconf(_SC_CLK_TCK)).

 (45) start_data  %lu  (since Linux 3.3)
 Address above which program initialized and
 uninitialized (BSS) data are placed.

 (46) end_data  %lu  (since Linux 3.3)
 Address below which program initialized and
 uninitialized (BSS) data are placed.

 (47) start_brk  %lu  (since Linux 3.3)
 Address above which program heap can be expanded
 with brk(2).

 (48) arg_start  %lu  (since Linux 3.5)
 Address above which program command-line arguments
 (argv) are placed.

 (49) arg_end  %lu  (since Linux 3.5)
 Address below program command-line arguments (argv)
 are placed.

 (50) env_start  %lu  (since Linux 3.5)
 Address above which program environment is placed.

 (51) env_end  %lu  (since Linux 3.5)
 Address below which program environment is placed.

 (52) exit_code  %d  (since Linux 3.5)
 The thread's exit status in the form reported by
 waitpid(2).
 */
class CPUSource: public iSource
{
    static const unsigned item_count = 52;
    std::string file_;
    char raw_[1024];
    strRowSplit<item_count + 1> data_;
    static const char* items_[item_count];
public:
    CPUSource();
    void bindPid(unsigned pid);
    virtual const char* const* get(const char* name);
    virtual void getItems(std::vector<Item>& v);
    virtual void load();
    virtual ~CPUSource()
    {
    }
    template<class T>
    void bind(T pid)
    {
        std::stringstream ss;
        ss << "/proc/" << pid << "/stat";
        file_ = ss.str();
    }
};

#endif /* SOURCE_H_ */
