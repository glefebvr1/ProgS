#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_INT 10
#define MAX_CHAINE 255
#define MAX_CHAINE_SAISIE 50
#define MAX_PRODUITS 255
#define VRAI 1
#define FAUX 0
#define FPRODUIT "produit.txt"

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

void Afficher_Ligne_Commande(type_ligne_commande *ligne_commande);

//Recherche dans le tableau de commande si un n° de produit existe déjà
type_ligne_commande *Recherche_Ligne(int no, type_ligne_commande *tab_commande, type_ligne_commande *derniere_ligne);

// Charge le fichier produit et l'enregistre dans un tableau de structures
type_produit *Charge_Produits(char chemin_fichier[], type_produit **dernier_produit);

//Recherche dans le tableau de produits si un n° de produit existe déjà. Retourne l'adresse du produit correspondant ou NULL si ce produit n'existe pas.
type_produit *Recherche_Produit(int no, type_produit *tab_produit, type_produit *dernier_produit);

void Ajout_Ligne(type_ligne_commande **tab_commande, type_ligne_commande **derniere_ligne, int nb_produits, type_produit *nv_ptr_produit, int quantite, float *total);

void Modif_Ligne(int nv_quantite, type_ligne_commande *ligne_commande, float *total);

void Commande_Produit(type_produit *tab_produit, type_ligne_commande **tab_commande, type_ligne_commande **derniere_ligne, type_produit *dernier_produit, float *total);

void Supprimer_ligne(type_ligne_commande **tab_commande, type_ligne_commande *adresse_commande, type_ligne_commande **derniere_ligne, float *total);

void Creation_Facture(char *nom, char *prenom, float total, type_ligne_commande *tab_commande, type_ligne_commande *derniere_ligne);

void main() {

	int choix;
	int init_nom;
	float total;
	char *nom;
	char *prenom;
	type_ligne_commande *tab_commande, *ligne_commande, *derniere_ligne;
	type_produit *tab_produit, *dernier_produit, *produit_courant;

	dernier_produit = NULL;

	tab_produit = Charge_Produits(FPRODUIT, &dernier_produit);

	if (tab_produit != NULL) {
		init_nom = FAUX;
		total = 0;
		tab_commande = NULL;
		derniere_ligne = NULL;

		//Option
		puts("1. Saisir le nom et le prenom du client.");
		puts("2. Commander un produit.");
		puts("3. Afficher la liste des produits commandes.");
		puts("4. Generer la facture");
		puts("");
		puts("0. Quitter le programme.");

		choix = Saisie_Entier();
		while (choix != 0){
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
				if (init_nom){
					Commande_Produit(tab_produit, tab_commande, &derniere_ligne, &total);
				} else {
					puts("Vous ne pouvez pas faire de commande tant que les nom et prenom n'ont pas ete entre.");
				}
				break;
			case 3:
				ligne_commande = tab_commande;
				while (ligne_commande <= derniere_ligne) {
					Afficher_Ligne_Commande(ligne_commande);
					ligne_commande++;
				}
				printf("Total : %.2f\n", total);
				break;
			case 4:
				if (init_nom) {
					Creation_Facture(nom, prenom, total, tab_commande, derniere_ligne);
				}
				else {
					puts("Vous ne pouvez pas generer de facture tant que");
					puts("le nom et le prenom n'ont pas ete saisis");
				}
				break;
			default:
				break;
			}
			choix = Saisie_Entier();
		}

		if (init_nom) {
			free(nom);
			free(prenom);
		}
		if (tab_commande != NULL) {
			free(tab_commande);
		}
		produit_courant = tab_produit;
		while (produit_courant <= dernier_produit) {
			free(produit_courant->marque);
			free(produit_courant->ref);
			produit_courant++;
		}
		free(tab_produit);
	}

	system("pause");
}

// Tests :
// - Saisie d'une chaine trop longue
// - allocation mémoire pour strlen + 1
// - saisie d'une chaine vide (\n)
char *Saisie_Chaine(){
	char chaine_tmp[MAX_CHAINE_SAISIE], *chaine;

	fgets(chaine_tmp, MAX_CHAINE_SAISIE, stdin);
	while (chaine_tmp[0] == '\n' || chaine_tmp[strlen(chaine_tmp) - 1] != '\n') {
		if (chaine_tmp[strlen(chaine_tmp) - 1] != '\n') {
			while (getchar() != '\n');
			puts("Nombre de caracteres trop grand");
		}
		else {
			puts("Saisie invalide");
		}
		fgets(chaine_tmp, MAX_CHAINE_SAISIE, stdin);
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
	printf("> ");
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
		printf("> ");
		fgets(entier, MAX_INT, stdin);
		ret = sscanf(entier, "%d", &valeur);
	}

	return valeur;
}

void Afficher_Ligne_Commande(type_ligne_commande *ligne_commande) {
	if (ligne_commande != NULL) {
		printf("Commande de %d %s %-s,\tprix unitaire : %7.2fCHF, total : %7.2fCHF\n", ligne_commande.quantite, ligne_commande.ptr_produit->marque, ligne_commande.ptr_produit->ref, ligne_commande.ptr_produit->prix_unitaire, ligne_commande.total_ligne);
	}
}

//Recherche dans le tableau de commande si un n° de produit existe déjà
// Tests :
// - n'importe quelle valeur de no
// - tab_commande NULL
// - dépassement de capacité
type_ligne_commande *Recherche_Ligne(int no, type_ligne_commande *tab_commande, type_ligne_commande *derniere_ligne) {
	type_ligne_commande *resultat, *element_courant;

	resultat = NULL;

	if (tab_commande != NULL) {
		element_courant = tab_commande;

		while (element_courant <= derniere_ligne && resultat == NULL) {
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
type_produit *Recherche_Produit(int no, type_produit *tab_produit, type_produit *dernier_produit) {
	type_produit *resultat, *element_courant;

	resultat = NULL;

	if (tab_produit != NULL && dernier_produit != NULL) {
		element_courant = tab_produit;

		while (element_courant <= dernier_produit && resultat == NULL) {
			if (no == element_courant->no) {
				resultat = element_courant;
			}
			element_courant++;
		}
	}
	return resultat;
}

type_produit Ajoute_Ligne_Produit(char ligne[], int no_ligne) {
	int ret, erreur, no;
	float prix;
	char marque[MAX_CHAINE], ref[MAX_CHAINE];
	type_produit produit;

	erreur = FAUX;

	if (ligne[strlen(ligne) - 1] != '\n' && strlen(ligne) == MAX_CHAINE - 1) {
		printf("Nombre de caracteres trop grand sur la ligne %d\n", no_ligne + 1);
		erreur = VRAI;
	}
	else {
		ret = sscanf(ligne, "%d\t%s\t%s\t%f", &no, marque, ref, &prix);
		if (ret != 4) {
			printf("Le format de la ligne %d est incorrect\n", no_ligne + 1);
			erreur = VRAI;
		}
		else {
			if (no < 0) {
				printf("La ligne %d est contient un no de produit invalide (< 0)\n", no_ligne + 1);
				erreur = VRAI;
			}
			else {
				produit.no = no;
				produit.prix_unitaire = prix;
				produit.marque = (char *)malloc(strlen(marque) * sizeof(char) + 1);
				produit.ref = (char *)malloc(strlen(ref) * sizeof(char) + 1);
				strcpy(produit.marque, marque);
				strcpy(produit.ref, ref);
			}
		}
	}

	if (erreur) {
		produit.no = -1;
	}

	return produit;
}

// Charge le fichier produit et l'enregistre dans un tableau de structures
// Tests
// - ligne incomplète
// - ligne vide
// - valeur incorrecte dans champ
// - no produit < 0
// - fichier inexistant ou pas de droits
// - nombre de produits trop élevés
// - erreur de fermeture du fichier
// - longueur de ligne trop grande dans fichier
// - gestion des doublons
// A TESTER - fichier vide
type_produit *Charge_Produits(char chemin_fichier[], type_produit **dernier_produit) {
	FILE *fichier_produit;
	char ligne[MAX_CHAINE], *ret;
	type_produit *tab_produit, tab_produit_tmp[MAX_PRODUITS], produit;
	int i, no_ligne;
	int erreur;

	erreur = FAUX;
	no_ligne = 0;
	fichier_produit = fopen(chemin_fichier, "r");

	if (fichier_produit == NULL) {
		printf("Le fichier %s n'existe pas ou n'est pas accessible\n", chemin_fichier);
		erreur = VRAI;
	}
	else {
		ret = fgets(ligne, MAX_CHAINE, fichier_produit);
		while (ret != NULL && !erreur) {
			if (no_ligne >= MAX_PRODUITS) {
				printf("Le fichier %s contient trop de produits\n", chemin_fichier);
				erreur = VRAI;
			}
			else {
				produit = Ajoute_Ligne_Produit(ligne, no_ligne);

				if (produit.no != -1) {
					if (Recherche_Produit(produit.no, tab_produit_tmp, *dernier_produit) != NULL) {
						printf("La ligne %d contient un doublon\n", no_ligne + 1);
						erreur = VRAI;
					}
					else {
						tab_produit_tmp[no_ligne] = produit;
					}
				}
				no_ligne++;
			}
			ret = fgets(ligne, MAX_CHAINE, fichier_produit);
		}
		if (fclose(fichier_produit) == EOF) {
			printf("Erreur de fermeture du fichier %s\n", chemin_fichier);
			erreur = VRAI;
		}

		if (ret == NULL && no_ligne == 0) {
			printf("Le fichier %s est vide\n", chemin_fichier);
			erreur = VRAI;
		}
	}

	if (erreur) {
		return NULL;
	}
	else {
		tab_produit = (type_produit *)malloc(no_ligne * sizeof(type_produit));

		for (i = 0; i < no_ligne; i++) {
			tab_produit[i] = tab_produit_tmp[i];
		}

		*dernier_produit = tab_produit + i - 1;

		return tab_produit;
	}
}

// Tests
// - quantité <= 0
// - pas de ligne
void Ajout_Ligne(type_ligne_commande **tab_commande, type_ligne_commande **derniere_ligne, int nb_produits, type_produit *nv_ptr_produit, int quantite, float *total) {

	if (quantite > 0) {
		//Ajout des valeurs quantité et total dans le tableau commande
		if (*tab_commande == NULL) {
			*tab_commande = (type_ligne_commande *)malloc(sizeof(type_ligne_commande) * nb_produits);
			*derniere_ligne = *tab_commande;
		}
		else {
			(*derniere_ligne)++;
		}
		(*derniere_ligne)->ptr_produit = nv_ptr_produit;
		(*derniere_ligne)->quantite = quantite;
		(*derniere_ligne)->total_ligne = quantite * nv_ptr_produit->prix_unitaire;
		*total = *total + (*derniere_ligne)->total_ligne;

		//Affichage du resultat
		Afficher_Ligne_Commande(*derniere_ligne);
	}
	else {
		puts("La quantite saisie ne peut etre <= 0");
	}
}

// Tests
// - empecher quantite negatives
void Modif_Ligne(int nv_quantite, type_ligne_commande *ligne_commande, float *total) {

	if (nv_quantite + ligne_commande->quantite > 0) {
		//modification des valeurs quantité et total dans le tableau commande
		ligne_commande->quantite = nv_quantite + ligne_commande->quantite;
		ligne_commande->total_ligne = ligne_commande->quantite * ligne_commande->ptr_produit->prix_unitaire;
		Afficher_Ligne_Commande(ligne_commande);
		//modification du total
		*total = *total + nv_quantite * ligne_commande->ptr_produit->prix_unitaire;
	}
	else {
		puts("Il n'est pas possible de commander une quantite inferieure a 1");
	}
}

// Tests
// - ligne commande vide
void Supprimer_ligne(type_ligne_commande **tab_commande, type_ligne_commande *adresse_commande, type_ligne_commande **derniere_ligne, float *total) {

	if (*tab_commande != NULL) {
		//modification du total
		*total = *total - (adresse_commande->total_ligne);

		while (adresse_commande < *derniere_ligne) {
			*adresse_commande = *(adresse_commande + 1);
			adresse_commande++;
		}

		if (*derniere_ligne == *tab_commande) {
			free(*tab_commande);
			*tab_commande = NULL;
		}
		else {
			(*derniere_ligne)--;
		}
	}
}

void Commande_Produit(type_produit *tab_produit, type_ligne_commande **tab_commande, type_ligne_commande **derniere_ligne, type_produit *dernier_produit, float *total) {

	int no_produit, quantite, nb_produits;
	type_produit *adresse_produit;
	type_ligne_commande *adresse_commande;

	//Demande du numéro de produit
	printf("Entrez le numero de produit : ");
	no_produit = Saisie_Entier();
	while (no_produit < 0){
		printf("Un numero de produit ne peut pas être negatif. Entrez à nouveau : ");
		no_produit = Saisie_Entier();
	}

	//On recherche si le produit existe.
	adresse_produit = Recherche_Produit(no_produit, tab_produit, dernier_produit);
	if (adresse_produit == NULL) {
		puts("Commande impossible car le produit n'existe pas.");
	}
	else {
		//Demande la quantité
		printf("Entrez la quantite desiree : ");
		quantite = Saisie_Entier();

		adresse_commande = Recherche_Ligne(no_produit, *tab_commande, *derniere_ligne);
		if (adresse_commande == NULL) {
			nb_produits = dernier_produit - tab_produit + 1;
			Ajout_Ligne(tab_commande, derniere_ligne, nb_produits, adresse_produit, quantite, total);
		}
		else {
			if (quantite == 0) {
				Supprimer_ligne(tab_commande, adresse_commande, derniere_ligne, total);
			}
			else {
				Modif_Ligne(quantite, adresse_commande, total);
			}
		}
	}
}

// Tests
// - fichier existe, pas de droits
// - pas possible d'enregistrer modif
// - Facture vide
void Creation_Facture(char *nom, char *prenom, float total, type_ligne_commande *tab_commande, type_ligne_commande *derniere_ligne) {
	FILE *fichier_facture;
	char nom_complet[MAX_CHAINE];

	strcpy(nom_complet, nom);
	strcat(nom_complet, prenom);
	fichier_facture = fopen(strcat(nom_complet, ".html"), "w");

	if (fichier_facture == NULL) {
		puts("Impossible de créer le fichier");
	}
	else {
		fputs("<html>\n<head>\n<title>Facture</title>\n</head>\n<body>\n", fichier_facture);
		fprintf(fichier_facture, "<h1>Facture de %s %s</h1>\n", nom, prenom);
		fputs("<table border>\n<tr bgcolor=\"yellow\">", fichier_facture);
		fputs("<td>No</td><td>Marque</td><td>Ref</td><td>Prix</td><td>Nb</td><td>Total</td></tr>\n", fichier_facture);
		while (tab_commande <= derniere_ligne) {
			fprintf(fichier_facture, "<tr><td>%d</td><td>%s</td><td>%s</td><td>%.2f</td><td>%d</td><td align=\"right\">%.2f</td></tr>\n", tab_commande->ptr_produit->no, tab_commande->ptr_produit->marque, tab_commande->ptr_produit->ref, tab_commande->ptr_produit->prix_unitaire, tab_commande->quantite, tab_commande->total_ligne);
			tab_commande++;
		}
		fprintf(fichier_facture, "<tr><td>Total</td><td>&nbsp;</td><td>&nbsp;</td><td>&nbsp;</td><td>&nbsp;</td><td align=\"right\">%.2f</td></tr>\n", total);
		fputs("</table>\n</body>\n</html>", fichier_facture);

		if (fclose(fichier_facture) == EOF) {
			puts("Erreur de fermeture du fichier");
		}
	}
}