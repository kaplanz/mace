//
//  mace.c
//  Matrix Arithmetic C-language Environment (Mace).
//
//  Created by Zakhary Kaplan on 2019-04-25.
//  Copyright © 2019 Zakhary Kaplan. All rights reserved.
//

#include "mace/mace.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mace/matrix.h"

// TODO: Add "ans" as input
// TODO: Prompt for invalid user function inputs

void mace(void) {
    printf("---------------------------------------------------------------\n");
    printf("Welcome to the Matrix Arithmetic C-language Environment (Mace).\n");
    printf("Copyright © 2019 Zakhary Kaplan. All rights reserved.\n");
    printf(
        "---------------------------------------------------------------\n\n");
    printf("Mace is a matrix arithmetic environment programmed in C.\n"
           "It uses bash-like syntax to perform matrix operations.\n\n");
    printf("Type \"help\" to see a list of commands.\n");

    // Allocate memory for for workspace, user input
    int size = 0;
    Matrix workspace[WORKSPACE_SIZE] = {};
    Matrix ans = NULL_MATRIX;

    // Begin running program
    while (1) {
        printf(">>> ");

        // Get user input
        char userInput[MAX] = {};
        fgets(userInput, MAX, stdin);
        strtok(userInput, "\n"); // remove newline from input

        // Store user inout as token to be processed
        char *token = userInput;

        // Validate input type
        char commandType = validateInput(&token);
        if (commandType != -1) {
            Matrix output; // reserve space for output of command

            switch (commandType) {
                case 0: // "\n"
                    continue; // do nothing on blank input

                case 1: // "help"
                    help(token);
                    continue;

                case 2: // "bye"
                    clr(&size, workspace, &ans);
                    break; // quit program

                case 3: // "print"
                    print(token, size, workspace, ans);
                    continue;

                case 4: // "clr"
                    clr(&size, workspace, &ans);
                    continue;

                case 5: // "mat"
                    output = mat(token, ans);
                    if (!isNull(output)) {
                        addToWorkspace(&size, workspace, output);
                    }
                    continue;

                case 6: // "ident"
                    output = ident(token);
                    if (!isNull(output)) {
                        addToWorkspace(&size, workspace, output);
                    }
                    continue;

                case 7: // "zeros"
                    output = zeros(token);
                    if (!isNull(output)) {
                        addToWorkspace(&size, workspace, output);
                    }
                    continue;

                case 8: // "add"
                    output = add(token, workspace, ans);
                    if (!isNull(output)) {
                        deleteMat(&ans); // delete previous answer
                        ans = output; // overwrite answer
                        printAns(ans);
                    }
                    continue;

                case 9: // "sub"
                    output = sub(token, workspace, ans);
                    if (!isNull(output)) {
                        deleteMat(&ans); // delete previous answer
                        ans = output; // overwrite answer
                        printAns(ans);
                    }
                    continue;

                case 10: // "mul"
                    output = mul(token, workspace, ans);
                    if (!isNull(output)) {
                        deleteMat(&ans); // delete previous answer
                        ans = output; // overwrite answer
                        printAns(ans);
                    }
                    continue;

                case 11: // "scl"
                    output = scl(token, workspace, ans);
                    if (!isNull(output)) {
                        deleteMat(&ans); // delete previous answer
                        ans = output; // overwrite answer
                        printAns(ans);
                    }
                    continue;

                case 12: // "trnsp"
                    output = trnsp(token, workspace, ans);
                    if (!isNull(output)) {
                        deleteMat(&ans); // delete previous answer
                        ans = output; // overwrite answer
                        printAns(ans);
                    }
                    continue;

                case 13: // "inv"
                    output = inv(token, workspace, ans);
                    if (!isNull(output)) {
                        deleteMat(&ans); // delete previous answer
                        ans = output; // overwrite answer
                        printAns(ans);
                    }
                    continue;

                case 14: // "det"
                    output = det(token, workspace, ans);
                    if (!isNull(output)) {
                        deleteMat(&ans); // delete previous answer
                        ans = output; // overwrite answer
                        printAns(ans);
                    }
                    continue;

                case 15: // "trc"
                    output = trc(token, workspace, ans);
                    if (!isNull(output)) {
                        deleteMat(&ans); // delete previous answer
                        ans = output; // overwrite answer
                        printAns(ans);
                    }
                    continue;

                default:
                    printf("Error: unknown command.\n");
                    break; // quit program
            }

            // Break out of program
            break;
        } else {
            printf("Invalid command.\n");
        }
    }
}

// -- Secondary functions --
int validateInput(char *input[]) {
    // Constant array of valid commands
    const char *commands[] = {
        "\n",
        "help",
        "bye",
        "print",
        "clr",
        "mat",
        "ident",
        "zeros",
        "add",
        "sub",
        "mul",
        "scl",
        "trnsp",
        "inv",
        "det",
        "trc",
    };
    const int NUM_COMMANDS = sizeof(commands) /
                             sizeof(char *); // number of valid commands

    // Create command token
    char *token = strtok(*input, " "); // " ("

    // Search commands for match with token
    int commandType = -1;
    for (int i = 0; i < NUM_COMMANDS; i++) {
        if (strcmp(token, commands[i]) == 0) {
            commandType = i; // set command type (0 reserved for base)
            break;
        }
    }

    // Get arguments token
    token = strtok(NULL, "\0"); // ")"
    *input = token;

    // Return input type
    return commandType;
}

void printEntry(int size, Matrix workspace[], int index) {
    printf("\n");
    printf("Mat%c (%dx%d) = \n",
           index + 'A',
           workspace[index].m,
           workspace[index].n);
    printMat(workspace[index]);
    printf("\n");
}

void printAns(Matrix ans) {
    printf("\n");
    printf("MatAns (%dx%d) = \n", ans.m, ans.n);
    printMat(ans);
    printf("\n");
}

void addToWorkspace(int *size, Matrix workspace[], Matrix object) {
    if (*size < WORKSPACE_SIZE) {
        // Add object to workspace
        workspace[*size] = object;

        // Incriment workspace size
        (*size)++;

        // Print added item
        printEntry(*size, workspace, *size - 1);
    } else {
        printf("Error: could not save new object to workspace. Clear the "
               "workspace with clr and try again.\n");
    }
}

int tagExists(int *size, char *tags[], char tag[]) {
    for (int i = 0; i < *size; i++) {
        if (strcmp(tags[i], tag) == 0) {
            return 1;
        }
    }

    return 0;
}

// -- Commands --
void help(char input[]) {
    char argv[MAX]; // create copy of argument input
    int helpCommandType; // get command type of input
    // Check if input is not null
    if (input != NULL) {
        strcpy(argv, input);
        helpCommandType = validateInput(&input);
    } else { // No parameters entered
        helpCommandType = 0;
    }

    if (helpCommandType == -1) {
        printf("\nNo help entry found for: %s\n", argv);
        printf("Use \"help\" to see a list of avalible commands.\n\n");
        return;
    } else if (helpCommandType) {
        printf("\nHelp menu: %s\n\n", argv);
    }

    switch (helpCommandType) {
        case 1: // "help"
            printf("Description:\n");
            printf("\t- Display help menu for Mace commands.\n");
            printf("\t- Call without parameters for quick help menu.\n");
            printf(
                "\t- Command name parameters specify individual command help "
                "menu.\n");

            printf("Parameters: string command (optional)\n");

            printf("Exmaple: help mat\n");
            break;

        case 2: // "bye"
            printf("Description: Quit the current Mace session. Closes "
                   "program.\n");
            break;

        case 3: // "print"
            printf("Description: Print all or some matricies from the "
                   "workspace.\n");

            printf("Parameters: string matrix identifier(s) (optional)\n");

            printf("Note: Identifiers are the letter associated with "
                   "a matrix in the workspace.\n");
            printf("\t- They can be written in either capital, or "
                   "lowercase,\n");
            printf("\t  and may be preceeded Mat (e.g. MatA).\n");
            printf("\t- The ans matrix can be written as MatAns, or ans.\n");

            printf("Examples:\n");
            printf("\t>>> print A B\n");
            printf("\t>>> print c ans\n");
            break;

        case 4: // "clr"
            printf("Description: Clear all saved variables (including ans) "
                   "from the workspace.\n");
            break;

        case 5: // "mat"
            printf("Description: Save a matrix to the "
                   "workspace.\n");
            printf("\t- Dimensions are "
                   "inferred from data.\n");
            printf("\t- Individual "
                   "items sepeerated by space, semicolons as "
                   "row-terminators.\n");
            printf("\t- Save the most recent output with parameter ans.\n");

            printf("Parameters: decimal data (or ans)\n");

            printf("Examples:\n");
            printf("\t>>> mat 1 2; 3 4\n");
            printf("\t>>> mat ans\n");
            break;

        case 6: // "ident"
            printf("Description: Save the identity matrix sized "
                   "nxn to the workspace.\n");

            printf("Parameters: integer n\n");

            printf("Example: ident 3\n");
            break;

        case 7: // "zeros"
            printf("Description: Save an empty matrix of zeros sized "
                   "mxn to the workspace.\n");

            printf("Parameters: integer m, n\n");

            printf("Example: zeros 3 4\n");
            break;

        case 8: // "add"
            printf("Description: Perform matrix addition on two "
                   "matricies from the workspace.\n");

            printf("Parameters: 2 string matrix identifiers\n");

            printf("Note: Identifiers are the letter associated with "
                   "a matrix in the workspace.\n");
            printf("\t- They can be written in either capital, or "
                   "lowercase,\n");
            printf("\t  and may be preceeded Mat (e.g. MatA).\n");
            printf("\t- The ans matrix can be written as MatAns, or ans.\n");

            printf("Examples:\n");
            printf("\t>>> add MatA MatB\n");
            printf("\t>>> add ans C\n");
            break;

        case 9: // "sub"
            printf("Description: Perform matrix subtraction on two "
                   "matricies from the workspace.\n");

            printf("Parameters: 2 string matrix identifiers\n");

            printf("Note: Identifiers are the letter associated with "
                   "a matrix in the workspace.\n");
            printf("\t- They can be written in either capital, or "
                   "lowercase,\n");
            printf("\t  and may be preceeded Mat (e.g. MatA).\n");
            printf("\t- The ans matrix can be written as MatAns, or ans.\n");

            printf("Examples:\n");
            printf("\t>>> sub d e\n");
            printf("\t>>> sub MatF MatAns\n");
            break;

        case 10: // "mul"
            printf("Description: Perform matrix multiplication on two "
                   "matricies from the workspace.\n");

            printf("Parameters: 2 string matrix identifiers\n");

            printf("Note: Identifiers are the letter associated with "
                   "a matrix in the workspace.\n");
            printf("\t- They can be written in either capital, or "
                   "lowercase,\n");
            printf("\t  and may be preceeded Mat (e.g. MatA).\n");
            printf("\t- The ans matrix can be written as MatAns, or ans.\n");

            printf("Examples:\n");
            printf("\t>>> mul a b\n");
            printf("\t>>> mul C ans\n");
            break;

        case 11: // "scl"
            printf("Description: Perform scalar multiplication on a "
                   "matrix the workspace.\n");

            printf("Parameters: double scalar, string matrix identifier\n");

            printf("Note: Identifiers are the letter associated with "
                   "a matrix in the workspace.\n");
            printf("\t- They can be written in either capital, or "
                   "lowercase,\n");
            printf("\t  and may be preceeded Mat (e.g. MatA).\n");
            printf("\t- The ans matrix can be written as MatAns, or ans.\n");

            printf("Examples:\n");
            printf("\t>>> scl -1.2 MatB\n");
            printf("\t>>> mul 5 ans\n");
            break;

        case 12: // "trnsp"
            printf("Description: Calculate the trnspose of a matrix "
                   "from the workspace.\n");

            printf("Parameters: string matrix identifier\n");

            printf("Note: Identifiers are the letter associated with "
                   "a matrix in the workspace.\n");
            printf("\t- They can be written in either capital, or "
                   "lowercase,\n");
            printf("\t  and may be preceeded Mat (e.g. MatA).\n");
            printf("\t- The ans matrix can be written as MatAns, or ans.\n");

            printf("Examples:\n");
            printf("\t>>> trnsp c\n");
            printf("\t>>> trnsp ans\n");
            break;

        case 13: // "inv"
            printf("Description: Calculate the inverse of a matrix "
                   "from the workspace.\n");

            printf("Parameters: string matrix identifier\n");

            printf("Note: Identifiers are the letter associated with "
                   "a matrix in the workspace.\n");
            printf("\t- They can be written in either capital, or "
                   "lowercase,\n");
            printf("\t  and may be preceeded Mat (e.g. MatA).\n");
            printf("\t- The ans matrix can be written as MatAns, or ans.\n");

            printf("Examples:\n");
            printf("\t>>> inv D\n");
            printf("\t>>> inv ans\n");
            break;

        case 14: // "det"
            printf("Description: Calculate the determinant of a matrix "
                   "from the workspace.\n");

            printf("Parameters: string matrix identifier\n");

            printf("Note: Identifiers are the letter associated with "
                   "a matrix in the workspace.\n");
            printf("\t- They can be written in either capital, or "
                   "lowercase,\n");
            printf("\t  and may be preceeded Mat (e.g. MatA).\n");
            printf("\t- The ans matrix can be written as MatAns, or ans.\n");

            printf("Examples:\n");
            printf("\t>>> det A\n");
            printf("\t>>> det ans\n");
            break;

        case 15: // "trc"
            printf("Description: Calculate the trace of a matrix "
                   "from the workspace.\n");

            printf("Parameters: string matrix identifier\n");

            printf("Note: Identifiers are the letter associated with "
                   "a matrix in the workspace.\n");
            printf("\t- They can be written in either capital, or "
                   "lowercase,\n");
            printf("\t  and may be preceeded Mat (e.g. MatA).\n");
            printf("\t- The ans matrix can be written as MatAns, or ans.\n");

            printf("Examples:\n");
            printf("\t>>> trc b\n");
            printf("\t>>> trc ans\n");
            break;

        default:
            // Print general help menu
            printf("\nQuick Help Menu:\n");

            printf("help\t- Get help using Mace.\n");
            printf("bye\t- Quit program.\n");
            printf("print\t- Print a matrix in the workspace.\n");
            printf("clr\t- Clear the workspace.\n");
            printf("mat\t- Make a new matrix.\n");
            printf("ident\t- Make an identity matrix.\n");
            printf("zeros\t- Make an empty matrix of zeros.\n");
            printf("add\t- Add two matricies.\n");
            printf("sub\t- Subtract two matricies.\n");
            printf("mul\t- Multiply two matricies.\n");
            printf("scl\t- Multiply a matrix by a scalar coefficient.\n");
            printf("trnsp\t- Find the transpose of a matrix.\n");
            printf("inv\t- Find the inverse of a matrix.\n");
            printf("det\t- Find the determinant of a matrix.\n");
            printf("trc\t- Find the trace of a matrix.\n");
            break;
    }

    printf("\n");
}

void print(char input[], int size, Matrix workspace[], Matrix ans) {
    int argc = 0;
    char argv[MAX];

    // Split input
    for (char *token = strtok(input, " "); token;
         token = strtok(NULL, " ")) { // " ,"

        // Get matrix identifier
        if (strlen(token) == 1)
            argv[argc++] = toupper(token[0]) - 'A';
        // Determine if "Mat" prefix is used
        else if (strncmp(token, "Mat", 3) == 0 && strlen(token) == 4)
            argv[argc++] = toupper(token[3]) - 'A';
        // Check for "ans" input
        else if (strcmp(token, "ans") == 0 || strcmp(token, "MatAns") == 0)
            argv[argc++] = ANS;
    }

    // Count parameters
    if (argc == 0) { // Print entire workspace
        if (size > 0 || !isNull(ans)) { // Check if workspace is empty
            printf("\nWorkspace (%d/%d):\n", size, WORKSPACE_SIZE);

            for (int i = 0; i < size; i++) {
                printEntry(size, workspace, i); // iteratively print each item
            }

            if (!isNull(ans))
                printAns(ans);
        } else { // If empty, alert user
            printf("\nWorkspace is empty.\n\n");
        }
    } else {
        // Print each operand
        for (int i = 0; i < argc; i++) {
            // Determine operand
            Matrix operand = (argv[i] == ANS) ? ans :
                                                workspace[(unsigned)argv[i]];

            // Print non null operands
            if (!isNull(operand)) {
                // Determine whether operand is in workspace, or is ans
                if (argv[i] == ANS) {
                    printAns(ans);
                } else {
                    printEntry(size, workspace, argv[i]);
                }
            } else { // Display error message for null operands
                // Check if ans was used while null
                if (isNull(ans) && (argv[i] == ANS)) {
                    printf(
                        "Error: perform an operation before attempting to use "
                        "ans.\n");
                } else {
                    printf("Error: operand #%d not recognized.\n", i + 1);
                }
            }
        }
    }
}

void clr(int *size, Matrix workspace[], Matrix *ans) {
    for (int i = 0; i < *size; i++) {
        deleteMat(&workspace[i]); // delete individual items
    }

    // Reset workspace size
    *size = 0;

    // Reset ans
    *ans = NULL_MATRIX;
}

Matrix mat(char input[], Matrix ans) {
    int argc = 0, rows = 0;
    double data[MAX] = {};

    char argv[MAX]; // create copy of argument input
    // Check if input is null
    if (input != NULL) {
        strcpy(argv, input);
    } else { // No data entered
        printf("Error: no matrix data entered. For help using mat, type "
               "\"help "
               "mat\".\n");
        return NULL_MATRIX;
    }

    // Poplate array of linear data
    for (char *token = strtok(argv, " ;"); token; // " ,;"
         token = strtok(NULL, " ;")) { // " ,;"
        data[argc++] = atof(token); // extract value from singular data token
    }

    // Count row terminating semicolons in argument
    for (char *token = strtok(input, ";"); token; token = strtok(NULL, ";"))
        rows++;

    if (strcmp(input, "ans") == 0) { // Use ans matrix as input
        if (!isNull(ans)) { // Check if ans is not null
            return copyMat(ans);
        } else { // Alert user
            printf("Error: perform an operation before attempting to use "
                   "ans.\n");
            return NULL_MATRIX;
        }
    } else if (argc % rows == 0) { // Only create matrix if no mismatch
        int cols = argc / rows;
        Matrix output = emptyMat(rows,
                                 cols); // create empty matrix of correct size

        // Delineate data, and populate matrix
        for (int i = 0; i < argc; i++) {
            int row = i / cols;
            int col = i % cols;
            output.data[row][col] = data[i];
        }

        return output;
    } else { // On mismatch, return NULL_MATRIX
        printf("Error: could not infer dimensions from data.");
        return NULL_MATRIX;
    }
}

Matrix ident(char input[]) {
    int argc = 0;
    int argv[MAX];

    // Split input
    for (char *token = strtok(input, " "); token;
         token = strtok(NULL, " ")) { // " ,"
        argv[argc++] = atoi(token);
    }

    // Count parameters
    if (argc == 1) {
        Matrix output = identityMat(argv[0]);
        // Check if output is not null
        if (isNull(output)) {
            printf("Error: invalid dimensions. Try again with a positive "
                   "integer.\n");
        }
        // Return result of operation
        return output;
    } else {
        printf("Error: incorrect number of parameters. (%d/1)\n", argc);
        return NULL_MATRIX;
    }
}

Matrix zeros(char input[]) {
    int argc = 0;
    int argv[MAX];

    // Split input
    for (char *token = strtok(input, " "); token;
         token = strtok(NULL, " ")) { // " ,"
        argv[argc++] = atoi(token);
    }

    // Count parameters
    if (argc == 2) {
        Matrix output = emptyMat(argv[0], argv[1]);

        // Check if output is not null
        if (isNull(output)) {
            printf("Error: invalid dimensions. Try again with two positive "
                   "integers.\n");
        }
        // Return result of operation
        return output;
    } else {
        printf("Error: incorrect number of parameters. (%d/2)\n", argc);
        return NULL_MATRIX;
    }
}

Matrix add(char input[], Matrix workspace[], Matrix ans) {
    int argc = 0;
    char argv[MAX];

    // Split input
    for (char *token = strtok(input, " "); token;
         token = strtok(NULL, " ")) { // " ,"

        // Get matrix identifier
        if (strlen(token) == 1)
            argv[argc++] = toupper(token[0]) - 'A';
        // Determine if "Mat" prefix is used
        else if (strncmp(token, "Mat", 3) == 0 && strlen(token) == 4)
            argv[argc++] = toupper(token[3]) - 'A';
        // Check for "ans" input
        else if (strcmp(token, "ans") == 0 || strcmp(token, "MatAns") == 0)
            argv[argc++] = ANS;
    }

    // Count parameters
    if (argc == 2) {
        Matrix operands[2]; // determine operands
        operands[0] = (argv[0] == ANS) ? ans : workspace[(unsigned)argv[0]];
        operands[1] = (argv[1] == ANS) ? ans : workspace[(unsigned)argv[1]];

        // Calculate output
        Matrix output = addMat(operands[0], operands[1]);

        // Check if output is null
        if (isNull(output)) {
            // Check if ans was used while null
            if (isNull(ans) && (argv[0] == ANS || argv[1] == ANS)) {
                printf("Error: perform an operation before attempting to use "
                       "ans.\n");
            } else if (isNull(operands[0]) ||
                       isNull(operands[1])) { // Operand is null
                printf("Error: operand not recognized.\n");
            } else {
                printf("Error: incompatible operands. Try again with "
                       "matricies of "
                       "same dimensions.\n");
            }
        }

        // Return result of operation
        return output;
    } else {
        printf("Error: incorrect number of parameters. (%d/2)\n", argc);
        return NULL_MATRIX;
    }
}

Matrix sub(char input[], Matrix workspace[], Matrix ans) {
    int argc = 0;
    char argv[MAX];

    // Split input
    for (char *token = strtok(input, " "); token;
         token = strtok(NULL, " ")) { // " ,"

        // Get matrix identifier
        if (strlen(token) == 1)
            argv[argc++] = toupper(token[0]) - 'A';
        // Determine if "Mat" prefix is used
        else if (strncmp(token, "Mat", 3) == 0 && strlen(token) == 4)
            argv[argc++] = toupper(token[3]) - 'A';
        // Check for "ans" input
        else if (strcmp(token, "ans") == 0 || strcmp(token, "MatAns") == 0)
            argv[argc++] = ANS;
    }

    // Count parameters
    if (argc == 2) {
        Matrix operands[2]; // determine operands
        operands[0] = (argv[0] == ANS) ? ans : workspace[(unsigned)argv[0]];
        operands[1] = (argv[1] == ANS) ? ans : workspace[(unsigned)argv[1]];

        // Calculate output
        Matrix output = addMat(operands[0], coeffMat(-1, operands[1]));

        // Check if output is null
        if (isNull(output)) {
            // Check if ans was used while null
            if (isNull(ans) && (argv[0] == ANS || argv[1] == ANS)) {
                printf("Error: perform an operation before attempting to use "
                       "ans.\n");
            } else if (isNull(operands[0]) ||
                       isNull(operands[1])) { // Operand is null
                printf("Error: operand not recognized.\n");
            } else {
                printf("Error: incompatible operands. Try again with "
                       "matricies of "
                       "same dimensions.\n");
            }
        }

        // Return result of operation
        return output;
    } else {
        printf("Error: incorrect number of parameters. (%d/2)\n", argc);
        return NULL_MATRIX;
    }
}

Matrix mul(char input[], Matrix workspace[], Matrix ans) {
    int argc = 0;
    char argv[MAX];

    // Split input
    for (char *token = strtok(input, " "); token;
         token = strtok(NULL, " ")) { // " ,"

        // Get matrix identifier
        if (strlen(token) == 1)
            argv[argc++] = toupper(token[0]) - 'A';
        // Determine if "Mat" prefix is used
        else if (strncmp(token, "Mat", 3) == 0 && strlen(token) == 4)
            argv[argc++] = toupper(token[3]) - 'A';
        // Check for "ans" input
        else if (strcmp(token, "ans") == 0 || strcmp(token, "MatAns") == 0)
            argv[argc++] = ANS;
    }

    // Count parameters
    if (argc == 2) {
        Matrix operands[2]; // determine operands
        operands[0] = (argv[0] == ANS) ? ans : workspace[(unsigned)argv[0]];
        operands[1] = (argv[1] == ANS) ? ans : workspace[(unsigned)argv[1]];

        // Calculate output
        Matrix output = mulMat(operands[0], operands[1]);

        // Check if output is null
        if (isNull(output)) {
            // Check if ans was used while null
            if (isNull(ans) && (argv[0] == ANS || argv[1] == ANS)) {
                printf("Error: perform an operation before attempting to use "
                       "ans.\n");
            } else if (isNull(operands[0]) ||
                       isNull(operands[1])) { // Operand is null
                printf("Error: operand not recognized.\n");
            } else {
                printf("Error: incompatible operands. Try again with "
                       "matricies of "
                       "valid dimensions to perform this operation.\n");
            }
        }

        // Return result of operation
        return output;
    } else {
        printf("Error: incorrect number of parameters. (%d/2)\n", argc);
        return NULL_MATRIX;
    }
}

Matrix scl(char input[], Matrix workspace[], Matrix ans) {
    int argc = 0;
    double argv[MAX];

    // Get scalar from first input
    char *token = strtok(input, " ");
    argv[argc++] = atof(token);
    // Set first input to value of "ans" if defined
    if (strcmp(token, "ans") == 0 || strcmp(token, "MatAns") == 0) {
        if (ans.m == 1 && isSquare(ans)) {
            argv[argc - 1] = ans.data[0][0];
        } else {
            printf("Error: perform an operation before attempting to use "
                   "ans.\n");
            return NULL_MATRIX;
        }
    }

    // Split further input
    for (char *token = strtok(NULL, " "); token;
         token = strtok(NULL, " ")) { // " ,"

        // Get matrix identifier
        if (strlen(token) == 1)
            argv[argc++] = toupper(token[0]) - 'A';
        // Determine if "Mat" prefix is used
        else if (strncmp(token, "Mat", 3) == 0 && strlen(token) == 4)
            argv[argc++] = toupper(token[3]) - 'A';
        // Check for "ans" input
        else if (strcmp(token, "ans") == 0 || strcmp(token, "MatAns") == 0)
            argv[argc++] = ANS;
    }

    // Count parameters
    if (argc == 2) {
        // Determine matrix operand
        Matrix operand = (argv[1] == ANS) ? ans : workspace[(int)argv[1]];

        // Calculate output
        Matrix output = coeffMat(argv[0], operand);

        // Check if output is null
        if (isNull(output)) {
            // Check if ans was used while null
            if (isNull(ans) && (argv[0] == ANS || argv[1] == ANS)) {
                printf("Error: perform an operation before attempting to use "
                       "ans.\n");
            } else if (isNull(operand)) { // Operand is null
                printf("Error: operand not recognized.\n");
            } else {
                printf("Error: could not perform operation.\n");
            }
        }

        // Return result of operation
        return output;
    } else {
        printf("Error: incorrect number of parameters. (%d/2)\n", argc);
        return NULL_MATRIX;
    }
}

Matrix trnsp(char input[], Matrix workspace[], Matrix ans) {
    int argc = 0;
    char argv[MAX];

    // Split input
    for (char *token = strtok(input, " "); token;
         token = strtok(NULL, " ")) { // " ,"

        // Get matrix identifier
        if (strlen(token) == 1)
            argv[argc++] = toupper(token[0]) - 'A';
        // Determine if "Mat" prefix is used
        else if (strncmp(token, "Mat", 3) == 0 && strlen(token) == 4)
            argv[argc++] = toupper(token[3]) - 'A';
        // Check for "ans" input
        else if (strcmp(token, "ans") == 0 || strcmp(token, "MatAns") == 0)
            argv[argc++] = ANS;
    }

    // Count parameters
    if (argc == 1) {
        // Determine operand
        Matrix operand = (argv[0] == ANS) ? ans : workspace[(unsigned)argv[0]];

        // Calculate output
        Matrix output = transpose(operand);

        // Check if output is null
        if (isNull(output)) {
            // Check if ans was used while null
            if (isNull(ans) && (argv[0] == ANS || argv[1] == ANS)) {
                printf("Error: perform an operation before attempting to use "
                       "ans.\n");
            } else if (isNull(operand)) {
                printf("Error: operand not recognized.\n");
            } else {
                printf("Error: could not perform operation.\n");
            }
        }

        // Return result of operation
        return output;
    } else {
        printf("Error: incorrect number of parameters. (%d/1)\n", argc);
        return NULL_MATRIX;
    }
}

Matrix inv(char input[], Matrix workspace[], Matrix ans) {
    int argc = 0;
    char argv[MAX];

    // Split input
    for (char *token = strtok(input, " "); token;
         token = strtok(NULL, " ")) { // " ,"

        // Get matrix identifier
        if (strlen(token) == 1)
            argv[argc++] = toupper(token[0]) - 'A';
        // Determine if "Mat" prefix is used
        else if (strncmp(token, "Mat", 3) == 0 && strlen(token) == 4)
            argv[argc++] = toupper(token[3]) - 'A';
        // Check for "ans" input
        else if (strcmp(token, "ans") == 0 || strcmp(token, "MatAns") == 0)
            argv[argc++] = ANS;
    }

    // Count parameters
    if (argc == 1) {
        // Determine operand
        Matrix operand = (argv[0] == ANS) ? ans : workspace[(unsigned)argv[0]];

        if (isSquare(operand)) {
            // Calculate output
            Matrix output = inverse(operand);

            // Check if output is null
            if (isNull(output)) {
                // Check if ans was used while null
                if (isNull(ans) && (argv[0] == ANS)) {
                    printf("Error: perform an operation before attempting to "
                           "use "
                           "ans.\n");
                } else if (isNull(operand)) {
                    printf("Error: operand not recognized.\n");
                } else {
                    printf("Error: input is not invertible.\n");
                }
            }

            // Return result of operation
            return output;
        } else {
            printf("Error: input is non-square matrix.\n");
            return NULL_MATRIX;
        }
    } else {
        printf("Error: incorrect number of parameters. (%d/q)\n", argc);
        return NULL_MATRIX;
    }
}

Matrix det(char input[], Matrix workspace[], Matrix ans) {
    int argc = 0;
    char argv[MAX];

    // Split input
    for (char *token = strtok(input, " "); token;
         token = strtok(NULL, " ")) { // " ,"

        // Get matrix identifier
        if (strlen(token) == 1)
            argv[argc++] = toupper(token[0]) - 'A';
        // Determine if "Mat" prefix is used
        else if (strncmp(token, "Mat", 3) == 0 && strlen(token) == 4)
            argv[argc++] = toupper(token[3]) - 'A';
        // Check for "ans" input
        else if (strcmp(token, "ans") == 0 || strcmp(token, "MatAns") == 0)
            argv[argc++] = ANS;
    }

    // Count parameters
    if (argc == 1) {
        // Determine operand
        Matrix operand = (argv[0] == ANS) ? ans : workspace[(unsigned)argv[0]];

        if (isSquare(operand)) {
            // Calculate output
            Matrix output = doubleToMat(determinant(operand));

            // Check if output is null
            if (isNull(output)) {
                printf("Error: could not perform operation.\n");
            }

            // Check if input is incorrectly zero
            if ((output.m == 1) && (output.n == 1) &&
                (output.data[0][0] == 0)) {
                // Check if ans was used while null
                if (isNull(ans) && (argv[0] == ANS)) {
                    printf("Error: perform an operation before attempting to "
                           "use ans.\n");
                } else if (isNull(operand)) {
                    printf("Error: operand not recognized.\n");
                } else { // Return output if zero determinant is correct
                    return output;
                }

                // Return null on false zero determinant
                return NULL_MATRIX;
            }

            // Return result of operation
            return output;
        } else {
            printf("Error: input is non-square matrix.\n");
            return NULL_MATRIX;
        }
    } else {
        printf("Error: incorrect number of parameters. (%d/1)\n", argc);
        return NULL_MATRIX;
    }
}

Matrix trc(char input[], Matrix workspace[], Matrix ans) {
    int argc = 0;
    char argv[MAX];

    // Split input
    for (char *token = strtok(input, " "); token;
         token = strtok(NULL, " ")) { // " ,"

        // Get matrix identifier
        if (strlen(token) == 1)
            argv[argc++] = toupper(token[0]) - 'A';
        // Determine if "Mat" prefix is used
        else if (strncmp(token, "Mat", 3) == 0 && strlen(token) == 4)
            argv[argc++] = toupper(token[3]) - 'A';
        // Check for "ans" input
        else if (strcmp(token, "ans") == 0 || strcmp(token, "MatAns") == 0)
            argv[argc++] = ANS;
    }

    // Count parameters
    if (argc == 1) {
        // Determine operand
        Matrix operand = (argv[0] == ANS) ? ans : workspace[(unsigned)argv[0]];

        if (isSquare(operand)) {
            // Calculate output
            Matrix output = doubleToMat(trace(operand));

            // Check if output is null
            if (isNull(output)) {
                printf("Error: could not perform operation.\n");
            }

            // Check if input is incorrectly zero
            if ((output.m == 1) && (output.n == 1) &&
                (output.data[0][0] == 0)) {
                // Check if ans was used while null
                if (isNull(ans) && (argv[0] == ANS)) {
                    printf("Error: perform an operation before attempting to "
                           "use "
                           "ans.\n");
                } else if (isNull(operand)) {
                    printf("Error: operand not recognized.\n");
                } else { // Return output if zero determinant is correct
                    return output;
                }

                // Return null on false zero determinant
                return NULL_MATRIX;
            }

            // Return result of operation
            return output;
        } else {
            printf("Error: input is non-square matrix.\n");
            return NULL_MATRIX;
        }
    } else {
        printf("Error: incorrect number of parameters. (%d/1)\n", argc);
        return NULL_MATRIX;
    }
}
