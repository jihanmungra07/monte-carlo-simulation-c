# Monte-carlo-simulation-c
This is a small Monte Carlo Simulation of a market maker and is written in the C programming language. 
The simulation estimates how much money a market maker makes on average for different bid-ask spreads, and shows why the best spread exists in the middle.
# Structure-of-the-model
Each session had 1,000 rounds, wherein each round consists of:
The true value of the asset fluctuating by a random integer between -4 to +4. The market maker does not see the change yet.
A group of "regular trader" exists with a 50% probability. They can buy or sell at random, but each of them have a random tolerance of 0 to 7 tick, and they can only trade if the market maker's half-spread is within the tolerance range.
A group of "informed trader" also exists with a 10% probability. They know the true value of the asset and only trade when the value lies outside of the market maker's quote, causing the market maker to lose some money.
The market maker learns the true value and re-centres the quote accordingly.

At the end of each session, profit is the cash plus the market maker's remaining inventory value at the final true price.
For each half-spread (defined as 'spr') from 1 to 7 ticks, where 1 tick is the smallest price increment, the simulation will run 2,000 sessions and average the profit. Every half-spread is tested on the same 2,000 random scenarios (defined by 'srand(s +1)', where s is the scenario number).
# Example
<img width="434" height="378" alt="image" src="https://github.com/user-attachments/assets/736aaabe-dbc4-4c11-bbb7-1ccb50d3d32b" />

# Compiling
gg -Wall -Wextra monte_carlo.c -o monte
# Running
./monte
