#include<stdio.h>
#include<string.h>
#include "view.h"


void read_frame(FILE *mp3, int frame_size, char *frame_id)
{
   if(frame_size <= 0)
   {
      printf("NO FRAME DATA\n");
      return;
   }
   
   char *buffer = malloc(frame_size + 1);
   if (!buffer) 
   {
       printf("Memory allocation failed.\n");
       return;
   }
   fread(buffer, 1, frame_size, mp3);
   buffer[frame_size] = '\0';

   if (strcmp(frame_id, "TXXX") == 0)
   {
      // TXXX has a description field, find "year" description
      char *description = buffer + 1; // After encoding byte
      char *value = description + strlen(description) + 1; // Value follows description

      if (strcmp(description, "year") == 0) 
      {
          printf("Year: %s\n", value);
      }
  } 
  else 
  {
      printf("%s: %s\n", frame_id, buffer + 1);
  }
}

void view(int *read_bytes, int *tag_size, FILE *fptr)
{
   printf("---------------------------------SELECTED VIEW DETAILS---------------------------------\n");
   printf("---------------------------------------------------------------------------------------\n");
   printf("                       %s\n", "MP3 TAG READER AND EDITOR FOR ID3v2");
   printf("---------------------------------------------------------------------------------------\n");
   while(*read_bytes < *tag_size)
   {
      char frame_name[5];
      char FREAME_HEADER[FRAME_HEADER_SIZE];

      fread(FREAME_HEADER, 1,  FRAME_HEADER_SIZE, fptr);
      memcpy(frame_name, FREAME_HEADER, 4);
      frame_name[4] = '\0';

      int frame_size  = get_frame_size((unsigned char *)FREAME_HEADER + 4);   //to skip the title part

      if(frame_name[0] == '\0')
      {
         break;
      }

      if (frame_size <= 0) {  // Ensure frame size is valid
         break;
     }

      if(strcmp(frame_name, "TPE1") == 0 || strcmp(frame_name, "TIT2") == 0 || strcmp(frame_name, "TALB") == 0 || strcmp(frame_name, "TXXX") == 0 || strcmp(frame_name, "TCON") == 0 || strcmp(frame_name, "TCOM") == 0)
      {
          read_frame(fptr, frame_size, frame_name); 
      }
      else
      {
         fseek(fptr, frame_size, SEEK_CUR);//skip un needed frames
      }
      
      *read_bytes += (FRAME_HEADER_SIZE + frame_size);
   }
   printf("---------------------------------------------------------------------------------------\n");
   printf("---------------------------------DETAILS DISPLAYED SUCCESSFULLY------------------------\n");

  // fclose(fptr);
   return;
} 

int get_frame_size(unsigned char *size_bytes) {
   return (size_bytes[0] << 21 | size_bytes[1] << 14 | size_bytes[2] << 7 | size_bytes[3]);
}
