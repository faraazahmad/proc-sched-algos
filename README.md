# Process Scheduling Algorithms
Algorithms for process scheduling

## CPU management algorithms
 - Shortest Job First (SJF)
 - Shortest Response Time First (SRTF)
 - Highest Response Ratio Next (HRRN)
 - Longest Job First _(TODO)_
 - Round Robin _(TODO)_
 - Priority Scheduling _(TODO)_
 - First Come First Served _(TODO)_
 - Longest Response Time First _(TODO)_

## Memory management algorithms
 - First Fit
 - Worst Fit
 - Best Fit
 - FIFO Page Replacement _(TODO)_
 - LRU Page Replacement _(TODO)_
 - LFU Page Replacement _(TODO)_


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