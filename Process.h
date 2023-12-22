/******************************************
 * Class for modelling a process
*******************************************/

#include<stdexcept>

class Process {
private:
    int procNr;     // Process number
    int readyTime;  // Ready time
    int execTime;   // Execution Time
    int deadline;   // Deadline
    int laxity;     // Laxity

public:
    Process(int procNr, int readyTime, int execTime, int deadline); // Constructor with deadline
    Process(int procNr, int readyTime, int execTime); // Constructor without deadline
    Process() {} // General constructor for copy operations

    // Lowering the execution time
    void operator -= (int n);

    // Getter
    int getExecTime();
    int getReadyTime();
    int getDeadline();
    int getProcessNumber();
    int getLaxity();
};

#include "Process.cpp"
