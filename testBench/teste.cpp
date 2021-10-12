#include <iostream>

int main(int argc, char const *argv[])
{
    char a = 0;
    char b = ' ';
    char c = 0;
    char d = '\0';

    std::cout << a << "-" << b << "-" << c << "-" << d << std::endl;

    std::cout << (a == b) << " " << (a == c) << (a == c) << std::endl;

    char s = 0;
    for (int i = 0; i < 256; i++)
    {

        std::cout << i << "|" << s << "|" << std::endl;
        s = s + 1;
    }

    return 0;
}

// while (PQ.size() > 0)
// {
//     cout << *PQ.top().huffPtr;
//     PQ.pop();
// }

//void HuffmanTree::checkTree(const HuffmanNode *nodo) const
// {
//     if (!nodo)
//     {
//         return;
//     }
//     if (nodo == this->root)
//     {
//         assert(nodo->parent == NULL);
//     }
//     if (nodo->left) // se tivermos nodo da esquerda
//     {
//         if (nodo->left->frequency > nodo->frequency) // Se o da esquerda for maior, teremos um erro e vamos mostrar os envolvidos
//         {
//             cerr << nodo->left << " " << nodo << endl;
//         }
//         assert(nodo->left->frequency <= nodo->frequency); // Podemos ter frequencias iguais, mas os char serao diferentes
//         assert(nodo->left->parent == nodo);
//         checkTree(nodo->left);
//     }
//     if (nodo->right)
//     {
//         if (nodo->right->frequency < nodo->frequency)
//         {
//             cerr << nodo->right << " " << nodo << endl;
//         }
//         assert(nodo->right->frequency >= nodo->frequency); // Podemos ter frequencias iguais, mas os char serao diferentes
//         assert(nodo->right->parent == nodo);
//         checkTree(nodo->left);
//     }
// }

//Funcao que verifica a integridade da arvore que tuddo esta de acordo
// void checkTree() const;

// void HuffmanTree::checkTree() const
// {
//     checkTree(root);
// }



//  typename MyMap<char,string>::iterator it = oMapa.begin();

    // for ( it ; it != oMapa.end(); it++)
    // {
    //     cout << (*it).first << " " << (*it).second << std::endl; 
    // }