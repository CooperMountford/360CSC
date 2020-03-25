#include <stdio.h>
#include <stdlib.h>

const int BLOCK_SIZE = 512;
const int NUM_BLOCKS = 4096;

// from tutorial video
void writeBlock(FILE* disk, int block, char* data) {
    fseek(disk, block * BLOCK_SIZE, SEEK_SET);
    fwrite(data, BLOCK_SIZE, 1, disk);
}
// from tutorial video
void readBlock(FILE* disk, int block, char* buff) {
    fseek(disk, block * BLOCK_SIZE, SEEK_SET);
    fread(buff, BLOCK_SIZE, 1, disk);
}

void InitLLFS(FILE* disk) {


}