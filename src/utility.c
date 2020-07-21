#include "headers/utility.h"

/*
    summary:                    Safely converts a string to an integer
    string                      The string to be converted to int
    error:                      Set if there was an error converting.
                                Should be set to GOOD before passing it in
                                You're asking for problems if you don't.

    Returns:                    If error is not set, it returns int version
                                of string If error is set, it's anyone's
                                guess what value it returns                
    Note:                       Don't trust the return value is error is set
                                as this function does not terminate early if
                                there is an error.
*/
int string_to_int(char *string, StringConErr *error)
{
    int number;

    if (string != NULL) { // NULL pointer makes strtol sad
        char *token;
        number = (int) strtol(string, &token, 10); // 10 for base-10
        if ((strlen(token) != 0) || (strlen(string) == 0)) {
            *error = NOT_NUMBER;
        }

        // Ensuring any additional white-space invalidates conversion
        for (int i = 0; i < strlen(string); i++) {
            if (string[i] == ' ' || string[i] == '\t') {
                *error = WHITE_SPACE; // having any white-space is bad
            }
        }

        // ensuring there is no leading 0
        if (strlen(string) > 1 && string[0] == '0') {
            *error = LEADING_ZERO; // string had white-space
        }
    } else {
        *error = NULL_STRING;
    }

    return number;
}

/*
        summary:        Gets the name of the file extension for the file name
                        Inputted.
        
        fileName:       The name of the file to get the extension for.

        returns:        The extension of the file, or NULL if couldn't be
                        found.
*/
char *get_file_extension(char *fileName)
{
        size_t fileLen = strlen(fileName);
        char c;
        for (int i = 0; i < fileLen; i++)
        {
                char c = fileName[i];
                if (c == '.')
                {
                        return fileName + i + 1;
                }
        }
        
        return NULL;
}