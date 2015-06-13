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

// Charge le fichier produit et l'enregistre dans un tableau de structures
type_produit *Charge_Produits(char chemin_fichier[MAX_CHAINE], int *nb_produits);

void main() {
	type_produit *tab_produit;
	int nb_produit, i;

	nb_produit = 0;

	tab_produit = Charge_Produits("produit.txt", &nb_produit);

	if (tab_produit != NULL) {
		for (i = 0; i < nb_produit; i++) {
			printf("%d %s %s %f\n", tab_produit[i].no, tab_produit[i].marque, tab_produit[i].ref, tab_produit[i].prix_unitaire);
		}
	}

	system("pause");
}

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