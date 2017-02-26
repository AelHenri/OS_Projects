#include "userinput.h"
#include "autocomplete.h"

#define MAX_SIZE 50
extern Autocomplete *autocomplete;

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

int autocompleteNext(char *firstchars, char *buffer, int printed) {
    next(&autocomplete, firstchars);
    getCurrent(&autocomplete, &buffer);
    printAutocomplete(printed, buffer);
    return strlen(buffer);
}

int autocompletePrevious(char *firstchars, char *buffer, int printed) {
    previous(&autocomplete, firstchars);
    getCurrent(&autocomplete, &buffer);
    printAutocomplete(printed, buffer);
    return strlen(buffer);
}

void user_input(char **line)
{
    int c;
    int buffersize = MAX_SIZE;
    char *buffer = malloc(buffersize * sizeof(char));
    char *firstchars = malloc(buffersize * sizeof(char));    
    int autocompleting = 0;
    int printed = 0;
    buffer[0] = '\0';
    int i = 0;
    int cursor = 0;
    while('\n'!=(c=getkey())) {
        if (c == '\033') { // if the first value is esc
            getkey(); // skip the [
            switch(getkey()) { // the real value
                case 'A':
                    if (!autocompleting) {
                        autocompleting = 1;
                        strcpy(firstchars, buffer);
                        printed = i;
                        if (cursor < i) {
                            for (int j = cursor; j<i; j++) printf(" ");
                        }
                        //cursor = i;
                        getCurrent(&autocomplete, &buffer);
                        printAutocomplete(printed, buffer);
                        printed = strlen(buffer);
                    }
                    else { 
                        printed = autocompleteNext(firstchars, buffer, printed);
                    }
                    i = printed;
                    cursor = printed;
                    break;
                case 'B':
                    if (autocompleting) {
                        printed = autocompletePrevious(firstchars, buffer, printed);
                        i = printed;
                        cursor = printed;
                    }
                    break;
                case 'C':
                    if (autocompleting) autocompleting = 0;
                    if (cursor < i) {
                        printf("%c", buffer[cursor]);// move cursor to the right
                        cursor++;
                    }
                    break;
                case 'D':
                    if (autocompleting) autocompleting = 0;
                    if (cursor > 0) {
                        cursor--;
                        printf("\b");// move cursor to the left
                    }
                    break;
            }
        }
        else if (c==8 && i>0 && cursor>0) {
            if (autocompleting) autocompleting = 0;
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
        else if (c==127 && cursor < i) {
            if (autocompleting) autocompleting = 0;
            i--;
            delete(buffer, cursor);
        }
        else if (c == 9) {
            if (!autocompleting) {
                autocompleting = 1;
                strcpy(firstchars, buffer);
                printed = i;
                getCurrent(&autocomplete, &buffer);
                printAutocomplete(printed, buffer);
                printed = strlen(buffer);
            }
            else {
                printed = autocompleteNext(firstchars, buffer, printed);
            }
            i = printed;
            c = printed;
        }

        else if (c >= 32 && c<= 255 && c!=127) {
            if (autocompleting) autocompleting = 0;
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
    addLine(&autocomplete, buffer);
    goToStart(&autocomplete);
    *line = malloc(sizeof(buffer));
    if (buffer != NULL)
        strcpy(*line, buffer);;
    printf("\n");
    free(buffer);
    buffer = NULL;
    free(firstchars);
    firstchars = NULL;
}