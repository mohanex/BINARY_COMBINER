#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <dirent.h>
#include <stdio.h>
#include <cstring>
#include <string.h>
#include <vector>

using namespace std;
void concatenateBinaryFiles(const vector<string>& filenames, const string& outputFilename);

int main() {
    string binFiles[45];
    char Bin_output[]="combinedFile.bin";
    remove(Bin_output);
    int i = 0;
    FILE *outputFile, *inputFile;
    string tmp;
    int length;
    char* char_array;
    string bin_extension = ".bin";
    char buffer[1024];
    int bytesRead;
    vector<string> filenames;

    printf("Test1\n\r");
    DIR* di;
    char* ptr1, * ptr2;
    int retn;
    struct dirent* dir;
    di = opendir("."); //specify the directory name
    if (di)
    {
        while ((dir = readdir(di)) != NULL)
        {
            ptr1 = strtok(dir->d_name, ".");
            ptr2 = strtok(NULL, ".");
            if (ptr2 != NULL)
            {
                retn = strcmp(ptr2, "bin");
                if (retn == 0)
                {
                    binFiles[i] = ptr1 + bin_extension;
                    printf("Test3 %d\n\r", i);
                }
            }
            i++;
        }
        closedir(di);
        printf("Test4\n\r");
    }
    outputFile = fopen(Bin_output, "wb");
    if (outputFile == NULL)
    {
        printf("\nErreur : impossible d'ouvrir le fichier de sortie");
        return -3;
    }
    for (int i = 0; i < 32; i++) {
        binFiles[i] = binFiles[i + 4];
        std::cout << binFiles[i] << "\n";
    }
    for (int i = 0; i < 32; i++) {
        tmp = binFiles[i];
        length = tmp.length();
        char_array = new char[length + 1];
        strcpy(char_array, tmp.c_str());

        inputFile = fopen(char_array, "rb");
        if (inputFile == NULL)
        {
            printf("\nErreur : impossible d'ouvrir le fichier d'entrée");
            return -3;
        }
        while ((bytesRead = fread(buffer, 1, sizeof(buffer), inputFile)) > 0) {
            fwrite(buffer, 1, bytesRead, outputFile);
        }
        fwrite(buffer, 1, bytesRead, outputFile);
        fclose(inputFile);
    
    }




    /*for (int i = 3; i < 35; i++) {
        filenames.push_back(binFiles[i]);
    }

    concatenateBinaryFiles(filenames, Bin_output);*/

}
void concatenateBinaryFiles(const vector<string>& filenames, const string& outputFilename) {
    ofstream outputFile(outputFilename, ios::binary | ios::app);

    if (!outputFile.is_open()) {
        cout << "Error opening output file!" << endl;
        return;
    }

    for (const string& filename : filenames) {
        ifstream inputFile(filename, ios::binary);

        if (!inputFile.is_open()) {
            cout << "Could not open input file: " << filename << endl;
            continue;
        }

        outputFile << inputFile.rdbuf();

        inputFile.close();
    }

    outputFile.close();
}


/*printf("chrobodom\n");
for (int i = 3; i < 35; i++)
    std::cout << binFiles[i] << "\n";
printf("chrobodom2\n"); */

/*tmp = binFiles[i];
length = tmp.length();
char_array = new char[length + 1];
strcpy(char_array, tmp.c_str());

inputFile = fopen(char_array, "rb");
if (inputFile == NULL)
{
    printf("\nErreur : impossible d'ouvrir le fichier d'entrée");
    return -3;
}
while ((bytesRead = fread(buffer, 1, sizeof(buffer), inputFile)) > 0) {
    fwrite(buffer, 1, bytesRead, outputFile);
}
fclose(inputFile);*/

