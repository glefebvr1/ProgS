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


void Afficher_Ligne_Commande(type_ligne_commande ligne_commande) {
	printf("Commande de %d %s %s, prix unitaire : %.2f CHF, prix total : %.2f CHF.\n", ligne_commande.quantite, ligne_commande.ptr_produit->marque, ligne_commande.ptr_produit->ref, ligne_commande.ptr_produit->prix_unitaire, ligne_commande.total_ligne);
}

// Tests
// - empecher quantite negatives
void Modif_Ligne(int nv_quantite, type_ligne_commande *ligne_commande, float *total) {

	if (nv_quantite + ligne_commande->quantite > 0) {
		//modification des valeurs quantité et total dans le tableau commande
		ligne_commande->quantite = nv_quantite + ligne_commande->quantite;
		ligne_commande->total_ligne = ligne_commande->quantite * ligne_commande->ptr_produit->prix_unitaire;
		Afficher_Ligne_Commande(*ligne_commande);
		//modification du total
		*total = *total + ligne_commande->total_ligne;
	}
	else {
		puts("Il n'est pas possible de commander une quantite inferieure a 1");
	}
}

void main() {
	type_produit produit1, produit2, produit3;
	type_ligne_commande ligne1, ligne2, ligne3, *resultat, *tab_commande;
	int nb_ligne;
	float total;

	produit1 = { 100, "truc", "machin", 10.4 };
	produit2 = { 300, "dgf", "sdfg", 14.48 };
	produit3 = { 400, "erewr", "maqrewchin", 30.55 };

	ligne1 = { &produit1, 4, 543.5 };
	ligne2 = { &produit2, 7, 453 };
	ligne3 = { &produit3, 4, 122.20 };

	nb_ligne = 3;
	total = 0;

	tab_commande = (type_ligne_commande *)malloc((nb_ligne)* sizeof(type_ligne_commande));
	tab_commande[nb_ligne].ptr_produit = NULL;
	tab_commande[0] = ligne1;
	tab_commande[1] = ligne2;
	tab_commande[2] = ligne3;

	Afficher_Ligne_Commande(tab_commande[2]);

	Modif_Ligne(-3, &tab_commande[2], &total);

	printf("%f\n", total);

	system("pause");
}