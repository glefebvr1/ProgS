#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_INT 10
#define MAX_CHAINE 255
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


//Saisie d'une chaine et 
char *Saisie_Chaine();

int Saisie_Entier();

void Afficher_Ligne_Commande(type_ligne_commande ligne_commande);

//Recherche dans le tableau de commande si un n° de produit existe déjà
type_ligne_commande *Recherche_Ligne(int no, type_ligne_commande *tab_commande);

// Charge le fichier produit et l'enregistre dans un tableau de structures
type_produit *Charge_Produits(char chemin_fichier[], int *nb_produits);

//Recherche dans le tableau de produits si un n° de produit existe déjà. Retourne l'adresse du produit correspondant ou NULL si ce produit n'existe pas.
type_produit *Recherche_Produit(int no, int nb_ligne_produit, type_produit *tab_produit);

void Creation_Ligne(type_ligne_commande *tab_commande, int *nb_ligne_commande, type_produit *nv_ptr_produit, int quantite, float *total);

void Modif_Ligne(type_ligne_commande *tab_commande, int nv_quantite, type_ligne_commande *ptr_commande, float *total);

void Commande_Produit(type_produit *tab_produit, type_ligne_commande *tab_commande, int *nb_ligne_commande, int *nb_ligne_produit, float *total);

void Supprimer_ligne(type_ligne_commande *tab_commande, int *nb_ligne_commande, type_ligne_commande *adresse_commande, float *total);

int Creation_Facture(char *nom, char *prenom, float total, type_ligne_commande *tab_commande, int nb_ligne_commande);

void main() {

	int choix;
	int init_nom;
	int i;
	float total;
	char *nom;
	char *prenom;
	int nb_ligne_commande;
	type_ligne_commande *tab_commande;
	int nb_ligne_produit;
	type_produit *tab_produit;
	char chaine_tmp[MAX_CHAINE];

	choix = 0;
	init_nom = FAUX;
	i = 0;
	tab_commande = NULL;
	tab_produit = NULL;

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
				//Saisie du nom
				puts("Entrez le nom du client.");
				nom = Saisie_Chaine();

				//Saisie du prénom
				puts("Entrez le prenom du client.");
				prenom = Saisie_Chaine();

				init_nom = VRAI;
				break;
			case 2:
				Commande_Produit(tab_produit, tab_commande, &nb_ligne_commande, &nb_ligne_produit, &total);
				break;
			case 3:
				for (i = 0; i < nb_ligne_commande; i++){
					Afficher_Ligne_Commande(tab_commande[i]);
				}
				printf("Total : %.2f\n", total);
				break;
			case 4:
				Creation_Facture(nom, prenom, total, tab_commande, nb_ligne_commande);
				break;
			case 0:
				puts("On quitte le programme.");
				break;
			default:
				puts("Choix non disponible.");
				break;
			}
	choix = Saisie_Entier();
	}

	if (init_nom) {
		free(nom);
		free(prenom);
	}
}

// Tests :
// - Saisie d'une chaine trop longue
// - allocation mémoire pour strlen + 1
// - saisie d'une chaine vide (\n)
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

// Propose et vérifie la saisie d'un entier par l'utilisateur
// Tests :
// - Saisie vide (\n)
// - Saisie trop longue
// - Saisie de valeur non entières
int Saisie_Entier(){

	char entier[MAX_INT];
	int ret, valeur;

	// lit un entier de max MAX_INT caractères
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

void Afficher_Ligne_Commande(type_ligne_commande ligne_commande) {
	printf("Commande de %d %s %s, prix unitaire : %.2f CHF, prix total : %.2f CHF.\n", ligne_commande.quantite, ligne_commande.ptr_produit->marque, ligne_commande.ptr_produit->ref, ligne_commande.ptr_produit->prix_unitaire, ligne_commande.total_ligne);
}

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

// Charge le fichier produit et l'enregistre dans un tableau de structures
type_produit *Charge_Produits(char chemin_fichier[], int *nb_produits) {
	FILE *fichier_produit;
	char ligne[MAX_CHAINE], marque[MAX_CHAINE], ref[MAX_CHAINE];
	type_produit *tab_produit, tab_produit_tmp[MAX_PRODUITS];
	int ret, i;
	int erreur;

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
		if (fclose(fichier_produit) == EOF) {
			puts("Erreur de fermeture du fichier");
			erreur = VRAI;
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

void Creation_Ligne(type_ligne_commande *tab_commande, int *nb_ligne_commande, type_produit *nv_ptr_produit, int quantite, float *total) {

	(*nb_ligne_commande)++;
	//Ajout des valeurs quantité et total dans le tableau commande
	tab_commande[*nb_ligne_commande].ptr_produit = nv_ptr_produit;
	tab_commande[*nb_ligne_commande].quantite = quantite;
	tab_commande[*nb_ligne_commande].total_ligne = quantite * (tab_commande[*nb_ligne_commande].ptr_produit->prix_unitaire);
	//modification du total
	*total = *total + (tab_commande[*nb_ligne_commande].total_ligne);

	//Affichage du resultat
	Afficher_Ligne_Commande(tab_commande[*nb_ligne_commande]);

}

void Modif_Ligne(type_ligne_commande *tab_commande, int nv_quantite, type_ligne_commande *ptr_commande, float *total) {

	//modification des valeurs quantité et total dans le tableau commande
	ptr_commande->quantite = nv_quantite;
	ptr_commande->total_ligne = nv_quantite * (ptr_commande->ptr_produit->prix_unitaire);
	Afficher_Ligne_Commande(*ptr_commande);
	//modification du total
	*total = *total + ptr_commande->total_ligne;

}

void Commande_Produit(type_produit *tab_produit, type_ligne_commande *tab_commande, int *nb_ligne_commande, int *nb_ligne_produit, float *total){

	int no_produit, quantite;
	type_produit *adresse_produit;
	type_ligne_commande *adresse_commande;

	//Demande du numéro de produit
	printf("Entrez le numero de produit : ");
	no_produit = Saisie_Entier();
	while (no_produit < 0){
		printf("Un numero de produit ne peut pas être negatif. Entrez à nouveau : ");
		no_produit = Saisie_Entier();
	}

	//Demande la quantité
	printf("Entrez la quantite désirée");
	quantite = Saisie_Entier();
	while (quantite < 0){
		printf("La quantite ne peut pas etre negative. Entrez a nouveau : ");
		quantite = Saisie_Entier();
	}

	//Recherche des adresses
	adresse_produit = Recherche_Produit(no_produit, nb_ligne_produit, tab_produit);
	adresse_commande = Recherche_Ligne(no_produit, *nb_ligne_commande, tab_commande);

	//On recherche si le produit existe.
	if (adresse_produit == NULL){
		puts("Commande impossible car le produit n'existe pas.");
	}
	else {
		if (adresse_commande == NULL) {
			Creation_Ligne(tab_commande, nb_ligne_commande, adresse_produit, quantite, total);
		}
		else {
			if (quantite = 0) {
				Supprimer_ligne(tab_commande, nb_ligne_commande, adresse_commande, total);
			}
			else {
				Modif_Ligne(tab_commande, quantite, adresse_commande, total);
			}
		}
	}
}


void Supprimer_ligne(type_ligne_commande *tab_commande, int *nb_ligne_commande, type_ligne_commande *adresse_commande, float *total) {

	type_ligne_commande *i;

	//modification du total
	*total = *total - (adresse_commande->total_ligne);

	puts("Supression de la commande.");
	for ( i = adresse_commande; i < &tab_commande[*nb_ligne_commande - 1]; i++) {
		adresse_commande++;
	}

	(*nb_ligne_commande)--;

}

int Creation_Facture(char *nom, char *prenom, float total, type_ligne_commande *tab_commande, int nb_ligne_commande) {
	FILE *fichier_facture;
	char nom_complet[MAX_CHAINE];
	int i;
	int erreur;

	erreur = FAUX;
	strcpy(nom_complet, nom);
	strcat(nom_complet, prenom);
	fichier_facture = fopen(strcat(nom_complet, ".html"), "w");

	if (fichier_facture == NULL) {
		puts("Impossible de créer le fichier");
		erreur = VRAI;
	}
	else {
		fputs("<html>\n<head>\n<title>Facture</title>\n</head>\n<body>", fichier_facture);
		fprintf(fichier_facture, "<h1>Facture de %s %s</h1>\n", nom, prenom);
		fputs("<table border>\n<tr bgcolor=\"yellow\">", fichier_facture);
		fputs("<td>No</td><td>Marque</td><td>Ref</td><td>Prix</td><td>Nb</td><td>Total</td></tr>", fichier_facture);
		for (i = 0; i < nb_ligne_commande; i++) {
			fprintf(fichier_facture, "<tr><td>%d</td><td>%s</td><td>%s</td><td>%.2f</td><td>%d</td><td align=\"right\">%.2f</td></tr>", tab_commande[i].ptr_produit->no, tab_commande[i].ptr_produit->marque, tab_commande[i].ptr_produit->ref, tab_commande[i].ptr_produit->prix_unitaire, tab_commande[i].quantite, tab_commande[i].total_ligne);
		}
		fprintf(fichier_facture, "<tr><td>Total</td><td>&nbsp;</td><td>&nbsp;</td><td>&nbsp;</td><td>&nbsp;</td><td align=\"right\">%.2f</td></tr>", total);
		fputs("</table>\n</body>\n</html>", fichier_facture);

		if (fclose(fichier_facture) == EOF) {
			puts("Erreur de fermeture du fichier");
			erreur = VRAI;
		}
	}

	if (erreur) {
		return FAUX;
	}
	else {
		return VRAI;
	}
}
