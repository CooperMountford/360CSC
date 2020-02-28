Details from https://www.wikiwand.com/en/Dining_philosophers_problem
Understood pseudocode from https://www.geeksforgeeks.org/dining-philosopher-problem-using-semaphores/
Understood threads from here https://computing.llnl.gov/tutorials/pthreads/
Referenced code from https://pseudomuto.com/2014/03/dining-philosophers-in-c/
Also used man7.org manual pages for code examples (ex. http://man7.org/linux/man-pages/man3/pthread_create.3.html)


I started by following the pseudomuto code but realized that they were doing
some things in a very strange manner and the code did not loop, so I looked at
the manpages for code examples of how to call the methods and went from there.

Though it seems like my threads run in a non-deterministic manner, they often
get caught in loops where they will call the same threads in the same order
for a couple of iterations and then variations will slowly creep in and the
order will start to look random. I have no idea what causes this, or even if
that is just what non-deterministic choices look like, but I found there to be
the same patterns when I ran the geeksforgeeks code so I figured it's ok.

The phil_info struct isn't the most useful thing since it only contains a
single int value right now, but that's because I started with it being a large
struct then moved different calls around so that the values were no longer
needed. I could do the same with the int, but it seems like it works right now
and it's only a couple extra lines of code so I left it the way it is.