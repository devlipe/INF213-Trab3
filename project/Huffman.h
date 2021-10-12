#pragma once

#include "MyQueue.h"
#include "MyPriorityQueue.h"
#include "MyMap.h"

class HuffmanNode
{
public:
    HuffmanNode(const char &ch_, const int freq_);

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

struct HuffNodePtr
{
    //*Atributos da struct
    HuffmanNode *huffPtr;
    int freq;

    //*Construtor da struct
    HuffNodePtr(HuffmanNode *ptr, int frequency);
    HuffNodePtr() : huffPtr(NULL){};

    //* Operadores de uso da struct
    bool operator>(const HuffNodePtr &other);
    bool operator<(const HuffNodePtr &other);
};

class HuffmanTree
{
private:
    HuffmanNode *root;
    int size;
    int *freqs;
    MyMap<char, std::string> oMapa;

    //* Funcoes de uso da classe
    void criaHuffmanTree();
    void criaMapa();
    void criaMapa(std::string code, HuffmanNode *nodo);
    void montaPriorityQueue(MyPriorityQueue<HuffNodePtr> &pq);
    void montaArvore(MyPriorityQueue<HuffNodePtr> &pq);
    void deleteHuffmanNodes(HuffmanNode *nodo);

    //* Funcoes de debugger
    void imprimeDFS_in(const HuffmanNode *nodo) const;

public:
    //* Construtor e destrutor

    HuffmanTree(int freqs[256]);
    ~HuffmanTree();

    //* Funcoes de uso do programa
    //TODO: Implementar as funcoes abaixo para finalizar a classe
    //Funcao que comprime um arquivo myvec e coloca o resultado em um vetor de bool
    void comprimir(MyVec<bool> &out, const MyVec<char>&in) const;
    //Funcao que dado um vetor de booleanos consegue descomprimir em um vetor de char
    void descomprimir(MyVec<char> &out, const MyVec<bool>&in) const;

    //* Funcoes de debugger
    //Imprime a arvore de maneira BFS com a utilizacao de duas filas
    void imprimeBFS() const;
    //Imprime a arvore in ordem de maneira recursiva
    void imprimeDFS_in() const;
};
