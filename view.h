

#ifndef VIEW_H
#define VIEW_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define FRAME_HEADER_SIZE 10

void read_frame(FILE *mp3, int frame_size, char *frame_id);
void view(int *read_bytes, int *tag_size, FILE *fptr);
int get_frame_size(unsigned char *size_bytes);

#endif // VIEW_H
