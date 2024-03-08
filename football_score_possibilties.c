#include <stdio.h>

void findCombinations(int score);

int main() {
    int score;
    while (1) {
        printf("Enter 0 or 1 to STOP\n");
        printf("Enter the NFL score: ");
        scanf("%d", &score);

        if (score <= 1) break;

        printf("Possible combinations of scoring plays for %d:\n", score);
        findCombinations(score);
    }
    return 0;
}

void findCombinations(int score) {
    for (int td2pt = 0; td2pt * 8 <= score; ++td2pt) {
        for (int tdFg = 0; tdFg * 7 + td2pt * 8 <= score; ++tdFg) {
            for (int td = 0; td * 6 + tdFg * 7 + td2pt * 8 <= score; ++td) {
                for (int fg = 0; fg * 3 + td * 6 + tdFg * 7 + td2pt * 8 <= score; ++fg) {
                    for (int safety = 0; safety * 2 + fg * 3 + td * 6 + tdFg * 7 + td2pt * 8 <= score; ++safety) {
                        if (safety * 2 + fg * 3 + td * 6 + tdFg * 7 + td2pt * 8 == score) {
                            printf("%d TD + 2pt, %d TD + FG, %d TD, %d 3pt FG, %d Safety\n", td2pt, tdFg, td, fg, safety);
                        }
                    }
                }
            }
        }
    }
}
