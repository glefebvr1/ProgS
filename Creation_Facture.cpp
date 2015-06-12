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

bool Creation_Facture(char chemin_fichier[MAX_CHAINE], char *nom, char *prenom, float total, type_ligne_commande *tab_commande, int nb_ligne_commande);

void main() {
	type_produit *tab_produit;
	int nb_produit, i;

	system("pause");
}


bool Creation_Facture(char chemin_fichier[MAX_CHAINE], char *nom, char *prenom, float total, type_ligne_commande *tab_commande, int nb_ligne_commande) {
	FILE *fichier_facture;
	int i;
	bool erreur;

	erreur = FAUX;
	fichier_facture = fopen(chemin_fichier, "w");

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