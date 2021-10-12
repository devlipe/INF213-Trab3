#pragma once

#include "MyQueue.h"
#include "MyPriorityQueue.h"

class HuffmanNode
{
public:
    HuffmanNode(const char &ch_, const int freq_);
    HuffmanNode(); // Construtor default

    HuffmanNode *left, *right;
    HuffmanNode *parent;

    // Guarada o char da letra
    char character; 
    // Guarda o numero de vezer que o character aparece
    int frequency;

    //*Funcoes de uso do programa
    //Compara se um nodo deve ficar a frente de outro
    bool operator>(const HuffmanNode &other);
    //Compara se um nodo deve ficar a tras de outro
    bool operator<(const HuffmanNode &other); 

    //* Funcoes de debugger do programa
    // Funcao que habilita modificar a saida de um nodo
    friend std::ostream &operator<<(
        std::ostream &,
        const HuffmanNode &); 
};

class HuffmanTree
{
private:
    HuffmanNode *root;
    int size;
    int *freqs;

    //* Funcoes de uso da classe
    void criaHuffmanTree();
    void montaPriorityQueue(MyPriorityQueue<HuffmanNode> &);

    //* Funcoes de debugger
    void imprimeDFS_in(const HuffmanNode *nodo) const;
    void checkTree(const HuffmanNode *nodo) const;

public:
    //* Construtor e destrutor

    HuffmanTree(int freqs[256]);
    ~HuffmanTree();

    //* Funcoes de uso do programa
    void deleteHuffmanNodes(HuffmanNode *nodo);

    //* Funcoes de debugger
    //Imprime a arvore de maneira BFS com a utilizacao de duas filas
    void imprimeBFS() const;
    //Imprime a arvore in ordem de maneira recursiva
    void imprimeDFS_in() const;
    //Funcao que verifica a integridade da arvore que tuddo esta de acordo
    void checkTree() const;
};
