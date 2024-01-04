// Comparison by ready times
bool byReadyTime(Process p1, Process p2, char direction = 'a') {
    switch (direction) {
        case 'a':
            return p1.getReadyTime() > p2.getReadyTime();
            break;

        case 'd':
            return p1.getReadyTime() < p2.getReadyTime();
            break;

        default:
            return p1.getReadyTime() > p2.getReadyTime();
    }
}


/* Sorting function for processes
 * Implementation using Bubble Sort
 *
 * Function arguments:
 * - Reference to the process list
 * - Function pointer to the comparison function (see above)
*/
void sortProcesses (std::vector<Process>& proclist, bool (*compare)(Process, Process, char), char direction='a') {
    int n=proclist.size()-1;

    Process tmpProc; // Outsourcing process for swapping processes in Bubble Sort

    // Bubble Sort
    while (n >= 1) {
        for (int a=0; a<n; a++) {
            if (compare(proclist.at(a), proclist.at(a+1), direction)) {
                tmpProc = proclist.at(a);
                proclist[a] = proclist.at(a+1);
                proclist[a+1] = tmpProc;
            }
        }

        n--;
    }
}
