#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if(argc < 2){ 
        printf("Pass arguments bro!");
        return 0;
    }

    FILE *pF = fopen(argv[1], "r");
    char *tape =(char*) calloc(30000, 1);
    tape += 1000;
    fseek(pF,0,SEEK_END);
    char program[ftell(pF)+1];
    program[ftell(pF)] = 0;
    fseek(pF,0,SEEK_SET);
    char buffer;
    int pos = 0;
    while((buffer = fgetc(pF)) != EOF){
        program[pos++] = buffer;
    }
    int *stack = (int*)calloc(30000, 4);
    pos = 0;


    while (pos < sizeof(program)-1)
    {
        buffer = program[pos];
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
                pos++;
                int count = 0;
                while ((buffer = program[pos]) !=  ']' || count != 0)
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
                pos--;
            }
            break;            
        }
        
        pos++;
    }
    free(tape);
    free(stack);
    fclose(pF);
    return 0;
}