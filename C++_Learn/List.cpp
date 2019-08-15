#include <iostream>

template <typename T>
struct ListNode {
	ListNode(const T& val = T())
		:_next(NULL)
		, _prev(NULL)
		, _val(val) {}

	ListNode<T>* _next;
	ListNode<T>* _prev;
	T _val;
};

//
//template <typename T, typename Ref, typename Ptr>
//class ListIterator {
//	typedef ListNode<T>* pNode;
//	typedef ListIterator<T, Ref, Ptr> Self;
//
//public:
//	ListIterator(const Self& l)
//	:_pNode(l._pNode){
//	}
//
//	T& operator*() {
//		return _pNode->val;
//	}
//
//	T* operator->() {
//		return this;
//	}
//
//
//
//	pNode _pNode;
//};

template <typename T>
class List {
	typedef ListNode<T> Node;
	typedef Node* pNode;
public:
	List() {
		CreateHead();
	}

	void Push_Back(const T& val) {
		pNode cur = _head;
		while (cur->_next != _head) {
			cur = cur->_next;
		}

		pNode node = new Node(val);
		node->_prev = cur;
		node->_next = cur->_next;
		cur->_next = node;
		node->_next->_prev = node;
	}

	void Clear() {
		pNode cur = _head->_next;;

		while (cur != _head) {
			_head->_next = cur->_next;
			delete cur;
			cur = _head->_next;
		}
		_head->_next = _head;
		_head->_prev = _head;
	}

	~List() {
		Clear();
		delete _head;
		_head = NULL;
	}

	void Print() {
		pNode cur = _head;
		while (cur->_next != _head) {
			std::cout << cur->_val << " ";
			cur = cur->_next;
		}
		std::cout << cur->_val;
		std::cout << std::endl;
	}

private:
	void CreateHead() {
		_head = new Node;
		_head->_next = _head;
		_head->_prev = _head;
	}

private:
	pNode _head;
};

void TestList() {
	List<int> l;

	l.Push_Back(1);
	l.Push_Back(2);
	l.Push_Back(3);
	l.Push_Back(4);
	l.Push_Back(5);
	l.Push_Back(6);
	l.Push_Back(7);	
	
	l.Print();

}
int main() {
	
	TestList();

	return 0;
}
