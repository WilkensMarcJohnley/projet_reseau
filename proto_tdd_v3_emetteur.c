int main(int argc, char* argv[]){
  unsigned char message[MAX_INFO]; /* message de l'application */
  int taille_msg; /* taille du message */
  paquet_t paquet,acc_reception; /* paquet utilisé par le protocole */
  int b_inf=0,b_sup, length_window,num_paquet,prochain_paquet=0;
  int window[16];
  for(int i=0;i<16;i++) window[i]=i;

  if(argc>=2){
    length_window=atoi(argv[1]);
  }else{
    length_window=7;
  }

  bsup=length_window;

  init_reseau(EMISSION);

  printf("[TRP] Initialisation reseau : OK.\n");
  printf("[TRP] Debut execution protocole transport.\n");


      /* lecture de donnees provenant de la couche application */
      de_application(message, &taille_msg);
      while(taille_msg!=0){
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
