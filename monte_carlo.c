#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

int rounds = 1000;
int sessions = 2000;
int choice = 1;
int jump_size = 3;
int skew = 0;
int max_skew = 2;

double sim_mean;
double sim_std_error;
double sim_std_dev;
void simulate(int spread, int skew_value)
{
    double total = 0;
    double total_sqrd = 0;
    for (int sns = 0; sns < sessions; sns++)
    {
        srand(sns + 1);
        int value = 10000;
        int quote = 10000;
        int cash = 0;
        int inventory = 0;

        for (int rds = 0; rds < rounds; rds++)
        {
            int jump = rand() % (2 * jump_size + 1) - jump_size;
            bool regular_arrives = rand() % 10 < 5;
            int tolerance = rand() % 7;
            bool regular_buys = rand() % 2;
            bool informed_arrives = rand() % 10 < 1;
            value += jump;
            int centre = quote - skew_value * inventory;

            if (regular_arrives && tolerance >= spread)
            {
                if (regular_buys)
                {
                    cash += centre + spread;
                    inventory--;
                }
                else
                {
                    cash -= centre - spread;
                    inventory++;
                }
            }
            if (informed_arrives)
            {
                if (value > centre + spread)
                {
                    cash += centre + spread;
                    inventory--;
                }
                else if (value < centre - spread)
                {
                    cash -= centre - spread;
                    inventory++;
                }
            }

            quote = value;
        }
        double profit = cash + inventory * value;
        total += profit;
        total_sqrd += profit * profit;
    }
    sim_mean = total / sessions;
    double variance = (total_sqrd / sessions - sim_mean * sim_mean) * sessions / (sessions - 1);
    sim_std_dev = sqrt(variance);
    sim_std_error = sqrt(variance / sessions);
}

int main()
{
    printf("Enter 1 to run the simulation with default parameters (1000 rounds, 2000 sessions, 3 jump size, and 0 skew)\n");
    printf("Enter 2 to customise the number of rounds, number of sessions, jump size and skew\n");
    scanf("%d", &choice);

    while (choice != 1 && choice != 2)
    {
        printf("Invalid number. Please enter 1 or 2.\n");
        scanf("%d", &choice);
    }

    if (choice == 2)
    {
        printf("Enter the number of rounds: ");
        scanf("%d", &rounds);
        while (rounds < 1)
        {
            printf("Rounds must be more than 0. Please enter the desired number of rounds again: ");
            scanf("%d", &rounds);
        }
        printf("Enter the number of sessions: ");
        scanf("%d", &sessions);
        while (sessions < 2)
        {
            printf("Sessions must be more than 1. Please enter the desired number of sessions again: ");
            scanf("%d", &sessions);
        }
        printf("Enter the jump size: ");
        scanf("%d", &jump_size);
        while (jump_size < 1)
        {
            printf("Jump size must be more than 0. Please enter the desired jump size again: ");
            scanf("%d", &jump_size);
        }
        printf("Enter the skew: ");
        scanf("%d", &skew);
        while (skew < 0)
        {
            printf("Skew must be more than or equal to 0. Please enter the desired skew again: ");
            scanf("%d", &skew);
        }
    }

    printf("Table 1 (with skew %d): \n", skew);
    printf("half_spread avg_profit std_error std_dev\n");
    for (int spread = 1; spread <= 7; spread++)
    {
        simulate(spread, skew);
        printf("%11d %10.1f %9.1f %7.1f\n", spread, sim_mean, sim_std_error, sim_std_dev);
    }

    int skew_table = 0;
    printf("Enter 1 to produce a comparison table with different skew values\n");
    printf("Enter 2 to exit the simulation\n");
    scanf("%d", &skew_table);
    while (skew_table != 1 && skew_table != 2)
    {
        printf("Invalid number. Please enter 1 or 2.\n");
        scanf("%d", &skew_table);
    }

    if (skew_table == 2)
    {
        printf("Exiting the simulation. Goodbye!\n");
        return 0;
    }

    printf("Enter the maximum skew value for the comparison table: ");
    scanf("%d", &max_skew);
    while (max_skew < 0)
    {
        printf("Maximum skew must be more than or equal to 0. Please enter the desired maximum skew again: ");
        scanf("%d", &max_skew);
    }

    printf("Table 2 (with skew values from 0 to %d): \n", max_skew);

    double profit[8][max_skew + 1];
    double risk[8][max_skew + 1];
    for (int spread = 1; spread <= 7; spread++)
    {
        for (int s = 0; s <= max_skew; s++)
        {
            simulate(spread, s);
            profit[spread][s] = sim_mean;
            risk[spread][s] = sim_std_dev;
        }
    }
    printf("half_spread");
    for (int s = 0; s <= max_skew; s++)
    {
        printf("  skew%d_profit   skew%d_risk", s, s);
    }
    printf("\n");
    for (int spread = 1; spread <= 7; spread++)
    {
        printf("%11d", spread);
        for (int s = 0; s <= max_skew; s++)
        {
            printf("  %12.1f   %10.1f", profit[spread][s], risk[spread][s]);
        }
        printf("\n");
    }
    return 0;
}
