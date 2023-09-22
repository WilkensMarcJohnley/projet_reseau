
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
    //bool verif_ctrl;

    init_reseau(RECEPTION);

    printf("[TRP] Initialisation reseau : OK.\n");
    printf("[TRP] Debut execution protocole transport.\n");

    /* tant que le récepteur reçoit des données */
    while(!fin){
      do {
        de_reseau(&paquet);

        /* extraction des donnees du paquet recu */
        for (int i=0; i<paquet.lg_info; i++) {
            message[i] = paquet.info[i];
        }

          acc_reception.lg_info=0;
          if(!verifier_controle(paquet)){
            acc_reception.type=NACK;
          }else{
            acc_reception.type=ACK;
          }
          vers_reseau(&acc_reception);
      } while(acc_reception.type!=ACK);

      fin = vers_application(message, paquet.lg_info);
    }


      printf("[TRP] Fin execution protocole transport.\n");
      return 0;
    }
