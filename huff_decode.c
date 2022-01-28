#include <stdio.h>

#include "arbrebin.h"
#include "assert.h"
#include "bfile.h"

void Decoder(FILE *fichier_encode, Arbre ArbreHuffman) {
       // AfficherArbre(ArbreHuffman);
    /* A COMPLETER */
    BFILE *in = bstart(fichier_encode, "r");
    int c = bitread(in);
    Arbre tmp = ArbreHuffman;
    while (!beof(in)){
    	if (c==0){
    		tmp=FilsGauche(tmp);
	}else {
		tmp=FilsDroit(tmp);
	}
	if (EstVide(FilsGauche(tmp)) && EstVide(FilsDroit(tmp))) {
		printf("%c",Etiq(tmp));
		tmp = ArbreHuffman;
	}
	c = bitread(in);
   }
	
    //printf("Programme non realise (Decoder)\n");
}

int main(int argc, char *argv[]) {
    FILE *fichier_encode = fopen(argv[1], "r");

    Arbre ArbreHuffman = LireArbre(fichier_encode);

    Decoder(fichier_encode, ArbreHuffman);

    fclose(fichier_encode);

    return 0;
}
