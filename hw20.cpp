
#include <iostream>
#include <windows.h>
using namespace std;

class Vector
{
	unsigned int size = 0;
	unsigned int capacity = 10;
	int* data = nullptr;

public:
	Vector() : Vector(10)
	{
		// cout << "C-TOR WITHOUT PARAMS!\n";
	}

	Vector(unsigned int capacity)
	{
		if (capacity < 10)
		{
			capacity = 10;
		}
		this->capacity = capacity;
		data = new int[capacity];
		// cout << "C-TOR WITH PARAMS!\n";
	}

	~Vector()
	{
		// cout << "DESTRUCTOR!\n";
		if (data != nullptr)
		{
			delete[] data;
			data = nullptr;
		}
	}

private:
	void EnsureCapacity()
	{
		if (size < capacity)
		{
			return;
		}

		capacity *= 2;

		int* temp = new int[capacity];
		for (int i = 0; i < size; i++)
		{
			temp[i] = data[i];
		}
		delete[] data;
		data = temp;
	}

	void QuickSortDesc(int low, int high)
	{
		if (low < high)
		{
			int index = PartitionDesc(low, high);
			QuickSortDesc(low, index - 1);
			QuickSortDesc(index + 1, high);
		}
	}

	int PartitionDesc(int low, int high)
	{
		int pivot = data[high];
		int i = low - 1;

		for (int j = low; j <= high - 1; j++)
		{
			if (data[j] >= pivot)
			{
				i++;
				Swap(data[i], data[j]);
			}
		}

		Swap(data[i + 1], data[high]);
		return i + 1;
	}

	void Swap(int& a, int& b)
	{
		int temp = a;
		a = b;
		b = temp;
	}

public:

	unsigned int GetSize() const
	{
		return size;
	}

	unsigned int GetCapacity() const
	{
		return capacity;
	}

	void Insert(int value, unsigned int index)
	{
		if (index > size)
		{
			cout << "Error!!\n";
			throw;
		}
		EnsureCapacity();
		for (unsigned int i = size; i > index; i--)
		{
			data[i] = data[i - 1];
		}
		data[index] = value;
		size++;

	}

	void RemoveByIndex(unsigned int index)
	{
		if (index >= size)
		{
			cout << "Error!!\n";
		}
		for (unsigned int i = index; i < size - 1; i++)
		{
			data[i] = data[i + 1];
		}
		size--;
	}

	void RemoveByValue(int value)
	{
		unsigned int index = 0;
		while (index < size)
		{
			if (data[index] == value)
			{
				for (unsigned int i = index; i < size - 1; i++)
				{
					data[i] = data[i + 1];
				}
				size--;
			}
			else
			{
				index++;
			}
		}
	}

	void PopFront()
	{
		if (size == 0)
		{
			cout << "Error!!\n";
			throw;
		}
		for (unsigned int i = 0; i < size - 1; i++)
		{
			data[i] = data[i + 1];
		}
		size--;
	}

	void PopBack()
	{
		if (size == 0)
		{
			cout << "Error!!\n";
			throw;
		}
		size--;
	}

	void PushBack(int value)
	{
		EnsureCapacity();
		data[size] = value;
		size++;

	}

	void PushFront(int value)
	{
		EnsureCapacity();
		for (int i = size; i > 0; i--) // i = 1
		{
			data[i] = data[i - 1]; // data[1] = data[0]
		}
		data[0] = value;
		size++;
	}

	void Clear()
	{
		size = 0;
	}

	bool IsEmpty() const
	{
		return size == 0;
	}

	void Print() const
	{
		if (IsEmpty())
		{
			cout << "Vector is empty.\n";
			return;
		}

		for (int i = 0; i < size; i++)
		{
			cout << data[i] << " ";
		}
		cout << "\n";
	}

	int LastIndexOf(int value) const
	{
		for (int i = size - 1; i >= 0; --i)
		{
			if (data[i] == value)
			{
				return i;
			}
		}
		return -1; 
	}

	void SortDesc()
	{
		QuickSortDesc(0, size - 1);
	}

	void Shuffle()
	{
		if (size <= 1)
		{
			return; 
		}

		srand(static_cast<unsigned int>(time(nullptr)));

		for (int i = size - 1; i > 0; --i)
		{
			int j = rand() % (i + 1);
			swap(data[i], data[j]);
		}
	}

	void RandomFill()
	{
		for (int i = 0; i < 5; i++)
		{
			PushBack(rand() % 100);
		}
	}

	int GetElementAt(unsigned int index) const
	{
		if (index < size)
		{
			return data[index];
		}
		else
		{
			cout << "Index out of bounds!\n";
		}
	}

	Vector(const Vector& other)
	{
		size = other.size;
		capacity = other.capacity;
		data = new int[capacity];

		for (unsigned int i = 0; i < size; ++i)
		{
			data[i] = other.data[i];
		}
	}


	Vector& operator=(const Vector& other)
	{
		if (this != &other) 
		{
			delete[] data;

			size = other.size;
			capacity = other.capacity;

			data = new int[capacity];

			for (unsigned int i = 0; i < size; ++i)
			{
				data[i] = other.data[i];
			}
		}
		return *this;
	}

	int& operator[](unsigned int index)
	{
		if (index < size)
		{
			return data[index];
		}
		else
		{
			cout << "Index out of bounds!\n";
		}
	}

	bool operator==(const Vector& other) const
	{
		if (size != other.size)
		{
			return false;
		}

		for (unsigned int i = 0; i < size; ++i)
		{
			if (data[i] != other.data[i])
			{
				return false;
			}
		}

		return true;
	}

	friend istream& operator>>(istream& input, Vector& vec);

	friend ostream& operator<<(ostream& output, const Vector& vec);

};

istream& operator>>(istream& input, Vector& vec)
{
	input >> vec.size;

	vec.data = new int[vec.size];

	for (unsigned int i = 0; i < vec.size; ++i)
	{
		input >> vec.data[i];
	}

	return input;
}

ostream& operator<<(ostream& output, const Vector& vec)
{
	for (unsigned int i = 0; i < vec.size; ++i)
	{
		output << vec.data[i] << " ";
	}

	return output;
}

int main()
{
	Vector bo;

	for (int i = 0; i < 10; i++)
	{
		bo.PushBack(rand() % 100);
		Sleep(15);
	}
	bo.Print();

	cout << "Function Remove By Index: ";
	bo.RemoveByIndex(0);
	bo.Print();
	cout << "\n";

	cout << "Function Pop Front: ";
	bo.PopFront();
	bo.Print();
	cout << "\n";

	cout << "Function Insert: ";
	bo.Insert(52, 3);
	bo.Print();
	cout << "\n";

	cout << "Function Pop Back: ";
	bo.PopBack();
	bo.Print();
	cout << "\n";

	cout << "Function Remove By Value: ";
	bo.RemoveByValue(76);
	bo.Print();
	cout << "\n";
}