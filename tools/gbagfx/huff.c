#include <stdbool.h>
#include <string.h>
#include <assert.h>
#include <stdio.h>
#include <stdint.h>
#include "global.h"
#include "huff.h"

static void CreateBinaryTree(uint32_t, uint32_t, uint32_t);

static inline void write_32_le(unsigned char * dest, int * destPos, uint32_t * buff, int * buffPos) {
    dest[*destPos] = *buff;
    dest[*destPos + 1] = *buff >> 8;
    dest[*destPos + 2] = *buff >> 16;
    dest[*destPos + 3] = *buff >> 24;
    *destPos += 4;
    *buff = 0;
    *buffPos = 0;
}

static inline void read_32_le(unsigned char * src, int * srcPos, uint32_t * buff) {
    uint32_t tmp = src[*srcPos];
    tmp |= src[*srcPos + 1] << 8;
    tmp |= src[*srcPos + 2] << 16;
    tmp |= src[*srcPos + 3] << 24;
    *srcPos += 4;
    *buff = tmp;
}

/*
=======================================
MAIN COMPRESSION/DECOMPRESSION ROUTINES
=======================================
*/
struct HuffmanData {
  uint32_t num;
  uint32_t frequency;
  uint32_t bitColumn;
  signed short parent;
  unsigned short parentNodes;
  signed short children[2];
  unsigned short numChildNodes;
  unsigned char bit;
};
uint32_t gDestSize, gHuffTableInitialSize;
int32_t gCurrentHuffTreeIndex, gNext, gHuffOffset;
struct HuffmanData gHuffTable[512];
unsigned char gHuffTree[256][2];

void HuffCompress (unsigned char * src, uint32_t srcSize, unsigned char * dest, int bitDepth)
{
  uint32_t i, j, k;
  uint32_t huffTableIndex = 1 << bitDepth;

  gHuffTableInitialSize = 1 << bitDepth;
  for (i = 0; i < gHuffTableInitialSize * 2; i++) {
    gHuffTable[i] = (struct HuffmanData){0};
    gHuffTable[i].num = i;
  }
  for (i = 0; i < gHuffTableInitialSize; i++)
    for (j = 0; j < srcSize; j++)
      for (k = 0; k < 8 / bitDepth; k++)
        if (i == ((src[j] >> k * 4) & (0xff >> 4 * (1 - bitDepth / 8))))
          gHuffTable[i].frequency++;
  for (i = 0; i < huffTableIndex; i++)
    for (j = 0; j < ARRAY_COUNT(gHuffTable[0].children); j++)
      gHuffTable[i].children[j] = -1;
  uint32_t count = 0;
  while (count < huffTableIndex - 1) {
    int32_t minIndex[2], minFrequency[2];
    for (i = 0; i < ARRAY_COUNT(gHuffTable[0].children); i++, count++) {
      minFrequency[i] = 0x7fffffff;
      for (j = 0; j < huffTableIndex; j++)
        if (gHuffTable[j].frequency  <  minFrequency[i] && !gHuffTable[j].parent) {
          minIndex[i] = j;
          minFrequency[i] = gHuffTable[j].frequency;
          gHuffTable[huffTableIndex].children[i] = j;
        }
      gHuffTable[minIndex[i]].parent = huffTableIndex;
      if (gHuffTable[huffTableIndex].numChildNodes < gHuffTable[minIndex[i]].numChildNodes)
        gHuffTable[huffTableIndex].numChildNodes = gHuffTable[minIndex[i]].numChildNodes;
    }
    if (minFrequency[1] > minFrequency[0]) {
      int16_t child = gHuffTable[huffTableIndex].children[0];
      gHuffTable[huffTableIndex].children[0] = gHuffTable[huffTableIndex].children[1];
      gHuffTable[huffTableIndex].children[1] = child;
    }
    for (i = 0; i < ARRAY_COUNT(gHuffTable[0].children); i++)
      gHuffTable[gHuffTable[huffTableIndex].children[i]].bit = i;
    gHuffTable[huffTableIndex].frequency = minFrequency[0] + minFrequency[1];
    gHuffTable[huffTableIndex].numChildNodes++;
    huffTableIndex++;
  }
  for (i = 0; i < huffTableIndex - 1; i++) {
    gHuffTable[i].parentNodes = 0;
    j = i;
    while (gHuffTable[j].parent) {
      gHuffTable[i].bitColumn >>= 1;
      gHuffTable[i].bitColumn |= gHuffTable[j].bit  <<  31;
      gHuffTable[i].parentNodes++;
      j = gHuffTable[j].parent;
    }
  }
  gCurrentHuffTreeIndex = 0;
  gNext = 1;
  for (i = 0; i <= gHuffTable[huffTableIndex - 1].numChildNodes; i++)
    CreateBinaryTree(huffTableIndex - 1, 1, i);
  if (gCurrentHuffTreeIndex & 0x1)
    gCurrentHuffTreeIndex++;
  gHuffTree[0][0] = gCurrentHuffTreeIndex - 1;

  dest[0] = bitDepth | 0x20;
  dest[1] = srcSize & 0xFF;
  dest[2] = (srcSize & 0xFF00) >> 8;
  dest[3] = (srcSize & 0xFF0000) >> 16;
  gDestSize = 4;
  for (i = 0; i < gCurrentHuffTreeIndex * 2; i++)
    dest[gDestSize++] = ((unsigned char *)gHuffTree)[i];

  uint32_t BitColumnTmp = 0;
  int BitCount = 0;
  for (i = 0; i < srcSize; i++) {
    for (j = 0; j < 8 / bitDepth; j++) {
      unsigned char SrcTmp = (src[i] >> j * 4) & (0xff >> 4 * (1 - bitDepth / 8));
      BitColumnTmp |= gHuffTable[SrcTmp].bitColumn >> BitCount;
      BitCount += gHuffTable[SrcTmp].parentNodes;
      for (k = 0; k < BitCount / 8; k++) {
        dest[gDestSize++] = BitColumnTmp >> 24;
        BitColumnTmp <<= 8;
      }
      BitCount %= 8;
    }
  }
  if (BitCount != 0)
    dest[gDestSize++] = BitColumnTmp >> 24;
  while (gDestSize & 0x3)
    dest[gDestSize++] = 0;
  for (i = 1 + gCurrentHuffTreeIndex * 2 / 4; i < gDestSize / 4; i++)  {
    unsigned char temp = dest[i * 4];
    dest[i * 4] = dest[i * 4 + 3];
    dest[i * 4 + 3] = temp;
    temp = dest[i * 4 + 1];
    dest[i * 4 + 1] = dest[i * 4 + 2];
    dest[i * 4 + 2] = temp;
  }
}

void CreateBinaryTree(uint32_t tableIndex, uint32_t bit, uint32_t nodes) {
  int i;
  if (gHuffTable[tableIndex].frequency == 0 && bit == 0)
    return;
  if (gHuffTable[tableIndex].parentNodes < nodes) {
    for (i = 0; i < ARRAY_COUNT(gHuffTable[0].children); i++)
      if (gHuffTable[tableIndex].children[i] != -1)
        CreateBinaryTree(gHuffTable[tableIndex].children[i], i, nodes);
  }
  else {
    if (gHuffTable[tableIndex].num < gHuffTableInitialSize)
      gHuffTree[gCurrentHuffTreeIndex][bit] = gHuffTable[tableIndex].num;
    else {
      for (i = 0; i < ARRAY_COUNT(gHuffTable[0].children); i++)
        if (gHuffTable[gHuffTable[tableIndex].children[i]].num < gHuffTableInitialSize)
          gHuffTree[gCurrentHuffTreeIndex][bit] |= 0x80 >> i;
      gHuffOffset = gNext - gCurrentHuffTreeIndex - 1;
      gHuffTree[gCurrentHuffTreeIndex][bit] |= gHuffOffset;
      gNext++;;
    }
    if (bit == 1)
      gCurrentHuffTreeIndex++;
  }
}

unsigned char * HuffDecompress(unsigned char * src, int srcSize, int * uncompressedSize_p) {
    if (srcSize < 4)
        goto fail;

    int bitDepth = *src & 15;
    if (bitDepth != 4 && bitDepth != 8)
        goto fail;

    int destSize = (src[3] << 16) | (src[2] << 8) | src[1];

    unsigned char *dest = malloc(destSize);

    if (dest == NULL)
        goto fail;

    int treePos = 5;
    int treeSize = (src[4] + 1) * 2;
    int srcPos = 4 + treeSize;
    int destPos = 0;
    int curValPos = 0;
    uint32_t destTmp = 0;
    uint32_t window;

    for (;;)
    {
        if (srcPos >= srcSize)
            goto fail;
        read_32_le(src, &srcPos, &window);
        for (int i = 0; i < 32; i++) {
            int curBit = (window >> 31) & 1;
            unsigned char treeView = src[treePos];
            bool isLeaf = ((treeView << curBit) & 0x80) != 0;
            treePos &= ~1; // align
            treePos += ((treeView & 0x3F) + 1) * 2 + curBit;
            if (isLeaf) {
                destTmp >>= bitDepth;
                destTmp |= (src[treePos] << (32 - bitDepth));
                curValPos++;
                if (curValPos == 32 / bitDepth) {
                    write_32_le(dest, &destPos, &destTmp, &curValPos);
                    if (destPos == destSize) {
                        *uncompressedSize_p = destSize;
                        return dest;
                    }
                }
                treePos = 5;
            }
            window <<= 1;
        }
    }

fail:
    FATAL_ERROR("Fatal error while decompressing Huff file.\n");
}
