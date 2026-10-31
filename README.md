# Monte-carlo-simulation-c
This is a small Monte Carlo Simulation of a market maker and is written in the C programming language. 
The simulation estimates how much money a market maker makes on average for different bid-ask spreads, and shows why the best spread exists in the middle.
# Structure-of-the-model
We have an option to go with a default simulation which ran on a set of random numbers or enter the the number of sessions and rounds we would like to simulate. The input for the custom run expects a non-negative integer only for the values of sessions and rounds, otherwise, the program may execute unexpected errors.
In the default case, each session had 1,000 rounds, wherein each round consists of:
A market maker quoting a price to buy (bid) an asset and a price to sell (ask) the same asset for every tick (represented by 'spread') from the value it last saw.
The true value of the asset fluctuates by a random integer between -3 to +3. The market maker does not see the change yet.
A group of "regular trader" exists with a 50% probability. They can buy or sell at random, but each of them have a random tolerance of 0 to 6 tick, and they can only trade if the market maker's half-spread is within the tolerance range.
A group of "informed trader" also exists with a 10% probability. They know the true value of the asset and only trade when the value lies outside of the market maker's quote, causing the market maker to lose some money.
The market maker learns the true value and re-centres the quote accordingly.

At the end of each session, profit is the cash plus the market maker's remaining inventory value at the final true price.
For each half-spread from 1 to 6 ticks, where 1 tick is the smallest price increment, the simulation will run 2,000 sessions and average the profit. Every half-spread is tested on the same 2,000 random scenarios (defined by 'srand(s +1)', where s is the scenario number).
# Use
Finding out which spread makes the market maker the highest amount of profit.
# Result
The image below shows the result of the default case for my code in Visual Studio Code.
<img width="392" height="268" alt="image" src="https://github.com/user-attachments/assets/49e009b1-2788-4674-8884-7d5c07f81a2e" />

# Compiling
gg -Wall -Wextra monte_carlo.c -o monte
# Running
./monte
