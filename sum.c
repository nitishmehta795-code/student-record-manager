#include <stdio.h>

int main(void) {
    int n, num, sum = 0;

    printf("How many numbers do you want to add? ");
    scanf("%d", &n);

    for (int i = 1; i <= n; i++) {
        printf("Enter number %d: ", i);
        scanf("%d", &num);
        sum += num;   /* same as sum = sum + num */
    }

    printf("Sum = %d\n", sum);
    return 0;
}