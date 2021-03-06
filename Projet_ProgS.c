/*
Titre			Projet de ProgS

Auteurs			François Bavaud et Guillaume Lefebvre

Description		Programme qui créé un fichier au format HTML à partir d'une commande
				passée par un client et d'un fichier contenant les produits

Date			19.06.2015
Version			1.0

Analyse :
Ce programme gère un seul client et une seule commande, elle-même composée de plusieurs lignes, où
chaque ligne correspond à un produit. On voit donc qu'il n'est pas nécessaire de créer une structure
client ou une structure commande, ceux-ci n'existant qu'à un seul exemplaire.
Par contre, les produits et les lignes de commandes existant en de nombreux exemplaires, il est donc
plus facile de créer une structure pour chacun d'entre eux, puis d'insérer ces structures dans des
tableaux.

Structure du programme :
- Ouverture du fichier produit, puis chargement de son contenu dans le tableau "tab_produit" de structures "type_produit"
- L'utilisateur est ensuite invité à saisir son nom et son prénom, puis de commander un produit
- Pour chaque produit commandé, une structure "type_ligne_commande" est ajoutée au tableau "tab_commande"
- Ensuite l'utilisateur a le loisir de commander d'autres produits, de modifier les quantités commandées
	et de supprimer un produit commandé
- L'utilisateur peut aussi, a tout moment, afficher la facture de la commande ou la générer au format HTML

Choix techniques :
- Utilisation d'un pointeur vers une structure "type_produit" depuis la structure "type_ligne_commande" afin
	de miniser la mémoire utilisée et éviter la redondance des informations
- Utilisation de pointeurs pour manipuler les tableaux afin d'une part de mieux se familiariser avec les pointeurs
	et d'autre part afin de minimiser l'espace mémoire occupé en n'allouant que l'espace nécessaire grâce à
	l'utilisation de l'allocation dynamique.
	Les tableaux "tab_produit" et "tab_commande" possèdent donc chacun un pointeur de premier et de dernier
	élément.
- Utilisation massive de tests pour vérifier les paramètres de chaque fonction, afin de minimiser non pas les 
	erreurs de saisies, mais plutôt les erreurs de programmation
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// Longueur max des entiers saisis (sans \n)
#define MAX_INT 10
// Longueur max d'une ligne d'un fichier (sans \n)
#define MAX_LIGNE 255
// Longueur max des chaînes de caractères
#define MAX_CHAINE 255
// Longueur max des chaînes saisies par l'utilisateur (sans \n)
#define MAX_CHAINE_SAISIE 50
// Nombre max de produits que le fichier FPRODUIT peut contenir
#define MAX_PRODUITS 255
// Fichier contenant la liste des produits
#define FPRODUIT "produit.txt"

// Booléen
#define VRAI 1
#define FAUX 0

// La structure type_produit contient toutes les informations de chaque produit
// chargé depuis le fichier
typedef struct {
	int no;
	char *marque;
	char *ref;
	float prix_unitaire;
} type_produit;

// La structure type_ligne_commande contient toutes les informations de chaque
// ligne de la commande. Un pointeur est utilisé pour référencer le produit
// commandé
typedef struct {
	type_produit *ptr_produit;
	int quantite;
	float total_ligne;
} type_ligne_commande;


// Saisie d'une chaine et vérification de cette chaine 
char *Saisie_Chaine();

// Saisie et vérification d'un entier
int Saisie_Entier();

// Affiche une ligne du tableau commande
void Afficher_Ligne_Commande(type_ligne_commande *ligne_commande);

// Recherche dans le tableau de commande si un n° de produit existe déjà
type_ligne_commande *Recherche_Ligne(int no, type_ligne_commande *tab_commande, type_ligne_commande *derniere_ligne);

// Verifie que les lignes du fichier produit ont un format correct
type_produit Verifie_Ligne_Produit(char ligne[], int no_ligne);

// Charge le fichier produit et l'enregistre dans un tableau de structures
type_produit *Charge_Produits(char chemin_fichier[], type_produit **dernier_produit);

// Recherche dans le tableau de produits si un n° de produit existe déjà. Retourne l'adresse du produit correspondant ou NULL si ce produit n'existe pas.
type_produit *Recherche_Produit(int no, type_produit *tab_produit, type_produit *dernier_produit);

// Ajoute une ligne au tableau de commande
void Ajout_Ligne(type_ligne_commande **tab_commande, type_ligne_commande **derniere_ligne, int nb_produits, type_produit *nv_ptr_produit, int quantite, float *total);

// Modifie la quantité d'une ligne de commande dans le tableau de commande
void Modif_Ligne(int nv_quantite, type_ligne_commande *ligne_commande, float *total);

// Gère l'ajout, la modification et la suppression de ligne dans le tableau de commande
void Commande_Produit(type_produit *tab_produit, type_ligne_commande **tab_commande, type_ligne_commande **derniere_ligne, type_produit *dernier_produit, float *total);

// Supprime une ligne dans le tableau de commande
void Supprimer_ligne(type_ligne_commande **tab_commande, type_ligne_commande *adresse_commande, type_ligne_commande **derniere_ligne, float *total);

// Génère le fichier HTML de facture au nom du client
void Creation_Facture(char *nom, char *prenom, float total, type_ligne_commande *tab_commande, type_ligne_commande *derniere_ligne);

void main() {

	// Déclaration des variables
	int choix;
	int init_nom;
	float total;
	char *nom;
	char *prenom;
	type_ligne_commande *tab_commande, *ligne_commande, *derniere_ligne;
	type_produit *tab_produit, *dernier_produit, *produit_courant;

	// Initialisation des variables
	init_nom = FAUX;
	total = 0;
	tab_commande = NULL;
	derniere_ligne = NULL;
	dernier_produit = NULL;

	// Chargement des produits en mémoire depuis le fichier
	tab_produit = Charge_Produits(FPRODUIT, &dernier_produit);

	// On quitte si on arrive pas à charger les produits
	if (tab_produit != NULL) {

		// Options
		puts("1. Saisir le nom et le prenom du client.");
		puts("2. Commander un produit.");
		puts("3. Afficher la liste des produits commandes.");
		puts("4. Generer la facture.");
		puts("");
		puts("0. Quitter le programme.");
		puts("");
		puts("Choisissez une option.");
		choix = Saisie_Entier();
		while (choix != 0) {
			switch (choix) {
			// Saisie du nom et prénom
			case 1:
				puts("Entrez le nom du client.");
				nom = Saisie_Chaine();

				puts("Entrez le prenom du client.");
				prenom = Saisie_Chaine();

				init_nom = VRAI;
				break;
			// Ajout, modification ou suppression de la commande d'un produit
			case 2:
				if (init_nom) {
					Commande_Produit(tab_produit, &tab_commande, &derniere_ligne, dernier_produit, &total);
				} else {
					puts("Vous ne pouvez pas faire de commande tant que les nom et prenom n'ont pas ete entre.");
				}
				break;
			// Affichage de la commande
			case 3:
				if (tab_commande == NULL) {
					puts("Aucune commande.");
				}
				else {
					// On affiche chaque ligne de la commande
					puts("\nListe des produits commandes : ");
					ligne_commande = tab_commande;
					while (ligne_commande <= derniere_ligne) {
						Afficher_Ligne_Commande(ligne_commande);
						ligne_commande++;
					}
					printf("\nTotal : %.2fCHF.\n\n", total);
				}
				break;
			// Génération de la facture HTML
			case 4:
				if (init_nom) {
					if (tab_commande != NULL) {
						Creation_Facture(nom, prenom, total, tab_commande, derniere_ligne);
					}
					else {
						// Erreur si aucune commande ajoutée
						puts("Vous ne pouvez pas generer de facture tant que");
						puts("vous n'avez pas passe de commande.");
					}
				}
				else {
					// Erreur si le nom n'a pas été initialisé
					puts("Vous ne pouvez pas generer de facture tant que");
					puts("le nom et le prenom n'ont pas ete saisis.");
				}
				break;
			default:
				break;
			}
			puts("Choisissez une option.");
			choix = Saisie_Entier();
		}

		// Libération de la mémoire
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
}

// Vérifie qu'une chaîne saisie soit correcte : pas de chaine vide ni de
// chaîne trop longue. Pas de caractères spéciaux.
// Retourne la chaîne de caractère saisie par l'utilisateur
char *Saisie_Chaine(){
	char chaine_tmp[MAX_CHAINE_SAISIE + 2], *chaine;

	// Tant que la chaîne saisie est incorrecte, on redemande la saisie
	printf("> ");
	fgets(chaine_tmp, MAX_CHAINE_SAISIE + 2, stdin);
	while (chaine_tmp[0] == '\n' || chaine_tmp[strlen(chaine_tmp) - 1] != '\n') {
		if (chaine_tmp[strlen(chaine_tmp) - 1] != '\n') {
			while (getchar() != '\n');
			puts("Nombre de caracteres trop grand.");
		}
		else {
			puts("Saisie invalide.");
		}
		printf("> ");
		fgets(chaine_tmp, MAX_CHAINE_SAISIE + 2, stdin);
	}

	// Suppression du '\n'
	if (chaine_tmp[strlen(chaine_tmp) - 1] == '\n') {
		chaine_tmp[strlen(chaine_tmp) - 1] = '\0';
	}

	// Copie de la chaîne dans un tableau dynamique
	chaine = (char *)malloc(sizeof(char) * strlen(chaine_tmp) + 1);
	strcpy(chaine, chaine_tmp);

	return chaine;
}

// Propose et vérifie la saisie d'un entier par l'utilisateur
int Saisie_Entier(){
	char entier[MAX_INT + 2];
	int ret, valeur;

	printf("> ");
	// lit un entier de max MAX_INT caractères
	fgets(entier, MAX_INT + 2, stdin);
	ret = sscanf(entier, "%d", &valeur);

	// Tant que le nombre saisi est incorrect, on redemande la saisie
	while (ret != 1 || entier[strlen(entier) - 1] != '\n') {
		if (entier[strlen(entier) - 1] != '\n') {
			while (getchar() != '\n');
			puts("Nombre trop grand.");
		}
		else {
			puts("Saisie invalide.");
		}
		printf("> ");
		fgets(entier, MAX_INT + 2, stdin);
		ret = sscanf(entier, "%d", &valeur);
	}

	return valeur;
}

// Affichage d'une ligne de commande
// Paramètres :
// - ligne_commande : élément du tableau tab_commande
void Afficher_Ligne_Commande(type_ligne_commande *ligne_commande) {
	if (ligne_commande != NULL) {
		printf("%4d %-10s %-10s prix unitaire : %6.2fCHF\ttotal : %10.2fCHF\n", ligne_commande->quantite, ligne_commande->ptr_produit->marque, ligne_commande->ptr_produit->ref, ligne_commande->ptr_produit->prix_unitaire, ligne_commande->total_ligne);
	}
}

// Recherche dans le tableau de commande  si une ligne de commande existe déjà pour
// le no de produit donné
// Renvoie NULL si aucune ligne de commande n'existe pour le no de produit donné,
// sinon renvoie un pointeur vers la ligne contenant le produit
// Paramètre :
// - no : Numéro de produit que l'on recherche
// - tab_commande : Tableau dans lequel on recherche le produit
// - derniere_ligne : Adresse du dernier élément du tableau de commande dans lequel on fait la recheche
type_ligne_commande *Recherche_Ligne(int no, type_ligne_commande *tab_commande, type_ligne_commande *derniere_ligne) {
	type_ligne_commande *resultat, *element_courant;

	resultat = NULL;

	// Pas de recherche s'il n'existe aucune commande
	if (tab_commande != NULL && derniere_ligne != NULL) {
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

// Recherche dans le tableau de produits si un n° de produit existe déjà.
// Retourne un pointeur vers le produit correspondant ou NULL si ce produit n'existe pas.
// Paramètre :
// - no : Numéro de produit que l'on recherche
// - tab_produit : Tableau dans lequel on recherche le produit
// - dernier_produit : Adresse du dernier élément du tableau de produit dans lequel on fait la recheche
type_produit *Recherche_Produit(int no, type_produit *tab_produit, type_produit *dernier_produit) {
	type_produit *resultat, *element_courant;

	resultat = NULL;

	// Pas de recherche s'il n'existe aucun produit
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

// Vérifie si une ligne du fichier "produit" ne contient pas d'erreur
// 	Retourne le produit extrait de la ligne  si aucune erreur,
// 	sinon retourne un produit "vide" dont le no vaut -1
// Paramètre :
// - ligne : Ligne du fichier "produit" que l'on va vérifier
// - no_ligne : numéro de la ligne dans le fichier "produit"
type_produit Verifie_Ligne_Produit(char ligne[], int no_ligne) {
	int ret, erreur, no;
	float prix;
	char marque[MAX_CHAINE], ref[MAX_CHAINE];
	type_produit produit;

	erreur = FAUX;

	if (ligne[strlen(ligne) - 1] != '\n' && strlen(ligne) >= MAX_LIGNE) {
		printf("Nombre de caracteres trop grand sur la ligne %d.\n", no_ligne + 1);
		erreur = VRAI;
	}
	else {
		ret = sscanf(ligne, "%d\t%s\t%s\t%f", &no, marque, ref, &prix);
		if (ret != 4) {
			printf("Le format de la ligne %d est incorrect.\n", no_ligne + 1);
			erreur = VRAI;
		}
		else {
			if (no < 0) {
				printf("La ligne %d est contient un no de produit invalide (< 0).\n", no_ligne + 1);
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

// Charge le fichier produit et l'enregistre dans un tableau de structures.
// Renvoie un pointeur vers le tableau de structures si le chargement à réussi,
// 	sinon renvoie NULL
// Toute erreur lors du chargement du fichier est considérée comme fatale et
// 	entraîne l'annulation du chargement
// Paramètre :
// - chemin_fichier : chemin du fichier produit.txt que l'on charge
// - dernier_produit : adresse de la ligne du dernier produit du tableau tab_produit
type_produit *Charge_Produits(char chemin_fichier[], type_produit **dernier_produit) {
	FILE *fichier_produit;
	char ligne[MAX_LIGNE + 2], *ret;
	type_produit *tab_produit, tab_produit_tmp[MAX_PRODUITS], produit;
	int i, no_ligne;
	int erreur;

	erreur = FAUX;
	no_ligne = 0;
	fichier_produit = fopen(chemin_fichier, "r");

	if (fichier_produit == NULL) {
		printf("Le fichier %s n'existe pas ou n'est pas accessible.\n", chemin_fichier);
		erreur = VRAI;
	}
	else {
		// Une fois le fichier ouvert, on récupère chaque ligne du fichier tant
		// qu'il existe des lignes
		ret = fgets(ligne, MAX_LIGNE + 2, fichier_produit);
		while (ret != NULL && !erreur) {
			if (no_ligne >= MAX_PRODUITS) {
				printf("Le fichier %s contient trop de produits\n", chemin_fichier);
				erreur = VRAI;
			}
			else {
				// On vérifie chaque ligne, puis si la ligne est ok, on ajoute le
				// produit correspondant au tableau tab_produit_tmp
				produit = Verifie_Ligne_Produit(ligne, no_ligne);
				if (produit.no != -1) {
					if (Recherche_Produit(produit.no, tab_produit_tmp, *dernier_produit) != NULL) {
						printf("La ligne %d contient un doublon\n", no_ligne + 1);
						erreur = VRAI;
					}
					else {
						tab_produit_tmp[no_ligne] = produit;
						*dernier_produit = &tab_produit_tmp[no_ligne];
					}
				}
				else {
					erreur = VRAI;
				}
				no_ligne++;
			}
			ret = fgets(ligne, MAX_LIGNE + 2, fichier_produit);
		}
		if (fclose(fichier_produit) == EOF) {
			printf("Erreur de fermeture du fichier %s.\n", chemin_fichier);
			erreur = VRAI;
		}

		if (ret == NULL && no_ligne == 0) {
			printf("Le fichier %s est vide.\n", chemin_fichier);
			erreur = VRAI;
		}
	}

	if (erreur) {
		return NULL;
	}
	else {
		// On copie la tableau statique des produits chargés dans un tableau
		// dynamique
		tab_produit = (type_produit *)malloc(no_ligne * sizeof(type_produit));
		for (i = 0; i < no_ligne; i++) {
			tab_produit[i] = tab_produit_tmp[i];
		}

		*dernier_produit = tab_produit + i - 1;

		return tab_produit;
	}
}

// Ajoute une ligne de commande au tableau des commandes, recalcule le total de la commande
// et incrémente le pointeur de dernière ligne de commande
// Paramètre :
// - nb_produits : nombre de produit total dans le tableau tab_produit
// - nv_ptr_produit : adresse du produit choisi dans le tableau tab_produit
// - total : prix total de la commande, qui sera ici modifiée
// - quantite : quantite que l'on veut commander du produit choisi
// - tab_commande : Tableau dans lequel on va ajouter une ligne pour le produit commandé
// - derniere_ligne : Adresse de la dernière ligne du tableau tab_commande
void Ajout_Ligne(type_ligne_commande **tab_commande, type_ligne_commande **derniere_ligne, int nb_produits, type_produit *nv_ptr_produit, int quantite, float *total) {

	if (nb_produits <= 0 || nv_ptr_produit == NULL) {
		puts("Erreur d'adressage.");
	}
	else {
		if (quantite > 0) {
			// Préparation pour insertion de la 1ère ligne
			if (*tab_commande == NULL) {
				*tab_commande = (type_ligne_commande *)malloc(sizeof(type_ligne_commande) * nb_produits);
				*derniere_ligne = *tab_commande;
			}
			// Préparation pour insertion des autres lignes
			else {
				(*derniere_ligne)++;
			}
			(*derniere_ligne)->ptr_produit = nv_ptr_produit;
			(*derniere_ligne)->quantite = quantite;
			(*derniere_ligne)->total_ligne = quantite * nv_ptr_produit->prix_unitaire;
			*total = *total + (*derniere_ligne)->total_ligne;

			// Affichage de la nouvelle ligne de commande
			Afficher_Ligne_Commande(*derniere_ligne);
		}
		else {
			puts("La quantite saisie ne peut etre <= 0.");
		}
	}
}

// Modifie une ligne de commande du tableau des commandes et recalcule le total de la commande
// Paramètre :
// - nv_quantite : modification que l'on apporte à la quantite d'un produit commande
// - ligne_commande : adresse de la ligne du tableau tab_commande où la quantite sera modifiée
// - total : prix total de la commande, qui sera ici modifiée
void Modif_Ligne(int nv_quantite, type_ligne_commande *ligne_commande, float *total) {

	if (ligne_commande == NULL) {
		puts("Erreur : la ligne est indéfinie.");
	}
	else {
		if (nv_quantite + ligne_commande->quantite > 0) {
			ligne_commande->quantite = nv_quantite + ligne_commande->quantite;
			ligne_commande->total_ligne = ligne_commande->quantite * ligne_commande->ptr_produit->prix_unitaire;

			*total = *total + nv_quantite * ligne_commande->ptr_produit->prix_unitaire;

			// Affichage de la ligne de commande modifiée
			Afficher_Ligne_Commande(ligne_commande);
		}
		else {
			puts("Il n'est pas possible de commander une quantite inferieure a 1.");
		}
	}
}

// Supprime une ligne de commande du tableau des commandes, recalcule le total de la commande,
// 	décale les éléments du tableau situés à droite de l'élément supprimé d'un cran à gauche et
// 	décrémente le pointeur de dernière ligne de commande
// Paramètre :
// - tab_commande : tableau qui contient les commandes. l'une d'elle sera supprimée.
// - adresse_commande : adresse correspondant à l'élément qui sera supprimé
// - total : prix total de la commande, qui sera ici modifiée
// - derniere_ligne : adresse de la dernière ligne du tableau tab_commande
void Supprimer_ligne(type_ligne_commande **tab_commande, type_ligne_commande *adresse_commande, type_ligne_commande **derniere_ligne, float *total) {

	if (*tab_commande != NULL && adresse_commande != NULL && *derniere_ligne != NULL) {

		*total = *total - (adresse_commande->total_ligne);

		// Décalage des éléments
		while (adresse_commande < *derniere_ligne) {
			*adresse_commande = *(adresse_commande + 1);
			adresse_commande++;
		}

		// Si le dernier élément est supprimé, libération de la mémoire
		if (*derniere_ligne == *tab_commande) {
			free(*tab_commande);
			*tab_commande = NULL;
		}
		else {
			(*derniere_ligne)--;
		}
		puts("La commande a ete supprimee.");
	}
	else {
		puts("Erreur d'adressage");
	}
}

// Gestion de l'ajout, modification ou suppression d'une ligne de commande
// Paramètre :
// - tab_produit : tableau contenant tous les produits. On ira y chercher les adresses des lignes du tableau selon les produit
// - tab_commande : tableau dans lequel seront ajouté, modifié ou supprimé des lignes correspondant à des commandes de produit
// - derniere_ligne : Adresse de la dernière ligne du tableau de tab_commande
// - dernier_produit : Adresse de la dernière ligne du tableau tab_produit
// - total : Prix total de la commande
void Commande_Produit(type_produit *tab_produit, type_ligne_commande **tab_commande, type_ligne_commande **derniere_ligne, type_produit *dernier_produit, float *total) {

	int no_produit, quantite, nb_produits;
	type_produit *adresse_produit;
	type_ligne_commande *adresse_commande;

	puts("Entrez le numero de produit.");
	no_produit = Saisie_Entier();
	while (no_produit < 0){
		puts("Un numero de produit ne peut pas être negatif. Entrez à nouveau.");
		no_produit = Saisie_Entier();
	}

	// On recherche si le produit existe.
	adresse_produit = Recherche_Produit(no_produit, tab_produit, dernier_produit);
	if (adresse_produit == NULL) {
		puts("Commande impossible car le produit n'existe pas.");
	}
	else {
		puts("Entrez la quantite desiree.");
		quantite = Saisie_Entier();

		// On recherche si une ligne de commande contient déjà ce produit
		adresse_commande = Recherche_Ligne(no_produit, *tab_commande, *derniere_ligne);
		// Si non, on ajoute une ligne
		if (adresse_commande == NULL) {
			if (dernier_produit == NULL || tab_produit == NULL) {
				puts("Erreur d'adressage.");
			}
			else {
				// On calcule le nb de produits en fonction des adresses du premier et du dernier produit
				nb_produits = dernier_produit - tab_produit + 1;
				Ajout_Ligne(tab_commande, derniere_ligne, nb_produits, adresse_produit, quantite, total);
			}
		}
		// Si oui, on modifie ou on supprime une ligne selon la quantité
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

// Génération du fichier HTML de la facture
// Paramètre :
// - nom : nom du client
// - prenom : prénom du client
// - total : prix total de la commande
// - tab_commande : tableau contenant toutes les lignes de commande
// - dernier_ligne : adresse de la dernière ligne du tableau tab_commande
void Creation_Facture(char *nom, char *prenom, float total, type_ligne_commande *tab_commande, type_ligne_commande *derniere_ligne) {
	FILE *fichier_facture;
	char nom_complet[MAX_CHAINE];

	if (tab_commande == NULL || derniere_ligne == NULL) {
		puts("Erreur d'adressage.");
	}
	else {
		// On nomme le fichier d'après le nom et prénom de la personne
		strcpy(nom_complet, nom);
		strcat(nom_complet, prenom);
		fichier_facture = fopen(strcat(nom_complet, ".html"), "w");

		if (fichier_facture == NULL) {
			puts("Impossible de creer le fichier, verifier le nom ou les droits.");
		}
		else {
			fputs("<html>\n<head>\n<title>Facture</title>\n</head>\n<body>\n", fichier_facture);
			fprintf(fichier_facture, "<h1>Facture de %s %s</h1>\n", nom, prenom);
			fputs("<table border>\n<tr bgcolor=\"yellow\">", fichier_facture);
			fputs("<td>No</td><td>Marque</td><td>Ref</td><td>Prix</td><td>Nb</td><td>Total</td></tr>\n", fichier_facture);
			// On imprime chaque ligne de commande
			while (tab_commande <= derniere_ligne) {
				fprintf(fichier_facture, "<tr><td>%d</td><td>%s</td><td>%s</td><td>%.2f</td><td>%d</td><td align=\"right\">%.2f</td></tr>\n", tab_commande->ptr_produit->no, tab_commande->ptr_produit->marque, tab_commande->ptr_produit->ref, tab_commande->ptr_produit->prix_unitaire, tab_commande->quantite, tab_commande->total_ligne);
				tab_commande++;
			}
			// On imprime le total de la commande
			fprintf(fichier_facture, "<tr><td>Total</td><td>&nbsp;</td><td>&nbsp;</td><td>&nbsp;</td><td>&nbsp;</td><td align=\"right\">%.2f</td></tr>\n", total);
			fputs("</table>\n</body>\n</html>", fichier_facture);

			printf("Fichier facture %s genere avec succes.\n", nom_complet);

			if (fclose(fichier_facture) == EOF) {
				puts("Erreur de fermeture du fichier.");
			}
		}
	}
}
