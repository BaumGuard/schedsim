/*****************************************************************
 * Implementation of the constructors, member functions (getter)
 * and the operator overloading for the class process
******************************************************************/

// Constructors
Process::Process(int procNr, int readyTime, int execTime, int deadline) {
    this->procNr = procNr;
    this->readyTime = readyTime;
    this->execTime = execTime;
    this->deadline = deadline;

    laxity = deadline - readyTime - execTime;
}


Process::Process(int procNr, int readyTime, int execTime) {
    this->procNr = procNr;
    this->readyTime = readyTime;
    this->execTime = execTime;
}

// Operator overloading for lowering the execution time
// If the execution time becomes negative, throw an error
void Process::operator -= (int n) {
    if (execTime - n >= 0) {
        execTime-=n;
        laxity = deadline - readyTime - execTime;
    }
    else
        throw std::logic_error("Execution time can not be negative");
}


// Getter
int Process::getExecTime() {
    return execTime;
}

int Process::getReadyTime() {
    return readyTime;
}

int Process::getDeadline() {
    return deadline;
}

int Process::getProcessNumber() {
    return procNr;
}

int Process::getLaxity() {
    return laxity;
}
