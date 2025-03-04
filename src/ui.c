#include "history.h"
#include "tokenizer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 256

int main(){
    List *history = init_history();
    if (!history){
        printf("Failed to initialize history.\n");
        return 1;
    }

    char input[BUFFER_SIZE];
    printf("Welcome to tokenizer!\n");
    printf("This program allows you to input text to  tokenize it.\n");
    printf("You can recall previous inputs using '!<id>' (e.g., '!2' recalls the second entry).\n");
    printf("Type 'exit' to quit.\n");

    while (1){
        printf("> ");
        fflush(stdout);
        
        if (fgets(input, BUFFER_SIZE, stdin) == NULL){
            break;
        }
        
        size_t len = strlen(input);
        if (len > 0 && input[len - 1] == '\n'){
            input[len - 1] = '\0';
        }

        if (strcmp(input, "exit") == 0){
            printf("Exiting program. Goodbye!\n");
            break;
        }

	//Check if the input is a history recall command
        if (input[0] == '!' && strlen(input) > 1){
            int id = atoi(input + 1);
            char *history_entry = get_history(history, id);
            if (history_entry){
                printf("Recalling history item %d: %s\n", id, history_entry);
                char **tokens = tokenize(history_entry);
                
                printf("Tokens:\n");
                print_tokens(tokens);
                free_tokens(tokens);
            } else {
                printf("No history entry found for ID %d.\n", id);
            }
            continue;
        }

        add_history(history, input);
        char **tokens = tokenize(input);
        
        printf("Tokens:\n");
        print_tokens(tokens);
        free_tokens(tokens);
    }

    printf("History:\n");
    print_history(history);
    free_history(history);
    
    return 0;
}
