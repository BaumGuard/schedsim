# schedsim
Process scheduling simulator

## Introduction
`schedsim` is a simulator for process scheduling. I developed it as a small project at university.<br />
Currently it only supports one CPU.

### Available scheduling algorithms
- Shortest Job First (SJF)
- Earliest Deadline First (EDF)
- Least Laxity First (LLF)
- First Come First Serve (FCFS)
- Round Robin

## Compilation and installation
Download `schedsim` to your computer:
```
git clone https://github.com/BaumGuard/schedsim
```
Compile:
```
make
```

## Usage
### Syntax
```
./schedsim <File> -<Scheduling algorithm> [<Time slice>]
```

### Options
Option | Meaning
-|-
`-sjf` | Shortest Job First
`-edf` | Earliest Deadline First
`-llf`  | Least Laxity First
`-fcfs` | First Come First Serve
`-rr <time slice>` | Round Robin (Expects the length of the time slice)

  ### File
  `schedsim` expects a file with the information about the processes as the first command line argument.<br />
  The information should be presented in the file in the following order:
  ```
  <Process number> <Ready Time> <Execution Time> <Deadline>
  ```

All values must be integers!

**Example file**
```
1 2 5 8
2 0 8 9
3 4 3 6
4 5 6 10
5 1 4 12
```

### Output
Under the heading (current scheduling algorithm) the output is divided into three parts:<br />

1. **Graphical representation** of the execution process
2. **Response time** for each process and the medium response time for all processes
3. **Waiting time** for each process and the medium waiting time for all processes

### Help
Run `schedsim` without arguments:
```
./schedsim
```
