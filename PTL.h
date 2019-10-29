#pragma once

template <class T>
class DataNode
{
	T data;

public:
	DataNode* next = nullptr, * prev = nullptr;

	DataNode<T>(T elem) { data = elem; }
	T& GetData() { return data; }
};

template <class T>
class stack
{
	DataNode<T>* stackTop = nullptr;
	int length = 0;

public:
	int size() { return length; }
	int empty() { return !length; }
	T& top() { return stackTop->GetData(); }
	void push(T& elem)
	{
		DataNode<T>* newNode = new DataNode<T>(elem);
		newNode->prev = stackTop;
		stackTop = newNode;
		length++;
	}
	void pop()
	{
		DataNode<T>* tmp = stackTop;
		stackTop = stackTop->prev;
		delete (tmp);
		length--;
	}
	stack() {}
	stack(const stack<T>& s)
	{
		if (!s.length)
		{
			stackTop = nullptr;
			length = 0;
			return;
		}
		stackTop = new DataNode<T>(s.stackTop->GetData());
		length = s.length;
		DataNode<T>* m = stackTop, * n = s.stackTop;
		while (n->prev != nullptr)
		{
			m->prev = new DataNode<T>(n->prev->GetData());
			m = m->prev, n = n->prev;
		}
	}
};

template <class T>
class queue
{
	DataNode<T>* queueFront = nullptr, * queueBack = nullptr;
	int length = 0;

public:
	int size() { return length; }
	int empty() { return !length; }
	T& front() { return queueFront->GetData(); }
	T& back() { return queueBack->GetData(); }
	void push(T& elem)
	{
		DataNode<T>* newNode = new DataNode<T>(elem);
		if (length)
			queueBack->next = newNode;
		queueBack = newNode;
		if (!length)
			queueFront = queueBack;
		length++;
	}
	void pop()
	{
		DataNode<T>* tmp = queueFront;
		queueFront = queueFront->next;
		delete (tmp);
		length--;
		if (!length)
			queueBack = nullptr;
	}
	queue<T>() {}
	queue<T>(const queue<T>& q)
	{
		if (!q.length)
		{
			queueFront = queueBack = nullptr;
			length = 0;
			return;
		}
		queueFront = new DataNode<T>(q.queueFront->GetData());
		length = q.length;
		DataNode<T>* n = queueFront, * m = q.queueFront;
		while (m->next != nullptr)
		{
			n->next = new DataNode<T>(m->next->GetData());
			n = n->next, m = m->next;
		}
		queueBack = n;
	}
};
