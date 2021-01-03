#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "projet.h"
#include <string.h>

/*
*Vérifie si un sommet est final
*/
int write_is_final(int sommet, bool isfinal){
	if (isfinal==true)		
		return sommet;
	else
		return false;
	
}

/*
Génére un automate qui reconnait le langage vide 
*/
struct automate automate_langage_vide(){
	struct automate g;				
	g.sommet_initial.num_etat=1;			
	g.sommet_initial.is_final=false;		
	g.tab_etats=malloc(1*sizeof(struct etat));
	g.tab_etats[0].num_etat=1;			/*1 seul etat*/
	g.tab_etats[0].is_final=false;			/*l'etat n'est final*/
	return g;	
}
/*
*Affichage d'un automate qui reconnait le langage vide 
*/
void print_automate_langage_vide(struct automate g){
	printf("Automate:\n");
	printf("---nombre de sommets : 1\n");
	printf("---liste des sommets : %d\n", g.tab_etats[0].num_etat);
	printf("---sommet initial : %d\n", g.sommet_initial.num_etat);
}

/*
*Génére un automate qui reconnait le mot vide 
*/
struct automate automate_mot_vide(){
	struct automate g;
	g.sommet_initial.num_etat=1;			
	g.sommet_initial.is_final=true;
	g.tab_etats=malloc(1*sizeof(struct etat));
	g.tab_etats[0].num_etat=1;			/*1 seul etat*/
	g.tab_etats[0].is_final=true;			/*l'etat est final*/
	return g;	
}
/*
*affiche un automate qui reconnait le mot vide 
*/
void print_automate_mot_vide(struct automate g2){
	printf("Automate:\n");
	printf("---nombre de sommets : 1\n");
	printf("---liste des sommets : %d\n", g2.tab_etats[0].num_etat);
	printf("---sommet initial : %d\n", g2.sommet_initial.num_etat);
	printf("---Sommet(s) final/finaux : %d\n", write_is_final(g2.tab_etats[0].num_etat, g2.tab_etats[0].is_final));
}

/*
*Genere un automate qui reconnait un mot composé d'un caractere
*/
struct automate automate_un_mot(char* mot){
	struct automate g;
	g.tab_etats=malloc(2*sizeof(struct etat));
	g.tab_arretes=malloc(1*sizeof(struct etat));

	g.sommet_initial.num_etat=1;		/*etat initial*/
	g.sommet_initial.is_final=false;	/*etat initial n'est pas final*/
	g.nb_etats=2;	
	g.nb_transitions=1;			/*2 etats*/

	g.tab_etats[0].num_etat=1;
	g.tab_etats[0].is_final=false;
	
	g.tab_etats[1].num_etat=2;		/* 2eme etat*/
	g.tab_etats[1].is_final=true;		/*2 etats, donc le deuxieme etat est final*/

	g.tab_arretes[0].sommet_depart.num_etat=1;
	g.tab_arretes[0].sommet_depart.is_final=false;

	g.tab_arretes[0].sommet_destination.num_etat=2;
	g.tab_arretes[0].sommet_destination.is_final=true;

	g.tab_arretes[0].symbole=mot;	
	return g;
}

/*
*Affiche un automate qui reconnait un mot
*/
void print_automate_un_mot(struct automate g3){
	printf("Automate:\n");
	printf("---nombre de sommets : 2\n");
	printf("---liste des sommets : %d - %d\n", g3.tab_etats[0].num_etat, g3.tab_etats[1].num_etat);
	printf("---sommet initial : %d\n", g3.sommet_initial.num_etat);
	printf("---Sommet(s) final/finaux : %d\n", write_is_final(g3.tab_etats[1].num_etat, g3.tab_etats[1].is_final));
	printf("---nombre des transitions : 1\n");
	printf("---Transition(s) : %d, %s, %d\n",g3.tab_arretes[0].sommet_depart.num_etat, g3.tab_arretes[0].symbole, g3.tab_arretes[0].sommet_destination.num_etat);
}

/*
*Ajoute un etat a l'automate
*/
void addToGraphe(struct automate* g, struct etat etat){
	for (int k=0;k<g->nb_etats;k++){
		if (g->tab_etats[k].num_etat == etat.num_etat){
			return;
		}
	}
	g->tab_etats[g->nb_etats]=etat;
	g->nb_etats++;
	return; 
}

/*
*Genere un automate qui reconnait la reunion des langages des deux automates passés en parametres
*/
struct automate reunion_automate(struct automate g1, struct automate g2){
	int i;
	int indiceGraphe;
	int dernierElement=1;
	int nb_etats=g1.nb_etats+g2.nb_etats-1;
	int j=0;
	int numero_etat=g1.nb_etats;
	int nbr_transitions=g1.nb_transitions+g2.nb_transitions;
	struct automate g;
	g.tab_etats=malloc(nb_etats*sizeof(struct etat));
	g.tab_arretes=malloc(nbr_transitions*sizeof(struct arrete));
	g.nb_transitions=g1.nb_transitions+g2.nb_transitions;
	
	for (int k=0;k<g1.nb_transitions;k++){
		g.tab_arretes[k]=g1.tab_arretes[k];
			
	}
	g.nb_etats=g1.nb_etats;
	for (int k=0;k<g1.nb_etats;k++){
		g.tab_etats[k]=g1.tab_etats[k];
	}

	for(i=g1.nb_transitions; i<nbr_transitions;i++){
		if(g2.tab_arretes[j].sommet_depart.num_etat==1){
			g.tab_arretes[i].sommet_depart.num_etat=1;
			g.tab_arretes[i].sommet_destination.num_etat=g2.tab_arretes[j].sommet_depart.num_etat+numero_etat;		
			g.tab_arretes[i].sommet_destination.is_final=g2.tab_arretes[j].sommet_destination.is_final;
			
		}		
		else{
			g.tab_arretes[i].sommet_depart.num_etat=g.tab_arretes[i-1].sommet_destination.num_etat;
			g.tab_arretes[i].sommet_destination.num_etat=g.tab_arretes[i].sommet_depart.num_etat+1;	
			g.tab_arretes[i].sommet_depart.is_final=g2.tab_arretes[j].sommet_depart.is_final;
			g.tab_arretes[i].sommet_destination.is_final=g2.tab_arretes[j].sommet_destination.is_final;
		}
		g.tab_arretes[i].symbole=g2.tab_arretes[j].symbole;
		addToGraphe(&g, g.tab_arretes[i].sommet_depart);
		addToGraphe(&g, g.tab_arretes[i].sommet_destination);
		j++;
		numero_etat++;
	}
	return g;
}

/*
*Affiche un automate resultat de la reunion
*/
void print_reunion(struct automate g){
	printf("\nAutomate\n");
	printf("---Nombre d'états : %d\n", g.nb_etats);
	printf("---Nombre de transactions : %d\n", g.nb_transitions);
	printf("---Etat initial : %d\n", g.tab_etats[0].num_etat);
	for(int i=0;i<g.nb_etats;i++){
		if(i<g.nb_etats-1){
			printf("-----Etat n° %d\n",g.tab_arretes[i].sommet_depart.num_etat);
			printf("-------Transaction avec le symbole %s vers l'etat %d\n",g.tab_arretes[i].symbole, g.tab_arretes[i].sommet_destination.num_etat);
			//printf("-------Final : %d\n",g.tab_arretes[i].sommet_depart.is_final);
		}
	}
	printf("\n-----Liste des etats finaux : \n");
	for (int i=0; i<g.nb_etats;i++){
		if(g.tab_etats[i].is_final==1){
			printf("-------Etat n° %d\n", g.tab_etats[i].num_etat);
		}
	}
	
}

/*
*Genere un automate qui la concatenation des langages des deux automates passés en paramétre 
*/
struct automate concatenation_automate(struct automate g1, struct automate g2){
	int i;
	int indiceGraphe;
	int dernierElement=1;
	int nb_etats=g1.nb_etats+g2.nb_etats-1;
	int j=0;
	int numero_etat=g1.nb_etats;
	int nbr_transitions=g1.nb_transitions+g2.nb_transitions;
	struct automate g;
	g.tab_etats=malloc(nb_etats*sizeof(struct etat));
	g.tab_arretes=malloc(nbr_transitions*sizeof(struct arrete));
	g.nb_transitions=g1.nb_transitions+g2.nb_transitions;
	
	for (int k=0;k<g1.nb_transitions;k++){
		g.tab_arretes[k]=g1.tab_arretes[k];
			
	}
	g.nb_etats=g1.nb_etats;
	for (int k=0;k<g1.nb_etats;k++){
		g.tab_etats[k]=g1.tab_etats[k];
	}

	for(i=g1.nb_transitions; i<nbr_transitions;i++){
		if(g2.tab_arretes[j].sommet_depart.num_etat==1){
			g.tab_arretes[i].sommet_depart.num_etat=g1.tab_arretes[g1.nb_transitions-1].sommet_destination.num_etat;
			g.tab_arretes[i].sommet_destination.num_etat=g2.tab_arretes[j].sommet_depart.num_etat+numero_etat;		
			g.tab_arretes[i].sommet_destination.is_final=g2.tab_arretes[j].sommet_destination.is_final;
			
		}		
		else{
			g.tab_arretes[i].sommet_depart.num_etat=g.tab_arretes[i-1].sommet_depart.num_etat+1;
			g.tab_arretes[i].sommet_destination.num_etat=g.tab_arretes[i-1].sommet_destination.num_etat+1;	
			g.tab_arretes[i].sommet_depart.is_final=g2.tab_arretes[j].sommet_depart.is_final;
			g.tab_arretes[i].sommet_destination.is_final=g2.tab_arretes[j].sommet_destination.is_final;	
		}
		
		g.tab_arretes[i].symbole=g2.tab_arretes[j].symbole;
		addToGraphe(&g, g.tab_arretes[i].sommet_depart);
		addToGraphe(&g, g.tab_arretes[i].sommet_destination);
		j++;
		numero_etat++;
	}
	for (i=0; i< g.nb_etats;i++){		
		if(i<g.nb_etats-1){
			g.tab_etats[i].is_final=false;
		}else{
			g.tab_etats[i].is_final=true;
		}
	}
	for (i=0; i< g.nb_transitions;i++){
		g.tab_arretes[i].sommet_depart.is_final=false;
		g.tab_arretes[i].sommet_destination.is_final=false;
	}
	g.tab_arretes[i-1].sommet_destination.is_final=true;
	
	return g;
}

/*
*Affiche un automate resultat de la concatenation
*/
void print_concatenate(struct automate g){
	printf("\nAutomate\n");
	printf("---Nombre d'états : %d\n", g.nb_etats);
	printf("---Nombre de transactions : %d\n", g.nb_transitions);
	printf("---Etat initial : %d\n", g.tab_etats[0].num_etat);
	for(int i=0;i<g.nb_etats;i++){
		if(i<g.nb_etats-1){
			printf("-----Etat n° %d\n",g.tab_arretes[i].sommet_depart.num_etat);
			printf("-------Transaction avec le symbole %s vers l'etat %d\n",g.tab_arretes[i].symbole, g.tab_arretes[i].sommet_destination.num_etat);
			printf("-------Final : %d\n",g.tab_arretes[i].sommet_depart.is_final);
		}
		else{
			printf("-----Etat n° %d\n",g.tab_arretes[i-1].sommet_destination.num_etat);
			printf("-------Final : %d\n",g.tab_arretes[i-1].sommet_destination.is_final);		
		}
	}
}


/*
*Genere un automate qui reconnait la fermeture de kleene pour l'automate passe en parametres
*/
struct automate fermeture_kleene(struct automate g){
	int nbrEtatsFinaux=0;
	int transitionsSommetInit=0;
	for (int i=0;i<g.nb_transitions;i++){
		if (g.tab_arretes[i].sommet_destination.is_final==true){
			nbrEtatsFinaux++;
		}
	}
	for (int i=0;i<g.nb_transitions;i++){
		if(g.tab_arretes[i].sommet_depart.num_etat==1){
			transitionsSommetInit++;
		}	
	}
	struct automate gRetour;
	int nbr_transitions=g.nb_transitions+transitionsSommetInit*nbrEtatsFinaux;
	gRetour.tab_etats=malloc(g.nb_etats*sizeof(struct etat)+1);
	gRetour.tab_arretes=malloc(nbr_transitions*sizeof(struct arrete)+1);
	for (int i=0;i<g.nb_transitions;i++){
		gRetour.tab_arretes[i]=g.tab_arretes[i];
	}
	int ajout=0;
	int j=0;
	int indice_while=0;
	for (int i=0; i<g.nb_transitions;i++){
		if (g.tab_arretes[i].sommet_destination.is_final==true){		
				while(indice_while<g.nb_transitions){
					if(g.tab_arretes[indice_while].sommet_depart.num_etat==1){	
						gRetour.tab_arretes[g.nb_transitions+ajout].sommet_depart=g.tab_arretes[i].sommet_destination;
						gRetour.tab_arretes[g.nb_transitions+ajout].sommet_destination.num_etat=g.tab_arretes[indice_while].sommet_destination.num_etat;
						gRetour.tab_arretes[g.nb_transitions+ajout].symbole=g.tab_arretes[indice_while].symbole;				
						ajout++;
						j++;	
					}
				indice_while++;
				}
				indice_while=0;
				j=0;
		}
	}
	gRetour.nb_transitions=nbr_transitions;
	gRetour.nb_etats=g.nb_etats;
	return gRetour;
}

/*
*Affiche l'automate de la fermeture de kleene genere
*/
void print_kleene(struct automate g){
	printf("\nAutomate : \n");
	printf("---nombre de sommets : %d\n", g.nb_etats);
	printf("---sommet initial : %d\n", g.tab_etats[0].num_etat);
	printf("---nombre des transitions : %d\n",g.nb_transitions);
	for (int i=0;i<g.nb_transitions;i++){
		printf("---Etat n° : %d\n",g.tab_arretes[i].sommet_depart.num_etat);
		printf("------Transition avec le symbole %s vers l'etat n° %d\n", g.tab_arretes[i].symbole, g.tab_arretes[i].sommet_destination.num_etat);		
		printf("------Final : %d\n", g.tab_arretes[i].sommet_depart.is_final);
	}
}

/*
*Execute un mot sur un automate et verifie s'il est valide
*/
bool mot_sur_automate(struct automate g,char* c ){
	int l_c;
	l_c=(int)strlen(c);
	if(g.nb_etats<l_c){
		return 0;
	}
    int i;
    /* s'assure si le string est en ascii*/
    int code;
    for(i=0;i<l_c;i++){
    	code=c[i];
    	if(code>255 || code<0){
    		printf("le string n'est pas en ascii \n");
    		return 0;
    	}

    }
    for(i=0;i<l_c;i++){
    	if(*(g.tab_arretes[i].symbole) != c[i]){
    		return 0;
    	}
    }
    return 1;
}
/*
*affiche un mot genere sur un automate et verifie s'il est valide ou pas 
*/
void print_mot_sur_automate(struct automate g,char * c)
{
    int l_c;
	l_c=(int)strlen(c);
    /* s'assure si le string est en ascii*/
    int code;
    int i;
    for(i=0;i<l_c;i++){
    	code = c[i];
    	if(code>255 || code <0){
    		printf("le string %s n'est pas en ascii \n",c);
    		return;
    	}
    }
	if(mot_sur_automate(g,c)==0){
		printf("string %s non valide sur l'automate  \n",c);
	}else{
		printf("string %s valide sur l'automate  \n",c);
	}
}

int main(){
	struct automate g;	
	g=automate_langage_vide();
	//print_automate_langage_vide(g);
	struct automate ga;
	ga=automate_un_mot("a");
	struct automate gb;
	gb=automate_un_mot("b");
	struct automate gc;
	gc=automate_un_mot("c");
	struct automate gd;
	gd=automate_un_mot("d");
	struct automate ge;
	ge=automate_un_mot("e");

	struct automate gab_reunion;
	gab_reunion=reunion_automate(ga, gb);

	struct automate gcd_reunion;
	gcd_reunion=reunion_automate(gc, gd);

	struct automate gabcd_reunion;
	gabcd_reunion=reunion_automate(gab_reunion, gcd_reunion);
	//print_reunion(gabcd_reunion);

	struct automate gab;
	gab=concatenation_automate(ga, gb);

	struct automate gcd;
	gcd=concatenation_automate(gc, gd);

	printf("\n------------------------concatenation-----------------------------\n");
	struct automate gabcd;
	gabcd=concatenation_automate(gab, gcd);

	struct automate gabcde;
	gabcde=concatenation_automate(gabcd, ge);
	print_concatenate(gabcde);/*concatenation sur les automate gabcd et ge */

	printf("\n------------------------reunion------------------------------------\n");
	struct automate gabcd_re_conc;
	gabcd_re_conc=reunion_automate(gab, gcd);
	print_reunion(gabcd_re_conc); /*reunion  les automate gab et gcd */

	printf("\n------------------------fermeture de kleene-----------------------------\n");
	/***Test Fermeture de kleene***/
	struct automate automate_kleene=fermeture_kleene(gabcd);	/*abcd devient (abcd)* */
	print_kleene(automate_kleene);

	printf("\n------------------------Automate deterministe -----------------------------\n");
	
	print_mot_sur_automate(gab,"ab");
	print_mot_sur_automate(gabcd,"abcd");
	print_mot_sur_automate(ga,"e");
}

