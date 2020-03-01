Referenced example code from here https://www.hacks.moe/posts/1/A_barebones_userlevel_thread_library?fbclid=IwAR36Pes2sbgXVeSPrU1Yifki2s_ZIGVHc2A1iIvlXy5uokE0vlx84-UDE1U
And here http://www.atakansarioglu.com/easy-task-scheduler-real-time/
Consulted with Alec Braithwaite, Austin Lee, and Rhett Devlin

I currently only have test1 working and that was accomplished by setting up a
main_context variable which represents the "base level" of the program and
using that to swap between task1 and task2 in test1.

All of the other functions are in varying states of completion and I believe
that many are very close to working but I am out of time and so must hand
in what I have. The reason I never quite got test2 to work is that while I was
able to work around many functions for test1, test2 required almost all of the
functions to be working to execute.

I hope the code I have so far and the comments I've made show that I was on the
right track to setting up my scheduler as I feel that I have a pretty good grasp
on what is missing and how to put it all together, but wasn't able to in time.