# 42 Philosophers

## About
This project is an introduction to threads and parallel programming.

## The Dining Philosophers Problem
This is a problem used to illustrate the issues of syncronization and how to solve them.
The problem poses that you have a certain number of philosophers around a table. Each has a plate in front of them and forks to their left and right. A philosopher must eat, think, and sleep in turn, so when they are doing one action, they can't do another.
To eat, a philosopher needs two forks, so if a philosopher is eating, his neighbours cannot be eating as well. After they eat, they will put the forks down, making them available to their neighbours.

In our case, the philosopher also has a maximum time between meals, so if they take too long to eat again, they will die. So, besides avoiding deadlocks, our programs must also be efficient so that everyone can eat in time.

##  Deadlocks
Deadlocks happen when the program cannot move foward because all the processes are waiting for the others to finish. For example, in the dining philosophers problem: if I start the routine by making all philosophers take fork to their left, no one would be able to eat because they would all be waiting for the fork to their right to be available. So they would die. 

To solve this issue there are a few options:
  - We can make the odd philosophers start taking the left fork and the even taking to right one.
  - Make the last philosopher take the forks inverted from the others.
  - Make either the odd or even philosophers wait some time before trying to take a fork.

In my case, I choose the second option. But what all the options do is try to prevent deadlocks from happening. The first and second will make sure the neighbours will always try to take the same fork first and second
