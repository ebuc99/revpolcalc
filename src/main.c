#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define NUMBER '0'
#define IDENTIFIER 'I'
#define MAXOPS 100
#define MAXINTBUF 50

int getops(char s[]);
void push(double a);
double pull(void);
double getTop(void); 
void duplicate(void);
void swap(void);
void clear(void);
void ident(char s[]);

int main() {
     int op;
     char s[MAXOPS];
     double temp_value;
     while((op=getops(s)) != EOF) {
         switch(op) {
            case NUMBER:
                push(atoi(s));
                break;
            case '+':
                push(pull() + pull());
                break;
            case '-':
                temp_value = pull();
                push(pull() - temp_value);
                break;
            case '*':
                push(pull() * pull());
                break;
            case '/':
                temp_value = pull();
                push(pull() / temp_value);
                break;
			case '%':
				temp_value = pull();
				push((int)pull() % (int)temp_value);
				break;
			case IDENTIFIER:
				ident(s);
				break;
            case '\n':
                printf("Ergebnis: %.2f\n", pull());
                break;
            default:
                printf("Unbekannt\n");
                break;
         }
     }
     return 0;
}

#include <string.h>
void ident(char s[]) {
	if(strstr(s, "p"))
		printf("oberstes Element: %.2f\n", getTop());
	else if(strstr(s, "d"))
		duplicate();
	else if(strstr(s, "s"))
		swap();
	else if(strstr(s, "c"))
		clear();
}
double dbbuf[MAXINTBUF];
int dbbufpos = 0;
void push(double a) {
     dbbuf[dbbufpos++] = a;
}

double pull(void) {
     if(dbbufpos)
         return dbbuf[--dbbufpos];
     else
         printf("Fehler: keine Werte im Puffer vorhanden!\n");
     return 0;
}

double getTop(void) {
	return dbbuf[dbbufpos - 1];
}

void duplicate(void) {
	dbbuf[dbbufpos] = dbbuf[dbbufpos-1];
	dbbufpos++;
}

void swap(void) {
	double temp = dbbuf[dbbufpos-1];
	dbbuf[dbbufpos-1] = dbbuf[dbbufpos-2];
	dbbuf[dbbufpos-2] = temp;
}

void clear(void) {
	while(dbbufpos)
		dbbuf[--dbbufpos] = 0;
}

int getch();
void ungetch(char c);

int getops(char s[]) {
    int i = 0;
    char c;
	int sign = 0;
    while((s[i] = c = getch()) == ' ');
    s[++i] = '\0';
	if(isalpha(c)) {
		while(isalpha(s[i++] = c = getch()));
		s[i] = '\n';
		return IDENTIFIER;
	}
    if(!isdigit(c)) {
		if(c == '-') {
			sign = 1;
		}
		else
			return c;
	}
    if(isdigit(c) || sign) {
		while(isdigit(s[i++] = c = getch()));
        s[i] = '\0';
    }
    if(c != EOF)
		ungetch(c);
	if((i == 2) && sign)
		return '-';
    return NUMBER;
}

#define MAXBUF 100
char buf[MAXBUF];
int i = 0;

int getch() {
     return i ? buf[--i] : getchar();
}

void ungetch(char c) {
     buf[i++] = c;
}
