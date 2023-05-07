//
// Created by Златослава on 02.05.2023.
//

#ifndef CW_2_STRUCTURES_H
#define CW_2_STRUCTURES_H

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
    int width;
    int height;
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
    unsigned char red;
    unsigned char green;
    unsigned char blue;

} RGB;

typedef struct {
    BMPFHeader file_header;
    BMPInfo info;
    RGB** data;
}BMP;
#pragma pack(pop)

#endif //CW_2_STRUCTURES_H
