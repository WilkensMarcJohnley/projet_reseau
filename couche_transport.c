#include <stdio.h>
#include "couche_transport.h"
#include "services_reseau.h"
#include "application.h"

/* ************************************************************************** */
/* *************** Fonctions utilitaires couche transport ******************* */
/* ************************************************************************** */

// RAJOUTER VOS FONCTIONS DANS CE FICHIER...

//renvoie la somme de controle du paquet p
uint8_t generer_controle(paquet_t p){
  uint8_t som_ctrl= (p.type)^(p.num_seq)^(p.lg_info);

  for(int i=0; i<sizeof(p.info); i++){
    som_ctrl=(som_ctrl)^(p.info[i]);
  }

  return som_ctrl;
}

// verifie la somme de controle
bool verifier_controle(paquet_t p){
  uint8_t som_ctrl_recu= (p.type)^(p.num_seq)^(p.lg_info);

  for(int i=0; i<sizeof(p.info); i++){
    som_ctrl_recu=(som_ctrl_recu)^(p.info[i]);
  }

  return som_ctrl_recu==p.somme_ctrl;
}


/* ===================== Fenêtre d'anticipation ============================= */

/*--------------------------------------*/
/* Fonction d'inclusion dans la fenetre */
/*--------------------------------------*/
int dans_fenetre(unsigned int inf, unsigned int pointeur, int taille) {

    unsigned int sup = (inf+taille-1) % SEQ_NUM_SIZE;

    return
        /* inf <= pointeur <= sup */
        ( inf <= sup && pointeur >= inf && pointeur <= sup ) ||
        /* sup < inf <= pointeur */
        ( sup < inf && pointeur >= inf) ||
        /* pointeur <= sup < inf */
        ( sup < inf && pointeur <= sup);
}
