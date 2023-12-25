/**********************
 * Auxiliary functions
***********************/

#include<sstream>


int** execArray;
int procQuant;
int totalExecTime;

// Function for splitting strings
// Used for parsing the input file
std::vector<std::string> split(const std::string& input) {
    std::vector<std::string> substrings;
    std::istringstream iss(input);
    std::string token;

    while (std::getline(iss, token, ' ')) {
        substrings.push_back(token);
    }

    return substrings;
}


// Medium time
float avgTime (int* rtArr, int size) {
    int sumRespTimes = 0;

    for (int i=0; i<size; i++)
        sumRespTimes += rtArr[i];

    return (float) sumRespTimes/size;
}


// Medium response time
void responseTime () {

    int responseTimeArr[procQuant];

    for (int a=0; a<procQuant; a++) {

        int responseTime = totalExecTime;

        for (int b=totalExecTime; b>=1; b--) {
            if (execArray[a][b] == 0)
                responseTime--;
            else
                break;
        }

        responseTimeArr[a] = responseTime;
        printf("P%d - Response time: %d\n", execArray[a][0], responseTime);
    }

    printf("Medium response time: %.2f\n", avgTime(responseTimeArr, procQuant));
}


// Medium waiting time
void waitingTime () {
    int waitingTimeArr[procQuant];

    for (int a=0; a<procQuant; a++) {
        int endIndex = 0;

        for (int b=totalExecTime; b>0; b--) {
            if (execArray[a][b] == 1) {
                endIndex = b;
                break;
            }
        }

        int waitingTime = 0;

        for (int b=0; b<=endIndex; b++) {
            if (execArray[a][b] == 0) {
                waitingTime++;
            }
        }

        waitingTimeArr[a] = waitingTime;

        printf("P%d - Wartezeit: %d\n", execArray[a][0], waitingTime);
    }

    printf("Mittlere Wartezeit: %.2f\n", avgTime(waitingTimeArr, procQuant));
}



// Determine the process with the lowest execution time
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

// Determine the process with the lowest laxity
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

// Determine process with the earliest deadline
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


// Determine the process index within a process list
int getIndexByProcNumber (std::vector<Process>& procs, int procNumber) {
    int pn = -1;

    for (int i=0; i<procs.size(); i++) {
        if (procs[i].getProcessNumber() == procNumber) {
            pn = i;
            break;
        }
    }

    return pn;
}



// Memory allocation for an array to store the execution process
void allocProcArray (std::vector<Process>& procs) {
    totalExecTime = 0;
    procQuant = procs.size();

    for (int i=0; i<procs.size(); i++)
        totalExecTime += procs[i].getExecTime();

    execArray = (int**)malloc(procs.size()*sizeof(int*));

    for (int i=0; i<procs.size(); i++)
        execArray[i] = (int*) malloc((totalExecTime+1)*sizeof(int));

    for (int i=0; i<procs.size(); i++)
        execArray[i][0] = procs[i].getProcessNumber();
}

// Freeing the array of the exeution process
void freeProcArray() {
    for (int i=0; i<procQuant; i++)
        free(execArray[i]);

    free (execArray);
}


// Mark the process at clock as executed
void markExecution(int procIndex, int clock) {
    execArray[procIndex][clock+1] = 1;
}


// Graphical output of the execution process
void printProcs() {

    for (int a=0; a<procQuant; a++) {

        printf("P%d ", execArray[a][0]);

        for (int b=1; b<=totalExecTime; b++) {
            if (execArray[a][b] == 0)
                printf("-");
            else
                printf("X");
        }
        printf("\n");
    }
}
