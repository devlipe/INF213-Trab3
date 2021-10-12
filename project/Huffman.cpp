#include "Huffman.h"

//! Implementacao Huffman Node

HuffmanNode::HuffmanNode(const char &ch_, const int freq_) : character(ch_), frequency(freq_), left(NULL), right(NULL), parent(NULL){};

HuffmanNode::HuffmanNode()
{
    left = right = parent = NULL;
    character = 0;
    frequency = 0;
}

std::ostream &operator<<(std::ostream &out, const HuffmanNode &node)
{
    out << " '" << node.character << "':" << node.frequency << " ";
    return out;
}

bool HuffmanNode::operator<(const HuffmanNode &other)
{
    if (this->frequency < other.frequency)
    {
        return true;
    }
    else if (this->frequency = other.frequency && this->character < other.character)
    {
        return true;
    }

    return false;
}

bool HuffmanNode::operator>(const HuffmanNode &other)
{
    if (this->frequency > other.frequency)
    {
        return true;
    }
    else if (this->frequency == other.frequency && this->character > other.character)
    {
        return true;
    }
    return false;
}

//! Implementacao Huffman Tree

HuffmanTree::HuffmanTree(int freqs_[256])
{
    freqs = freqs_;

    criaHuffmanTree();
}

void HuffmanTree::criaHuffmanTree()
{
    MyPriorityQueue<HuffmanNode> PQ;

    montaPriorityQueue(PQ); // Passamos a lista por referencia para que ela seja alterada dentro da funcao
    
}

void HuffmanTree::montaPriorityQueue(MyPriorityQueue<HuffmanNode> &pq)
{
    for (int i = 0; i < 256; i++)
    {
        if (freqs[i] > 0)
        {
            HuffmanNode *nodoPtr = new HuffmanNode(i, -freqs[i]); // Como a lista deve ser crescente, as frequencias sao negativas
            pq.push(*nodoPtr);
        }
    }
}

HuffmanTree::~HuffmanTree()
{
    deleteHuffmanNodes(root);
}

void HuffmanTree::deleteHuffmanNodes(HuffmanNode *nodo)
{
    if (!nodo)
    {
        return;
    }
    deleteHuffmanNodes(nodo->left);
    deleteHuffmanNodes(nodo->right);
    delete root;
}

void HuffmanTree::checkTree() const
{
    checkTree(root);
}

void HuffmanTree::checkTree(const HuffmanNode *nodo) const
{
    if (!nodo)
    {
        return;
    }
    if (nodo == this->root)
    {
        assert(nodo->parent == NULL);
    }
    if (nodo->left) // se tivermos nodo da esquerda
    {
        if (nodo->left->frequency > nodo->frequency) // Se o da esquerda for maior, teremos um erro e vamos mostrar os envolvidos
        {
            cerr << nodo->left << " " << nodo << endl;
        }
        assert(nodo->left->frequency <= nodo->frequency); // Podemos ter frequencias iguais, mas os char serao diferentes
        assert(nodo->left->parent == nodo);
        checkTree(nodo->left);
    }
    if (nodo->right)
    {
        if (nodo->right->frequency < nodo->frequency)
        {
            cerr << nodo->right << " " << nodo << endl;
        }
        assert(nodo->right->frequency >= nodo->frequency); // Podemos ter frequencias iguais, mas os char serao diferentes
        assert(nodo->right->parent == nodo);
        checkTree(nodo->left);
    }
}

void HuffmanTree::imprimeBFS() const
{
    MyQueue<HuffmanNode *> q;
    MyQueue<HuffmanNode *> u;
    if (!root)
    {
        return;
    }

    u.push(root);

    int nivel = 0;
    while (!u.empty())
    {
        q = u;
        u = MyQueue<HuffmanNode *>();

        cout << "Nivel " << nivel++ << " : "; // Imprime nivel a nivel
        while (!q.empty())
        {
            HuffmanNode *p = q.front();
            q.pop();
            cout << p << " "; // temos a saida de um nodo com sobreescrita

            //Enquanto printamos um nodo, colocamos seus filhos em outra lista
            if (p->left)
            {
                u.push(p->left);
            }
            if (p->right)
            {
                u.push(p->right);
            }
        }
        cout << endl;
    }
}

void HuffmanTree::imprimeDFS_in() const
{
    imprimeDFS_in(root);
}

void HuffmanTree::imprimeDFS_in(const HuffmanNode *nodo) const
{
    if (!nodo)
    {
        return;
    }
    imprimeDFS_in(nodo->left);
    cout << nodo;
    imprimeDFS_in(nodo->right);
}