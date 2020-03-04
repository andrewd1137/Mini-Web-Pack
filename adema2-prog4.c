//Andrew DeMarco
#include <stdio.h>
#include <string.h>

int readFile();
void bundleFile();

int main() {
    char bufferOne[1024];
    char bufferTwo[1024];

    readFile(bufferOne,bufferTwo);
    bundleFile(bufferOne, bufferTwo);

    return 0;
}

int readFile(char bufferOne[1024], char bufferTwo[1024]){
    char fileOneName[25];
    char fileTwoName[25];

    //checks for the files that the user enters and reads the contents in the files, if they exist.
    printf("Please Enter the First File Name: ");
    scanf("%s", fileOneName);
    FILE* fileOne = fopen(fileOneName, "r");
    if(fileOne == NULL){
        printf("File '%s' was not found, exiting program.\n", fileOneName);
        return 1;
    }
    printf("Please Enter the Second File Name: ");
    scanf("%s", fileTwoName);
    FILE* fileTwo = fopen(fileTwoName, "r");
    if(fileTwo == NULL){
        printf("File '%s' was not found, exiting program.\n", fileTwoName);
        return 1;
    }
    fscanf(fileOne, "%[^\0]", bufferOne);
    fscanf(fileTwo, "%[^\0]", bufferTwo);

    //prints the size of the first and second file, as well as the total size of the two files
    printf("\nFile One Size: %i\n", ftell(fileOne));
    printf("File Two Size: %i\n", ftell(fileTwo));
    printf("Sum of Two Separate Files : %d\n", ftell(fileOne) + ftell(fileTwo));

    fclose(fileOne);
    fclose(fileTwo);
    return 0;
}

void bundleFile(char bufferOne[1024], char bufferTwo[1024]){
    char *addSpace = " ";
    char bufferThree[1024];

    //puts a space at the end of the first file before combining it with file two
    strcat(bufferOne, addSpace);
    strcat(bufferOne, bufferTwo);

    int fileLength = 0;
    fileLength = strlen(bufferOne);

    //checks the new combined file for new lines and tabs and changes them to a single space
    int i=0;
    for(i=0; i<=fileLength; i++){
        if(bufferOne[i] == '\n' || bufferOne[i] == '\t'){
            bufferThree[i] = *addSpace;
        }
        else bufferThree[i] = bufferOne[i];
    }

    //checks the new one line file for consecutive spaces and turns them into one space
    int i2 = 0;
    for(i=0; i<=fileLength; i++){
        if(bufferThree[i] == ' ' && bufferThree[i+1] == ' '){
            //Do Nothing
        }
        else{
            bufferThree[i2] = bufferThree[i];
            i2++;
        }
    }
    //writes the final file, which is all one line with single spaces into a new file, and then prints the size
    FILE* bundledFile = fopen("bundle.js", "w");
    if(bundledFile == NULL){
        printf("File was not found. Exiting Program.\n");
    }
    fprintf(bundledFile, "%s", bufferThree);
    printf("Bundled File Size: %i\n\n", ftell(bundledFile));
    printf("The Bundled File has Been Successfully Saved.\n");
    fclose(bundledFile);
}
