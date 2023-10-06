#include <stdio.h>
#include <stdlib.h>
#include "application.h"
#include "couche_transport.h"
#include "services_reseau.h"
int main(int argc, char* argv[])
{
    unsigned char message[MAX_INFO]; /* message pour l'application */
    paquet_t paquet, acc_reception; /* paquet utilisé par le protocole */
    int fin = 0; /* condition d'arrêt */
    //int tab_pack_attendu[16];
    int pack_attendu=0;
    /*
    for(int i=0,i<16;i++){
      tab_pack_attendu[i]=i;
    }
*/

    init_reseau(RECEPTION);

    printf("[TRP] Initialisation reseau : OK.\n");
    printf("[TRP] Debut execution protocole transport.\n");
    while(!fin){
      de_reseau(&paquet);
      if(verifier_controle(paquet)){
        acc_reception.lg_info=0;
        acc_reception.type=ACK;
        acc_reception.somme_ctrl=generer_controle(acc_reception);
        if(paquet.num_seq==pack_attendu%16){
          for (int i=0; i<paquet.lg_info; i++){
              message[i] = paquet.info[i];
          }
          pack_attendu++;
          vers_reseau(&acc_reception);
          fin = vers_application(message, paquet.lg_info);
        }else{
          vers_reseau(&acc_reception);
        }
      }
    }


    printf("[TRP] Fin execution protocole transport.\n");
    return 0;
}
