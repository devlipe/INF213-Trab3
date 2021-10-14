#include "Huffman.h"

//! Implementacao Huffman Node

HuffmanNode::HuffmanNode(const char &ch_, const int freq_) : character(ch_), frequency(freq_), left(NULL), right(NULL), parent(NULL){};

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
	if (this->frequency = other.frequency && this->character < other.character)
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
	if (this->frequency == other.frequency && this->character > other.character)
	{
		return true;
	}
	return false;
}

//! Implementacao Huffman Node Ptr

HuffNodePtr::HuffNodePtr(HuffmanNode *ptr, int frequency)
{
	huffPtr = ptr;
	freq = -frequency; // As frequencias sao negativas pois estamos ordenando ao contrario os structs
}

bool HuffNodePtr::operator<(const HuffNodePtr &other)
{
	if (this->freq < other.freq)
	{
		return true;
	}
	if (this->freq == other.freq && this->huffPtr->character < other.huffPtr->character)
	{
		return true;
	}
	return false;
}

bool HuffNodePtr::operator>(const HuffNodePtr &other)
{
	if (this->freq > other.freq)
	{
		return true;
	}
	if (this->freq == other.freq && this->huffPtr->character > other.huffPtr->character)
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
	MyPriorityQueue<HuffNodePtr> PQ;
	montaPriorityQueue(PQ); // Passamos a lista por referencia para que ela seja alterada dentro da funcao
	montaArvore(PQ);
	criaMapa();
}

void HuffmanTree::montaPriorityQueue(MyPriorityQueue<HuffNodePtr> &pq)
{
	for (int i = 0; i < 256; i++)
	{
		if (freqs[i] > 0)
		{
			HuffNodePtr nodePtr(new HuffmanNode(i, freqs[i]), freqs[i]);
			pq.push(nodePtr);
		}
	}
}

void HuffmanTree::montaArvore(MyPriorityQueue<HuffNodePtr> &pq)
{
	while (pq.size() > 1)
	{
		HuffNodePtr smallerNode = pq.top();
		pq.pop();
		HuffNodePtr greaterNode = pq.top();
		pq.pop();

		HuffmanNode *father = new HuffmanNode(0, smallerNode.huffPtr->frequency + greaterNode.huffPtr->frequency); // Criamos um novo nodo com char = 0

		father->left = smallerNode.huffPtr;	 // Colocamos o menor filho na esquerda
		father->right = greaterNode.huffPtr; // Colocamos o maior filho na direita

		// Atribuimos os pais
		smallerNode.huffPtr->parent = father;
		greaterNode.huffPtr->parent = father;

		HuffNodePtr auxPtr(father, father->frequency);
		pq.push(auxPtr);
	}
	if (!pq.size()) // Se estivermos compactando um arquivo fazio, a PQ tera size 0
	{
		root = NULL;
	}
	else
	{
		root = pq.top().huffPtr; // a root sera o nodo que sobrou
	}
}

void HuffmanTree::criaMapa()
{
	if (!root) // Se nao tivermos uma arvore, nao precisamos criar um mapa
	{
		return;
	}

	std::string codigo = "";
	criaMapa(codigo, root);
}

void HuffmanTree::criaMapa(std::string code, HuffmanNode *nodo)
{
	if (nodo && eFolha(nodo)) /// caso o nodo seja null (arvore vazia)
	{
		oMapa[nodo->character] = code;
	}
	if (nodo->left)
	{
		criaMapa(code + "0", nodo->left); // Adicionamos 0 ser for a esquerda
	}
	if (nodo->right)
	{
		criaMapa(code + "1", nodo->right);
	}
}

bool HuffmanTree::eFolha(HuffmanNode *nodo) const
{
	return (!nodo->left && !nodo->right);
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
	delete nodo;
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
			cout << *p << " "; // temos a saida de um nodo com sobreescrita

			// Enquanto printamos um nodo, colocamos seus filhos em outra lista
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
	cout << *nodo;
	imprimeDFS_in(nodo->right);
}

void HuffmanTree::comprimir(MyVec<bool> &out, const MyVec<char> &in) const
{
	for (int i = 0; i < in.size(); i++)
	{
		char c = in[i]; // Pegamos um caracter do arquivo
		string codigo = recuperaCodigo(c);

		gravaBitsVetorBool(codigo, out);
	}
}

string HuffmanTree::recuperaCodigo(const char c) const
{
	typename MyMap<char, std::string>::iterator it = oMapa.find(c);
	return (*it).second; // Descobrimos o codigo relacionado com um caracter
}

void HuffmanTree::gravaBitsVetorBool(const string &codigo, MyVec<bool> &out) const
{
	for (int j = 0; j < codigo.length(); j++) // Como o tamanho do codigo e variavel usamos um for pelo tamanho dele
	{
		char bit = codigo[j];

		out.push_back((bit == '1'));
	}
}

void HuffmanTree::descomprimir(MyVec<char> &out, const MyVec<bool> &in) const
{
	HuffmanNode *andarilho = root;

	if (andarilho && eFolha(andarilho)) // Caso tivermos um arquivo com somente um char repetido varias vezes, temos que tratar esse caso
	{									// Tratamos tambem o caso da arvore vazia, que se for null, nao entrara no if
		for (int i = 0; i < andarilho->frequency; i++)
		{
			out.push_back(andarilho->character);
		}
		return;
	}

	for (int i = 0; i < in.size(); i++) // se a arvore for vazia, o vetor in tambem sera vazio, logo o for nao ocorrera
	{
		bool boolean = in[i];

		if (boolean)
		{
			andarilho = andarilho->right;
		}
		else
		{
			andarilho = andarilho->left;
		}
		if (eFolha(andarilho))
		{
			out.push_back(andarilho->character);
			andarilho = root;
		}
	}
}

void HuffmanTree::imprimeMapa()
{
	typename MyMap<char, string>::iterator it = oMapa.begin();

	for (it; it != oMapa.end(); it++)
	{
		cout << (*it).first << " " << (*it).second << std::endl;
	}
}