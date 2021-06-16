#include <iostream>
#include<fstream>
#include<vector>
using namespace std;

/////////////////////////////////////////        NODE         /////////////////////////////////////
template< class T>
class NODE
{
public:
	T data;
	NODE<T>* left;
	NODE<T>* right;

	NODE()
	{
		data = 0;
		left = nullptr;  right = nullptr;
	}
	NODE(T val, NODE<T>* aptr, NODE<T>* bptr)
	{
		data = val;
		left = aptr;
		right = bptr;
	}
	bool operator==(const NODE<T>& a)
	{
		return(data == a.data);
	}
	bool operator>=(const NODE<T>& a)
	{
		return(data >= a.data);
	}
	bool operator<=(const NODE<T>& a)
	{
		return(data <= a.data);
	}
	bool operator>(const NODE<T>& a)
	{
		return(data > a.data);
	}
	bool operator<(const NODE<T>& a)
	{
		return(data < a.data);
	}
	friend ostream& operator <<(ostream& out, const NODE& obj)
	{
		out << obj.data;
		return out;
	}
};
/////////////////////////////////////////        BST         /////////////////////////////////////

template<class  T>
class BST
{
	NODE<T>* root;
public:
	BST()
	{
		root = nullptr;
	}
	BST(T data)
	{
		root = new NODE<T>;
		root->data = data;
		root->left = root->right = nullptr;
	}
	~BST()
	{
		destructor(root);
	}
	void destructor(NODE<T>* curr)
	{
		if (curr)
		{
			destructor(curr->left);
			destructor(curr->right);
			delete curr;
		}
	}
	bool Search(T key)
	{
		NODE<T>* temp = Search(root, key);
		if (temp == nullptr)
		{
			cout << "Element is not found" << endl; return false;
		}
		else
		{
			cout << "Element is found" << endl; return true;
		}
	}
	NODE<T>* Search(NODE<T>* curr, T key)
	{
		if (curr == nullptr || curr->data == key)
			return curr;

		if (curr->data < key)
			return Search(curr->right, key);
		else
			return Search(curr->left, key);

	}
	void Insert(T data)
	{
		NODE<T>* temp = Insert(root, data);
		if (root == nullptr)
			root = temp;
	}
	NODE<T>* Insert(NODE<T>* curr, T key)
	{
		if (curr == nullptr)
			return new NODE<T>(key, nullptr, nullptr);
		if (curr->data < key)
			curr->right = Insert(curr->right, key);
		else if (curr->data > key)
			curr->left = Insert(curr->left, key);

		return curr;
	}
};
/////////////////////////////////////////        MIN HEAP        ///////////////////////////////////////  

template <class T>
void swap(T* x, T* y);

template <class T>
class MinHeap
{
	T* arr;
	int capacity;
	int heap_size;
public:
	int size()
	{
		return heap_size;
	}
	MinHeap(int cap)
	{
		heap_size = 0;
		capacity = cap;
		arr = new T[cap];
	}
	void insert(T k)
	{
		heap_size++;
		int i = heap_size - 1;
		arr[i] = k;
		while (i != 0 && *arr[(i - 1) / 2] > *arr[i])
		{
			swap(arr[i], arr[(i - 1) / 2]);
			i = (i - 1) / 2;
		}
	}
	T extractMin()
	{
		T root = arr[0];
		arr[0] = arr[heap_size - 1];
		heap_size--;
		MinHeapify(0);
		return root;
	}
	void MinHeapify(int i)
	{
		int l = 2 * i + 1;
		int r = 2 * i + 2;
		int smallest = i;
		if (l < heap_size && *arr[l] < *arr[i])
			smallest = l;
		if (r < heap_size && *arr[r] < *arr[smallest])
			smallest = r;
		if (smallest != i)
		{
			swap(arr[i], arr[smallest]);
			MinHeapify(smallest);
		}
	}
};
template <class T>
void swap(T* x, T* y)
{
	T temp = *x;
	*x = *y;
	*y = temp;
}
/////////////////////////////////////////        ELEMENT        ///////////////////////////////////////  
class ELEMENT
{
public:
	char element;
	int freq;
	ELEMENT()
	{
		element = 0; freq = 0;
	}
	ELEMENT(char c) { element = c, freq = 0; }
	void inc_freq() { freq++; }
	int get_freq() { return freq; }
	char get_char() { return element; }

	friend ostream& operator <<(ostream& out, const ELEMENT& obj)
	{
		out << obj.element << " " << obj.freq << endl;
		return out;
	}
	bool operator==(const ELEMENT& a)
	{
		return(freq == a.freq);
	}
	bool operator>=(const ELEMENT& a)
	{
		return(freq >= a.freq);
	}
	bool operator<=(const ELEMENT& a)
	{
		return(freq <= a.freq);
	}
	bool operator>(const ELEMENT& a)
	{
		return(freq > a.freq);
	}
	bool operator<(const ELEMENT& a)
	{
		return(freq < a.freq);
	}

};

struct charCode
{
	char a;
	vector<bool> code;
	friend ostream& operator <<(ostream& out, const charCode& obj)
	{
		out << obj.a;
		for (int i = 0; i < obj.code.size(); i++)
		{
			cout << obj.code[i];
		}
		return out;
	}
};
void getCodes(NODE<ELEMENT>* node, vector<charCode>& codes, vector<bool> temp)
{
	if (node->left)
	{
		temp.push_back(0);
		getCodes(node->left, codes, temp);
		temp.pop_back();
	}
	if (node->right)
	{
		temp.push_back(1);
		getCodes(node->right, codes, temp);
		temp.pop_back();
	}
	if (!node->left && !node->right)
	{
		charCode a;
		a.a = node->data.element;
		a.code = temp;
		codes.push_back(a);
	}
}
unsigned char  ToByte(bool b[8])
{
	unsigned char c = 0;
	for (int i = 0; i < 8; ++i)
		if (b[i])
			c |= 1 << i;
	return c;
}
void FromByte(unsigned char c, bool b[8])
{
	for (int i = 0; i < 8; ++i)
		b[i] = (c & (1 << i));
}

int main()
{
	////////////////////////////////// storing frquency ////////////////////////////
	ifstream fin("file.txt");
	vector<ELEMENT> frequency;
	char ch; int count = 0;
	if (fin.is_open())
	{
		int i = 0;
		fin.get(ch);
		while (!fin.eof())
		{
			count = 0;
			for (i = 0; i < frequency.size(); i++)
			{
				if (frequency[i].get_char() == ch)
				{
					frequency[i].inc_freq();
					count = 1;
					break;
				}
			}
			if (count == 0)
			{
				ELEMENT a(ch);
				frequency.push_back(a);
				frequency[i].inc_freq();
			}
			fin.get(ch);
		}
	}
	fin.close();
	MinHeap<NODE<ELEMENT>*> abc(frequency.size());
	////////////////////////////////////   creating heap
	for (int i = 0; i < frequency.size(); i++)
	{
		NODE<ELEMENT>* a = new NODE<ELEMENT>(frequency[i], NULL, NULL);
		abc.insert(a);
	}
	while (abc.size() > 1)
	{
		NODE<ELEMENT>* a1 = abc.extractMin();
		NODE<ELEMENT>* a2 = abc.extractMin();
		NODE<ELEMENT>* moo = new NODE<ELEMENT>();
		moo->data.freq = a1->data.freq + a2->data.freq;
		moo->left = a1;
		moo->right = a2;
		abc.insert(moo);
	}

	NODE<ELEMENT>* san = abc.extractMin();
	NODE<ELEMENT>* tempo = san;
	vector<charCode> mycode;
	vector<bool> pb;
	getCodes(san, mycode, pb);
	fin.open("file.txt", ios::binary);
	ofstream comp("Compressed.txt", ios::binary);
	ifstream na;
	ofstream decomp;
	decomp.open("Decompressed.txt", ios::binary);
	charCode* searched = nullptr;
	bool bro[8];
	vector<bool> temp;
	if (fin.is_open())
	{
		int k = 0;
		do
		{
			fin.get(ch);
			searched = nullptr;
			for (int i = 0; i < mycode.size(); i++)
			{
				if (mycode[i].a == ch)
				{
					searched = &mycode[i];
					break;
				}
			}
			if (searched != nullptr) {
				temp = searched->code;
				for (int i = 0; i < temp.size(); i++)
				{
					bro[k] = temp[i];
					++k;
					if (k == 8)
					{
						unsigned char c = ToByte(bro);
						cout << c;
						comp << c;
						k = 0;
					}
				}
			}

		} while (!fin.eof());
		cout << endl;
	}
	comp.close();
	na.open("Compressed.txt", ios::binary);
	while (na)
	{
		na.get(ch);
		FromByte(ch, bro);
		for (int i = 0; i < 8; i++)
		{

			if (bro[i])
				tempo = tempo->right;
			else
				tempo = tempo->left;

			if (!tempo->left and !tempo->right)
			{
				cout << tempo->data.element;
				decomp << tempo->data.element;
				tempo = san;
			}
		}
	}
	system("pause");
}
