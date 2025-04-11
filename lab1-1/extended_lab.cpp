#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BIGRAMS 1000

typedef struct {
    char bigram[3];  
    int count;
} BigramFreq;

const char *commonBigrams[] = {
    "TH", "HE", "IN", "ER", "AN", "RE", "ND", "ON", "EN", "AT",
    "OU", "ED", "HA", "TO", "OR", "IT", "IS", "HI", "ES", "NG",
    "ST", "AR", "NT", "SE", "LE", "VE", "ME", "DE", "CO", "TA",
    "EC", "MA", "TI", "TE", "AL", "LL", "RO", "LI", "EL", "CA",
    "RI", "CH", "IC", "GE", "NE", "RA", "DI", "WA", "NO", "BE",
    "SO", "LO", "UR", "UT", "TR", "NA", "FO", "WI", "WE", "EA",
    "CL", "PR", "MO", "AB", "US", "IM", "AC", "BO", "DO", "PE",
    "FR", "CR", "PL", "SH", "DR", "AD", "EX", "AP", "BR", "CU",
    "GA", "HO", "KN", "OP", "SP", "UN", "WH", "YA", "VI", "WI",
    "BL", "AM", "SC", "QU", "AV", "FL", "GL", "GR", "GU", "SU"
};


int extractBigramFreqs(const char *text, int len, BigramFreq *freqs) {
    int total = 0;
    for (int i = 0; i < len - 1; i += 2) {
        char a = text[i];
        char b = text[i + 1];

        char bg[3] = { a, b, '\0' };
        int found = 0;

        for (int j = 0; j < total; j++) {
            if (strcmp(freqs[j].bigram, bg) == 0) {
                freqs[j].count++;
                found = 1;
                break;
            }
        }

        if (!found) {
            strcpy(freqs[total].bigram, bg);
            freqs[total].count = 1;
            total++;
        }
    }
    return total;
}

int compareFreq(const void *a, const void *b) {
    return ((BigramFreq *)b)->count - ((BigramFreq *)a)->count;
}


void decodeByBigramSubstitution(const char *cipher, int len) {
    BigramFreq freqs[MAX_BIGRAMS];
    int n = extractBigramFreqs(cipher, len, freqs);

    qsort(freqs, n, sizeof(BigramFreq), compareFreq);

    int mapSize = sizeof(commonBigrams) / sizeof(commonBigrams[0]);
    printf("\nË«×ÖÄ¸ÆµÂÊÌæ»»Ó³Éä£º\n");
    for (int i = 0; i < mapSize && i < n; i++) {
        printf("  %s ¡ú %s\n", freqs[i].bigram, commonBigrams[i]);
    }

    printf("\n¼òµ¥Ó³Éä½á¹û:\n");
    for (int i = 0; i < len - 1; i += 2) {
        char bg[3] = { cipher[i], cipher[i + 1], '\0' };
        int matched = 0;
        for (int j = 0; j < mapSize && j < n; j++) {
            if (strcmp(bg, freqs[j].bigram) == 0) {
                printf("%s", commonBigrams[j]);
                matched = 1;
                break;
            }
        }
        if (!matched) {
            printf("%s", bg); 
        }
    }
    printf("\n");
}

int main() {
    const char *cipher ="RIGAUNLPGNANYFPLHRZMUBDSLDLXTGCXGYOFQNTDGSKMKXPLHBRHAHOFLDLXEXNUPTSGFNEWHKDFSNHZOFXBHZLTPMIXLXYSOPGOLXEBNFPOFZGRSOHDPHTLLCXLHKHTOKTPTPNSMPPOBKNFSFISEOHRLDLXPSNFRMNSLTQFEIKBMPRONFARRBKCMDZTQETHFPHQGFUOLXDSELHZTLAGMKTPLEOPLTEIUGLOFMRLSDFAKIDQFNMKTPTHRLFYOFCYNSPTHKISNFVMHOGRHRFQGYKMXBSTOKZOOFHCAQOFGRYGFATGITOFMIFATHZCKBBNFMRLFLHOGLIZLEZTSFPLTPUMOFBSDSPOHZBGTPLTOKAHINZOGCGYPORDRLQZMZGDSTMDRHSDNPLXZOBDXLUHETBXIMNQKIFTMDVAFMSQMDXGANTLRLOFZOGRBKTZIMNFARDMHRINXLUHGTHRROLXPMHZBGTOKIPLXBPXDMRLZGLXHRDQDHNRIMTHNLFOUZBGXLBGITHDLEGYGEDQOPVGNFQUBOEBDMTMUNKMLEDPIOBGZKQLLEGYUYPLRHSDFASFISEOHRLDLXNFEDFLARIOLDHDBMDHLXOFCYLTLKHZBGRIGAUNLPOFNISLLEZOGCPLPOTGHMXBTDLGHZTHBXHDPTOFDPNFEGNFFRTLTIRGFXDSKIAQEKNFELTPOFHLRBSDPOTHTPIHPLAHNLZUZOBDXLUHBHIZLXAOHDSNRZZOLDHDNLNPBGBGYUPMISPLTMDHAULTELHPOFZOBDRLHRQSMPTHCGOFESLRGDRGFLDZ";
    int len = strlen(cipher);
    decodeByBigramSubstitution(cipher, len);
    return 0;
}

