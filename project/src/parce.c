#include "../inc/parce.h"

char *search_field(const char *str, const char *field) {
    char data_field[255];
    snprintf(data_field, sizeof(data_field), "%s:", field);
    char *res = strcasestr(str, data_field);
    if (!res) {
        return NULL;
    }
    if (!(res - str)) {
        res += get_cnt_space(res);
        return res + strlen(field) + 1;
    }
    while (*(res - 1) != '\n') {
        char *tmp = res;
        tmp++;
        res = strcasestr(tmp, data_field);
    }
    res += strlen(field) + 1;
    return res + get_cnt_space(res);
}
size_t get_cnt_space(char *beg) {
    char *tmp = beg;
    size_t k = 0;
    while (isspace(*tmp++)) {
        k++;
    }
    return k;
}
int parse_str(char *str, char *field, char **dst) {
    char *data = search_field(str, field);

    if (!data) {
        asprintf(dst, "%s", "");
        return EXIT_SUCCESS;
    }

    char *end = strchr(data, '\r');
    if (!end) {
        end = strchr(data, '\n');
    }
    while (1) {
        if (*end == '\n' && (*(end + 1) == ' ')) {
            end = strchr(end + 1, '\n');
        } else if (*end == '\r' && *(end + 1) == ' ') {
            end = strchr(end + 1, '\n');
        } else if (*end == '\r' && *(end + 2) == ' ') {
            end = strchr(end + 2, '\n');
        } else {
            data += get_cnt_space(data);
            asprintf(dst, "%.*s", (int)(end - data), data);
            // char *end_r = strrchr(*dst, '\r');
            // char *end_n = strrchr(*dst, '\n');
            // char *end = end_n;
            // if ((end_r - end_n) > 0) {
            //     end = end_r;
            // }
            // if (!end) {
            //     return EXIT_SUCCESS;
            // }
            char *end = *dst + strlen(*dst);
            for (char *cur = *dst; cur != end; cur++) {
                if (*cur == '\n' || *cur == '\r') {
                    *cur = 27;
                }
            }
            *end = '\0';
            size_t len = strlen(*dst);
            for (size_t i = 0; i < len; i++) {
                // if (isspace(*(*dst + i))) {
                if (*(*dst + i + 1) == 27) {
                    // while (isspace(*(*dst + i + 1))) {
                        while (*(*dst + i + 1) == 27) {
                        for (size_t j = i + 1; j < len; j++) {
                            *(*dst + j) = *(*dst + j + 1);
                        }
                        len--;
                    }
                }
            }
            return EXIT_SUCCESS;
        }
    }
}
letter_t *parse_header(char *str) {
    letter_t *letter = calloc(sizeof(letter_t), 1);
    if (!letter) {
        return NULL;
    }
    if (parse_str(str, "From", &(letter->sender))) {
        free_letter(letter);
        return NULL;
    }
    if (parse_str(str, "To", &(letter->recipient))) {
        free_letter(letter);
        return NULL;
    }
    if (parse_str(str, "Date", &(letter->date))) {
        free_letter(letter);
        return NULL;
    }
    get_content_type(str, &(letter->count_part));
    return letter;
}
void free_letter(letter_t *src) {
    free(src->date);
    free(src->recipient);
    free(src->sender);
    free(src);
}
int get_content_type(char *str, size_t *value) {
    char content_type[255];
    char *content_header = search_field(str, "Content-Type");
    if (!content_header) {
        *value = 1;
        return EXIT_SUCCESS;
    }
    char *end = strchr(content_header, '\r');
    if (!end) {
        end = strchr(content_header, '\n');
    }
    snprintf(content_type, sizeof(content_type), "%s", content_header);
    char *multipart = strcasestr(content_type, "multipart/");
    if (!multipart) {
        *value = 1;
        return EXIT_SUCCESS;
    }
    *value = get_boundary(str, "boundary");
    return EXIT_SUCCESS;
}
size_t get_boundary(char *content_type, const char *field) {
    char *boundary = strcasestr(content_type, field);
    if (!boundary || isalpha(*(boundary - 1))) {
        return 1;
    }
    boundary += strlen(field);
    boundary += get_cnt_space(boundary);
    boundary += 1;
    boundary += get_cnt_space(boundary);
    char res[255];
    size_t boundary_cnt = 0;
    char *cur = boundary;
    size_t cnt = 0;
    if (*cur == '\"') {
        boundary++;
        cur++;
        while (*cur != '\"') {
            cur++;
        }
        cnt = cur - boundary;
    } else {
        while (*cur != '\r' && *cur != '\n') {
            cnt++;
            cur++;
        }
    }
    res[0] = '-';
    res[1] = '-';
    res[2] = '\0';
    strncat(res, boundary, cnt);
    size_t cnt_wp_end = 0;
    for (size_t i = cnt + 1; i > 0; i--) {
        if (res[i] == ' ') {
            cnt_wp_end++;
        }
        else
        {
            break;
        }
    }
    res[cnt + 2 - cnt_wp_end] = '\0'; 
    char *tmp_new = strcasestr(content_type, res);
    char *tmp = tmp_new + 1;
    char *data;
    while (tmp_new) {
        data = strcasestr(tmp_new, "Content");
        if (data) {
            boundary_cnt++;
        }
        tmp = tmp_new;
        tmp++;
        tmp_new = strcasestr(tmp, res);
        tmp = tmp_new;
    }
    return boundary_cnt;
}
void letter_print(letter_t *src) {
    printf("%s|%s|%s|%zu\n", src->sender, src->recipient, src->date, src->count_part);
}