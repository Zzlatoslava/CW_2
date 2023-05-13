//
// Created by Златослава on 02.05.2023.
//

#ifndef CW_2_STRUCTURES_H
#define CW_2_STRUCTURES_H

;
#pragma pack(push, 1)
typedef struct {
    unsigned char type[2];
    unsigned int size;
    unsigned short reserved1 ;
    unsigned short reserved2 ;
    unsigned int bits;
} BMPFHeader;

typedef struct {
    unsigned int header_size;
    unsigned int width;
    unsigned int height;
    unsigned short planes;
    unsigned short bit_count;
    unsigned int compression;
    unsigned int image_size;
    int Xpels_per_meter;
    int Ypels_per_meter;
    unsigned int colors_used;
    unsigned int colors_important;
} BMPInfo;

typedef struct {
    unsigned char blue;
    unsigned char green;
    unsigned char red;

} RGB;

typedef struct {
    BMPFHeader* file_header;
    BMPInfo *info;
    RGB* data;
}BMP;

typedef struct {
    BMPFHeader* header ;
    BMPInfo* info ;
    RGB* pixels;
    unsigned int w ;
    unsigned int h;
}Image;
#pragma pack(pop)

#endif //CW_2_STRUCTURES_H
