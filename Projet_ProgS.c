CACAPROUT
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_CHAINE 255
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


//Saisie d'une chaine et 
void Saisie_Chaine(char chaine[MAX_CHAINE]);

int Saisie_Entier();

void Afficher_Ligne_Commande(type_ligne_commande ligne_commande);

//Recherche dans le tableau de commande si un n° de produit existe déjà
type_ligne_commande *Recherche_Ligne(int no, int nb_ligne_commande, type_ligne_commande *tab_commande);

// Charge le fichier produit et l'enregistre dans un tableau de structures
type_produit *Charge_Produits(char chemin_fichier[MAX_CHAINE], int *nb_produits);

//Recherche dans le tableau de produits si un n° de produit existe déjà. Retourne l'adresse du produit correspondant ou NULL si ce produit n'existe pas.
type_produit *Recherche_Produit(int no, int nb_ligne_produit, type_produit *tab_produit);

void Creation_Ligne(type_produit *tab_produit, type_ligne_commande *tab_commande, int nb_ligne_commande);

void Modif_Ligne(type_ligne_commande *tab_commande,int nv_quantite);

void Commande_Produit(type_produit *tab_produit, type_ligne_commande *tab_commande, int nb_ligne_commande, int nb_ligne_produit);

void Supprimer_ligne(type_ligne_commande *tab_commande, int nb_ligne_commande, int no);

void Creation_Facture(char *nom, char *prenom, float total, type_ligne_commande *tab_commande, int nb_ligne_commande);

void main(){

	char *nom;
	char *prenom;
	float total;
	int nb_ligne_commande;
	type_ligne_commande *tab_commande;
	int nb_ligne_produit;
	type_produit *tab_produit;
	char chaine_tmp[MAX_CHAINE];





}


//Saisie d'une chaine et 
void Saisie_Chaine(char chaine[MAX_CHAINE]){


	
}

int Saisie_Entier(){


	
}

void Afficher_Ligne_Commande(type_ligne_commande ligne_commande){


	
}

//Recherche dans le tableau de commande si un n° de produit existe déjà
type_ligne_commande *Recherche_Ligne(int no, int nb_ligne_commande, type_ligne_commande *tab_commande){


	
}

//Recherche dans le tableau de produits si un n° de produit existe déjà. Retourne l'adresse du produit correspondant ou NULL si ce produit n'existe pas.
type_produit *Recherche_Produit(int no, int nb_ligne_produit, type_produit *tab_produit){


	
}

void Creation_Ligne(type_produit *tab_produit, type_ligne_commande *tab_commande, int nb_ligne_commande){


	
}

void Modif_Ligne(type_ligne_commande *tab_commande,int nv_quantite){


	
}

void Commande_Produit(type_produit *tab_produit, type_ligne_commande *tab_commande, int nb_ligne_commande, int nb_ligne_produit){


	
}

void Supprimer_ligne(type_ligne_commande *tab_commande, int nb_ligne_commande, int no){


	
}

void Creation_Facture(char *nom, char *prenom, float total, type_ligne_commande *tab_commande, int nb_ligne_commande){


	
}