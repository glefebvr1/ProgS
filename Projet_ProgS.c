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

void Creation_Ligne(type_produit *tab_produit, type_ligne_commande *tab_commande, int nb_ligne_commande, type_produit ptr_produit);

void Modif_Ligne(type_ligne_commande *tab_commande,int nv_quantite, type_ligne_commande ptr_commande);

void Commande_Produit(type_produit *tab_produit, type_ligne_commande *tab_commande, int nb_ligne_commande, int *nb_ligne_produit);

void Supprimer_ligne(type_ligne_commande *tab_commande, int nb_ligne_commande, int no);

void Creation_Facture(char *nom, char *prenom, float total, type_ligne_commande *tab_commande, int nb_ligne_commande);

void main(){

	char *nom;
	char *prenom;
	float total;
	int nb_ligne_commande;
	type_ligne_commande *tab_commande;
	int *nb_ligne_produit;
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

	for (int i = 0; i < nb || !trouve; i++) {
		
		if (nb_ligne_commande = tab_produit.no){
			trouve = VRAI;
			pointeur = &tab_produit[i];
		} else {
			pointeur = NULL;
		}
	}

	return pointeur;
}

// Charge le fichier produit et l'enregistre dans un tableau de structures
type_produit *Charge_Produits(char chemin_fichier[MAX_CHAINE], int *nb_produits) {
	FILE *fichier_produit;
	char ligne[MAX_CHAINE], marque[MAX_CHAINE], ref[MAX_CHAINE];
	type_produit *tab_produit, tab_produit_tmp[MAX_PRODUITS];
	int ret, i;
	bool erreur;

	erreur = FAUX;
	fichier_produit = fopen(chemin_fichier, "r");

	if (fichier_produit == NULL) {
		puts("Le fichier n'existe pas ou n'est pas accessible");
		erreur = VRAI;
	}
	else {
		while (fgets(ligne, MAX_CHAINE, fichier_produit) != NULL && !erreur) {
			ret = sscanf(ligne, "%d\t%s\t%s\t%f", &tab_produit_tmp[*nb_produits].no, marque, ref, &tab_produit_tmp[*nb_produits].prix_unitaire);
			if (ret != 4) {
				printf("Le format de la ligne %d est incorrect\n", *nb_produits + 1);
				erreur = VRAI;
			}
			else {
				tab_produit_tmp[*nb_produits].marque = (char *)malloc(strlen(marque) * sizeof(char));
				tab_produit_tmp[*nb_produits].ref = (char *)malloc(strlen(ref) * sizeof(char));
				strcpy(tab_produit_tmp[*nb_produits].marque, marque);
				strcpy(tab_produit_tmp[*nb_produits].ref, ref);
				(*nb_produits)++;
			}
		}

		tab_produit = (type_produit *)malloc(*nb_produits * sizeof(type_produit));
		for (i = 0; i < *nb_produits; i++) {
			tab_produit[i] = tab_produit_tmp[i];
		}
	}

	if (erreur) {
		return NULL;
	}
	else {
		return tab_produit;
	}
}

void Creation_Ligne(type_produit *tab_produit, type_ligne_commande *tab_commande, int nb_ligne_commande, type_produit ptr_produit){

	(*nb_ligne_commande)++;
	

	
	
	
}

void Modif_Ligne(type_ligne_commande *tab_commande,int nv_quantite, type_ligne_commande ptr_commande){



	
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
			Creation_Ligne(tab_produit, tab_commande, nb_ligne_commande, adresse_produit);
		} else {
			Modif_Ligne(tab_commande,quantite, adresse_commande);
		}

	}

	


	
}

void Supprimer_ligne(type_ligne_commande *tab_commande, int nb_ligne_commande, int no){


	
}

void Creation_Facture(char *nom, char *prenom, float total, type_ligne_commande *tab_commande, int nb_ligne_commande){


	
}
