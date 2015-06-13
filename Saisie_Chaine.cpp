#include <stdlib.h>
#include <stdio.h>
#include <string.h>

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


char *Saisie_Chaine(){
	char chaine_tmp[MAX_CHAINE], *chaine;

	fgets(chaine_tmp, MAX_CHAINE, stdin);
	while (chaine_tmp[0] == '\n' || chaine_tmp[strlen(chaine_tmp) - 1] != '\n') {
		if (chaine_tmp[strlen(chaine_tmp) - 1] != '\n') {
			while (getchar() != '\n');
			puts("Nombre de caracteres trop grand");
		}
		else {
			puts("Saisie invalide");
		}
		fgets(chaine_tmp, MAX_CHAINE, stdin);
	}

	//suppression du '\n'
	if (chaine_tmp[strlen(chaine_tmp) - 1] == '\n') {
		chaine_tmp[strlen(chaine_tmp) - 1] = '\0';
	}

	chaine = (char *)malloc(sizeof(char) * strlen(chaine_tmp) + 1);
	strcpy(chaine, chaine_tmp);

	return chaine;
}

// Tests :
// - Saisie d'une chaine trop longue
// - allocation mémoire pour strlen + 1
// - saisie d'une chaine vide (\n)
void main() {
	char *chaine;

	chaine = Saisie_Chaine();

	puts(chaine);
	free(chaine);

	system("pause");
}