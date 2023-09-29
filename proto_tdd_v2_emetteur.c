#include <stdio.h>
#include "application.h"
#include "couche_transport.h"
#include "services_reseau.h"


/* =============================== */
/* Programme principal - émetteur  */
/* =============================== */

int main(int argc, char* argv[]){
  unsigned char message[MAX_INFO]; /* message de l'application */
  int taille_msg, num_paquet; /* taille du message */
  paquet_t paquet,acc_reception; /* paquet utilisé par le protocole */
  int evenement, env_max=0;

  init_reseau(EMISSION);

  printf("[TRP] Initialisation reseau : OK.\n");
  printf("[TRP] Debut execution protocole transport.\n");


        /* lecture de donnees provenant de la couche application */
        de_application(message, &taille_msg);
        num_paquet=0;
        /* tant que l'émetteur a des données à envoyer */
        while(taille_msg!=0){
          //construction du paquet
          for(int i=0; i<taille_msg;i++){
            paquet.info[i]=message[i];
          }

          paquet.type=DATA;
          paquet.num_seq=num_paquet%2;
          paquet.lg_info=taille_msg;
          paquet.somme_ctrl=generer_controle(paquet);

          do{
            vers_reseau(&paquet);
            env_max++;
            depart_temporisateur(200);
            evenement=attendre();
          }while(evenement!=-1 && env_max<10);

          if(env_max==10){
            printf("erreur reseau");
            return -1;
          }
          env_max=0;
          de_reseau(&acc_reception);
          arret_temporisateur();
          num_paquet++;
          de_application(message, &taille_msg);
        }
        printf("[TRP] Fin execution protocole transfert de donnees (TDD).\n");
        return 0;
    }
