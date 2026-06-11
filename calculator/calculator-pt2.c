#include <stdio.h>

int main(){
	double a,b;
	char op;

	printf("Inserire numeri e operatori. ES: 1+3\n");
	scanf("%lf %c %lf", &a, &op, &b);

	double r = 0;

	if (op=='+') r=a+b;
	else if (op=='*') r=a*b;
	else if (op=='-') r=a-b;
	/* ERRATO PARZIALMENTE: l'else finale è generico, ovvero se un utente
	   aggiungesse @, direbbe impossibile dividere per 0*/
	
    // else if (op=='/' && b!=0) r=a/b;
	// else {
	//       	printf("Impossibile dividere per 0\n");
	//			return 1;
	//      }

	/* SOLUZIONE: */
	else if (op=='/'){
		if(b!=0) r=a/b;
		else {
				printf("Impossibile dividere per 0\n");
				return 1;
		}
	} else {
				printf("Non è stato possibile calcolare\n");
				return 1;
	}

	printf("%.2f\n", r);
	
	return 0;
}	
