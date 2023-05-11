#include  <stdio.h>

{
	int n1, n2, product;

	printf("Enter you first integer: ");
	scanf("%d", &n1);

	printf("Enter your second interger: ");
	scanf("%d", &n2);

	product = n1 * n2;

	printf("The product of %d and %d is %d\n", n1, n2, product);

	return (0);
}
