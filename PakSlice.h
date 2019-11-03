//
// Created by junk_chuan on 2019/10/31.
//

#ifndef NETWORK_PROJ_PAKSLICE_H
#define NETWORK_PROJ_PAKSLICE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SLICELEN 1000U

char **PakSlice(char * srcdata, unsigned int datasize, unsigned int * piece, unsigned int * left)
{
    *piece = datasize / SLICELEN;
    *left = datasize % SLICELEN;
    if (*left)
        (*piece)++;
    char **SliceData = (char **)malloc(sizeof(char *) * (*piece));
    for (unsigned int i = 0; i < *piece-1; ++i)
    {
        /* code */
        SliceData[i] = (char *)malloc(sizeof(char) * (SLICELEN + 3));
        SliceData[i][0] = char(i+1);
        SliceData[i][1] = char(*piece);

        for (int j = 0; j < 1000; ++j)
        {
            /* code */
            SliceData[i][j+2] = srcdata[i*SLICELEN + j];
        }
        SliceData[i][1002] = '\0';
    }
    SliceData[*piece-1] = (char *)malloc(sizeof(char) * (*left + 2));
    SliceData[*piece-1][0] = char(*piece);
    SliceData[*piece-1][1] = char(*piece)
    for (int i = 0, j = 1000*(*piece-1); i < *left; ++i, ++j)
    {
        /* code */
        SliceData[*piece-1][i+2] = srcdata[j];
    }

    free(srcdata);
    srcdata = NULL;
    return SliceData;
}

#endif //NETWORK_PROJ_PAKSLICE_H
