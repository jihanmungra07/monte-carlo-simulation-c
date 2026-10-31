#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int rounds = 1000;
int sessions = 2000;
int choice = 1;
int main() {
    printf("Enter 1 to run the simulation with default parameters (1000 rounds, 2000 sessions)\n");
    printf("Enter 2 to customise the number of rounds and sessions\n");
    scanf("%d", &choice);

    while (choice != 1 && choice != 2) {
        printf("Invalid number. Please enter 1 or 2.\n");
        scanf("%d", &choice);
    }
    
    if (choice == 2) {
        printf("Enter the number of rounds: ");
        scanf("%d", &rounds);
        printf("Enter the number of sessions: ");
        scanf("%d", &sessions);
    }
  
    printf("half_spread avg_profit\n");
    for (int tick = 1; tick <= 7; tick++) {
        double total = 0;
        for (int s = 0; s < sessions; s++) {
            srand(s + 1);
            int value = 10000;
            int quote = 10000;
            int cash = 0;
            int inventory = 0;

            for (int r = 0; r < rounds; r++) {
                int jump = rand() % 7 - 3;
                bool normal_arrives = rand() % 10 < 5;
                int tolerance = rand() % 7;
                bool normal_buys = rand() % 2;
                bool informed_arrives = rand() % 10 < 1;
                value += jump;

                if (normal_arrives && tolerance >= tick) {
                    if (normal_buys) {
                        cash += quote + tick;
                        inventory--;
                    } else {
                        cash -= quote - tick;
                        inventory++;
                    }
                }
                if (informed_arrives) {
                    if (value > quote + tick) {
                        cash += quote + tick;
                        inventory--;
                    } else if (value < quote - tick) {
                        cash -= quote - tick;
                        inventory++;
                    }
                }
            quote = value;
        }
         total += cash + inventory * value;
     }
    
    printf("%d %0.1f\n", tick, total / sessions);
   }

return 0;
}
