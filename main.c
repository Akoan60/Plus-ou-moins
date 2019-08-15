//AKOAN
//Cree le: 23/05/2019
//Derniere modif: 24/05/2019
//Jeu de Plus ou Moins à l'aide des pointeurs

#define _CRT_SECURE_NO_WARNINGS //Necessaire avec Visual Studio pour eviter une erreur avec scanf
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//Declaration des prototypes
int niveau(int);
void game();
void multijoueur();

//Initialisation des variables
int continuer_la_partie = 1, choix_niveau = 0, nombre_max = 0,
	nombre_entree = 0, nombre_mystere = 0;
const int MIN = 1;
char ami = ' ';
char reponse = ' ';

//Initialisation des pointeurs
int *pointeur_max = &nombre_max, *pointeur_niveau = &choix_niveau,
	*pointeur_mystere = &nombre_mystere;

//Debut fonction principale
int main(int argc, char* argv())
{
	//Initialisation srand()
	srand(time(NULL));

	printf("Le but du jeu est de deviner un nombre entre 1 et la borne que tu choisis.\n\n");

	while (continuer_la_partie)
	{
		//!!! IMPORTANT: La valeur nombre_max utilise dans multijoueur() est determine dans niveau()!!!

		//Le joueur choisi le niveau de difficulte de la partie
		printf("Quel niveau de difficulte est-que tu veux \?\n");
		printf("1. Entre 1 et 100\n2. Entre 1 et 1000\n3. Entre 1 et 10000\n");
		scanf("%d", &choix_niveau);
		printf("\n");
		printf("Tu dois devine un nombre entre 1 et %d\n\n", niveau(choix_niveau));

		//L'utilisateur a le choix entre une parite solo ou a plusieurs
		multijoueur();

		//La partie commence, on demande a l'utilisateur d'entree des valeurs
		game();

		//On demande a l'utlisiateur si il veux refaire une partie
		printf("Est-ce que tu veux rejouer ? y/n \n");
		scanf(" %c", &reponse); //Un espace est mis avant %c pour ignorer les characteres precedent
		switch (reponse)
		{
		case 'y':
			printf("\n");
			break;
		case 'n':
			continuer_la_partie = 0;
			printf("Au revoir !\n");
			break;
		default:
			printf("Je n\'ai pas compris ce que tu veux faire !(\n\n");
			return 0;
		}
	}
	return 0;
}

//Cette fonction permets au joueur de choisir son niveau de jeu
int niveau(int choix_niveau)
{	
	//Determination de la borne superieure en fonction du choix du joueur
	switch (choix_niveau)
	{
	case 1:
		nombre_max = 100;
		break;
	case 2:
		nombre_max = 1000;
		break;
	case 3:
		nombre_max = 10000;
		break;
	default:
		printf("Le niveau que tu as choisi n\'est pas valide !\n");
	}
	return nombre_max;
}

//Cette fonction donne le choix au joueur entre un mode solo ou multijoueur
void multijoueur()
{
	printf("Est-ce que tu joues avec un ami \? y/n\n");
	scanf(" %c", &ami);
	printf("\n");

	switch (ami)
	{
	case 'y':
		printf("Entre le nombre a devine: ");
		scanf("%d", pointeur_mystere);
		break;
	case 'n':
		*pointeur_mystere = (rand() % (*pointeur_max - MIN + 1)) + MIN;
		break;
	default:
		printf("Je n'ais pas compris !");
		return 0;
	}
}

//Cette fonction contient le jeu principale, les valeurs entrees par l'utlisateur sont comparees a la valeur mystere
void game()
{
	//Initialisation du compteur a chaque partie
	int compteur = 0;
	do
	{
		printf("Quelle est le nombre ? ");
		scanf("%d", &nombre_entree);
		if (*pointeur_mystere > nombre_entree)
		{
			printf("C\'est plus!\n");
		}
		else if (*pointeur_mystere < nombre_entree)
		{
			printf("C\'est moins !\n");
		}
		compteur++;
	} while (nombre_entree != *pointeur_mystere);

	printf("\nBravo, tu as trouve le nombre mystere apres %d essai(s) !\n\n", compteur);
}