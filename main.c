#include <stdio.h>
#include <string.h>
#include"edit.h"
#include "view.h"



int main(int argc, char *argv[]) 
{
    if (argc < 3) {
        printf("------------------------------------------------------------------------------------\n");
        printf("ERROR: ./a.out : INVALID ARGUMENTS\n");
        printf("USAGE:\n");
        printf("To view please pass like: ./a.out -v mp3filename\n");
        printf("To edit please pass like: ./a.out -e -t/-a/-A/-y/-m/-c changing text mp3filename\n");
        printf("To get help please pass like: ./a.out --help\n");
        printf("------------------------------------------------------------------------------------\n");
        return 1;
    }

    else if (strcmp(argv[1], "-v") == 0 && strstr(argv[2], ".mp3") != NULL) 
    {
        FILE *fptr = fopen(argv[2], "rb");

        if (fptr == NULL) 
        {
            printf("Failed to open the MP3 file\n");
            return 1;
        }

        char id[10];
        fread(id, 1, 10, fptr);

        if (strncmp(id, "ID3", 3) == 0) 
        {
            printf("ID3 tag found...\n");
            char major = id[3];
            char minor = id[4];

            if (major == 3 && minor == 0) 
            {
                printf("Version ID verified\n");
                int tag_size = get_frame_size((unsigned char *)id + 6);
                int read_bytes = 0;
                view(&read_bytes, &tag_size, fptr);
            } else 
            {
                printf("The file does not belong to ID3v2.3 version\n");
            }
        } else 
        {
            printf("No ID3 tag found in the file.\n");
        }

        fclose(fptr);
    } else if(strcmp(argv[1], "-e") == 0 && argv[2] != NULL  && argv[3] != NULL && strstr(argv[4], ".mp3") != NULL)
    {

        printf("---------------------------------SELECTED EDIT DETAILS---------------------------------\n");
        printf("--------SELECTED EDIT OPTION---------\n");
        char *tag = NULL;
        if(strcmp(argv[2], "-t") == 0)
        {
            printf("--------CHANGE THE TITLE---------\n");
            tag = "TIT2";
        }
        else if(strcmp(argv[2], "-a") == 0)
        {
            printf("--------CHANGE THE ARTIST---------\n");
            tag = "TPE1";
        }
        else if(strcmp(argv[2], "-A") == 0)
        {
            printf("--------CHANGE THE ALBUM---------\n");
            tag = "TALB"; 
        }
        else if(strcmp(argv[2], "-y") == 0)
        {
            printf("--------CHANGE THE YEAR---------\n");
            tag = "TYER";
        }
        else if(strcmp(argv[2], "-m") == 0)
        {
            printf("--------CHANGE THE CONTENT---------\n");
            tag = "TCOM";
        }
        else                                   //if(strcmp(argv[2], "-c") == 0)
        {
            printf("--------CHNAGE THE COMMENT---------\n");
            tag = "TCON";
        }
        
        edit_title_details(argv[4], tag, argv[3]);
    }
    else
    {
        printf("---------------------------------HLEP MENU------------------------------------------\n");
        printf("1. -v: TO VIEW MP3 FILE CONTENTS\n");
        printf("2. -2: TO EDIT MP3 FILE CONTENTS\n");
        printf("       2.1. -t -> TO EDIT SONG DETAILS\n");
        printf("       2.2. -a -> TO EDIT ARTIST DETAILS\n");
        printf("       2.3. -A -> TO EDIT ALBUL DETAILS\n");
        printf("       2.4. -y -> TO EDIT YEAR DETAILS\n");
        printf("       2.5. -m -> TO EDIT CONTENT DETAILS\n");
        printf("       2.6. -c -> TO EDIT COMMENT DETAILS\n");
        printf("------------------------------------------------------------------------------------\n");
    }

    return 0;
}
