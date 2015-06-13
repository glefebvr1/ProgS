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


//Recherche dans le tableau de produits si un n° de produit existe déjà. Retourne l'adresse du produit correspondant ou NULL si ce produit n'existe pas.
// Tests :
// - n'importe quelle valeur de no
// - tab_produit NULL
// - dépassement de capacité
type_produit *Recherche_Produit(int no, type_produit *tab_produit) {
	type_produit *resultat, *element_courant;

	resultat = NULL;

	if (tab_produit != NULL) {
		element_courant = tab_produit;

		while (element_courant->no >= 0 && resultat == NULL) {
			if (no == element_courant->no) {
				resultat = element_courant;
			}
			element_courant++;
		}
	}
	return resultat;
}

void Afficher_Produit(type_produit produit) {
	printf("Produit %d %s %s, prix unitaire : %.2f CHF\n", produit.no, produit.marque, produit.ref, produit.prix_unitaire);
}

void main() {
	type_produit produit1, produit2, produit3, *resultat, *tab_produit;

	produit1 = { 100, "truc", "machin", 10.4 };
	produit2 = { 300, "dgf", "sdfg", 14.48 };
	produit3 = { 400, "erewr", "maqrewchin", 1043.3444 };

	tab_produit = (type_produit *)malloc(3 * sizeof(type_produit));
	tab_produit[0] = produit1;
	tab_produit[1] = produit2;
	tab_produit[2] = produit3;
	tab_produit[3].no = -1;

	resultat = Recherche_Produit(400, NULL);

	if (resultat == NULL) {
		puts("n'existe pas");
	}
	else {
		Afficher_Produit(*resultat);
	}

	system("pause");
}