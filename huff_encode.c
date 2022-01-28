
#include "arbrebin.h"
#include "bfile.h"
#include "fap.h"
#include "huffman_code.h"
#include <assert.h>
#include <stdio.h>

typedef struct {
    int tab[256];
} TableOcc_t;

struct code_char HuffmanCode[256];

void ConstruireTableOcc(FILE *fichier, TableOcc_t *TableOcc) {

    int c;

    /* A COMPLETER ... */
    //printf("Programme non realise (ConstruireTableOcc)\n");
    for (c=0; c<256; c++) {
    	TableOcc->tab[c]=0;
    }
    c = fgetc(fichier);
    while (c != EOF) {
        TableOcc->tab[c] ++;
        c = fgetc(fichier);
    };


    int i;
    for (i = 0; i < 256; i++) {
        if (TableOcc->tab[i] != 0)
            printf("Occurences du caractere %c (code %d) : %d\n", i, i,
                   TableOcc->tab[i]);
    }
}

fap InitHuffman(TableOcc_t *TableOcc) {
    /* A COMPLETER */
    //printf("Programme non realise (InitHuffman)\n");
    fap res = creer_fap_vide();
    //int k =0;
    Arbre A ;
    for (int c=0; c<256; c++) {
    	if (TableOcc->tab[c]!=0){
    		A = NouveauNoeud(ArbreVide(), (Element) c,ArbreVide());
    		res=inserer(res, A, TableOcc->tab[c]);
    		//k++;
    	}
    }
    //A = NouveauNoeud(ArbreVide(), (Element) k,ArbreVide());
    //res=inserer(res, A, 0);
    return res;
}

Arbre ConstruireArbre(fap file) {
    /* A COMPLETER */
    //printf("Programme non realise (ConstruireArbre)\n");
    Arbre e1, e2, e3;
    int p1, p2;
    
    //file = extraire(file, &e1, &p1);
    //int N = e1->etiq;
    //int i=1;
    while (1){
    	file = extraire(file, &e1, &p1);
    	if (est_fap_vide(file)) {
    		break ;
    	}
    	file = extraire(file, &e2, &p2);
    	e3 = NouveauNoeud(e1, (Element) 0, e2);
    	file = inserer(file, e3, p1+p2);
    	//i++;
    }
    return e1;
}

void rec (Arbre huff, struct code_char c){

	if (EstVide(FilsGauche(huff)) && EstVide(FilsDroit(huff))){
		printf("le code de %c est : ", Etiq(huff));
		for(int j = 0 ; j<c.lg ; j++) {
			HuffmanCode[Etiq(huff)].code[j] = c.code[j];
			printf("%d",c.code[j]);
		}
		printf("\n");
		HuffmanCode[Etiq(huff)].lg = c.lg;
	}else {
		c.code[c.lg]=0;
		c.lg++;
		rec(FilsGauche(huff), c);
		c.code[c.lg-1]=1;
		rec(FilsDroit(huff), c);
	}

}

void ConstruireCode(Arbre huff) {
    /* A COMPLETER */
    //printf("Programme non realise (ConstruireCode)\n");
    
	struct code_char c;
	c.lg=0;
	rec(huff, c);
    
}

void Encoder(FILE *fic_in, FILE *fic_out, Arbre ArbreHuffman) {
    /* A COMPLETER */
    //printf("Programme non realise (Encoder)\n");
    int c;
    BFILE *out;
    EcrireArbre(fic_out, ArbreHuffman);
    out = bstart(fic_out, "w");
    
    while ((c=fgetc(fic_in)) != EOF) {
        for(int i=0; i<HuffmanCode[c].lg; i++){
        	bitwrite(out, HuffmanCode[c].code[i]);
        }
    }
    bstop(out);
}

int main(int argc, char *argv[]) {

    TableOcc_t TableOcc;
    FILE *fichier;
    FILE *fichier_encode;

    fichier = fopen(argv[1], "r");
    /* Construire la table d'occurences */
    ConstruireTableOcc(fichier, &TableOcc);
    fclose(fichier);

    /* Initialiser la FAP */
    fap file = InitHuffman(&TableOcc);

    /* Construire l'arbre d'Huffman */
    Arbre ArbreHuffman = ConstruireArbre(file);

        AfficherArbre(ArbreHuffman);

    /* Construire la table de codage */
    ConstruireCode(ArbreHuffman);

    /* Encodage */
    fichier = fopen(argv[1], "r");
    fichier_encode = fopen(argv[2], "w");

    Encoder(fichier, fichier_encode, ArbreHuffman);
    LibererArbre(ArbreHuffman);
    
    fclose(fichier_encode);
    fclose(fichier);

    return 0;
}
