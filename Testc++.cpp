// Testc++.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>
#include <sstream>
#include <fstream>
#include <string.h>
#include <stdexcept>
#include <stdio.h>
#include <string>
#include <vector>
#include <random>
#include <algorithm>
#include <iterator>
#include <memory>

using namespace std;

namespace Database
{
	typedef struct tagPoint2D
	{
		int _x = 0;
		int _y = 0;
		tagPoint2D(int x, int y) : _x(x), _y(y) {}
		tagPoint2D() {}
	}Point2D;

	inline bool operator!=(const Point2D& point1, const Point2D& point2)
	{
		return point1._x != point2._x || point1._y != point2._y;
	}

	inline ostream& operator<<(ostream& out, const Point2D& point)
	{
		return out << "x: " << point._x << "\ty: " << point._y << endl;
	}

	inline bool operator<(const Point2D& point1, const Point2D& point2)
	{
		return point1._x < point2._x && point1._y < point2._y;
	}
}

using namespace Database;

namespace Util
{
	vector<int> ArraySample = { 1, 13, 44, 2, 5, 8, 10, 124, 56, 23, 54, 52, 17, 87, 99, 34, 55 };

	vector<int> CreateRandomVector(int size)
	{
		// First create an instance of an engine.
		random_device rnd_device;
		// Specify the engine and distribution.
		mt19937 mersenne_engine{ rnd_device() };  // Generates random integers
		uniform_int_distribution<int> dist{ 1, 52 };
		auto gen = [&dist, &mersenne_engine]()
		{
			return dist(mersenne_engine);
		};
		vector<int> vec(size);
		generate(begin(vec), end(vec), gen);
		return vec;
	}

	unsigned int GenerateRandomNumber()
	{
		std::random_device dev;
		std::mt19937 rng(dev());
		std::uniform_int_distribution<std::mt19937::result_type> dist1to100(1, 100);
		return dist1to100(rng);
	}

	void Swap(int &a, int &b)
	{
		int temp = a;
		a = b;
		b = temp;
	}

	void DumpArray(const vector<int>& arr)
	{
		cout << "________ARRAY_______\n";
		for (auto const&iter : arr)
		{
			cout << iter << " ";
		}
		cout << "\n________________________\n";
	}

	template<typename T> 
	void SafeDeleteMemory(T* mem)
	{
		if (mem)
		{
			delete(mem);
			mem = nullptr;
		}
	}

	template<typename T> 
	void SafeDeleteMemoryArray(T* mem)
	{
		if (mem)
		{
			delete [](mem);
			mem = nullptr;
		}
	}
}

namespace Search
{
	// O(n)
	bool SearchLinear(const vector<int>& arr, int x, int* pos)
	{
		cout << "SearchLinear , target : " << x << endl;
		for (size_t i = 0; i < arr.size(); i++)
		{
			if (arr[i] == x)
			{
				*pos = i;
				return true;
			}
		}
		return false;
	}
	// O log2(n)
	bool SearchBinary(const vector<int>& arr, int x, int* pos)
	{
		int size = static_cast<int>(arr.size());
		int left = 0; int right = size - 1;
		do
		{
			int mid = (left + right) / 2;
			if (arr[mid] == x)
			{
				*pos = mid;
				return true;
			}
			else if (arr[mid] > x)
			{
				right = mid - 1;
			}
			else
			{
				left = mid + 1;
			}
		} while (left <= right);
		return false;
	}
}

namespace Sort
{
	void InterchangeSort(vector<int>& arr, bool sortAscending)
	{
		for (size_t i = 0; i < arr.size() - 1; ++i)
		{
			for (size_t j = i + 1; j < arr.size(); ++j)
			{
				if (sortAscending)
				{
					if (arr[i] > arr[j])
					{
						Util::Swap(arr[i], arr[j]);
					}
				}
				else
				{
					if (arr[i] < arr[j])
					{
						Util::Swap(arr[i], arr[j]);
					}
				}
			}
		}
	}
}

namespace SingleLinkedList
{
	typedef struct tagNode
	{
		Point2D _data;
		struct tagNode *_pNext = nullptr;
		tagNode(const Point2D& data, tagNode *pNext):
			_data(data), _pNext(pNext) {}
	}Node;

	typedef struct tagSingleNodeList
	{
		Node *pHeadNode = nullptr;
		Node *pTailNode = nullptr;
	}SingleNodeList;

	class SingleNodeListManager
	{
	private:
		SingleNodeList m_List;
	public:

		Node* CreateNode(const Point2D& point)
		{
			 Node *pNewNode = new Node(point, nullptr);
			 return pNewNode;
		}

		void CreateListRandomNode(int nSize)
		{
			for (int i = 0; i < nSize; ++i)
			{
				int x = Util::GenerateRandomNumber();
				int y = Util::GenerateRandomNumber();
				Point2D newPoint(x, y);
				Node* pNewNode = CreateNode(newPoint);
				InsertNodeAtTail(pNewNode);
			}
		}

		bool InsertNodeAtHead(Node *pNewNode)
		{
			if (!pNewNode) return false;
			if (m_List.pHeadNode == nullptr)
			{
				m_List.pHeadNode = pNewNode;
				m_List.pTailNode = m_List.pHeadNode;
			}
			else
			{
				pNewNode->_pNext = m_List.pHeadNode;
				m_List.pHeadNode = pNewNode;
			}
			return true;
		}

		bool InsertNodeAtTail(Node *pNewNode)
		{
			if (!pNewNode) return false;
			if (m_List.pTailNode == nullptr)
			{
				m_List.pHeadNode = pNewNode;
				m_List.pTailNode = m_List.pHeadNode;
			}
			else
			{
				m_List.pTailNode->_pNext = pNewNode;
				m_List.pTailNode = pNewNode;
			}
			return true;
		}
		bool InsertNodeAfterNode(Node *pNewNode, Node *pAfterNode)
		{
			if (!pNewNode) return false;
			if (pAfterNode == nullptr)
			{
				InsertNodeAtHead(pNewNode);
			}
			else
			{
				pNewNode->_pNext = pAfterNode->_pNext;
				pAfterNode->_pNext = pNewNode;
				if (m_List.pTailNode == pAfterNode)
				{
					m_List.pTailNode = pAfterNode;
				}
			}
			return true;
		}

		bool RemoveHeadNode()
		{
			Node* pDeleteNode = nullptr;
			if (m_List.pHeadNode)
			{
				pDeleteNode = m_List.pHeadNode;
				m_List.pHeadNode = m_List.pHeadNode->_pNext;
				Util::SafeDeleteMemory(pDeleteNode);
				if (m_List.pHeadNode == nullptr)
				{
					m_List.pTailNode = nullptr;
				}
				return true;
			}
			return false;
		}

		bool RemoveAfterNode(Node *pAfterNode)
		{
			Node* pDeleteNode = nullptr;
			if (!pAfterNode)
			{
				pDeleteNode = pAfterNode->_pNext; // delete node after it is _pNext
				if (!pDeleteNode)
				{
					if (pDeleteNode == m_List.pTailNode)
					{
						m_List.pTailNode = pAfterNode;
					}
					pAfterNode->_pNext = pDeleteNode->_pNext;
					Util::SafeDeleteMemory(pDeleteNode);
				}
				return true;
			}
			return false;
		}

		bool RemoveNodeByData(const Point2D& point)
		{
			Node *pDeleteNode = m_List.pHeadNode, *pAfterNode = nullptr;
			while (pDeleteNode != nullptr && pDeleteNode->_data != point)
			{
				pAfterNode = pDeleteNode;
				pDeleteNode = pDeleteNode->_pNext;
			}
			if (pDeleteNode == nullptr)
			{
				return false;
			}
			else if (pAfterNode != nullptr)
			{
				RemoveAfterNode(pAfterNode);
			}
			else // pDeleteNode->_data == point
			{
				RemoveHeadNode();
			}
		}

		Node* SearchNodeByData(const Point2D& point)
		{
			Node* pNodeFound = m_List.pHeadNode;
			while (pNodeFound != nullptr && pNodeFound->_data != point)
			{
				pNodeFound = pNodeFound->_pNext;
			}
			return pNodeFound;
		}

		void DumpList()
		{
			Node* pNodeFound = m_List.pHeadNode;
			while (pNodeFound != nullptr)
			{
				cout << pNodeFound->_data;
				pNodeFound = pNodeFound->_pNext;
			}
		}

		void ReleaseList()
		{
			Node* pNodeFound = nullptr;
			while (m_List.pHeadNode != nullptr)
			{
				pNodeFound = m_List.pHeadNode;
				m_List.pHeadNode = pNodeFound->_pNext;
				Util::SafeDeleteMemory(pNodeFound);
			}
		}

		void SortList()
		{
			auto fSwap2Node = [](Point2D& point1, Point2D& point2) -> void
			{
				Point2D temp;
				temp = point1;
				point1 = point2;
				point2 = temp;
			};

			Node* pNodeFound = nullptr, *pNextNode = nullptr, *pMinNode = nullptr;
			pNodeFound = m_List.pHeadNode;
			while (pNodeFound != m_List.pTailNode)
			{
				pMinNode = pNodeFound;
				pNextNode = pNodeFound->_pNext;
				while (pNextNode != nullptr)
				{
					if (pNextNode->_data < pNodeFound->_data)
					{
						pMinNode = pNextNode;
					}
					pNextNode = pNextNode->_pNext;
				}
				fSwap2Node(pMinNode->_data, pNodeFound->_data);
				pNodeFound = pNodeFound->_pNext;
			}
		}
	};
}

#define HASH_TABLE_SIZE 100
namespace HashTable
{
	typedef struct tagHashNode
	{
		int _key = 0;
		int _value = 0;
		struct tagHashNode *_pNext = nullptr;
		tagHashNode(const int& key, const int& value, tagHashNode *pNext) :
			_key(key), _value(value), _pNext(pNext) {}
	}HashNode;

	inline ostream& operator<<(ostream& out, HashNode* node)
	{
		return out << "key : " << node->_key << " -- value : " << node->_value << endl;
	}

	class HashTableManager
	{
	private:
		typedef HashNode* HashTable[HASH_TABLE_SIZE];
		HashTable m_HashTable;
		vector<int> m_KeyPool;

		void AddTailLinkedList(int indexTable, int value, int key)
		{
			HashNode* &pListAtIndex = m_HashTable[indexTable];
			HashNode* newNode = new HashNode(key, value, nullptr);
			if (pListAtIndex == nullptr) // list empty
			{
				pListAtIndex = newNode;
			}
			else
			{
				HashNode* pIterator = pListAtIndex;
				while (pIterator != nullptr && pIterator->_pNext != nullptr)
				{
					pIterator = pIterator->_pNext;
				}
				pIterator->_pNext = newNode; // add at tail list
			}
		}

		void DeleteHeadLinkedList(HashNode* pHeadNode)
		{
			if (pHeadNode)
			{
				HashNode* pDeleteNode = pHeadNode;
				pHeadNode = pHeadNode->_pNext;
				Util::SafeDeleteMemory(pDeleteNode);
			}
		}

		void DeleteAfterLinkedList(HashNode* pAfterNode)
		{
			if (pAfterNode)
			{
				HashNode* pDeleteNode = pAfterNode->_pNext;
				pAfterNode->_pNext = pDeleteNode->_pNext;
				Util::SafeDeleteMemory(pDeleteNode);
			}
		}

		void TraverseLinkedList(HashNode* list)
		{
			while (list)
			{
				cout << list;
				list = list->_pNext;
			}
		}

		void ReleaseLinkedList(HashNode* list)
		{
			HashNode* pDeleteNode = nullptr;
			while (list)
			{
				pDeleteNode = list;
				list = list->_pNext;
				Util::SafeDeleteMemory(pDeleteNode);
			}
		}

	public:
		void InitHashTable()
		{
			for (int i = 0; i < HASH_TABLE_SIZE; ++i)
			{
				m_HashTable[i] = nullptr;
			}
		}

		int HashFunction(int key)
		{
			return key % HASH_TABLE_SIZE;
		}

		int GetHashTableMaxkey()
		{
			return *max_element(m_KeyPool.begin(), m_KeyPool.end());
		}

		size_t GetTableSize()
		{
			return m_KeyPool.size();
		}

		void InsertNode(int value, int key = 0)
		{
			if (key == 0)
			{
				key = GetHashTableMaxkey() + 1;
			}
			m_KeyPool.push_back(key);
			int indexTable = HashFunction(key);
			AddTailLinkedList(indexTable, value, key); // collision resolving
		}

		HashNode* LookupNode(int key)
		{
			int indexTable = HashFunction(key);
			HashNode* pIterator = m_HashTable[indexTable];
			while (pIterator != nullptr && pIterator->_key != key)
			{
				pIterator = pIterator->_pNext;
			}
			return pIterator;
		}

		bool DeleteNode(int key)
		{
			int indexTable = HashFunction(key);
			HashNode* pIterator = m_HashTable[indexTable];
			HashNode* pAfterNode = pIterator;
			while (pIterator != nullptr && pIterator->_key != key)
			{
				pAfterNode = pIterator;
				pIterator = pIterator->_pNext;
			}
			if (pIterator == nullptr)
			{
				return false;
			}
			else if (pIterator == m_HashTable[indexTable])
			{
				DeleteHeadLinkedList(m_HashTable[indexTable]);
			}
			else
			{
				DeleteAfterLinkedList(pAfterNode);
			}
			return true;
		}

		void DumpHashTable()
		{
			for (int i = 0; i < HASH_TABLE_SIZE; ++i)
			{
				TraverseLinkedList(m_HashTable[i]);
			}
		}

		void ReleaseHashTable()
		{
			for (int i = 0; i < HASH_TABLE_SIZE; ++i)
			{
				ReleaseLinkedList(m_HashTable[i]);
			}
		}
	};
}

namespace DoubleLinkedList
{

}

namespace Tree
{

}

int main()
{
	// Sort
	//vector<int> sample = Util::CreateRandomVector(10);
	vector<int> sample = Util::ArraySample;

	cout << "Array Created: " << endl;
	Util::DumpArray(sample);
	int posFound = -1;
	if (Search::SearchLinear(sample, 8, &posFound))
	{
		cout << "SearchLinear found at " << posFound << endl;
	}
	else
	{
		cout << "SearchLinear not found!" << endl;
	}
	
	Sort::InterchangeSort(sample, true);
	if (Search::SearchBinary(sample, 8, &posFound))
	{
		cout << "SearchBinary found at " << posFound << endl;
	}
	else
	{
		cout << "SearchBinary not found!" << endl;
	}

	Util::DumpArray(sample);

	// Linked list
	SingleLinkedList::SingleNodeListManager SNLM;
	SNLM.CreateListRandomNode(10);
	SNLM.DumpList();
	SNLM.SortList();
	SNLM.DumpList();
	SNLM.ReleaseList();

	//HashTable
	HashTable::HashTableManager HM;
	HM.InitHashTable();
	HM.InsertNode(11, 1);
	HM.InsertNode(12, 2);
	HM.InsertNode(13, 3);
	HM.InsertNode(14, 4);
	HM.InsertNode(15, 5);
	HM.DumpHashTable();
	HM.ReleaseHashTable();

	system("pause");

	return 0;
}