# Process Scheduling Algorithms
Algorithms for process scheduling

## CPU management algorithms
 - Shortest Job First (SJF)
 - Shortest Remaining Time First (SRTF)
 - Highest Remaining Ratio Next (HRRN)
 #### TODO
 - Longest Job First
 - Round Robin
 - Priority Scheduling
 - First Come First Served
 - Longest Response Time First

<hr>

## Memory management algorithms
 - First Fit
 - Worst Fit
 - Best Fit
 #### TODO
 - FIFO Page Replacement
 - LRU Page Replacement
 - LFU Page Replacement


## How to compile
Run the following command
```
make build NAME=filename_without_extension
```

where `filename_without_extension` is the name of the
file without the `.cpp` extension.

for example:
```
make build NAME=sjf
```

## Run a compiled program
Similar to the compile command, run
```
make run NAME=filename_without_extension
```

## Delete all compiled binaries
```
make clean-all
```