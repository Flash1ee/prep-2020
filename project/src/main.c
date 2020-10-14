#include <stdio.h>
#include <string.h>

#include "utils.h"
#include "write.h"

int main(void) {
    while (TRUE) {
        printf("%s", "please enter action\n1 enter data client:\n2 enter data transaction:\n3 update base\n");

        int choice = 0;
        if (scanf("%d", &choice) != 1) {
            break;
        }
        switch (choice) {
            case CLIENT: {
                FILE* client_file = NULL;
                client_file = fopen(CLIENT_FILE, "a+");
                if (!client_file) {
                    puts("Not access");
                } else {
                    write_client_file(client_file);
                    fclose(client_file);
                }
                break;
            }
            case TRANSACTION: {
                FILE* transaction_file = NULL;
                transaction_file = fopen(TRANSACTION_FILE, "a+");
                if (!transaction_file) {
                    puts("Not access");
                } else {
                    write_transaction_file(transaction_file);
                    fclose(transaction_file);
                }
                break;
            }
            case BLACKRECORD: {
                FILE* client_file = NULL;
                FILE* transaction_file = NULL;
                FILE* blackrecord_file = NULL;

                client_file = fopen(CLIENT_FILE, "r");
                transaction_file = fopen(TRANSACTION_FILE, "r");
                blackrecord_file = fopen(BLACKRECORD_FILE, "w");

                if (!client_file || !transaction_file || !blackrecord_file) {
                    if (client_file) {
                        fclose(client_file);
                    }
                    if (transaction_file) {
                        fclose(transaction_file);
                    }
                    if (blackrecord_file) {
                        fclose(blackrecord_file);
                    }
                    puts("Not access");
                    break;
                } else {
                    write_blackrecord_file(client_file, transaction_file, blackrecord_file);
                    fclose(client_file);
                    fclose(transaction_file);
                    fclose(blackrecord_file);
                    break;
                }
            }
            default:
                puts("error");
        }
    }
    return EXIT_SUCCESS;
}
