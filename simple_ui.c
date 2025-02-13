#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 256

int main(void){
    char input[BUFFER_SIZE];

    printf("Welcome to the simple UI!\n");
    printf("Type anything and it will be echoed back. Type 'exit' to quit.\n");

    while (1){
        printf("> "); //Indicator showing program is ready                                        
        if (fgets(input, BUFFER_SIZE, stdin) == NULL){
            break; //Exit if input fails                                                          
        }

        //Remove trailing newline character if present                                            
        size_t len = strlen(input);
        if (len > 0 && input[len - 1] == '\n'){
            input[len - 1] = '\0';
        }
	
        //Check if user wants to exit                                                             
        if (strcmp(input, "exit") == 0){
            printf("Exiting program. Goodbye!\n");
            break;
        }

        printf("%s\n", input); //Echo the input back                                              
    }

    return 0;
}
