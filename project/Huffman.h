#pragma once

#include "MyQueue.h"
#include "MyPriorityQueue.h"
#include "MyMap.h"


class HuffmanNode
{
public:
    HuffmanNode(const unsigned char &ch_, const int freq_);

    HuffmanNode *left, *right;
    HuffmanNode *parent;

    // Guarada o unsigned char da letra
    unsigned char character;
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
    MyMap<unsigned char, std::string> oMapa;

    //* Funcoes de uso da classe

    //Fucao que cuida de cirar uma arvore de huffman
    void criaHuffmanTree();
    //Funcao que cria um mapa para facilitar a codificacao 
    void criaMapa();
    //Funcao recursiva que gera o mapa (Passamos por copia a string para evitar que fiquem com codigos iguais)
    void criaMapa(std::string code, HuffmanNode *nodo);
    //Funcao que cria a lista de prioridades de ponteiros de HuffmanNodes
    void montaPriorityQueue(MyPriorityQueue<HuffNodePtr> &pq);
    //Funcao que cira a arvore de huffman com base na fila de prioridades
    void montaArvore(MyPriorityQueue<HuffNodePtr> &pq);
    //Funcao que deleta a arvore depois de um determidado nodo
    void deleteHuffmanNodes(HuffmanNode *nodo);
    //Funcao que recupera um codigo do mapa dado um unsigned char
    string recuperaCodigo(const unsigned char c) const;
    //Funcao que grava os bits em um vetor de bool com base em um codigo dado
    void gravaBitsVetorBool(const string &codigo, MyVec<bool> &out) const;
    //Funcao que verifica se o nodo e uma folha
    bool eFolha(HuffmanNode *nodo) const;

    //* Funcoes de debugger
    void imprimeDFS_in(const HuffmanNode *nodo) const;

public:
    //* Construtor e destrutor

    HuffmanTree(int freqs[256]);
    ~HuffmanTree();

    //* Funcoes de uso do programa

    //Funcao que comprime um arquivo myvec e coloca o resultado em um vetor de bool
    void comprimir(MyVec<bool> &out, const MyVec<unsigned char> &in) const;
    //Funcao que dado um vetor de booleanos consegue descomprimir em um vetor de unsigned char
    void descomprimir(MyVec<unsigned char> &out, const MyVec<bool> &in) const;

    //* Funcoes de debugger

    //Imprime a arvore de maneira BFS com a utilizacao de duas filas
    void imprimeBFS() const;
    //Imprime a arvore in ordem de maneira recursiva
    void imprimeDFS_in() const;
    //Funcao que imprime o mapa de codigos gerados
    void imprimeMapa();
};
