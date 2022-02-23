
extern char* utoa_s(int num);
extern int atou_s(char* num);



int main(int argc, char **argv) {
    int b = 8745;
    char* c = utoa_s(b);
    printf("%s\n", c);
}