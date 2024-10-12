#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct{
    int jj, mm, aa;
} date;

typedef struct evenement{
    char nom[50];
    char lieu[30], description[50], titre[20], categorie[30];
    int heure;
    struct evenement *suivant, *precedent;
    date dateE;
} evenement;

// Fonction d'ajout au début
evenement *ajoutdebut(evenement *L, char *nom, char *lieu, char *desc, char *titre, char *cat, int hh, date d_e){
    evenement *nv = malloc(sizeof(evenement));
    if (nv == NULL) {
        printf("Erreur d'allocation de memoire.\n");
        exit(1);
    }
    strcpy(nv->nom, nom);
    strcpy(nv->lieu, lieu);
    strcpy(nv->description, desc);
    strcpy(nv->titre, titre);
    strcpy(nv->categorie, cat);
    nv->heure = hh;
    nv->dateE = d_e;
    nv->suivant = nv->precedent = nv; // Initialise les champs suivant et precedent
    if (L == NULL) {
        return nv;
    } else {
        evenement *dernier = L->precedent;
        dernier->suivant = nv;
        nv->precedent = dernier;
        nv->suivant = L;
        L->precedent = nv;
    }
    return nv;
}

// Fonction d'ajout à la fin
evenement *ajoutfin(evenement *L, char *nom, char *lieu, char *desc, char *titre, char *cat, int hh, date d_e){
    evenement *nv = malloc(sizeof(evenement));
    if (nv == NULL) {
        printf("Erreur d'allocation de memoire.\n");
        exit(1);
    }
    strcpy(nv->nom, nom);
    strcpy(nv->lieu, lieu);
    strcpy(nv->description, desc);
    strcpy(nv->titre, titre);
    strcpy(nv->categorie, cat);
    nv->heure = hh;
    nv->dateE = d_e;
    nv->suivant = nv->precedent = nv; // Initialise les champs suivant et precedent
    if (L == NULL) {
        return nv;
    } else {
        evenement *dernier = L->precedent;
        dernier->suivant = nv;
        nv->precedent = dernier;
        nv->suivant = L;
        L->precedent = nv;
    }
    return L;
}

// Ajout après un événement spécifique
evenement *ajouteapres(evenement *L, char *nom, char *lieu, char *desc, char *titre, char *cat, int hh, date d_e, char *nomA) {
    evenement *ptr = L;
    while (ptr->suivant != L) {
        if (strcmp(ptr->nom, nomA) == 0) {
            evenement *nv = malloc(sizeof(evenement));
            if (nv == NULL) {
                printf("Erreur d'allocation de memoire.\n");
                exit(1);
            }
            strcpy(nv->nom, nom);
            strcpy(nv->lieu, lieu);
            strcpy(nv->description, desc);
            strcpy(nv->titre, titre);
            strcpy(nv->categorie, cat);
            nv->heure = hh;
            nv->dateE = d_e;
            nv->suivant = ptr->suivant;
            nv->precedent = ptr;
            ptr->suivant->precedent = nv;
            ptr->suivant = nv;
            return L;
        } else {
            ptr = ptr->suivant;
        }
    }
    printf("Evenement non trouve! \n");
    return L;
}

// Modification d'événement
evenement *modifier_E(evenement *L){
    char nom_M[20];
    printf("Entrer le nom de l'evenement a modifier: ");
    scanf("%s", nom_M);
    evenement *ptr = L;
    int trouve = 0;
    do {
        if (strcmp(ptr->nom, nom_M) == 0) {
            printf("Veuillez saisir les informations du nouvel evenement: \n");
            printf("Nom: ");
            scanf("%s", ptr->nom);
            printf("Lieu: ");
            scanf("%s", ptr->lieu);
            printf("Titre: ");
            scanf("%s", ptr->titre);
            printf("Description: ");
            scanf("%s", ptr->description);
            printf("Categorie: ");
            scanf("%s", ptr->categorie);
            printf("Heure:(HH) ");
            scanf("%d", &ptr->heure);
            printf("Date (JJ/MM/AAAA): ");
            scanf("%d%d%d", &ptr->dateE.jj, &ptr->dateE.mm, &ptr->dateE.aa);
            trouve = 1;
            break;
        }
        ptr = ptr->suivant;
    } while (ptr != L);

    if (!trouve) {
        printf("Evenement non trouve!\n");
    }
    return L;
}


// Fonction d'affichage
void afficherE(evenement *L){
    evenement *ptr = L;
    printf("\n");
    do {
        printf("Nom: %s\n", ptr->nom);
        printf("Titre: %s\n", ptr->titre);
        printf("Lieu: %s\n", ptr->lieu);
        printf("Description: %s\n", ptr->description);
        printf("Categorie: %s\n", ptr->categorie);
        printf("Heure: %d\n", ptr->heure);
        printf("Date: %d/%d/%d\n", ptr->dateE.jj, ptr->dateE.mm, ptr->dateE.aa);
        printf("\n");
        ptr = ptr->suivant;
    } while (ptr != L);
}

// Recherche par date
evenement *rechere_par_date(evenement *L){
    date d_r;
    printf("Entrer la date de l'evenement a rechercher (JJ/MM/AAAA): ");
    scanf("%d%d%d",&d_r.jj,&d_r.mm,&d_r.aa);
    
    int trouve = 0;
    evenement *ptr = L;
    
    do {
        if (ptr->dateE.jj == d_r.jj && ptr->dateE.mm == d_r.mm && ptr->dateE.aa == d_r.aa) {
            printf("\n");
            printf("Nom: %s\n", ptr->nom);
            printf("Titre: %s\n", ptr->titre);
            printf("Lieu: %s\n", ptr->lieu);
            printf("Description: %s\n", ptr->description);
            printf("Categorie: %s\n", ptr->categorie);
            printf("Heure: %d\n", ptr->heure);
            printf("Date: %d/%d/%d\n", ptr->dateE.jj, ptr->dateE.mm, ptr->dateE.aa);
            printf("\n");
            trouve = 1;
        }
        ptr = ptr->suivant;
    } while (ptr != L);

    if (!trouve) {
        printf("Aucun evenement trouve pour cette date.\n");
    }

    return L;
}

//recherche par lieu
evenement *recherche_par_lieu(evenement *L){
    char lieu_R[20];
    int trouve = 0;
    printf("Entrer le lieu de l'evenement a rechercher: ");
    fflush(stdin);
    gets(lieu_R);
    evenement *ptr = L;
    do {
        if (strcmp(ptr->lieu, lieu_R) == 0) {
            printf("\n");
            printf("Nom: %s\n", ptr->nom);
            printf("Titre: %s\n", ptr->titre);
            printf("Lieu: %s\n", ptr->lieu);
            printf("Description: %s\n", ptr->description);
            printf("Categorie: %s\n", ptr->categorie);
            printf("Heure: %d\n", ptr->heure);
            printf("Date: %d/%d/%d\n", ptr->dateE.jj, ptr->dateE.mm, ptr->dateE.aa);
            printf("\n");
            trouve = 1;
            break; // Sortir de la boucle dès qu'un événement est trouvé
        }
        ptr = ptr->suivant;
    } while (ptr != L);
    if (!trouve) {
        printf("Aucun evenement trouve pour ce lieu.\n");
    }
    return L;
}



// Recherche par titre
evenement *recherche_par_titre(evenement *L){
    char titre_R[20];
    int trouve = 0;

    printf("Entrer le titre de l'evenement a rechercher: ");
    fflush(stdin);
    gets(titre_R);

    evenement *ptr = L;
    
    do {
        if (strcmp(ptr->titre, titre_R) == 0) {
            printf("\n");
            printf("Nom: %s\n", ptr->nom);
            printf("Titre: %s\n", ptr->titre);
            printf("Lieu: %s\n", ptr->lieu);
            printf("Description: %s\n", ptr->description);
            printf("Categorie: %s\n", ptr->categorie);
            printf("Heure: %d\n", ptr->heure);
            printf("Date: %d/%d/%d\n", ptr->dateE.jj, ptr->dateE.mm, ptr->dateE.aa);
            printf("\n");
            trouve = 1;
        }
        ptr = ptr->suivant;
    } while (ptr != L);

    if (!trouve) {
        printf("Aucun evenement trouve pour ce titre.\n");
    }

    return L;
}


// Recherche par auteur
evenement *recherche_par_auteur(evenement *L){
    char aut_R[20];
    int trouve = 0;

    printf("Entrer le nom de l'auteur de l'evenement a rechercher: ");
    fflush(stdin);
    gets(aut_R);

    evenement *ptr = L;
    
    do {
        if (strcmp(ptr->nom, aut_R) == 0) {
            afficherE(ptr);
            trouve = 1;
        }
        ptr = ptr->suivant;
    } while (ptr != L);

    if (!trouve) {
        printf("Aucun evenement trouve pour cet auteur.\n");
    }

    return L;
}


//suppression au debut
evenement *supprimer_debut(evenement *L){
        evenement *ptr=L;
        if(L==NULL){
                printf("La liste est vide suppression impossible! ");
        }else if(L->suivant==L){
                free(ptr);
                L=NULL;
        }else {
                evenement *dernier=L->precedent;
                L=L->suivant;
                dernier->suivant=L;
                L->precedent=dernier;
                free(ptr);
        }
     return L;
}

//suppression a la fin
evenement *supprimer_fin(evenement *L){
        if(L==NULL){
                printf("La liste est vide suppression impossible! ");
        }else{
              evenement *dernier=L->precedent;
              dernier->precedent->suivant=L;
              L->precedent=dernier->precedent;
              free(dernier);  
        }
    return L;
}

//supprimer apres un evenement specefique
evenement *supprimer_specefique(evenement *L){
        evenement *ptr=L,*tmp;
        char nom_S[20];
        printf("Entrer le nom de l'evenement apres lequel voulez vous effectuer la suppression: ");
        fflush(stdin);
        gets(nom_S);
        while(strcmp (ptr->nom,nom_S)!=0 ){
                ptr=ptr->suivant;
        }
         tmp=ptr;
         tmp=tmp->suivant;
        if(ptr->suivant==L){
                tmp=supprimer_fin(tmp);
        }else{
                ptr->suivant=tmp->suivant;
                tmp->suivant->precedent=ptr;
                free(tmp);
        }
    return L;
}


// Fonction pour gérer les catégories
void gerer_categorie(evenement *L){
    char cat[30];
    int trouve = 0;
    
    printf("Entrer la categorie des evenements que vous voulez afficher: ");
    scanf("%s", cat);
    
    evenement *ptr = L;
    
    do {
        if(strcmp(ptr->categorie, cat) == 0) {
            printf("\n");
            printf("Nom: %s\n", ptr->nom);
            printf("Titre: %s\n", ptr->titre);
            printf("Lieu: %s\n", ptr->lieu);
            printf("Description: %s\n", ptr->description);
            printf("Categorie: %s\n", ptr->categorie);
            printf("Heure: %d\n", ptr->heure);
            printf("Date: %d/%d/%d\n", ptr->dateE.jj, ptr->dateE.mm, ptr->dateE.aa);
            printf("\n");
            trouve = 1;
        }
        ptr = ptr->suivant;
    } while(ptr != L);
    
    if (!trouve) {
        printf("Aucun evenement trouvé dans la categorie specifiee.\n");
    }
}



// Fonction pour trier les événements par nom dans l'ordre croissant
evenement *tri_croissant_par_nom(evenement *L) {
    if (L == NULL || L->suivant == L) {
        // Rien à trier si la liste est vide ou ne contient qu'un élément
        return L;
    }

    evenement *listeTriee = NULL; // Initialisation de la liste triée
    evenement *courant = L;

    // Parcourir la liste d'origine
    while (courant != NULL) {
        evenement *aInserer = courant; // Événement actuel à insérer dans la liste triée
        courant = courant->suivant; // Avancer dans la liste non triée

        // Trouver l'emplacement d'insertion dans la liste triée par nom
        if (listeTriee == NULL || strcmp(aInserer->nom, listeTriee->nom) <= 0) {
            // Cas où l'événement doit être inséré au début ou la liste triée est vide
            aInserer->suivant = listeTriee;
            if (listeTriee != NULL) {
                listeTriee->precedent = aInserer;
            }
            listeTriee = aInserer;
        } else {
            // Parcourir la liste triée pour trouver l'emplacement d'insertion
            evenement *ptr = listeTriee;
            while (ptr->suivant != NULL && strcmp(aInserer->nom, ptr->suivant->nom) > 0) {
                ptr = ptr->suivant;
            }

            // Insérer l'événement dans la liste triée
            aInserer->suivant = ptr->suivant;
            aInserer->precedent = ptr;
            if (ptr->suivant != NULL) {
                ptr->suivant->precedent = aInserer;
            }
            ptr->suivant = aInserer;
        }
    }

    return listeTriee; // Retourner la liste triée par nom
}



evenement *tri_croissant_par_lieu(evenement *L) {
    if (L == NULL || L->suivant == L) {
        // Rien à trier si la liste est vide ou ne contient qu'un élément
        return L;
    }

    evenement *listeTriee = NULL; // Initialisation de la liste triée
    evenement *courant = L;

    // Parcourir la liste d'origine
    while (courant != NULL) {
        evenement *aInserer = courant; // Événement actuel à insérer dans la liste triée
        courant = courant->suivant; // Avancer dans la liste non triée

        // Trouver l'emplacement d'insertion dans la liste triée par lieu
        if (listeTriee == NULL || strcmp(aInserer->lieu, listeTriee->lieu) <= 0) {
            // Cas où l'événement doit être inséré au début ou la liste triée est vide
            aInserer->suivant = listeTriee;
            aInserer->precedent = NULL;
            if (listeTriee != NULL) {
                listeTriee->precedent = aInserer;
            }
            listeTriee = aInserer;
        } else {
            // Parcourir la liste triée pour trouver l'emplacement d'insertion
            evenement *ptr = listeTriee;
            while (ptr->suivant != NULL && strcmp(aInserer->lieu, ptr->suivant->lieu) > 0) {
                ptr = ptr->suivant;
            }

            // Insérer l'événement dans la liste triée
            aInserer->suivant = ptr->suivant;
            aInserer->precedent = ptr;
            if (ptr->suivant != NULL) {
                ptr->suivant->precedent = aInserer;
            }
            ptr->suivant = aInserer;
        }
    }

    return listeTriee; // Retourner la liste triée par lieu
}



// Fonction pour trier les événements par catégorie dans l'ordre croissant
evenement *tri_croissant_par_categorie(evenement *L) {
    if (L == NULL || L->suivant == L) {
        // Rien à trier si la liste est vide ou ne contient qu'un élément
        return L;
    }
    evenement *listeTriee = NULL; // Initialisation de la liste triée
    evenement *courant = L;

    // Parcourir la liste d'origine
    while (courant != NULL) {
        evenement *aInserer = courant; // Événement actuel à insérer dans la liste triée
        courant = courant->suivant; // Avancer dans la liste non triée
        // Trouver l'emplacement d'insertion dans la liste triée par catégorie
        if (listeTriee == NULL || strcmp(aInserer->categorie, listeTriee->categorie) <= 0) {
            // Cas où l'événement doit être inséré au début ou la liste triée est vide
            aInserer->suivant = listeTriee;
            if (listeTriee != NULL) {
                listeTriee->precedent = aInserer;
            }
            listeTriee = aInserer;
        } else {
            // Parcourir la liste triée pour trouver l'emplacement d'insertion
            evenement *ptr = listeTriee;
            while (ptr->suivant != NULL && strcmp(aInserer->categorie, ptr->suivant->categorie) > 0) {
                ptr = ptr->suivant;
            }

            // Insérer l'événement dans la liste triée
            aInserer->suivant = ptr->suivant;
            aInserer->precedent = ptr;
            if (ptr->suivant != NULL) {
                ptr->suivant->precedent = aInserer;
            }
            ptr->suivant = aInserer;
        }
    }

    return listeTriee; // Retourner la liste triée par catégorie
}



int main(){
    char nom[20], lieu[50], description[50], titre[20], categorie[30], nomAjout[20];
    int heure, nbE, choix;
    date d_even;
    evenement *liste = NULL;

    system("cls");
    printf("Entrer le nombre d'evenements que vous voulez ajouter: ");
    scanf("%d", &nbE);

    for(int i = 0; i < nbE; i++){
        printf("Entrer les informations du nouvel evenement:\n");
        printf("Le nom: ");
        scanf("%s", nom);
        printf("Le lieu: ");
        scanf("%s", lieu);
        printf("Le titre: ");
        scanf("%s", titre);
        printf("La description: ");
        scanf("%s", description);
        printf("Categorie: ");
        scanf("%s", categorie);
        printf("L'heure (HH): ");
        scanf("%d", &heure);
        printf("La date sous forme (JJ/MM/AAAA): ");
        scanf("%d%d%d", &d_even.jj, &d_even.mm, &d_even.aa);
        liste = ajoutfin(liste, nom, lieu, description, titre, categorie, heure, d_even);
    }

    debut:
    printf("\n");
    printf("---------------------\n");
    printf("\tMenu: \n");
    printf("---------------------\n");
    printf("1- Gestion des evenements: \n");
    printf("2- Quitter: \n");
    printf("Veuillez saisir votre choix: ");
    scanf("%d", &choix);
    printf("\n");

    switch(choix){ 
        case 2: 
            printf("Au revoir! Notre programme reste a votre disposition a tout moment.\n");
            exit(0);

        case 1:
            debut2:
            do{    
                printf("\n");
                printf("================================================\n");
                printf("1- Ajout d'un evenement: \n");
                printf("2- Modification d'un evenement:\n");
                printf("3- Suppression d'un evenement: \n");
                printf("4- Recherche d'un evenement: \n");
                printf("5- Afficher les evenements:\n");
                printf("6- Gerer les categorie: \n");
                printf("7- Tri des evenements: \n");
                printf("8- Quitter le menu de gestion des evenements\n");
                printf("================================================\n");
                printf("\n");
                printf("Veuillez saisir votre choix: ");
                scanf("%d", &choix);
                printf("\n");

                switch(choix){
                    case 1: 
                        printf("\n");
                        printf("1- Ajout au debut: \n");
                        printf("2- Ajout a la fin: \n");
                        printf("3- Ajout apres un evenement specifique: \n");
                        printf("4- Retour: \n");
                        printf("Choix: ");
                        scanf("%d", &choix);
                        printf("\n");

                        switch(choix){
                            case 1:
                                printf("Entrer les informations du nouvel evenement:\n");
                                printf("Le nom: ");
                                scanf(" %s", nom);
                                printf("Le lieu: ");
                                scanf(" %s", lieu);
                                printf("Le titre: ");
                                scanf(" %s", titre);
                                printf("La description: ");
                                scanf(" %s", description);
                                printf("Categorie: ");
                                scanf("%s", categorie);
                                printf("L'heure (HH): ");
                                scanf("%d", &heure);
                                printf("La date sous forme (JJ/MM/AAAA): ");
                                scanf("%d%d%d", &d_even.jj, &d_even.mm, &d_even.aa);
                                printf("\n");
                                liste = ajoutdebut(liste, nom, lieu, description, titre, categorie, heure, d_even);
                                break;

                            case 2:
                                printf("Entrer les informations du nouvel evenement:\n");
                                printf("Le nom: ");
                                scanf(" %s", nom);
                                printf("Le lieu: ");
                                scanf(" %s", lieu);
                                printf("Le titre: ");
                                scanf(" %s", titre);
                                printf("La description: ");
                                scanf(" %s", description);
                                printf("Categorie: ");
                                scanf("%s", categorie);
                                printf("L'heure (HH): ");
                                scanf("%d", &heure);
                                printf("La date sous forme (JJ/MM/AAAA): ");
                                scanf("%d%d%d", &d_even.jj, &d_even.mm, &d_even.aa);
                                liste = ajoutfin(liste, nom, lieu, description, titre, categorie, heure, d_even);
                                break;

                            case 3:
                                printf("Entrer le nom de l'evenement apres lequel vous voulez ajouter: ");
                                scanf(" %s", nomAjout);
                                printf("Entrer les informations du nouvel evenement:\n");
                                printf("Le nom: ");
                                scanf(" %s", nom);
                                printf("Le lieu: ");
                                scanf(" %s", lieu);
                                printf("Le titre: ");
                                scanf(" %s", titre);
                                printf("La description: ");
                                scanf(" %s", description);
                                printf("Categorie: ");
                                scanf("%s", categorie);
                                printf("L'heure (HH): ");
                                scanf(" %d", &heure);
                                printf("La date sous forme (JJ/MM/AAAA): ");
                                scanf("%d%d%d", &d_even.jj, &d_even.mm, &d_even.aa);
                                liste = ajouteapres(liste, nom, lieu, description, titre, categorie, heure, d_even, nomAjout);
                                break;

                            case 4:
                                goto debut2;
                                break;
                        }
                        break;

                    case 2:
                        liste = modifier_E(liste); 
                        break;

                    case 3: printf("\n");
                        printf("1- Suppression au debut: \n");
                        printf("2- Supppression a la fin: \n");
                        printf("3- suppression apres un evenement specifique: \n");
                        printf("4- Retour: \n");
                        printf("Choix: ");
                        scanf("%d",&choix);
                        printf("\n");
                        switch(choix){
                        case 1: liste=supprimer_debut(liste);
                                break;
                        case 2: liste=supprimer_fin(liste);
                                break;
                        case 3: liste=supprimer_specefique(liste);
                                break;
                        case 4: goto debut2; break;
                    }
                        break;

                    case 4:
                        printf("\n");
                        printf("1. Par date: \n");
                        printf("2. Par lieu: \n");
                        printf("3. Par titre: \n");
                        printf("4. Par nom: \n");
                        printf("5. Retour: \n");
                        printf("Choix: ");
                        scanf("%d",&choix);
                        printf("\n");
                        switch(choix){
                        case 1: liste=rechere_par_date(liste);
                                break;
                        case 2: liste=recherche_par_lieu(liste);
                                break;
                        case 3: liste=recherche_par_titre(liste);
                                break;
                        case 4: liste=recherche_par_auteur(liste);
                                break;
                        case 5: goto debut2; break;
                        }
                        break;

                    case 5:
                        afficherE(liste);
                        break;

                    case 6: 
                        gerer_categorie(liste);
                        break;
                    case 7:
                        printf("\n");
                        printf("1- Tri par nom: \n");
                        printf("2- Tri par lieu: \n");
                        printf("3- Tri par categorie: \n");
                        printf("Choix: ");
                        scanf("%d",&choix);
                        switch(choix){
                            case 1: liste=tri_croissant_par_nom(liste); break;
                            case 2: liste=tri_croissant_par_lieu(liste); break;
                            case 3: liste=tri_croissant_par_categorie(liste); break;
                        }
                        break;

                    case 8: 
                        goto debut;
                        break;

                    default:
                        printf("Choix invalide! \n");
                        break;
                }
            } while(choix != 4);
            break;
    }

    return 0;
}

