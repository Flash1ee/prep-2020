#include "io.h"

void client_info() {
    printf("1 Number account: \n"
           "2 Client name: \n"
           "3 Surname: \n"
           "4 Addres client: \n"
           "5 Client Telnum: \n"
           "6 Client indebtedness: \n"
           "7 Client credit limit: \n"
           "8 Client cash payments: \n");
}
void transaction_info() {
    printf("1 Number account: \n"
           "2 Client cash payments: \n");
}
int client_input(FILE *stream, Data *client) {
    if (!stream) {
        return ARG_ERR;
    }
    int rc = fscanf(stream,
                    "%d"
                    "%" LEN(NAME)"s"
                    "%" LEN(SURNAME)"s"
                    "%" LEN(ADDRES)"s"
                    "%" LEN(TELNUM)"s"
                    "%lf%lf%lf",
                    &(client->number),
                    client->name,
                    client->surname,
                    client->addres,
                    client->tel_number,
                    &(client->indebtedness), &(client->credit_limit), &(client->cash_payments));
    return rc;
}
int client_out(FILE *stream, const Data *client) {
    if (!stream) {
        return ARG_ERR;
    }
    int rc = fprintf(stream, "%-12d%-11s%-11s%-16s%20s%12.2f%12.2f%12.2f\n", client->number,
                     client->name,
                     client->surname,
                     client->addres,
                     client->tel_number,
                     client->indebtedness, client->credit_limit, client->cash_payments);
    return rc;
}
int transaction_input(FILE *stream, Data *transfer) {
    if (!stream) {
        return ARG_ERR;
    }
    int rc = fscanf(stream, "%d %lf", &(transfer->number), &(transfer->cash_payments));
    return rc;
}
int transaction_out(FILE *stream, const Data *transfer) {
    if (!stream) {
        return ARG_ERR;
    }
    int rc = fprintf(stream, "%-3d%-6.2f\n", transfer->number, transfer->cash_payments);
    return rc;
}
int blackrecord_input(FILE *stream, Data *client) {
    if (!stream) {
        return ARG_ERR;
    }
    int rc = fscanf(stream,
                    "%d"
                    "%" LEN(NAME)"s"
                    "%" LEN(SURNAME)"s"
                    "%" LEN(ADDRES)"s"
                    "%" LEN(TELNUM)"s"
                    "%lf%lf%lf",
                    &(client->number),
                    client->name,
                    client->surname,
                    client->addres,
                    client->tel_number,
                    &(client->indebtedness), &(client->credit_limit), &(client->cash_payments));
    return rc;
}
int blackrecord_out(FILE *stream, const Data *client) {
    if (!stream) {
        return -1;
    }
    int rc = fprintf(stream, "%-12d%-11s%-11s%-16s%20s%12.2f%12.2f%12.2f\n",
                     client->number, client->name,
                     client->surname, client->addres, client->tel_number,
                     client->indebtedness, client->credit_limit, client->cash_payments);
    return rc;
}
