#include "Huffman.h"


int main(int argc, char const *argv[])
{
    int freqs[256] = {0};


    freqs['A'] = 15;
    freqs['B'] = 20;
    freqs['a'] = 30;
    freqs['b'] = 27;
    freqs['C'] = 16;
    freqs['c'] = 27;


    HuffmanTree arvore(freqs);
    
    return 0;
}
