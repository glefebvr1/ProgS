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
type_produit *Recherche_Produit(int no, int *nb_ligne_produit, type_produit *tab_produit);

void Creation_Ligne(type_ligne_commande *tab_commande, int nb_ligne_commande, type_produit nv_ptr_produit, int quantite);

void Modif_Ligne(type_ligne_commande *tab_commande,int nv_quantite, type_ligne_commande ptr_commande, int quantite);

void Commande_Produit(type_produit *tab_produit, type_ligne_commande *tab_commande, int *nb_ligne_produit);

void Supprimer_ligne(type_ligne_commande *tab_commande, int nb_ligne_commande, type_ligne_commande adresse_commande);

void Creation_Facture(char *nom, char *prenom, type_ligne_commande *tab_commande, int nb_ligne_commande);

void main(){

	int choix;
	int init_nom;
	int i;
	float *total;
	char *nom;
	char *prenom;
	int nb_ligne_commande;
	type_ligne_commande *tab_commande;
	int *nb_ligne_produit;
	type_produit *tab_produit;
	char chaine_tmp[MAX_CHAINE];

	choix = 0;
	init_nom = FAUX;
	i = 0;

	//Option
	puts("1. Saisir le nom et le prenom du client.");
	puts("2. Commander un produit.");
	puts("3. Afficher la liste des produits.");
	puts("4. Generer la facture");
	puts("");
	puts("0. Quitter le programme.");

	choix = Saisie_Entier();
	while(choix != 0){
		switch (choix){
			case 1:
			  Saisie_nom(nom,prenom,chaine_tmp);
			  init_nom = VRAI;
			  break;
			case 2:
			  Commande_Produit(tab_produit,tab_commande,nb_ligne_commande,)
			  break;
			case 3:
			  for (i = 0; i < nb_ligne_commande; i++){
			  	Afficher_Ligne_Commande(tab_commande[i])
			  }
			  printf("Total : %.2f\n", total);
			  break;
			case 4:
			  Creation_Facture(nom, prenom, tab_commande, nb_ligne_commande)
			  break;
			case 0:
			  puts("On quitte le programme.")
			  break;
			default:
			  puts("Choix non disponible.")
			  break;
			}
	choix = Saisie_Entier();
	}


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


	printf("Commande de %d %s %s, prix unitaire : %.2f CHF, prix total : %.2f CHF.\n", tab_commande.quantite, tab_commande.ptr_produit.nom, tab_commande.ptr_produit.ref, tab_commande.ptr_produit.prix_unitaire, tab_commande.total_ligne);


}

//Recherche dans le tableau de commande si un n° de produit existe déjà
type_ligne_commande *Recherche_Ligne(int no, int nb_ligne_commande, type_ligne_commande *tab_commande){

	int trouve = FAUX;
	type_ligne_commande *pointeur;

	for (int i = 0; i < nb || !trouve; i++) {
		
		if (nb_ligne_commande = tab_commande.ptr_produit.no){
			trouve = VRAI;
			pointeur = &tab_commande[i];
		} else {
			pointeur = NULL;
		}
	}
	return pointeur;
}

//Recherche dans le tableau de produits si un n° de produit existe déjà. Retourne l'adresse du produit correspondant ou NULL si ce produit n'existe pas.
type_produit *Recherche_Produit(int no, int *nb_ligne_produit, type_produit *tab_produit){

	int trouve = FAUX;
	type_ligne_commande *pointeur;

	for (int i = 0; i < nb_ligne_produit || !trouve; i++) {
		
		if (nb_ligne_commande = tab_produit.no){
			trouve = VRAI;
			pointeur = &tab_produit[i];
		} else {
			pointeur = NULL;
		}
	}

	return pointeur;
}

void Creation_Ligne(type_ligne_commande *tab_commande, int nb_ligne_commande, type_produit nv_ptr_produit, int quantite, float *total){
	//Ajout d'une ligne au tableau commande
	(*nb_ligne_commande)++;
	//Ajout des valeurs quantité et total dans le tableau commande
	tab_commande[nb_ligne_commande].ptr_produit = nv_ptr_produit;
	tab_commande[nb_ligne_commande].quantite = quantite;
	tab_commande[nb_ligne_commande].total_ligne = quantite*tab_commande[nb_ligne_commande].ptr_produit.prix_unitaire;
	//modification du total
	total = total + tab_commande[nb_ligne_commande].total_ligne;

	//Affichage du resultat
	Afficher_Ligne_Commande(tab_commande[nb_ligne_commande])

}

void Modif_Ligne(type_ligne_commande *tab_commande,int nv_quantite, type_ligne_commande ptr_commande, float *total){

	//modification des valeurs quantité et total dans le tableau commande
	ptr_commande->quantite = nv_quantite;
	ptr_commande->total_ligne = nv_quantite*ptr_commande->ptr_produit.prix_unitaire;
	Afficher_Ligne_Commande(*ptr_commande)
	//modification du total
	total = total + ptr_commande->total_ligne;

}

void Commande_Produit(type_produit *tab_produit, type_ligne_commande *tab_commande, int nb_ligne_commande, int *nb_ligne_produit){

	int no_produit, quantite;
	type_produit *adresse_produit;
	type_ligne_commande *adresse_commande;

	//Demande du numéro de produit
	printf("Entrez le numero de produit : ");
	no_produit = Saisie_Entier();
	while(no_produit < 0){
		printf("Un numero de produit ne peut pas être negatif. Entrez à nouveau : ");
		no_produit = Saisie_Entier();
	}

	//Demande la quantité
	Printf("Entrez la quantite désirée");
	quantite = Saisie_Entier();
	while(quantite < 0){
		printf("La quantite ne peut pas etre negative. Entrez a nouveau : ");
		quantite = Saisie_Entier();
	}

	//Recherche des adresses
	adresse_produit = Recherche_Produit(no_produit, *nb_ligne_produit, tab_produit);
	adresse_commande = Recherche_Ligne(no_produit, nb_ligne_commande, tab_commande);

	//On recherche si le produit existe.
	if  (adresse_produit == NULL){
		puts("Commande impossible car le produit n'existe pas.")
	} else {
		if (adresse_commande == NULL) {
			Creation_Ligne(tab_commande, nb_ligne_commande, adresse_produit, quantite, total);
		} else {
			if (quantite = 0){
				Supprimer_ligne(tab_commande, nb_ligne_commande, adresse_commande,total)
			} else {
				Modif_Ligne(tab_commande,quantite, adresse_commande,total);	
			}
		}
	}
}

void Supprimer_ligne(type_ligne_commande *tab_commande, int nb_ligne_commande, type_ligne_commande adresse_commande, float *total){

	type_ligne_commande *i;

	//modification du total
	total = total - adresse_commande->total_ligne

	puts("Supression de la commande.")
	for ( i = adresse_commande; i < &tab_commande[nb_ligne_commande - 1]; i++) {
		*adresse_commande = *adresse_commande + 1;
	}

	(*nb_ligne_commande)--;

}

void Creation_Facture(char *nom, char *prenom, float total, type_ligne_commande *tab_commande, int nb_ligne_commande){


	
}