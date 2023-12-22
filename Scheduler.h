/*********************************************
 * Implementation of the scheduling algorithms
 * - Shortest Job First (SJF)
 * - Least Laxity First (LLF)
 * - Earliest Deadline First (EDF)
 * - First Come First Serve (FCFS)
 * - Round Robin
**********************************************/


#include<vector>
#include "sorting.h"
#include "aux.h"

std::vector<Process> tmpProcs;


// Shortest Job First
void SJF (std::vector<Process> p) {

    tmpProcs = p;

    // List of all currently ready processes
    std::vector<Process> readyProcs;

    int clock = 0; // Time slice clock

    printf("\x1B[1mShortest Job First (SJF)\x1B[0m\n");

    // While the process list still contains elements
    while (!p.empty()) {
        readyProcs.clear(); // Emptying the list before filling it

        // Creating the list of the currently ready processes
        // If a process appears before or at the current clock, add it to the list
        for (int i=0; i<p.size(); i++) {
            if (p[i].getReadyTime() <= clock) {
                readyProcs.push_back(p[i]);
            }
        }

        int minProc = getMinExecTimeProc(readyProcs); // Determine process with the shortest execution time

        int indexOfMinProc = getIndexByProcNumber(p, minProc); // Determine the index of the process with the shortest execution

        p[indexOfMinProc] -= 1; // Decrementing the execution time of the executed process (See the operation overloading in the class Process)

        // If a process is being finished in the current time slice, delete it from the process list
        if (p[indexOfMinProc].getExecTime() == 0) {
            p.erase(p.begin()+indexOfMinProc);
        }

        // Mark the execution for the process at the current clock
        markExecution(getIndexByProcNumber(tmpProcs, minProc), clock);

        clock++; // Increment clock
    }

}


// Earliest Deadline First
// The approach is similar to SJF except for the following comments.
void EDF (std::vector<Process> p) {
    std::vector<Process> readyProcs;

    tmpProcs = p;

    int clock = 0;

    printf("\x1B[1mEarliest Deadline First (EDF)\x1B[0m\n");

    while (!p.empty()) {
        readyProcs.clear();

        for (int i=0; i<p.size(); i++) {
            if (p[i].getReadyTime() <= clock) {
                readyProcs.push_back(p[i]);
            }
        }

        int minProc = getMinDeadlineProc(readyProcs); // Determine the process with the earliest deadline

        int indexOfMinProc = getIndexByProcNumber(p, minProc); // Determine the index of the process with the earliest deadline

        p[indexOfMinProc] -= 1;

        if (p[indexOfMinProc].getExecTime() == 0) {
            p.erase(p.begin()+indexOfMinProc);
        }

        markExecution(getIndexByProcNumber(tmpProcs, minProc), clock);

        clock++;
    }
}



// Lowest Laxity First
// The approach is similar to SJF except for the following comments.
void LLF (std::vector<Process> p) {
    std::vector<Process> readyProcs;

    tmpProcs = p;

    int clock = 0;

    printf("\x1B[1mLeast Laxity First (LLF)\x1B[0m\n");

    while (!p.empty()) {
        readyProcs.clear();

        for (int i=0; i<p.size(); i++) {
            if (p[i].getReadyTime() <= clock) {
                readyProcs.push_back(p[i]);
            }
        }

        int minProc = getMinLaxityProc(readyProcs); // Determine the process with the least laxity

        int indexOfMinProc = getIndexByProcNumber(p, minProc); // Determine the index of the process with the least laxity

        p[indexOfMinProc] -= 1;

        if (p[indexOfMinProc].getExecTime() == 0) {
            p.erase(p.begin()+indexOfMinProc);
        }


        markExecution(getIndexByProcNumber(tmpProcs, minProc), clock);

        clock++;
    }
}


// First Come First Serve
void FCFS (std::vector<Process> p) {

    int responseTime = 0;

    tmpProcs = p;

    // Sort the processes according to their ready times
    sortProcesses(p, byReadyTime);

    printf("\x1B[1mFirst Come First Serve (FCFS)\x1B[0m\n");

    // Iteration over the process list
    for (int a=0; a<p.size(); a++) {

        for (int b=responseTime; b<responseTime+p[a].getExecTime(); b++)
            markExecution(getIndexByProcNumber(tmpProcs,p[a].getProcessNumber()), b);

        responseTime += p[a].getExecTime(); // Adding the execution time of the finished process to the response time (Gives the response time of the finished process)

    }
}


// Round Robin
// In addition to the process list it accepts the length of the time slice
void RoundRobin (std::vector<Process> p, int quant) {
    std::vector<Process> readyProcs; // List of the ready processes

    tmpProcs = p;

    int clock = 0; // Clock for the response time
    int wait = 0; // Clock for the classification of the process

    printf("\x1B[1mRound Robin - Quantum: %d\x1B[0m\n", quant);

    while (!p.empty()) {
        readyProcs.clear();

        // Sort processes according to their ready times
        // Consequently, the first process to arrive will get the first time slice of a round
        sortProcesses(p, byReadyTime);

        // Generate the list of the currently ready processes
        for (int i=0; i<p.size(); i++) {
            if (p[i].getReadyTime() <= wait) {
                readyProcs.push_back(p[i]);
            }
        }

        // Iteration over the list of the ready processes
        for (int i=0; i<readyProcs.size(); i++) {

            // For the non-termination of a process
            if (readyProcs[i].getExecTime() - quant > 0) {
                p[getIndexByProcNumber(p, readyProcs[i].getProcessNumber())] -= quant; // Subtract the time slice from the edited process

                for (int a=clock; a<clock+quant; a++)
                    markExecution(getIndexByProcNumber(tmpProcs, readyProcs[i].getProcessNumber()), a);

                clock += quant; // Increase the clock by the time slice
            }
            else {
                for (int a=clock; a<clock+readyProcs[i].getExecTime(); a++)
                    markExecution(getIndexByProcNumber(tmpProcs, readyProcs[i].getProcessNumber()), a);

                clock += readyProcs[i].getExecTime(); // Increase the clock by the remaining execution time
                p.erase(p.begin()+getIndexByProcNumber(p, readyProcs[i].getProcessNumber())); // Remove the process from the process list

            }

        }
        wait += quant; // Increasing the clock for queueing processes

    }
}
