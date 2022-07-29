#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

//8-bit unsigned type that will hold a byte. 
//can also be defined as "unsigned char bytes[]"
typedef uint8_t BYTE;
int main(int argc, char *argv[])
{
    //Check command-line argument
    if (argc != 2)
    {
        printf("the command-line argument is, ./recover card.raw\n");
        return 1;
    }
    //open the memory card
    FILE *source = fopen(argv[1], "r");
    if (source == NULL)
    {
        printf("source is null");
        return 1;
    }

    //counter - to know how many jpeg has been created so far
    int i = 0;
    // create an empty string for filename
    char filename[8];
    //assign zero to variable jpegfound 
    int jpegfound = 0;
    //create a pointer to a file output where we will write our jpeg to
    FILE *output;
    //create an array of type byte and size 512
    BYTE buffer[512];
    //read 512 bytes into a buffer
    while (fread(&buffer, sizeof(BYTE), 512, source))
    {
        // Check first four byte if it is a jpeg
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            //first jpeg
            if (i == 0)
            {
               //reassign one to variable jpegfound since the first jpeg has been found
                jpegfound = 1;
            }
            //already found a jpeg? yes
            else
            {
                //close the previous jpeg  
                fclose(output);
            }
            //(since the if else condition are mutually exclusive but would contain similar fxn on lines 53,54,55...
            //...in d interest of best design write the common fxns outside of the condition)
            // name file
            sprintf(filename, "%03i.jpg", i);
            // open file 
            output = fopen(filename, "w");
            // increment count
            i++;
        }
        //not a jpeg header
        //but already found a jpeg, continue writing to the open jpeg file
        if (jpegfound == 1)
        {
            fwrite(&buffer, sizeof(BYTE), 512, output);
        }
    }
    fclose(source);
    fclose(output);
    printf("DONE\n");
    //TERMINATE PROGRAM
    return 0;
}
