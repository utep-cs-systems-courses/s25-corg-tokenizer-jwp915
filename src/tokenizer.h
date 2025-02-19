#include "tokenizer.h"
#include <stdio.h>
#include <stdlib.h>

//Checks if a character is a space or tab
int space_char(char c){
    return (c == ' ' || c == '\t');
}

//Checks if a character is not a space and not null terminator
int non_space_char(char c){
    return !space_char(c) && c != '\0';
}

//Finds the start of the next token in a string
char *token_start(char *str){
    if (!str) return NULL;
    while (*str && space_char(*str)) str++;
    return *str ? str : NULL;
}

//Finds the end of a token in a string
char *token_terminator(char *token){
    if (!token) return NULL;
    while (*token && non_space_char(*token)) token++;
    return token;
}

//Counts the number of tokens in a string
int count_tokens(char *str){
    int count = 0;
    char *tok = token_start(str);
    while (tok){
        count++;
        tok = token_start(token_terminator(tok));
    }
    return count;
}

//Copies a substring of given length into a newly allocated string
char *copy_str(char *inStr, short len){
    if (!inStr || len <= 0) return NULL;
    char *copy = (char *)malloc(len + 1);
    if (!copy) return NULL;
    for (short i = 0; i < len; i++){
        copy[i] = inStr[i];
    }
    copy[len] = '\0';
    return copy;
}

//Tokenizes a string into an array of tokens
char **tokenize(char *str){
    if (!str) return NULL;
    int num_tokens = count_tokens(str);
    char **tokens = (char **)malloc((num_tokens + 1) * sizeof(char *));
    if (!tokens) return NULL;
    
    int i = 0;
    char *tok = token_start(str);
    while (tok){
        char *end = token_terminator(tok);
        tokens[i++] = copy_str(tok, end - tok);
        str = end;
        tok = token_start(str);
    }
    tokens[i] = NULL;
    return tokens;
}

//Prints all tokens in the tokenized array
void print_tokens(char **tokens){
    if (!tokens) return;
    for (int i = 0; tokens[i]; i++){
        printf("%s\n", tokens[i]);
    }
}

//Frees memory allocated for tokens and the token array
void free_tokens(char **tokens){
    if (!tokens) return;
    for (int i = 0; tokens[i]; i++){
        free(tokens[i]);
    }
    free(tokens);
}

#endif
