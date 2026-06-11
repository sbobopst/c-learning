#include <stdio.h>

int main(){
	double a,b;
	char op;

	printf("Inserire numeri ed operatori, ad es: 1+3\n");
	
	/* ERRATO: Sto chiedendo all'utente di usare le , (3,+,4) */ 
	// scanf("%lf, %c, %lf", &a, &op, &b); 
	
	/* SOLUZIONE: */
	scanf("%lf %c %lf", &a, &op, &b);

	/* ERRATO: Stai confrontando op con indirizzo di memoria "".
	   AD es: char op = 43 (ovvero '+')
	   Se fai op == "+" stai facendo: 43 == 0x4021A0 ad es */
	// if(op=="+")
	
	/* SOLUZIONE: */
	if(op=='+') {

		/* ERRATO: stai dicendo di inserire a+b al primo %lf,
		   il secondo %lf non servirebbe a nulla! */
		// printf("%lf,%lf", a+b);

		/* SOLUZIONE: */
		printf("%lf", a+b);
	}
	return 0;
}
