#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

char* randstring(size_t length) {

    static char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";        
    char *randomString = NULL;

    if (length) {
        randomString = malloc(sizeof(char) * (length +1));

        if (randomString) {            
            for (int n = 0;n < length;n++) {            
                int key = rand() % (int)(sizeof(charset) -1);
                randomString[n] = charset[key];
            }

            randomString[length] = '\0';
        }
    }

    return randomString;
}

int main(int argc, char** argv) {
    // important that num_cands evenly divisible by num_parties
    if (argc == 7 && argv[6][0] == 'c') {
        // vote_sys_gen num_parties num_seats num_ballots num_cands cand_name_length c
        FILE * file;
        
        int num_parties = atoi(argv[1]);
        // ballot ordering
        int num_seats = atoi(argv[2]);
        int num_ballots = atoi(argv[3]);
        int num_cands = atoi(argv[4]);
        size_t name_len = atoi(argv[5]);

        file = fopen("data/output_file.txt", "w");

        if(!file) {
            printf("Unable to create file.\n");
            exit(EXIT_FAILURE); 
        }

        fprintf(file, "CPL\n");
        fprintf(file, "%s\n", argv[1]);

        // char buffer[128];
        char parties[num_parties];
        for (int i = 0 ; i < num_parties ; i++) {
            parties[i] = '\0';
        }
        char party;
        int no_repeats = 0;
        fprintf(file, "[");
        for (int i = 0 ; i < num_parties ; i++) {
            party = '\0';
            no_repeats = 0;
            while(!no_repeats) {
                char * tmp =  randstring(1);
                party = (char) tmp[0];
                int ind = 0;
                while (parties[ind] != '\0') {
                    if (party == parties[ind++]) {
                        party = '\0';
                        break;
                    }
                }
                if (party != '\0') {
                    no_repeats = 1;
                    parties[i] = party;
                    if (i == num_parties-1) {
                        fprintf(file, "%c", parties[i]);
                    } else {
                        fprintf(file, "%c,", parties[i]);
                    }
                }
            }
        }
        fprintf(file, "]\n");
        fprintf(file, "%s\n", argv[2]);
        fprintf(file, "%s\n", argv[3]);
        fprintf(file, "%s\n", argv[4]);

        for (int i = 0 ; i < num_parties ; i++) {
            for(int k = 0 ; k < ceil(num_cands/num_parties) ; k++) {
                fprintf(file, "[%s,%c,%d]\n", randstring(name_len), parties[i], k+1);
            }
        }
        char base[num_cands];
        for (int i = 0 ; i < num_cands ; i++ ) {
            base[i] = ',';    
        }
        char * ballot = malloc(sizeof(base));
        for (int i = 0 ; i < num_ballots ; i ++) {
            strcpy(ballot, base);
            int key = rand() % (int)(sizeof(base) -1);
            ballot[key] = '1';
            ballot[sizeof(base)] = '\0';
            fprintf(file, "%s\n", ballot);
        }
        fclose(file);
    }
    else if (argc == 7 && argv[6][0] == 'o') {
        FILE * file;
        // vote_sys_gen num_seats num_ballots num_cands name_len num_parties o
        int num_seats = atoi(argv[1]);
        int num_ballots = atoi(argv[2]);
        int num_cands = atoi(argv[3]);
        size_t name_len = atoi(argv[4]);
        int num_parties = atoi(argv[5]);

        file = fopen("data/output_file.txt", "w");

        if(!file) {
            printf("Unable to create file.\n");
            exit(EXIT_FAILURE); 
        }

        fprintf(file, "OPL\n");
        fprintf(file, "%s\n", argv[1]);
        fprintf(file, "%s\n", argv[2]);
        fprintf(file, "%s\n", argv[3]);
        // char buffer[128];
        char parties[num_parties];
        for (int i = 0 ; i < num_parties ; i++) {
            parties[i] = '\0';
        }
        char party;
        int no_repeats = 0;
        for (int i = 0 ; i < num_parties ; i++) {
            party = '\0';
            no_repeats = 0;
            while(!no_repeats) {
                char * tmp =  randstring(1);
                party = (char) tmp[0];
                // printf("party is: %c\n", party);
                int ind = 0;
                while (parties[ind] != '\0') {
                    if (party == parties[ind++]) {
                        party = '\0';
                        break;
                    }
                }
                if (party != '\0') {
                    no_repeats = 1;
                    parties[i] = party;
                }
            }
            for(int k = 0 ; k < ceil(num_cands/num_parties) ; k++) {
                fprintf(file, "[%s,%c]\n", randstring(name_len), party);
            }
        }
        char base[num_cands];
        for (int i = 0 ; i < num_cands ; i++ ) {
            base[i] = ',';    
        }
        char * ballot = malloc(sizeof(base));
        for (int i = 0 ; i < num_ballots ; i ++) {
            strcpy(ballot, base);
            int key = rand() % (int)(sizeof(base) -1);
            ballot[key] = '1';
            ballot[sizeof(base)] = '\0';
            fprintf(file, "%s\n", ballot);
        }
        fclose(file);
    }
    return 0;
}