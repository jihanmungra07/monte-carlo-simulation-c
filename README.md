# Monte-carlo-simulation-c
This is a small Monte Carlo simulation of a market maker and is written in the C programming language. 
The simulation estimates how much money a market maker makes on average for different bid-ask spreads, and shows why the most profitable spread exists between the extremes.
# Structure of the model
The program has an option to go with a default simulation which runs on a set of random numbers. Another option is to enter the number of sessions and rounds we would like to simulate. The input for the custom run expects a positive integer only for the values of sessions and rounds, otherwise, the program may behave enexpectedly.
# Execution of the model
In the default case, 2,000 sessions were run where each session had 1,000 rounds, and each round consisted of:

1) A market maker quoting a price to buy (bid) an asset and a price to sell (ask) the same asset for every 'spread' ticks and above the value it last saw. This distance is called the half-spread
2) The true value of the asset fluctuates by a random integer from -3 to +3. The market maker does not see the change yet.
3) A "regular trader" arrives with a 50% probability. They can buy or sell at random, but each of them have a random tolerance of 0 to 6 ticks, and they can only trade if the market maker's half-spread is no larger than their tolerance.
4) An "informed trader" also arrives with a 10% probability. They know the true value of the asset and only trade when the value is above the market marker's ask or below the bid  , causing the market maker to lose some money.
5) The market maker learns the true value and re-centres the quote accordingly.

At the end of each session, profit is the cash plus the market maker's remaining inventory value (the value of the market maker’s remaining inventory).
For each half-spread from 1 to 7 ticks, where 1 tick is the smallest price increment, the simulation will run 2,000 sessions and average the profit. Every half-spread is tested on the same 2,000 random scenarios (defined by 'srand (s +1)', where s is the scenario number), so the comparison is fair.
# Use
Finding out which half-spread makes the market maker the highest amount of average profit.
# Result
The image below shows the result of the default case for my code in Visual Studio Code.
<img width="392" height="268" alt="image" src="https://github.com/user-attachments/assets/49e009b1-2788-4674-8884-7d5c07f81a2e" />

The average profit is highest at half-spreads of 3 and 4 ticks. If we observe below that, the market maker loses money to informed traders. And if we observe above that, fewer regular traders accept the spread, and at 7 ticks none accept the spread, so the average profit is 0.
# Compiling
gcc -Wall -Wextra monte_carlo.c -o monte
# Running
./monte
