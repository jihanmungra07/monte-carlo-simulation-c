# Monte Carlo simulation (C)
This is a small Monte Carlo simulation of a market maker and is written in the C programming language. 
The simulation estimates how much money a market maker makes on average for different bid-ask spreads, and shows why the most profitable spread exists between the extremes.
# Structure of the model
The program can run a default simulation, consisting of 2,000 sessions of 1,000 rounds each, with fixed random seeds, so the results can be reproduced. Alternatively, the user can input a positive integer for the number of sessions and number of rounds for each session. Note that any input which is not a positive integer can cause the program to behave unexpectedly.

# Execution of the model
In the default case, the program runs 2,000 sessions with 1,000 rounds each, where 1 tick is the smallest price increment. Each round consists of:

1) The market maker quotes a price to buy (bid) an asset and a price to sell (ask) the same asset, `spread` ticks below and above the value it last saw. This distance is called the half-spread.
2) The true value of the asset fluctuates by a random integer from -3 to +3. The market maker does not see the change yet.
3) A "regular trader" arrives with a 50% probability. The trader buys or sells at random, but has a random tolerance of 0 to 6 ticks, and they can only trade if the market maker's half-spread is no larger than their tolerance.
4) An "informed trader" also arrives with a 10% probability. They know the true value of the asset and only trade when the value is above the market maker's ask or below the bid, causing the market maker to lose some money.
5) The market maker learns the true value and re-centres the quote accordingly.

At the end of each session, profit is the cash plus the value of the market maker's remaining inventory at the final true price.
For each half-spread from 1 to 7 ticks, the simulation runs for the desired number of sessions and averages the profit. Every half-spread is tested on the same random scenarios, defined by `srand(s + 1)`, where `s` is the session number, so the comparison is fair.
# Purpose
To find which half-spread gives the market maker the highest average profit.
# Result
The image below shows the result of the default case.

<img width="390" height="274" alt="image" src="https://github.com/user-attachments/assets/bf533f09-23a6-4d3e-ac01-2a86edc29ec3" />


Average profit is highest at half-spreads of 3 and 4 ticks. At smaller spreads (1 and 2 ticks), informed traders can trade against the market maker’s out-of-date quotes, which reduces its profit. At larger spreads, fewer regular traders accept the spread, and at 7 ticks none do, so the average profit is 0.
# Compiling
```
gcc -Wall -Wextra monte_carlo.c -o monte
```
# Running
```
./monte
```
