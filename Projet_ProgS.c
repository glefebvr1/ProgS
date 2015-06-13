#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_INT 10
#define MAX_CHAINE 255
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

void Afficher_Ligne_Commande(type_ligne_commande ligne_commande);

//Recherche dans le tableau de commande si un n° de produit existe déjà
type_ligne_commande *Recherche_Ligne(int no, type_ligne_commande *tab_commande);

// Charge le fichier produit et l'enregistre dans un tableau de structures
type_produit *Charge_Produits(char chemin_fichier[], int *nb_produits);

//Recherche dans le tableau de produits si un n° de produit existe déjà. Retourne l'adresse du produit correspondant ou NULL si ce produit n'existe pas.
type_produit *Recherche_Produit(int no, int nb_ligne_produit, type_produit *tab_produit);

void Ajout_Ligne(type_ligne_commande **derniere_commande, type_produit *nv_ptr_produit, int quantite, float *total);

void Modif_Ligne(int nv_quantite, type_ligne_commande *ligne_commande, float *total);

void Commande_Produit(type_produit *tab_produit, type_ligne_commande *tab_commande, type_ligne_commande **derniere_ligne, float *total);

void Supprimer_ligne(type_ligne_commande *tab_commande, type_ligne_commande *adresse_commande, type_ligne_commande **derniere_ligne, float *total);

void Creation_Facture(char *nom, char *prenom, float total, type_ligne_commande *tab_commande);

void main() {

	int choix;
	int init_nom;
	float total;
	char *nom;
	char *prenom;
	type_ligne_commande *tab_commande, *ligne_commande, *derniere_ligne;
	int nb_produits;
	type_produit *tab_produit;

	nb_produits = 0;
	tab_produit = Charge_Produits(FPRODUIT, &nb_produits);

	if (tab_produit != NULL) {
		init_nom = FAUX;
		total = 0;
		tab_commande = (type_ligne_commande *)malloc(sizeof(type_ligne_commande) * nb_produits);
		tab_commande->ptr_produit = NULL;
		derniere_ligne = tab_commande;

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
				Commande_Produit(tab_produit, tab_commande, &derniere_ligne, &total);
				break;
			case 3:
				ligne_commande = tab_commande;
				while (ligne_commande->ptr_produit != NULL) {
					Afficher_Ligne_Commande(*ligne_commande);
					ligne_commande++;
				}
				printf("Total : %.2f\n", total);
				break;
			case 4:
				if (init_nom) {
					Creation_Facture(nom, prenom, total, tab_commande);
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
	}

	system("pause");
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

void Afficher_Ligne_Commande(type_ligne_commande ligne_commande) {
	printf("Commande de %d %s %s, prix unitaire : %.2f CHF, total : %.2f CHF.\n", ligne_commande.quantite, ligne_commande.ptr_produit->marque, ligne_commande.ptr_produit->ref, ligne_commande.ptr_produit->prix_unitaire, ligne_commande.total_ligne);
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
type_produit *Charge_Produits(char chemin_fichier[], int *nb_produits) {
	FILE *fichier_produit;
	char ligne[MAX_CHAINE], marque[MAX_CHAINE], ref[MAX_CHAINE];
	type_produit *tab_produit, tab_produit_tmp[MAX_PRODUITS + 1];
	int ret, i, no;
	float prix;
	int erreur;

	erreur = FAUX;
	fichier_produit = fopen(chemin_fichier, "r");
	tab_produit_tmp[0].no = -1;

	if (fichier_produit == NULL) {
		puts("Le fichier n'existe pas ou n'est pas accessible");
		erreur = VRAI;
	}
	else {
		while (fgets(ligne, MAX_CHAINE, fichier_produit) != NULL && !erreur) {
			if (ligne[strlen(ligne) - 1] != '\n' && strlen(ligne) == MAX_CHAINE - 1) {
				printf("Nombre de caracteres trop grand sur la ligne %d\n", *nb_produits + 1);
				erreur = VRAI;
			}
			else {
				ret = sscanf(ligne, "%d\t%s\t%s\t%f", &no, marque, ref, &prix);
				if (ret != 4) {
					printf("Le format de la ligne %d est incorrect\n", *nb_produits + 1);
					erreur = VRAI;
				}
				else {
					if (no < 0) {
						printf("La ligne %d est contient un no de produit invalide (< 0)\n", *nb_produits + 1);
						erreur = VRAI;
					}
					else {
						if (Recherche_Produit(no, tab_produit_tmp) != NULL) {
							printf("La ligne %d contient un doublon\n", *nb_produits + 1);
							erreur = VRAI;
						}
						else {
							if (*nb_produits >= MAX_PRODUITS) {
								puts("Le fichier contient trop de produits");
								erreur = VRAI;
							}
							else {
								tab_produit_tmp[*nb_produits].no = no;
								tab_produit_tmp[*nb_produits].prix_unitaire = prix;
								tab_produit_tmp[*nb_produits].marque = (char *)malloc(strlen(marque) * sizeof(char));
								tab_produit_tmp[*nb_produits].ref = (char *)malloc(strlen(ref) * sizeof(char));
								strcpy(tab_produit_tmp[*nb_produits].marque, marque);
								strcpy(tab_produit_tmp[*nb_produits].ref, ref);
								(*nb_produits)++;
								tab_produit_tmp[*nb_produits].no = -1;
							}
						}
					}
				}
			}
		}
		if (fclose(fichier_produit) == EOF) {
			puts("Erreur de fermeture du fichier");
			erreur = VRAI;
		}

		tab_produit = (type_produit *)malloc(*nb_produits * sizeof(type_produit));

		for (i = 0; i <= *nb_produits; i++) {
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

// Tests
// - quantité <= 0
// - pas de ligne
void Ajout_Ligne(type_ligne_commande **derniere_ligne, type_produit *nv_ptr_produit, int quantite, float *total) {

	if (quantite > 0) {
		//Ajout des valeurs quantité et total dans le tableau commande
		if ((*derniere_ligne)->ptr_produit != NULL) {
			(*derniere_ligne)++;
		}
		(*derniere_ligne)->ptr_produit = nv_ptr_produit;
		(*derniere_ligne)->quantite = quantite;
		(*derniere_ligne)->total_ligne = quantite * nv_ptr_produit->prix_unitaire;
		*total = *total + (*derniere_ligne)->total_ligne;

		((*derniere_ligne) + 1)->ptr_produit = NULL;

		//Affichage du resultat
		Afficher_Ligne_Commande(**derniere_ligne);
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
		Afficher_Ligne_Commande(*ligne_commande);
		//modification du total
		*total = *total + nv_quantite * ligne_commande->ptr_produit->prix_unitaire;
	}
	else {
		puts("Il n'est pas possible de commander une quantite inferieure a 1");
	}
}

// Tests
// - ligne commande vide
void Supprimer_ligne(type_ligne_commande *tab_commande, type_ligne_commande *adresse_commande, type_ligne_commande **derniere_ligne, float *total) {

	//modification du total
	*total = *total - (adresse_commande->total_ligne);

	while (adresse_commande < *derniere_ligne) {
		*adresse_commande = *(adresse_commande + 1);
		adresse_commande++;
	}

	(*derniere_ligne)->ptr_produit = NULL;
	if (*derniere_ligne != tab_commande) {
		*derniere_ligne--;
	}
}

void Commande_Produit(type_produit *tab_produit, type_ligne_commande *tab_commande, type_ligne_commande **derniere_ligne, float *total) {

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

	//On recherche si le produit existe.
	adresse_produit = Recherche_Produit(no_produit, tab_produit);
	if (adresse_produit == NULL) {
		puts("Commande impossible car le produit n'existe pas.");
	}
	else {
		//Demande la quantité
		printf("Entrez la quantite desiree : ");
		quantite = Saisie_Entier();

		adresse_commande = Recherche_Ligne(no_produit, tab_commande);
		if (adresse_commande == NULL) {
			Ajout_Ligne(derniere_ligne, adresse_produit, quantite, total);
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
void Creation_Facture(char *nom, char *prenom, float total, type_ligne_commande *tab_commande) {
	FILE *fichier_facture;
	char nom_complet[MAX_CHAINE];

	strcpy(nom_complet, nom);
	strcat(nom_complet, prenom);
	fichier_facture = fopen(strcat(nom_complet, ".html"), "w");

	if (fichier_facture == NULL) {
		puts("Impossible de créer le fichier");
	}
	else {
		fputs("<html>\n<head>\n<title>Facture</title>\n</head>\n<body>", fichier_facture);
		fprintf(fichier_facture, "<h1>Facture de %s %s</h1>\n", nom, prenom);
		fputs("<table border>\n<tr bgcolor=\"yellow\">", fichier_facture);
		fputs("<td>No</td><td>Marque</td><td>Ref</td><td>Prix</td><td>Nb</td><td>Total</td></tr>", fichier_facture);
		while (tab_commande->ptr_produit != NULL) {
			fprintf(fichier_facture, "<tr><td>%d</td><td>%s</td><td>%s</td><td>%.2f</td><td>%d</td><td align=\"right\">%.2f</td></tr>", tab_commande->ptr_produit->no, tab_commande->ptr_produit->marque, tab_commande->ptr_produit->ref, tab_commande->ptr_produit->prix_unitaire, tab_commande->quantite, tab_commande->total_ligne);
		}
		fprintf(fichier_facture, "<tr><td>Total</td><td>&nbsp;</td><td>&nbsp;</td><td>&nbsp;</td><td>&nbsp;</td><td align=\"right\">%.2f</td></tr>", total);
		fputs("</table>\n</body>\n</html>", fichier_facture);

		if (fclose(fichier_facture) == EOF) {
			puts("Erreur de fermeture du fichier");
		}
	}
}
