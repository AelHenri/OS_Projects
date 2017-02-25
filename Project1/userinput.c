#include "userinput.h"

#define MAX_SIZE 50

int getkey() {
    int character;
    struct termios orig_term_attr;
    struct termios new_term_attr;

    /* save original terminal attributes */
    tcgetattr(fileno(stdin), &orig_term_attr);
    memcpy(&new_term_attr, &orig_term_attr, sizeof(struct termios));
    /* set the terminal to raw mode */
    new_term_attr.c_lflag &= ~(ECHO|ICANON);
    tcsetattr(fileno(stdin), TCSANOW, &new_term_attr);

    /* read a character from the stdin stream without blocking */
    /*   returns EOF (-1) if no character is available */
    character = fgetc(stdin);

    /* restore the original terminal attributes */
    tcsetattr(fileno(stdin), TCSANOW, &orig_term_attr);

    return character;
}

void append(char *string, char c) {
    int len = strlen(string);
    string[len] = c;
    string[len+1] = '\0';
}

void insert(char *string, char c, int pos) {
    char *tmp = malloc(sizeof(string));
    int len = strlen(string);
    int tmpi = len-pos+1;

    for (int i = len+1; i > pos; i--) {
        string[i] = string[i-1];
        tmp[tmpi] = string[i-1];
        tmpi--;
    }
    string[pos] = c;
    tmp[0] = c;
    printf("%s", tmp);
    for (int i = 0; i < len-pos; i++) {
        printf("\b");
    }
    free(tmp);
    tmp = NULL;
}

void backspace(char *string, int pos) {
    char *tmp = malloc(sizeof(string));
    int len = strlen(string);
    int tmpi = 0;
    for (int i = pos; i < len; i++) {
        string[i] = string[i+1];
        tmp[tmpi] = string[i+1];
        tmpi++;
    }
    printf("\b%s ", tmp);
    for (int i = 0; i < len-pos; i++) {
        printf("\b");
    }
    free(tmp);
    tmp = NULL;
}

void delete(char *string, int pos) {
    char *tmp = malloc(sizeof(string));
    int len = strlen(string);
    int tmpi = 0;
    for (int i = pos; i < len; i++) {
        string[i] = string[i+1];
        tmp[tmpi] = string[i+1];
        tmpi++;
    }
    printf("%s ", tmp);
    for (int i = 0; i < len-pos; i++) {
        printf("\b");
    }
    free(tmp);
    tmp = NULL;
}

void user_input(char **line)
{
    int c;
    int buffersize = MAX_SIZE;
    char *buffer = malloc(buffersize * sizeof(char));
    int i = 0;
    int cursor = 0;
    while('\n'!=(c=getkey())) {
        if (c == '\033') { // if the first value is esc
            getkey(); // skip the [
            switch(getkey()) { // the real value
                case 'A':
                    printf("up");// autocomplete previous
                    break;
                case 'B':
                    printf("down");// autocomplete next
                    break;
                case 'C':
                    if (cursor < i) {
                        printf("%c", buffer[cursor]);// move cursor to the right
                        cursor++;
                    }
                    break;
                case 'D':
                    if (cursor > 0) {
                        cursor--;
                        printf("\b");// move cursor to the left
                    }
                    break;
            }
        }
        else if (c==8 && i>0 && cursor>0) {
            i--;
            cursor--;
            if (cursor == i) {
                buffer[i] = '\0';
                printf("\b \b");
            }
            else {
                backspace(buffer, cursor);
            }
        }
        else if (c==127) {
            i--;
            delete(buffer, cursor);
        }
        else if (c == 9) printf("Autocomplete !");

        else if (c >= 32 && c<= 255 && c!=127) {
            if (cursor == i) {
                printf("%c", c);
                append(buffer, c);
            }
            else {
                insert(buffer, c, cursor);
            }
            i++;
            cursor++;
        }
        
        if (i+1 >= buffersize) {
            buffersize += MAX_SIZE;
            buffer = realloc(buffer, buffersize);
        }
    }
    //printf("\n", buffer);
    *line = malloc(sizeof(buffer));
    strcpy(*line, buffer);
    free(buffer);
}