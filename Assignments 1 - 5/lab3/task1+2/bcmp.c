#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct diff {
    long offset; /* offset of the difference in file starting from zero*/
    unsigned char orig_value;     /* value of the byte in ORIG */
    unsigned char new_value;     /* value of the byte in NEW */
} diff;

typedef struct node node;

struct node {
    diff *diff_data; /* pointer to a struct containing the offset and the value of the bytes in each of the files*/
    node *next;
};

void list_print(node *diff_list, FILE* output){/*print recursively */
    if(diff_list == NULL){
        return;
    }
    list_print(diff_list->next, output);
    fprintf(output,"byte %lu %02X %02X\n", diff_list->diff_data->offset, diff_list->diff_data->orig_value, diff_list->diff_data->new_value);
}

diff* copy_const(diff* data){
    diff *output = malloc(sizeof(diff));
    output->new_value = data->new_value;
    output->orig_value = data->orig_value;
    output->offset = data->offset;
    return output;
}

node* list_append(node* diff_list, diff* data){
    node *head = (node*) malloc(sizeof(node));
    if(diff_list == NULL){
        head->next = NULL;
        diff *insert;
        insert = copy_const(data);
        head->diff_data = insert;
        return head;
    }
    head->next = diff_list;
    diff *newdata;
    newdata  = copy_const(data);
    head->diff_data = newdata;
    return head;
}


void list_free(node *diff_list){
    if(diff_list == NULL){
        return;
    }
    free(diff_list->diff_data);
    list_free(diff_list->next);
    free(diff_list);
}
void restore(char* file2, node* lst){
    FILE* second = fopen(file2,"r");
    fseek(second, 0, SEEK_END);
    int count = ftell(second);
    unsigned char *buffer = malloc(count*sizeof(char));
    fseek(second, 0, SEEK_SET);
    fread(buffer, count, sizeof(char), second);
    while(lst != NULL){
        buffer[lst->diff_data->offset] = lst->diff_data->orig_value;
        lst = lst->next;
    }
    second = fopen(file2, "w");
    fprintf(second, "%s", buffer);
    free(buffer);
    fclose(second);
}

void bcmp(char* file1, char* file2, FILE* output, int n, int flagt, int flagr){
    FILE* first = fopen(file1,"r");/*old*/
    FILE* second = fopen(file2,"r");/*new*/
    fseek(first, 0, SEEK_END);
    fseek(second, 0, SEEK_END);
    FILE* shorter;
    FILE* longer;
    int flag; /*who is longer*/
    if(ftell(first) >= ftell(second)){
        shorter = second;
        longer = first;
        flag = 1;
    }
    else{
        shorter = first;
        longer = second;
        flag = 0;
    }
    fseek(shorter, 0, SEEK_SET);
    fseek(longer, 0, SEEK_SET);

    char c; /*for the shorter file*/
    char d; /*for the longer file*/
    long ind = 0;
    int count = 0; /*for '-t' flag */
    node* lst = NULL;
    while(((c = fgetc(shorter)) != EOF) && n != 0){
        if(c == '\n'){
            continue;
        }
        d = fgetc(longer);
        if(c == d){
            ind += 1;
            continue;
        }
        n -= 1;
        count += 1;
        unsigned char old = flag? d:c;
        unsigned char new = flag? c:d;
        diff data = {ind, old, new};
        lst = list_append(lst, &data);
        ind += 1;
    }
    if(flagr) {
        restore(file2, lst);
    }
    if(flagt){
        fprintf(output, "There are %d changes\n", count);
        return;
    }

    list_print(lst, output);

    list_free(lst);
}



int main(int argc, char **argv) {
    FILE* output = stdout;
    int i;
    int flago = -1;
    int flagt = 0;
    int flagr = 0;
    int n = -1;
    for(i = 1; i < argc; i++){
        if(strcmp(argv[i],"-o")==0) {
            output = fopen(argv[++i], "w");
            flago = 1;
        }
        else if(strcmp(argv[i],"-t")==0){
            flagt = 1;
        }
        else if (strcmp(argv[i],"-k")==0){
            n = atoi(argv[++i]);
        }
        else if (strcmp(argv[i],"-r")==0){
            n = atoi(argv[++i]);
            flagr = 1;
        }
    }

    char *first;
    char *second;
    first = argv[argc - 3 - flago];
    second = argv[argc - 2 - flago];

    bcmp(first, second, output, n, flagt, flagr);
    return 0;
}

/*
int main(int argc, char **argv) {
    diff data = {0, 'c', 'a'};
    node* lst = list_append(NULL, &data);
    diff data2 = {1, 'd', 'v'};
    lst = list_append(lst, &data2);
    diff data3 = {2, 'e', 'v'};
    lst = list_append(lst, &data3);
    list_print(lst, stdout);
    list_free(lst);
    return 0;
}
*/


