/*
 * Colin Powell
 * CS362: Random Testing Quiz
 * 18/02/03
 */



#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

// declare global buffer to prevent mem. leaks from inputString
// idea from class Piazza post: "C: Returning a char pointer from a function"
char *buf = NULL;

char inputChar()
{
    // TODO: rewrite this function
    
    // list of characters to match
    char choices[] = "[]{}() ax";
    int sz = sizeof(choices) / sizeof(choices[0]);

    // return one of the characters to match
    return choices[ (rand() % sz) ];
}

char *inputString()
{
    // TODO: rewrite this function
    // length of "reset\0"
    int buf_len = 6; 
    int i = 0;      // counter
    
    // idea from Piazza post: "Random Testing Quiz Program Time"
    char candidates[] = {"rest\0"};

    // save number of candidate chars
    int num_cand_chars = sizeof(candidates) / sizeof(candidates[0]);

    // prevent memory leaks:
    if(buf) {
        free(buf);    
    }

    // malloc enough space for a terminal NULL char, in case NULL not
    // at end of randomly-generated string.
    buf = (char *)(malloc((buf_len + 1) * sizeof(char)));
    memset(buf, '\0', sizeof(char) * (buf_len + 1));
    // fill with random char in list of candidate chars 
    for(i = 0; i < buf_len; i++) {
        buf[i] = candidates [ rand() % (num_cand_chars) ];
    }

    return buf;

}

void testme()
{
  int tcCount = 0;
  char *s;
  char c;
  int state = 0;
  while (1)
  {
    tcCount++;
    c = inputChar();
    s = inputString();
    printf("Iteration %d: c = %c, s = %s, state = %d\n", tcCount, c, s, state);

    if (c == '[' && state == 0) state = 1;
    if (c == '(' && state == 1) state = 2;
    if (c == '{' && state == 2) state = 3;
    if (c == ' '&& state == 3) state = 4;
    if (c == 'a' && state == 4) state = 5;
    if (c == 'x' && state == 5) state = 6;
    if (c == '}' && state == 6) state = 7;
    if (c == ')' && state == 7) state = 8;
    if (c == ']' && state == 8) state = 9;
    if (s[0] == 'r' && s[1] == 'e'
       && s[2] == 's' && s[3] == 'e'
       && s[4] == 't' && s[5] == '\0'
       && state == 9)
    {
      printf("error ");
      exit(200);
    }
  }
}


int main(int argc, char *argv[])
{
    srand(time(NULL));
    testme();
    return 0;
}
