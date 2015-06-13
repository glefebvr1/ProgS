#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_CHAINE 255
#define MAX_PRODUITS 255
#define VRAI 1
#define FAUX 0

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

void Afficher_Ligne_Commande(type_ligne_commande ligne_commande) {
	printf("Commande de %d %s %s, prix unitaire : %.2f CHF, prix total : %.2f CHF.\n", ligne_commande.quantite, ligne_commande.ptr_produit->marque, ligne_commande.ptr_produit->ref, ligne_commande.ptr_produit->prix_unitaire, ligne_commande.total_ligne);
}

// Tests
// - quantité <= 0
// - 
void Ajout_Ligne(type_ligne_commande **derniere_commande, type_produit *nv_ptr_produit, int quantite, float *total) {

	if (quantite > 0) {
		//Ajout des valeurs quantité et total dans le tableau commande
		(*derniere_commande)++;
		(*derniere_commande)->ptr_produit = nv_ptr_produit;
		(*derniere_commande)->quantite = quantite;
		(*derniere_commande)->total_ligne = quantite * nv_ptr_produit->prix_unitaire;
		*total = *total + (*derniere_commande)->total_ligne;

		((*derniere_commande) + 1)->ptr_produit = NULL;

		//Affichage du resultat
		Afficher_Ligne_Commande(**derniere_commande);
	}
	else {
		puts("La quantite saisie ne peut etre <= 0");
	}

}

void main() {
	type_produit produit1, produit2, produit3, produit4;
	type_ligne_commande ligne1, ligne2, ligne3, *derniere_commande, *tab_commande;
	int nb_ligne;
	float total;

	produit1 = { 100, "truc", "machin", 10.4 };
	produit2 = { 300, "dgf", "sdfg", 14.48 };
	produit3 = { 400, "erewr", "maqrewchin", 1043.3444 };
	produit4 = { 500, "fdsag", "fdsgss", 658.765 };

	ligne1 = { &produit1, 4, 543.5 };
	ligne2 = { &produit2, 7, 453 };
	ligne3 = { &produit3, 1, 43.4564 };

	nb_ligne = 10;
	total = 353.45;

	tab_commande = (type_ligne_commande *)malloc((nb_ligne)* sizeof(type_ligne_commande));
	tab_commande[nb_ligne].ptr_produit = NULL;
	tab_commande[0] = ligne1;
	tab_commande[1] = ligne2;
//	tab_commande[2] = ligne3;

	derniere_commande = &tab_commande[1];

	Ajout_Ligne(&derniere_commande, &produit3, 0, &total);
	printf("%f\n", total);
	Ajout_Ligne(&derniere_commande, &produit4, 5, &total);
	printf("%f\n", total);

	system("pause");
}