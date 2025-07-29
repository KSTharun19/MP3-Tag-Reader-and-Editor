#include "edit.h"

void edit_title_details(char *filename, char *tag, char *new_content)
{
   FILE *fptr = fopen(filename, "r+b");

   if(fptr == NULL)
   {
    printf("FIALED TO OPEN SURCE FILE...\n");
    return;
   }

   char header[10];
   fread(header, 1, 10, fptr);

   if(strncmp(header, "ID3", 3) != 0)
   {
    printf("NO ID3 TAG FOUND\n");
    fclose(fptr);
    return;
   }
   
   int header_size = (header[6] << 21 | header[7] << 14 | header[8] << 7 | header[9]);

   while (ftell(fptr) < header_size)
   {
      char tag_name[5] = {0};
      fread(tag_name, 1, 4, fptr);

      if (strlen(tag_name) == 0)  // If tag name is empty, break
         break;

      char size_bytes[4];
      fread(size_bytes, 1, 4, fptr);

      int tag_size = (size_bytes[0] << 21 | size_bytes[1] << 14 | size_bytes[2] << 7 | size_bytes[3]);

      fseek(fptr, 2, SEEK_CUR);  // Skip flags

      if(strcmp(tag_name, tag) == 0)
      {
        printf("found tag: %s, Updating the new content...\n", tag);

        if (tag_size < 1) 
        {
        printf("Invalid tag size detected. Stopping...\n");
        fclose(fptr);
        return;
        }

        fputc(0, fptr);

        int write_size = strlen(new_content);
        if(write_size > tag_size - 1)
        {
         write_size = tag_size - 1; // Prevent buffer overflow
        }

        fwrite(new_content, 1, write_size, fptr);

         printf("tag: %s is updated to %s\n", tag_name, new_content);
         break;
      }
      else
      {
        fseek(fptr, tag_size, SEEK_CUR);  //skip to next frame
      }
   }
   
}
