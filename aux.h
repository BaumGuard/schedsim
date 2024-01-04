/**********************
 * Auxiliary functions
***********************/

#include<tgmath.h>


int** execArray;
int procQuant;
int totalExecTime;
int idleTime;

int maxLeadingZeros;

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
        printf("P%0*d - Response time: %d\n", maxLeadingZeros+1, execArray[a][0], responseTime);
    }

    printf("Medium response time: %.2f\n", avgTime(responseTimeArr, procQuant));
}


// Medium waiting time
void waitingTime () {
    int waitingTimeArr[procQuant];

    for (int a=0; a<procQuant; a++) {
        int endIndex = 0;

        for (int b=totalExecTime; b>0; b--) {
            if (execArray[a][b] == 1 || execArray[a][b] == 2) {
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

        printf("P%0*d - Waiting time: %d\n", maxLeadingZeros+1, execArray[a][0], waitingTime);
    }

    printf("Medium waiting time: %.2f\n", avgTime(waitingTimeArr, procQuant));
}


// Get largest process number
int getMaxProcNumber () {
    int maxProcNumber = execArray[0][0];

    for (int i=1; i<procQuant; i++) {
        if (execArray[i][0] > maxProcNumber)
            maxProcNumber = execArray[i][0];
    }

    return maxProcNumber;
}



// Check if the list contains a process
bool containsProcess (std::vector<Process>& procs, int procNumber) {
    bool contained = false;

    for (int i=0; i<procs.size(); i++) {
        if (procs[i].getProcessNumber() == procNumber) {
            contained = true;
            break;
        }
    }

    return contained;
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

    std::vector<Process> tmpProcList = procs;

    for (int i=0; i<procs.size(); i++)
        totalExecTime += procs[i].getExecTime();

    sortProcesses(tmpProcList, byReadyTime);

    for (int i=procQuant-1; i>=0; i--) {
        if (tmpProcList[i-1].getReadyTime()+tmpProcList[i-1].getExecTime() < tmpProcList[i].getReadyTime())
            idleTime += (tmpProcList[i].getReadyTime()-(tmpProcList[i-1].getReadyTime()+tmpProcList[i-1].getExecTime()));
    }

    totalExecTime += idleTime;

    execArray = (int**)malloc(procs.size()*sizeof(int*));

    for (int i=0; i<procs.size(); i++)
        execArray[i] = (int*) malloc((totalExecTime+1)*sizeof(int));

    for (int a=0; a<procs.size(); a++)
        for (int b=0; b<totalExecTime+1; b++)
            execArray[a][b] = 0;

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
void markExecution(int procIndex, int clock, int mode=1) {
    execArray[procIndex][clock+1] = mode;
}


// Graphical output of the execution process
void printProcs() {

    maxLeadingZeros = log10(getMaxProcNumber());

    for (int a=0; a<procQuant; a++) {

        char leadingZeros[5] = "";

        for (int i=(int)log10(execArray[a][0]); i<maxLeadingZeros; i++)
            leadingZeros[i] = '0';

        printf("P%0*d ", maxLeadingZeros+1, execArray[a][0]);

        for (int b=1; b<=totalExecTime; b++) {
            if (execArray[a][b] == 0)
                printf("-");
            else if (execArray[a][b] == 1)
                printf("X");
            else if (execArray[a][b] == 2)
                printf("M");
        }
        printf("\n");
    }
}
