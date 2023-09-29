#include <stdio.h>
#include "application.h"
#include "couche_transport.h"
#include "services_reseau.h"

/* =============================== */
/* Programme principal - récepteur */
/* =============================== */

int main(int argc, char* argv[]){
  unsigned char message[MAX_INFO]; /* message de l'application */
  int taille_msg; /* taille du message */
  paquet_t paquet,acc_reception; /* paquet utilisé par le protocole */
  int b_inf=0,curseur=0,taille_fenetre;
  Evenement evt;
  int taille_tab=16;
  paquet_t tab_pack[taille_tab];

  if(argc>=2){
    taille_fenetre=atoi(argv[1])
    taille_fenetre--;
  }else{
    taille_fenetre=6;
  }

  //bsup=taille_fenetre-1;

  init_reseau(EMISSION);

  printf("[TRP] Initialisation reseau : OK.\n");
  printf("[TRP] Debut execution protocole transport.\n");


      /* lecture de donnees provenant de la couche application */
      de_application(message, &taille_msg);
      while(taille_msg!=0){
        if(dans_fenetre(b_inf,curseur,taille_fenetre)){
          for(int i=0; i<taille_msg;i++){
            tab_pack[curseur].info[i]=message[i];
          }

          tab_pack[curseur].numseq=curseur;
          tab_pack[curseur].lg_info=taille_msg;
          tab_pack[curseur].somme_ctrl=generer_controle(tab_pack[curseur]);
          vers_reseau(tab_pack[curseur]);
          if(b_inf==curseur) depart_temporisateur(200);
          curseur= (curseur++)%taille_tab;

        }else{
          evt=attendre();
          if(evt==-1){
            de_reseau(acc_reception);
            if(verifier_controle(acc_reception) && dans_fenetre(b_inf,acc_reception.num_seq,taille_fenetre)){
              b_inf=(b_inf++)%16;
              if(b_inf==curseur){
                arret_temporisateur();
              }
            }
          }else{}
        }







        for(int i=0;i<taille_msg;i++){
          paquet.info[i]=message[i];
        }
        paquet.lg_info=taille_msg;
        paquet.somme_ctrl=generer_controle(paquet);
        paquet.num_seq=prochain_paquet;
        paquet.type=DATA;




      }

      printf("[TRP] Fin execution protocole transfert de donnees (TDD).\n");
      return 0;
    }
