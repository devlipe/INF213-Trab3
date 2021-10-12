#include "Huffman.h"


int main(int argc, char const *argv[])
{
    int freqs[256] = {0};


    freqs['A'] = 30;
    freqs['B'] = 30;
    freqs['C'] = 15;
    freqs['D'] = 20;
    freqs['E'] = 30;
    freqs['F'] = 27;
    freqs['a'] = 30;

    HuffmanTree arvore(freqs);
    
    return 0;
}
