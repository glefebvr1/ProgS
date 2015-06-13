#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_INT 3
#define MAX_CHAINE 5
#define MAX_PRODUITS 255
#define VRAI 1
#define FAUX 0
#define FPRODUIT produit.txt

//structures

typedef struct {
	int no;
	char *marque;
	char *ref;
	float prix_unitaire;
} type_produit;

typedef struct {
	type_produit *ptr_produit;
	int quantite;
	float total_ligne;
} type_ligne_commande;


// Tests :
// - Saisie vide (\n)
// - Saisie trop longue
// - Saisie de valeur non entières
int Saisie_Entier(){

	char entier[MAX_INT];
	int ret, valeur;

	// lit un entier de max 9 caractères
	fgets(entier, MAX_INT, stdin);
	ret = sscanf(entier, "%d", &valeur);

	while (ret != 1 || entier[strlen(entier) - 1] != '\n') {
		if (entier[strlen(entier) - 1] != '\n') {
			while (getchar() != '\n');
			puts("Nombre trop grand");
		}
		else {
			puts("Saisie invalide");
		}
		fgets(entier, MAX_INT, stdin);
		ret = sscanf(entier, "%d", &valeur);
	}

	return valeur;
}

void main() {
	int test;

	test = Saisie_Entier();

	printf("%d\n", test);

	system("pause");
}