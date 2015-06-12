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

void Saisie_nom(char **nom, char **prenom, char chaine[MAX_CHAINE]);

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

	fgets(chaine, MAX_CHAINE, stdin);
	//suppression du '\n'
	chaine[strlen(chaine) - 1] = '\0';

}

void Saisie_nom(char **nom, char **prenom, char chaine[MAX_CHAINE]){

	//Saisie du nom
	puts("Entrez le nom du client.");
	Saisie_Chaine(chaine);
	*nom = (char *)malloc(sizeof(char)*strlen(chaine));
	strcpy(*nom, chaine);
	//vérification que la nom n'est pas vide
	while (chaine[0] == '\0'){
		puts("Entrez le nom du client. Ceci est obligatoire !");
		Saisie_Chaine(chaine);
		*nom = (char *)malloc(sizeof(char)*strlen(chaine));
		strcpy(*nom, chaine);
	}

	//saisie du prenom
	puts("Entrez le prenom du client.");
	Saisie_Chaine(chaine);
	*prenom = (char *)malloc(sizeof(char)*strlen(chaine));
	strcpy(*prenom, chaine);
	//vérification que la prénom n'est pas vide
	while (chaine[0] == '\0'){
		puts("Entrez le prenom du client. Ceci est obligatoire !");
		Saisie_Chaine(chaine);
		*prenom = (char *)malloc(sizeof(char)*strlen(chaine));
		strcpy(*prenom, chaine);
	}
}

// Propose et vérifie la saisie d'un entier par l'utilisateur
int Saisie_Entier(){

   char entier[10];
   int ret, valeur;

   // lit un entier de max 9 caractères
   fgets(entier, 10, stdin);
   ret = sscanf(entier, "%d", &valeur);

   while (ret != 1) {
       fgets(entier, 10, stdin);
       ret = sscanf(entier, "%d", &valeur);
   }

   return valeur;
}

void Afficher_Ligne_Commande(type_ligne_commande ligne_commande){


	printf("%d\t %s\t %s\t %f\t %d\t %f\t", ligne_commande.ptr_produit.no, ligne_commande.ptr_produit.marque, ligne_commande.ptr_produit.ref, ligne_commande.ptr_produit.prix_unitaire, ligne_commande.quantite, ligne_commande.total_ligne);


}

//Recherche dans le tableau de commande si un n° de produit existe déjà
type_ligne_commande *Recherche_Ligne(int no, int nb_ligne_commande, type_ligne_commande *tab_commande){

	int trouve = FAUX;
	type_ligne_commande *pointeur;

	for (int i = 0; i < nb || !trouve; i++) {
		
		if (nb_ligne_commande = tab_commande.ptr_produit.no){
			trouve = VRAI;
			pointeur = &tab_commande[i];
			return pointeur;
		}
	}
}

//Recherche dans le tableau de produits si un n° de produit existe déjà. Retourne l'adresse du produit correspondant ou NULL si ce produit n'existe pas.
type_produit *Recherche_Produit(int no, int nb_ligne_produit, type_produit *tab_produit){

	int trouve = FAUX;
	type_ligne_commande *pointeur;

	for (int i = 0; i < nb || !trouve; i++) {
		
		if (nb_ligne_commande = tab_produit.no){
			trouve = VRAI;
			pointeur = &tab_produit[i];
		}
	}

	return pointeur;
	
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