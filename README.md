## Asssignment set 2


### Contents
- 2.1: code for subassignments 2.1 and 2.2

- 2.3: ros code for subassignment 2.3

Makefile: for compiling assignment 2.1 (without Xenomai) and 2.2 (with Xenomai)



### Building


Build 2.1 and 2.2 with:
```
    make
```

Build individual subassignments with:
```
    make 2.1
    make 2.2
```

Build 2.3 like a normal ROS package.

### Running

Run 2.1 and 2.2 with:
```
    ./2.1
    ./2.2 # requires root privileges
```

Run the testset with:
```
    ./stress_test # may require root privileges
```
which outputs to the "results" folder.


For 2.3, start both "loop16" and "seq16" nodes. 