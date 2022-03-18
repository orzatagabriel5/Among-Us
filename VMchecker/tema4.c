#include "utils.h"

void* (* Abilities[4])(void* x) = {RotateMatrix, DecodeString, InvertArray, KillPlayer};

char *fromEnumtoString(PlayerRoles playerRole)
{
	char *str = calloc(MAX_LEN_STR_ATR, sizeof(char));
	switch(playerRole)
	{
		case Rotator:
			str = strcpy(str, "Rotator");
			break;
		case Decoder:
			str = strcpy(str, "Decoder");
			break;
		case Invertor:
			str = strcpy(str, "Invertor");
			break;
		case Impostor:
			str = strcpy(str, "Impostor");
			break;
	}
	return str;
}

// Task 1
void *RotateMatrix(void *input)
{
	
	// TODO
	int n = *((int*)input);
	int **matrice, **copie, i, j;
	matrice = (int**)malloc(MAX_LEN_STR_LOC * sizeof(int*));
	copie = (int**)malloc(MAX_LEN_STR_LOC *sizeof(int*));
	for(i = 0; i < n; i++)
	{
		*(matrice + i) = (int*)malloc(MAX_LEN_STR_LOC * sizeof(int));
	}
	
	for(i = 0; i < n; i++)
	{
		*(copie + i) = (int*)malloc(MAX_LEN_STR_LOC * sizeof(int));
	}
	//Am alocat o matrice si o copie unde pun valorile initiale
	for (i = 0; i < n; i++)
	{	for(j = 0; j < n; j++)
		{
			if(j + 1 < 10)
			{
				*(*(copie + i) + j) = (i + 1) * 10 + j + 1;
			}else if(j + 1 >= 10 && j + 1 < 100)
			{
				*(*(copie + i) + j) = (i + 1) * 100 + j + 1;
			}else if(j + 1 >= 100)
			{
				*(*(copie + i) + j) = (i + 1) * 1000 + j + 1;
			}
		}
	}
	for(i = 0; i < n; i++)
    {
        for(j = n - 1; j >= 0; j--)
        {
            matrice[i][(n-1)-j] = copie[j][i];
        }
    }
	//Aici am rotit matricea
	char *v, cifre[10];
	int aux, q, count, z = 0;
	v = malloc(MAX_LEN_STR_OUT * sizeof(char));
	//Pentru a scrie matricea intr-un sir de caractere
	//am luat fiecare cifra din numerele din matrice
	//si le-am introdus pe rand in vectorul de caractere v.
	//Cand ajung la finalul unei linii adaug /n la vector,
	//iar daca nu adaug un spatiu, dar mai putin atunci cand
	//ajung la finalul matricei, unde pun terminatorul de sir.
	for(i = 0 ; i < n ; i++)
	{
		for(j = 0 ; j < n; j++)
		{
			count = 0;
			aux = matrice[i][j];
			while (aux != 0)
			{
				cifre[count] = aux % 10 + 48;
				aux = aux / 10;
				count++;
			}
			for(q = count - 1; q >= 0; q--)
			{
				*(v + z) = cifre[q];
				z++;
			}
			if(j == n - 1 && i != n - 1)
			{
				v[z] = '\n';
				z++;
			}else if(j == n - 1 && i == n - 1)
			{
				z++;
			}else
			{
				v[z] = ' ';
				z++;
			}
		}
	} 
	v[z] = '\0';
	
	for(i = 0; i < n; i++)
	{
		free(matrice[i]);
		free(copie[i]);
	}
	free(matrice);
	free(copie);
	return v;
}

// Task 2

void *DecodeString(void *input)
{
	// TODO
	//Am folosit functia strtok ca sa citresc numai
	//numerele intregi din sirul de caractere si
	//in acelasi timp le-am adunat in variabila sum,
	//pe care am transformat-o intr-un sir de caractere
	// cu funtia sprintf.
	long long suma = 0;
	char *p;
	char *n = (char*)input;
    p = strtok(n, "_");
	while (p != NULL)
	{
		suma += atoi(p);
		p = strtok(NULL, "_");
	} 
	char *s;
	s = malloc(MAX_LEN_STR_LOC * sizeof(char));
	sprintf(s, "%lld", suma);
	return (void *)s;
}

//Task 3
void *InvertArray(void *input)
{
	int *v = (int*)input, i, j, aux, x, z = 0, count, *cifre, *invers;
	x = v[0];
	unsigned char *sir;
	invers = malloc(MAX_LEN_STR_LOC * sizeof(int));
	cifre = malloc(MAX_LEN_STR_LOC * sizeof(int));
	sir = malloc(MAX_LEN_STR_LOC * sizeof(char));
	if(x % 2 == 0){
		for(i = 0; i < x / 2; i++){
			//Aici am intershimbat valorile.
			aux = v[2 * i + 1];
			v[2 * i + 1] = v[2 * i + 2];
			v[2 * i + 2] = aux;
		}
		for(i = 0; i < x; i++){
			//Am suprascris primul element din vector.
			v[i] = v[i + 1];
		}
		for(i = 0; i < x; i++){
			count = 0;
			aux = v[i];
			//Pentru fiecare cifra din fiecare numar din invers
			//scriu in vectorul cifre valoarea corepsunzatoare 
			//acestora din sirul ascii.
			int negativ = 0;
			// Daca numarul este negativ il inmultesc cu -1
			// si setez un flag.
			if (aux < 0){
				aux = aux * (-1);
				negativ = 1;
			}
			if(aux == 0){
				cifre[count] = 0 + 48;
				count++;
			} else{
				while(aux != 0){
					cifre[count] = aux % 10 + 48;
					aux = aux / 10;
					count++;
				}
			}
			//Daca numarul a fost negativ pun un - in fata sirului de cifre.
			if(negativ == 1)
			{
				cifre[count] = '-';
				count++;
			}
			for(j = count - 1; j >= 0; j--){
				sir[z] = cifre[j];
				z++;
			}
			//Copiez in sir[] fiecare cifra din cifre[] care ca deveni
			//un caracter, pun spatiu intre fiecare numar scris
			//si la final pun terminatorul de sir.
			//count este folosit pt a stii cate cifre are fiecare numar.
			if(i != x - 1){
				sir[z] = ' ';
				z++;
			}
		}
		sir[z] = '\0';
		free(cifre);
		free(invers);
		return (void*)sir;
	} else{
		//Suprascriu primul element din vector
		for(i = 0; i < x; i++){
			v[i] = v[i + 1];
		}
		//Dau lui invers valorile din v
		//de la ultimul la primul element
		for(i = 0; i < x; i++){
			invers[x - 1 - i] = v[i];
		}
		for(i = 0; i < x; i++){
			count = 0;
			aux = invers[i];
			int negativ = 0;
			if (aux < 0){
				negativ = 1;
				aux = aux * (-1);
			}
			if(aux == 0){
				cifre[count] = 0 + 48;
				count++;
			} else
			{
				while(aux != 0){
					cifre[count] = aux % 10 + 48;
					aux = aux / 10;
					count++;
				}
			}
			if(negativ == 1)
			{
				cifre[count] = '-';
				count++;
			}
			for(j = count - 1; j >= 0; j--){
				sir[z] = cifre[j];
				z++;
			}
			if(i != x - 1){
				sir[z] = ' ';
				z++;
			}	
		}
		sir[z] = '\0';
		free(cifre);
		free(invers);
		return (void*)sir;
	}
	free(cifre);
	free(invers);

	return NULL;
}

//Task 4
Player *allocPlayer()
{
	// TODO
	Player *player = malloc(sizeof(Player));
	player->name = malloc(MAX_LEN_STR_ATR * sizeof(char));
	player->color = malloc(MAX_LEN_STR_ATR * sizeof(char));
	player->hat = malloc(MAX_LEN_STR_ATR * sizeof(char));
	player->alive = 1;
	player->indexOfLocation = 0;
	return player;
}

//Task 4
Game *allocGame()
{
	// TODO
	Game *game = malloc(sizeof(Game));
	game->name = malloc(MAX_LEN_STR_ATR * sizeof(char));
	return game;
}

//Task 5
Player *ReadPlayer(FILE *inputFile)
{
	// TODO
	Player *player;
	player = allocPlayer();
	int numar_locatii, contor = 0, i=0;
	char str[1200], nume_jucator[100], culoare[20], palarie[30], *p;
	fscanf(inputFile, "%s", nume_jucator);
	fscanf(inputFile, "%s", culoare);
	fscanf(inputFile, "%s", palarie);
	strcpy(player->name, nume_jucator);
	strcpy(player->color, culoare);
	strcpy(player->hat, palarie);
	fscanf(inputFile, "%d\n", &numar_locatii);
	player->numberOfLocations = numar_locatii;
	fgets(str, 1200, inputFile);
	str[strlen(str) - 1] = '\0';
	p = strtok(str, "() ,\n");
	//Am alocat si restul de elemente din cele 2 structuri
	player->locations = (Location*)malloc(MAX_LEN_STR_LOC * sizeof(Location));
	while(p != NULL)
	{
		if(contor % 2 == 0)
		{
			player->locations[i].x = atoi(p);
			contor++;
		} else
		{
			player->locations[i].y = atoi(p);
			contor++;
			i++;
		}
		p = strtok(NULL, "() ,\n");
	}
	char rol[20];
	fscanf(inputFile, "%s", rol);
	//In functie de de rolul jucatorului pun la playerRole
	// valoarea unui enum.
	if(strcmp(rol, "Rotator") == 0)
	{
		player->playerRole = Rotator;
	}
	if(strcmp(rol, "Decoder") == 0)
	{
		player->playerRole = Decoder;
	}
	if(strcmp(rol, "Invertor") == 0)
	{
		player->playerRole = Invertor;
	}
	if(strcmp(rol, "Impostor") == 0)
	{
		player->playerRole = Impostor;
	}

	player->ability = Abilities[player->playerRole];

	return player;
}

// Task 5
Game *ReadGame(FILE *inputFile)
{
	// TODO
	int i;
	Game *game;
	game = allocGame();
	char nume[20];
	int kill_range, numar_crewmates;
	fscanf(inputFile, "%s", nume);
	fscanf(inputFile, "%d", &kill_range);
	fscanf(inputFile, "%d", &numar_crewmates);
	strcpy(game->name, nume);
	game->killRange = kill_range;
	game->numberOfCrewmates = numar_crewmates;
	game->crewmates = (Player**)malloc(numar_crewmates * sizeof(Player*));
	// Aloc fiecare crewmate cu allocPlayer si
	// dupa apelez ReadPlayer pt fiecare.
	for(i = 0; i < numar_crewmates; i++)
	{
		game->crewmates[i] = allocPlayer();
		game->crewmates[i] = ReadPlayer(inputFile);
	}
	game->impostor = allocPlayer();
	game->impostor = ReadPlayer(inputFile);
	return game;
}

// Task 6
void WritePlayer(Player *player, FILE *outputFile)
{
	// TODO
	int i;
	fprintf(outputFile, 
	"Player %s with color %s, hat %s and role %s has entered the game.\n",
	player->name, player->color, player->hat, fromEnumtoString(player->playerRole));
	fprintf(outputFile, "%s","Player's locations: ");
	for(i = 0; i < player->numberOfLocations; i++)
	{
		fprintf(outputFile, "(%d,%d) ", player->locations[i].x, player->locations[i].y);
	}
	fprintf(outputFile, "%s","\n");
	return;
}

// Task 6
void WriteGame(Game *game, FILE *outputFile)
{
	// TODO	
	int i;
	fprintf(outputFile, "Game %s has just started!\n", game->name);
	fprintf(outputFile, "\tGame options:\n");
	fprintf(outputFile, "Kill Range: %d\n", game->killRange);
	fprintf(outputFile, "Number of crewmates: %d\n\n", game->numberOfCrewmates);
	fprintf(outputFile, "%s","\tCrewmates:\n");
	for(i = 0; i < game->numberOfCrewmates; i++)
	{
		WritePlayer(game->crewmates[i], outputFile);
	}
	fprintf(outputFile, "%s","\n\tImpostor:\n");
	WritePlayer(game->impostor, outputFile);
	return;
}

//Task 7
void *KillPlayer(void *input)
{
	// TODO
	int i, dist, min = 9999, contor;
	char *output = malloc(MAX_LEN_STR_LOC * sizeof(char)), d[20];
	Game *game = (Game*)input;
	for(i = 0; i < game->numberOfCrewmates; i++)
	{	
		int index = game->crewmates[i]->indexOfLocation;
		int index_impostor = game->impostor->indexOfLocation;
		if(game->crewmates[i]->alive == 0)
		{
			//Daca jucatorul este mort trec peste el.
			continue;
		}
		dist = abs(game->impostor->locations[index_impostor].x - game->crewmates[i]->locations[index].x)
			+ abs(game->impostor->locations[index_impostor].y - game->crewmates[i]->locations[index].y);
		if(dist <= min && dist <= game->killRange)
		{
			//Aici pun distanta minima in min si salvez index-ul jucatorului
			// care va fi omorat.
			min = dist;
			contor = i;
		}
	}
	if(min == 9999)
	{
		//Daca min nu este modificat inseamna ca jucatorul nu
		//a omorat pe nimeni.
		strcpy(output, "Impostor ");
		strcat(output, game->impostor->name);
		strcat(output, " couldn't kill anybody.");
	} else
	{
		//Daca min isi schimba valoarea initiala jucatorul
		//cu index-ul contor moare.
		game->crewmates[contor]->alive = 0;
		strcpy(output, "Impostor ");
		strcat(output, game->impostor->name);
		strcat(output, " has just killed crewmate ");
		strcat(output, game->crewmates[contor]->name);
		strcat(output, " from distance ");
		sprintf(d, "%d", min);
		strcat(output, d);
		strcat(output, ".");
	}
	

	return (void*)output;
}

// Task 8
void CalcuateNextCycleOfGame(Game *game, FILE *outputFile, void **inputMatrix)
{
	// TODO
	int i;

	for(i = 0; i < game->numberOfCrewmates; i++)
	{
		int index;
		//Daca jucatorul are doar o locatie
		//indexul lui va fi mereu 0.
		if(game->crewmates[i]->numberOfLocations == 1)
		{
			index = 0;
		} else 
		{
			index = game->crewmates[i]->indexOfLocation;
		}
		//Ca sa incep cu indexOfLocation 1 l-am incrementat
		// de la inceput cu 1.
		if(index == game->crewmates[i]->numberOfLocations - 1)
		{
			game->crewmates[i]->indexOfLocation = 0;
		} else
		{
			game->crewmates[i]->indexOfLocation += 1; 
		}
		//Dau inca odata lui index valoarea de la indexOfLocation
		//pentru ca am incrementat-o cu 1.
		index = game->crewmates[i]->indexOfLocation;


		if(game->crewmates[i]->alive == 0)
		{
			fprintf(outputFile, "Crewmate %s is dead.\n", game->crewmates[i]->name);
		} else
		{
			fprintf(outputFile, "Crewmate %s went to location (%d,%d).\n", game->crewmates[i]->name, 
			game->crewmates[i]->locations[index].x, game->crewmates[i]->locations[index].y);
			fprintf(outputFile, "Crewmate %s's output:\n", game->crewmates[i]->name);
			fprintf(outputFile, "%s\n", (char*)Abilities[game->crewmates[i]->playerRole](inputMatrix[i]));
		}
	}
	//La fel am facut si la impostor.
	int index_impostor;
	if(game->impostor->numberOfLocations == 1)
	{
		index_impostor = 0;
	} else
	{
		index_impostor = game->impostor->indexOfLocation;
	}
	
	if(index_impostor == game->impostor->numberOfLocations - 1)
	{
		game->impostor->indexOfLocation = 0;
	} else
	{
		game->impostor->indexOfLocation += 1;
	}

	index_impostor = game->impostor->indexOfLocation;

	fprintf(outputFile, "Impostor %s went to location (%d,%d).\n", game->impostor->name, 
			game->impostor->locations[index_impostor].x, game->impostor->locations[index_impostor].y);
	fprintf(outputFile, "Impostor %s's output:\n", game->impostor->name);
	fprintf(outputFile, "%s\n", (char*)Abilities[game->impostor->playerRole](inputMatrix[i]));

	return;
}

// Task 9
//Am dat free la tot ce am alocat dinamic in program
//mai putin la ce trebuia sa dau return.
void FreePlayer(Player *player)
{
	// TODO
	free(player->name);
	free(player->color);
	free(player->hat);
	free(player->locations);
	free(player);
	return;
}

// Task 9
void FreeGame(Game *game)
{
	
	free(game->name);
	free(game->impostor);
	for(int i = 0; i < game->numberOfCrewmates; i++)
	{
		FreePlayer(game->crewmates[i]);
	}
	free(game->crewmates);
	free(game);
	// TODO
	return;
}

