#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if(argc < 2){ 
        printf("Pass arguments bro!");
        return 0;
    }

    char *tape = calloc(30000, 1);
    tape += 1000;
    int *stack = calloc(30000, 4);
    int pos = 0;
    FILE *pF = fopen(argv[1], "r");
    char buffer;
    while ((buffer = fgetc(pF)) != EOF)
    {
        switch (buffer)
        {
        case '+':
            (*tape)++;
            break;
        case '-':
            (*tape)--;
            break;
        case '>':
            tape++;
            break;
        case '<':
            tape--;
            break;
        case '.':
            printf("%c", *tape);
            break;
        case ',':
            scanf("%c", tape);
            break;
        case '[':
            if ((*tape) == 0)
            {
                int count = 0;
                while ((buffer = fgetc(pF)) != ']' || count != 0)
                {
                    if (buffer == ']')
                        count--;
                    else if (buffer == '[')
                        count++;
                    pos++;
                }
            }
            else
            {
                *stack = pos;
                stack += 4;
            }
            break;
        case ']':
            stack-=4;
            if ((*tape) != 0)
            {
                pos = (*stack);  

                fseek(pF, pos, SEEK_SET);
                pos--;
            }
            break; 
        case '\n':
        case '\r':
            pos++;           
        }
        
        pos++;
    }
    free(tape);
    free(stack);
    fclose(pF);
    return 0;
}