#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <unistd.h>
#include <time.h>

typedef struct  liste
{
    char NUMBER[50];
    char STREET[50];
    char CITY[50];
    char POSTCODE[50];

} maliste;

char *strsep (char **stringp, const char *delim){
    char *begin, *end;
    begin = *stringp;
    if (begin == NULL) return NULL;
    end = begin + strcspn (begin, delim);
    if (*end) {  *end++ = '\0';  *stringp = end;  }
    else *stringp = NULL;
    return begin; }


maliste data[20];

void write_intoCSV( int nbDonnees, int temps) {

    FILE *output = fopen("C:\\documents\\projet\\algo\\charge.txt", "w"); //a replacer par chemin qu'on veut pour enregistrer les données
    fprintf(output,"%i,%i,\n",nbDonnees,temps);

    fclose(output);
    output=0;
}

void reverse(maliste  tab[], int i, int j) { //renverse un tableau
    while (i < j)
    {
        maliste temp = tab[i];
        tab[i] = tab[j];
        tab[j] = temp;
        i++;
        j--;
    }

}
//les codes postaux étant des char, on utilise strcmp pour comparer ---> code postqux à remplacer par l'attribut que l'on  veux

//nous avons trié notre tableau d'enregistrement en fonction de leur numero , pour trier en fonction des codes postaux
//il faut juste remplacer NUMBER PAR POSTCODE
//sur la sortie on verra qu'il tri les enregistrement par code postaux du plus petit au plus grand
//nous avons  affiché le tableau non trié et le tableau trié pour que vous voyez la différence 
int giveIndexOfHigherElement(maliste arr[] , int n) {  // renvoie l'indice du plus grand élément parmi ceux d'indices inférieurs ou égal à i
    int mi, i;
    for (mi = 0, i = 0; i < n; ++i)
        if (strcmp(arr[i].NUMBER ,arr[mi].NUMBER)>0)
            mi = i;
    return mi;
}


/**
 * Basé sur l'algorithme de geeksforgeeks  https://www.geeksforgeeks.org/pancake-sorting/
 * @param arr
 * @param n
 */
void triBreton(maliste arr[], int n) //prend en entrée le tableau et la taille du tableau, et le tri de manière croissante
{
    for (int i = n; i > 1; i--)
    {
        int mi = giveIndexOfHigherElement(arr, i);
        if (mi != i - 1)
        {
            reverse(arr, 0,mi);
            reverse(arr, 0,i - 1);
        }
    }
}

int main() {
    FILE *file = fopen("C:\\documents\\projet\\algo\\france.csv", "r");// remplacer par l'emplacement du fichier france.csv sur votre ordinateur 
    char buffer[500];
    if (!file) {
        printf("erreur lors de l'ouverture du fichier");
    }

    int nbLigne = 0;
    int nbChamp ;
    int nbDonnees= 20;
    int i = 0;

    clock_t debut = clock();
    while (fgets(buffer, 500, file) && i < nbDonnees) {
        //lecture d'une ligne
        nbChamp = 0;
        nbLigne++;
        if (nbLigne == 1)
            continue;
        char *s = strdup(buffer);
        char *champ = strsep(&s, ",");
        while (champ) {
            if (nbChamp == 2)
                strcpy(data[i].NUMBER, champ);
            if (nbChamp == 3)
                strcpy(data[i].STREET, champ);
            if (nbChamp == 5)
                strcpy(data[i].CITY, champ);
            if (nbChamp == 8)
                strcpy(data[i].POSTCODE, champ);
            champ = strsep(&s, ",");
            nbChamp++;
        }
        i++;
    }
    clock_t fin = clock();
    int duree =1000 * (fin - debut) / CLOCKS_PER_SEC;
    printf("temps de chargement pour %d donnees :  %d \n",nbDonnees, duree);
    write_intoCSV(nbDonnees ,duree );

    fclose(file);


    printf("#########Affichage des donnees avant le tri breton par code postal croissant \n");
    for (int i=0; i<nbDonnees;i++)
        printf("%s, %s, %s , %s \n", data[i].NUMBER, data[i].STREET, data[i].CITY, data[i].POSTCODE);


    //int arr[] = {1, 3, 4, 2, 7, 3};
   // int arr1[] = { 23, 10, 20, 11, 12, 6, 7 };
    triBreton(data,nbDonnees);
    printf("\n\n#########Affichage apres le tri breton par code postal croissant \n");
    for (int i = 0; i < nbDonnees; ++i)
        printf("%s, %s, %s , %s \n", data[i].NUMBER, data[i].STREET, data[i].CITY, data[i].POSTCODE);

}
