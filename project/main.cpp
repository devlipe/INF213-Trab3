#include "Huffman.h"
#include <fstream>

void geraVetorDeBooleans(int numeroDeBits, MyVec<bool> &vetorBool, ifstream &arquivoComprimido)
{
    char byte;
    int bitsExcedentes = 0;
    int k = 0;
    for (k; k < numeroDeBits; k = k + 8)
    {
        arquivoComprimido.read(&byte, sizeof(char));

        for (int i = 0; i < 8; i++)
        {
            vetorBool.push_back((byte & (1 << i)) != 0); // Checamos se o bit em questao esta ligado ou n
        }
    }
    bitsExcedentes = k - numeroDeBits;

    for (int i = 0; i < bitsExcedentes; i++) // Como podemos ter um numero de bits que nao seja multiplo de 8, temos que remover os excedentes
    {
        vetorBool.pop_back();
    }
}

void descomprimeArquivo(ifstream &arquivoComprimido, ofstream &arquivoDescomprimido)
{
    MyVec<char> vetorChar;
    MyVec<bool> vetorBool;
    int frequencias[256] = {0};
    int numeroDeBits = 0;

    arquivoComprimido.read(reinterpret_cast<char *>(&numeroDeBits), sizeof(int));
    arquivoComprimido.read(reinterpret_cast<char *>(frequencias), 256 * sizeof(int));

    HuffmanTree arvore(frequencias);

    arvore.descomprimir(vetorChar, vetorBool);

    for (int i = 0; i < vetorChar.size(); i++)
    {
        arquivoDescomprimido << vetorChar[i]; // Escrevemos no arquivo de saida o vetor de char
    }
}

void geraFrequenciasEVetorDeChar(ifstream &in, MyVec<char> &vetorChar, int frequencias[256])
{
    char c;
    while (in.read(&c, sizeof(char))) // Lemos ate acabar o arquivo
    {
        frequencias[c]++;
        vetorChar.push_back(c);
    }
}

void gravaArquivoComprimido(const MyVec<bool> &vetorBool, ofstream &arquivoComprimido)
{
    int bitAtual = 0;
    char byte = 0;

    for (int i = 0; i < vetorBool.size(); i++)
    {
        bool bit = vetorBool[i];
        if (bit)
        {
            byte |= (1 << bitAtual);
        }

        bitAtual++;

        if (bitAtual == 8)
        {
            arquivoComprimido.write(&byte, sizeof(char));
            byte = 0;
            bitAtual = 0;
        }
    }
    if (bitAtual) // Se tivermos bits registrados no byte mesmo apos a saida do for, temos que coloca-los no aquivo compactado
    {
        arquivoComprimido.write(&byte, sizeof(char));
        byte = 0;
        bitAtual = 0;
    }
}

void comprimeArquivo(ifstream &arquivoDescomprimido, ofstream &arquivoComprimido)
{
    int frequencias[256] = {0};
    MyVec<char> vetorChar;
    MyVec<bool> vetorBool;

    geraFrequenciasEVetorDeChar(arquivoDescomprimido, vetorChar, frequencias);

    HuffmanTree arvore(frequencias);

    arvore.comprimir(vetorBool, vetorChar);

    int numeroBits = vetorBool.size();

    arquivoComprimido.write(reinterpret_cast<char *>(&numeroBits), sizeof(int));
    arquivoComprimido.write(reinterpret_cast<char *>(frequencias), 256 * sizeof(int)); // Gravamos as frequencias para que seja possivel descompactar o arquivo

    gravaArquivoComprimido(vetorBool, arquivoComprimido);
}

int main(int argc, char const *argv[])
{

    if (argc != 4)
    {
        cerr << "Numero de argumentos invalido. Esperado 4 (exec, metodo, entrada, saida) Encontrado: " << argc << endl;
        exit(1);
    }

    char medotoExec = tolower(*argv[1]); // Metodo de execucao
    string pathEntrada = argv[2];        // Arquvo de entrada
    string pathSaida = argv[3];          // Arquivo de saida

    ifstream arquivoEntrada;
    arquivoEntrada.open(pathEntrada, ios::binary | ios::in);

    if (!arquivoEntrada.is_open())
    {
        cerr << "Arquivo de entrada nao aberto. Nome do arquivo: " << pathEntrada << endl;
        exit(1);
    }

    ofstream arquivoSaida;
    arquivoSaida.open(pathSaida, ios::binary | ios::out);

    if (!arquivoSaida.is_open())
    {
        cerr << "Arquivo de saida nao aberto. Nome do arquivo: " << pathSaida << endl;
        exit(1);
    }

    if (medotoExec == 'c')
    {
        comprimeArquivo(arquivoEntrada, arquivoSaida);
    }
    else if (medotoExec == 'd')
    {
        descomprimeArquivo(arquivoEntrada, arquivoSaida);
    }
    else
    {
        cerr << "Metodo de execucao invalido. Esperado c ou d, encontrado: " << medotoExec << endl;
    }

    arquivoEntrada.close();
    arquivoSaida.close();

    return 0;
}
