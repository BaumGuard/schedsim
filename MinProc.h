/********************************************
 * Get process by minimal criterium
*********************************************/


// Get process with lowest ready time
int getMinReadyTimeProc (std::vector<Process> procs) {
    int minExecTime = procs[0].getReadyTime();
    int minProc = procs[0].getProcessNumber();

    for (int i=1; i<procs.size(); i++){
        if (procs[i].getReadyTime() < minExecTime) {
            minExecTime = procs[i].getReadyTime();
            minProc = procs[i].getProcessNumber();
        }
    }

    return minProc;
}

// Get process with shortest execution time
int getMinExecTimeProc (std::vector<Process> procs) {
    int minExecTime = procs[0].getExecTime();
    int minProc = procs[0].getProcessNumber();

    for (int i=1; i<procs.size(); i++){
        if (procs[i].getExecTime() < minExecTime) {
            minExecTime = procs[i].getExecTime();
            minProc = procs[i].getProcessNumber();
        }
    }

    return minProc;
}

// Get process with longest execution time
int getMaxExecTimeProc (std::vector<Process> procs) {
    int maxExecTime = procs[0].getExecTime();
    int maxProc = procs[0].getProcessNumber();

    for (int i=1; i<procs.size(); i++){
        if (procs[i].getExecTime() < maxExecTime) {
            maxExecTime = procs[i].getExecTime();
            maxProc = procs[i].getProcessNumber();
        }
    }

    return maxProc;
}

// Get process with least laxity
int getMinLaxityProc (std::vector<Process> procs) {
    int minLaxity = procs[0].getLaxity();
    int minProc = procs[0].getProcessNumber();

    for (int i=1; i<procs.size(); i++){
        if (procs[i].getLaxity() < minLaxity) {
            minLaxity = procs[i].getLaxity();
            minProc = procs[i].getProcessNumber();
        }
    }

    return minProc;
}

// Get process with next deadline
int getMinDeadlineProc (std::vector<Process> procs) {
    int minDeadline = procs[0].getDeadline();
    int minProc = procs[0].getProcessNumber();

    for (int i=1; i<procs.size(); i++){
        if (procs[i].getDeadline() < minDeadline) {
            minDeadline = procs[i].getDeadline();
            minProc = procs[i].getProcessNumber();
        }
    }

    return minProc;
}
