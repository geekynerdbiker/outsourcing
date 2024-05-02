#! /usr/bin/env python3

from __future__ import print_function
import sys
from optparse import OptionParser
import random


# to make Python2 and Python3 act the same -- how dumb
def random_seed(seed):
    try:
        random.seed(seed, version=1)
    except:
        random.seed(seed)
    return


parser = OptionParser()
parser.add_option("-s", "--seed", default=0, help="the random seed", action="store", type="int", dest="seed")
parser.add_option("-j", "--jobs", default=3, help="number of jobs in the system", action="store", type="int",
                  dest="jobs")
parser.add_option("-a", "--arrival", default=0, help="set arrival time", type="string", dest="arrivals")
parser.add_option("-l", "--jlist", default="",
                  help="instead of random jobs, provide a comma-separated list of run times", action="store",
                  type="string", dest="jlist")
parser.add_option("-m", "--maxlen", default=10, help="max length of job", action="store", type="int", dest="maxlen")
parser.add_option("-p", "--policy", default="FIFO", help="sched policy to use: SJF, FIFO, RR", action="store",
                  type="string", dest="policy")
parser.add_option("-q", "--quantum", help="length of time slice for RR policy", default=1, action="store", type="int",
                  dest="quantum")
parser.add_option("-c", help="compute answers for me", action="store_true", default=False, dest="solve")

(options, args) = parser.parse_args()
options.arrivals = options.arrivals.split(',')

for i in range(len(options.arrivals)):
    options.arrivals[i] = int(options.arrivals[i])

if len(options.arrivals) > options.jobs:
    parser.error('Arrival times cannot be more than job num.')

while len(options.arrivals) < options.jobs:
    options.arrivals.append('0')
random_seed(options.seed)

print('ARG policy', options.policy)
if options.jlist == '':
    print('ARG jobs', options.jobs)
    print('ARG arrivals', options.arrivals)
    print('ARG maxlen', options.maxlen)
    print('ARG seed', options.seed)
else:
    print('ARG jlist', options.jlist)
print('')

print('Here is the job list, with the run time of each job: ')

import operator

joblist = []
if options.jlist == '':
    for jobnum in range(0, options.jobs):
        runtime = int(options.maxlen * random.random()) + 1
        arrival = options.arrivals[jobnum]
        joblist.append([jobnum, runtime, arrival])
        print('  Job', jobnum, '( length = ' + str(runtime) + ', arrival time = ' + str(arrival) + ' )')
else:
    jobnum = 0
    for runtime in options.jlist.split(','):
        arrival = options.arrivals[jobnum]
        joblist.append([jobnum, float(runtime), arrival])
        jobnum += 1
    for job in joblist:
        print('  Job', job[0], '( length = ' + str(job[1]) + ', arrival time = ' + str(job[2]) + ' )')
print('\n')

if options.solve == True:
    print('** Solutions **\n')
    if options.policy == 'SJF':
        joblist = sorted(joblist, key=operator.itemgetter(1))
        options.policy = 'FIFO'

    if options.policy == 'FIFO':
        thetime = 0
        print('Execution trace:')
        for job in joblist:
            print('  [ time %3d ] Run job %d for %.2f secs ( DONE at %.2f )' % (
                thetime + job[2], job[0], job[1], thetime + job[1] + job[2]))
            thetime += job[1] + job[2]

        print('\nFinal statistics:')
        t = 0.0
        count = 0
        turnaroundSum = 0.0
        waitSum = 0.0
        responseSum = 0.0
        for tmp in joblist:
            jobnum = tmp[0]
            runtime = tmp[1]

            response = t + tmp[2]
            turnaround = t + runtime + tmp[2]
            wait = t + tmp[2]
            print('  Job %3d -- Response: %3.2f  Turnaround %3.2f  Wait %3.2f' % (jobnum, response, turnaround, wait))
            responseSum += response
            turnaroundSum += turnaround
            waitSum += wait
            t += runtime
            count = count + 1
        print('\n  Average -- Response: %3.2f  Turnaround %3.2f  Wait %3.2f\n' % (
            responseSum / count, turnaroundSum / count, waitSum / count))

    if options.policy == 'STCF':
        print('Execution trace:')
        turnaround = {}
        response = {}
        lastran = {}
        wait = {}
        quantum = float(options.quantum)
        jobcount = len(joblist)
        for i in range(0, jobcount):
            lastran[i] = 0.0
            wait[i] = 0.0
            turnaround[i] = 0.0
            response[i] = -1

        runlist = []
        waitlist = []
        order = []

        for e in joblist:
            if e[2] == 0:
                runlist.append(e)
            else:
                waitlist.append(e)

        waitlist.sort(key=lambda x: x[2])

        thetime = 0.0
        while jobcount > 0:
            if waitlist:
                next = waitlist[0]
                if thetime >= next[2]:
                    runlist.append(waitlist.pop(0))
                if not runlist:
                    runlist.append(waitlist.pop(0))
                    while thetime < next[2]:
                        print('  [ time %3d ] Wait for next process for %.2f secs' % (thetime, quantum))
                        thetime += quantum
            runlist.sort(key=lambda x: x[1])
            job = runlist.pop(0)
            jobnum = job[0]
            runtime = float(job[1])
            if response[jobnum] == -1:
                response[jobnum] = thetime
            currwait = thetime - lastran[jobnum]
            wait[jobnum] += currwait

            if job[2] > thetime:
                thetime += quantum
                runlist.append(job)
                continue
            if runtime > quantum:
                runtime -= quantum
                ranfor = quantum
                print('  [ time %3d ] Run job %3d for %.2f secs' % (thetime, jobnum, ranfor))
                runlist.append([jobnum, runtime, job[2]])
            else:
                ranfor = runtime
                print('  [ time %3d ] Run job %3d for %.2f secs ( DONE at %.2f )' % (
                    thetime, jobnum, ranfor, thetime + ranfor))
                turnaround[jobnum] = thetime + ranfor
                jobcount -= 1
            thetime += ranfor
            lastran[jobnum] = thetime

        print('\nFinal statistics:')
        turnaroundSum = 0.0
        waitSum = 0.0
        responseSum = 0.0
        for i in range(0, len(joblist)):
            turnaroundSum += turnaround[i]
            responseSum += response[i]
            waitSum += wait[i]
            print(
                '  Job %3d -- Response: %3.2f  Turnaround %3.2f  Wait %3.2f' % (i, response[i], turnaround[i], wait[i]))
        count = len(joblist)

        print('\n  Average -- Response: %3.2f  Turnaround %3.2f  Wait %3.2f\n' % (
            responseSum / count, turnaroundSum / count, waitSum / count))

    if options.policy == 'RR':
        print('Execution trace:')
        turnaround = {}
        response = {}
        lastran = {}
        wait = {}
        quantum = float(options.quantum)
        jobcount = len(joblist)
        for i in range(0, jobcount):
            lastran[i] = 0.0
            wait[i] = 0.0
            turnaround[i] = 0.0
            response[i] = -1

        runlist = []
        waitlist = []
        order = []

        for e in joblist:
            if e[2] == 0:
                runlist.append(e)
            else:
                waitlist.append(e)

        waitlist.sort(key=lambda x: x[2])

        thetime = 0.0
        while jobcount > 0:
            if waitlist:
                next = waitlist[0]
                if thetime >= next[2]:
                    runlist.append(waitlist.pop(0))
                if runlist:
                    runlist.append(waitlist.pop(0))
                    while thetime < next[2]:
                        print('  [ time %3d ] Wait for next process for %.2f secs' % (thetime, quantum))
                        thetime += quantum
            job = runlist.pop(0)
            jobnum = job[0]
            runtime = float(job[1])
            if response[jobnum] == -1:
                response[jobnum] = thetime
            currwait = thetime - lastran[jobnum]
            wait[jobnum] += currwait

            if job[2] > thetime:
                thetime += quantum
                runlist.append(job)
                continue
            if runtime > quantum:
                runtime -= quantum
                ranfor = quantum
                print('  [ time %3d ] Run job %3d for %.2f secs' % (thetime, jobnum, ranfor))
                runlist.append([jobnum, runtime, job[2]])
            else:
                ranfor = runtime
                print('  [ time %3d ] Run job %3d for %.2f secs ( DONE at %.2f )' % (
                    thetime, jobnum, ranfor, thetime + ranfor))
                turnaround[jobnum] = thetime + ranfor
                jobcount -= 1
            thetime += ranfor
            lastran[jobnum] = thetime

        print('\nFinal statistics:')
        turnaroundSum = 0.0
        waitSum = 0.0
        responseSum = 0.0
        for i in range(0, len(joblist)):
            turnaroundSum += turnaround[i]
            responseSum += response[i]
            waitSum += wait[i]
            print(
                '  Job %3d -- Response: %3.2f  Turnaround %3.2f  Wait %3.2f' % (i, response[i], turnaround[i], wait[i]))
        count = len(joblist)

        print('\n  Average -- Response: %3.2f  Turnaround %3.2f  Wait %3.2f\n' % (
            responseSum / count, turnaroundSum / count, waitSum / count))


    if options.policy != 'FIFO' and options.policy != 'SJF' and options.policy != 'RR' and options.policy != 'STCF':
        print('Error: Policy', options.policy, 'is not available.')
        sys.exit(0)
else:
    print('Compute the turnaround time, response time, and wait time for each job.')
    print('When you are done, run this program again, with the same arguments,')
    print('but with -c, which will thus provide you with the answers. You can use')
    print('-s <somenumber> or your own job list (-l 10,15,20 for example)')
    print('to generate different problems for yourself.')
    print('')
