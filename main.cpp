/***************************************+*
 * main function of schedsim
******************************************/

#include "Process.h"
#include "Scheduler.h"
#include<fstream>
#include<cstring>


int main (int argc, char* argv[]) {

    if (argc > 1) {

        // List of processes
        std::vector<Process> pl;

        // Read in a process file
        std::ifstream inputFile(argv[1]);

        std::string currentLine;
        while (std::getline(inputFile, currentLine)) {
            std::vector<std::string> vec = split(currentLine);

            // Creating the processes
            pl.push_back(Process(std::stoi(vec[0]),std::stoi(vec[1]),std::stoi(vec[2]),std::stoi(vec[3])));
        }


    allocProcArray(pl);

        // Call the scheduling algorithm requested by the user
        if (argc >= 3) {

            if (strcmp(argv[2],"-sjf")==0)
                SJF(pl);
            else if (strcmp(argv[2], "-edf")==0)
                EDF(pl);
            else if (strcmp(argv[2], "-fcfs")==0)
                FCFS(pl);
            else if (strcmp(argv[2], "-llf")==0)
                LLF(pl);
            else if (strcmp(argv[2], "-rr")==0) {
                if (argc == 4)
                    RoundRobin(pl, atoi(argv[3]));
                else
                    throw std::logic_error("No quantum supplied for Round Robin");
            }

            printf("\n");
            printProcs();
            printf("\n");
            responseTime();
            printf("\n");
            waitingTime();
            printf("\n");

        }

        else throw std::logic_error("No scheduling algorithm selected");

    }

    // If no file and scheduling algorithm have been entered, show the help display
    else
        printf("\e[1;34mschedsim - help file\e[0m\n\n\e[1;34mSyntax\e[0m\nschedsim <File> <Scheduling algorithm> [<Quantum>]\n\n\e[1;34mAvailable scheduling algorithms\e[0m\n\t-sjf\t\tShortest Job First\n\t-edf\t\tEarliest Deadline First\n\t-llf\t\tLowest Laxity First\n\t-fcfs\t\tFirst Come First Serve\n\t-rr <Quantum>\tRound Robin with time slice\n\n");


    freeProcArray();
}
