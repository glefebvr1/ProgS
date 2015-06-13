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


//Recherche dans le tableau de commande si un n° de produit existe déjà
// Tests :
// - n'importe quelle valeur de no
// - tab_commande NULL
// - dépassement de capacité
type_ligne_commande *Recherche_Ligne(int no, type_ligne_commande *tab_commande) {
	type_ligne_commande *resultat, *element_courant;

	resultat = NULL;

	if (tab_commande != NULL) {
		element_courant = tab_commande;

		while (element_courant->ptr_produit != NULL && resultat == NULL) {
			if (no == element_courant->ptr_produit->no) {
				resultat = element_courant;
			}
			element_courant++;
		}
	}

	return resultat;
}

void Afficher_Ligne_Commande(type_ligne_commande ligne_commande) {
	printf("Commande de %d %s %s, prix unitaire : %.2f CHF, prix total : %.2f CHF.\n", ligne_commande.quantite, ligne_commande.ptr_produit->marque, ligne_commande.ptr_produit->ref, ligne_commande.ptr_produit->prix_unitaire, ligne_commande.total_ligne);
}

void main() {
	type_produit produit1, produit2, produit3;
	type_ligne_commande ligne1, ligne2, ligne3, *resultat, *tab_commande;
	int nb_ligne;

	produit1 = { 100, "truc", "machin", 10.4 };
	produit2 = { 300, "dgf", "sdfg", 14.48 };
	produit3 = { 400, "erewr", "maqrewchin", 1043.3444 };

	ligne1 = { &produit1, 4, 543.5 };
	ligne2 = { &produit2, 7, 453 };
	ligne3 = { &produit3, 1, 43.4564 };

	nb_ligne = 3;

	tab_commande = (type_ligne_commande *)malloc((nb_ligne) * sizeof(type_ligne_commande));
	tab_commande[nb_ligne].ptr_produit = NULL;
	tab_commande[0] = ligne1;
	tab_commande[1] = ligne2;
	tab_commande[2] = ligne3;

	resultat = Recherche_Ligne(400, tab_commande);

	if (resultat == NULL) {
		puts("n'existe pas");
	}
	else {
		Afficher_Ligne_Commande(*resultat);
	}

	system("pause");
}