# Activity-Planner

# Description:  
This program reads from a file called act.txt which contains a number representing the number of activities, followed by the activities themselves. Each activity has three digits representing its identifying number, start time, and end time. The algorithm will determine what is the optimal order of activities. 

# Example:

Input:  
act.txt contents:  
```
11
1 1 4
2 3 5
3 0 6
4 5 7
5 3 9
6 5 9
7 6 10
8 8 11
9 8 12
10 2 14
11 12 16
3
3 6 8
1 7 9
2 1 2
```
Output:  
Set 1  
Number of activities selected = 4  
Activities: 2 4 9 11  

Set 2  
Number of activities selected = 2  
Activities: 2 1 

# How to compile  
```
g++ act.cpp 
```
# How to run
```
a.out
```
