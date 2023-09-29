#include <stdio.h>
#include "application.h"
#include "couche_transport.h"
#include "services_reseau.h"

/* =============================== */
/* Programme principal - récepteur */
/* =============================== */
int main(int argc, char* argv[])
{
    unsigned char message[MAX_INFO]; /* message pour l'application */
    paquet_t paquet, acc_reception; /* paquet utilisé par le protocole */
    int fin = 0; /* condition d'arrêt */
    int paquet_attendu=0; 

    init_reseau(RECEPTION);

    printf("[TRP] Initialisation reseau : OK.\n");
    printf("[TRP] Debut execution protocole transport.\n");

    /* tant que le récepteur reçoit des données */
    while(!fin){
          de_reseau(&paquet);
            if(verifier_controle(paquet)){
              acc_reception.lg_info=0;
              acc_reception.type=ACK;
              if(paquet.num_seq==((paquet_attendu%2))){
                for (int i=0; i<paquet.lg_info; i++){
                    message[i] = paquet.info[i];
                }
                paquet_attendu++;
                vers_reseau(&acc_reception);
                fin = vers_application(message, paquet.lg_info);
              }else{
                vers_reseau(&acc_reception);
              }
            }
            /* extraction des donnees du paquet recu */
          }

      printf("[TRP] Fin execution protocole transport.\n");
      return 0;
  }
