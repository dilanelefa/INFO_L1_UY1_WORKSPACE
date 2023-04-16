#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

#define nomFichier "repertoire.txt"
#define length "nb.txt"

typedef struct contact
{
    char nom[20];
    char prenom[20];
    int age;
    char n_telephone[11];   
}contact;

int length_contact()
{
    FILE *file;
    file = fopen(length , "r");
    if(file == NULL)
    {
        exit(EXIT_FAILURE);
    }
    int n;
    fread(&n,sizeof(int), 1, file);
    if(fclose(file) == EOF)
        exit(EXIT_FAILURE);
    return n;
}

void tri_aphabet(contact p1[])
{
    int n = length_contact();
    int i , permut;
    contact temp;
    do
    {
        permut = 1;
        for(i = 0; i < n-1 ; i++)
        {
            if(strcmp(p1[i].nom , p1[i+1].nom) >= 0)
            {
                temp = p1[i];
                p1[i] = p1[i+1];
                p1[i+1] = temp;
                permut = 0;
            }
        }
    } while (permut != 1);
}

void Enregistrer_contact()
{
    system("cls");
    printf("\n\n\t-----------------| REPERTOIRE DE CONTACT|----------------\n\n");
    contact con;
    FILE *file;
    file = fopen(nomFichier , "a");
    if(file == NULL)
    {
        exit(EXIT_FAILURE);
    }
    printf("\t\tEnregistrement du contact\n");
    printf("\t\t\t Nom: ");
    scanf("%s",con.nom);
    printf("\t\t\t Prenom: ");
    scanf("%s", con.prenom);
    printf("\t\t\t Age: ");
    scanf("%d", &con.age);
    printf("\t\t\t Numero de telephone: ");
    fflush(stdin);
    scanf("%[^\n]", con.n_telephone);
    fwrite(&con, sizeof(contact), 1, file);
    if(fclose(file) == EOF)
        exit(EXIT_FAILURE);
    
    int n = length_contact();
    n++;
    file = fopen(length , "w");
    if(file == NULL)
    {
        exit(EXIT_FAILURE);
    }
    fwrite(&n,sizeof(int), 1, file);
    if(fclose(file) == EOF)
        exit(EXIT_FAILURE);
    
    printf("\t\t Contact bien enregistrer");
    getch();
}

void recuperer_contact(contact p1[])
{
    int i,n;
    n = length_contact();
    FILE *file;
    file = fopen(nomFichier , "r");
    if(file == NULL)
    {
        exit(EXIT_FAILURE);
    }
    for(i = 0; i < n ; i++)
    {   
        fread(&p1[i], sizeof(contact), 1, file);
    }
    if(fclose(file) == EOF)
        exit(EXIT_FAILURE);
}

void afficher_repertoire()
{
    system("cls");
    printf("\n\n\t-----------------| REPERTOIRE DE CONTACT|----------------\n\n");
    int i;
    int n = length_contact();
    contact p1[n];
    recuperer_contact(p1);
    printf("\t\t%-20s %-15s %-4s %-15s\n", "Nom", "Prenom", "Age", "Numero Telephone");
    printf("\t\t----------------------------------------------------------\n");
    for(i = 0; i < n ; i++)
    {   
        printf("\t\t%-20s %-15s %-4d %-15s\n", p1[i].nom , p1[i].prenom, p1[i].age, p1[i].n_telephone);
    }

   getch();
}

void rechercher_par_nom()
{
    system("cls");
    printf("\n\n\t-----------------| REPERTOIRE DE CONTACT|----------------\n\n");
    int i;
    int n = length_contact();
    contact p1[n];
    recuperer_contact(p1);
    char nom[20];
    printf("\t\tnom de la personne: ");
    scanf("%s", nom);
    printf("\t\tElement trouve.\n\n");
    printf("\t\t%-20s %-15s %-4s %-15s\n", "Nom", "Prenom", "Age", "Numero Telephone");
    printf("\t\t----------------------------------------------------------\n");
    for(i = 0; i < n ; i++)
    {
        if(strcmp(nom , p1[i].nom) == 0)
        {
            printf("%-20s %-15s %-4d %-15s\n", p1[i].nom , p1[i].prenom, p1[i].age, p1[i].n_telephone);
        }
    }   

    getch();
}

void rechercher_direct(int n)
{
    if(n > length_contact() || n == 0)
    {
        printf("\t\tContact non exitant.\n");
        return;
    }

    FILE *file;
    file = fopen(nomFichier , "r");
    fseek(file, sizeof(contact)*(n-1) , SEEK_SET);
    contact p1;
    fread(&p1,sizeof(contact), 1, file);
    printf("\t\t%-20s %-15s %-4s %-15s\n", "Nom", "Prenom", "Age", "Numero Telephone");
    printf("\t\t----------------------------------------------------------\n");
    printf("\t\t%-20s %-15s %-4d %-15s\n", p1.nom , p1.prenom, p1.age, p1.n_telephone);
    
    if(fclose(file) == EOF)
        exit(EXIT_FAILURE);
}

void supprimer_contact()
{
    system("cls");
    printf("\n\n\t-----------------| REPERTOIRE DE CONTACT|----------------\n\n");
    int i, n ,k= length_contact();
    char numero[11];
    contact p1[n];
    recuperer_contact(p1);
    printf("\t\tEntrer le numero a supprimer: ");
    fflush(stdin);
    scanf("%s", numero);
    int tr = 0;
    i = 0;

    while(tr != 1 && i < n)
    {
        if(strcmp(numero , p1[i].n_telephone) == 0)
        {
            tr = 1;
            k = i;
        }    
        i++;
    }
    contact temp;
    temp = p1[n-1];
    p1[n-1] = p1[k];
    p1[k] = temp;
    FILE *file;
    file = fopen(nomFichier , "w");
    if(file == NULL)
        return;
    for(i = 0 ; i < n-1 ; i++)
        fwrite(&p1[i] , sizeof(contact), 1 , file);
    if(fclose(file) == EOF)
        return;
    n = n-1;
    file = fopen(length , "w");
    if(file == NULL)
        return;
    fwrite(&n,sizeof(int), 1 ,file);
    if(fclose(file) == EOF)
        return;
}


int main(int argc, char const *argv[])
{
    char ch;
    do
    {
        system("cls");
        printf("\n\n\t-----------------| REPERTOIRE DE CONTACT|----------------\n\n");
        printf("\t\t1. Enregistrer un contact\n");
        printf("\t\t2. Afficher la liste des contact\n");
        printf("\t\t3. Rechercher un contact par nom\n");
        printf("\t\t4. Supprimer un contact\n");
        printf("\t\t0. Quitter\n\n");
        printf("\t\tEntrer votre choix: ");
        fflush(stdin);
        ch = getch();

        switch (ch)
        {
        case '1':
            Enregistrer_contact();
            break;
        case '2':
            afficher_repertoire();
            break;
        case '3':
            rechercher_par_nom();
            break;
        case '4':
            supprimer_contact();
            break;
        default:
            ch = '0';
            break;
        }
    } while (ch != '0');
    
    return 0;
}
