#pragma once
#include <cassert>
#include <fstream>
#include <string>


void Write(std::string& str, FILE* file);
std::string& Read(FILE* file);


struct ListNode {
	ListNode *      prev;
	ListNode *      next;
	ListNode *      rand; // указатель на произвольный элемент данного списка либо NULL
	std::string     data;
};


class List {
public:

	void Serialize(FILE* file)
	{
		assert(file);
		
		uint32_t sizeOfList = static_cast<uint32_t>(this->count);
		
		char* buf = reinterpret_cast<char*>(&sizeOfList);
		fwrite(buf, sizeof(uint32_t), 1, file);
		
		if(sizeOfList > 0)
		{
			for(int i =0;i<sizeOfList;i++)
			{
				Write(this->operator[](i), file);
			}
		}

	}	// сохранение в файл (файл открыт с помощью fopen(path, "wb"))

	
	void Deserialize(FILE* file)
	{
		this->ReleseNodes();

		//Read num of nodes
		char* sizeBuffer = new char[sizeof(uint32_t)];
		fread(sizeBuffer, sizeof(uint32_t), 1, file);
		uint32_t* sizeOfList = reinterpret_cast<uint32_t*>(sizeBuffer);

		if(*sizeOfList > 0)
		{
			for(int i =0; i < *sizeOfList;i++)
			{
				this->Add(Read(file));
			}
		}
		delete (sizeOfList);



	}	// загрузка из файла (файл открыт с помощью fopen(path, "rb"))

	
	std::string& operator[](int Nth)
	{
		
		assert(Nth <= (count - 1));
		
		ListNode* iterator = head;
		while(Nth)
		{
			iterator = iterator->next;
			Nth--;		
		}
		return iterator->data;
	}

	void Add(std::string& value)
	{
		
		ListNode* newNode = new ListNode();
		newNode->data = value;
		newNode->next = nullptr;
		newNode->prev = tail;
		
		if (head == nullptr && tail == nullptr) { head = newNode;  }
		else tail->next = newNode;
		tail = newNode;
		count++;
		
	}

	void ReleseNodes()
	{
		while(count)
		{
			auto tmp = tail->prev;
			delete(tail);
			tail = tmp;
			count--;
			
		}
		head = nullptr;
		
	}
	
private:
	ListNode* head;
	ListNode* tail;
	int count;
};


//Write a string "str" into stream "os"
void Write(std::string& str, FILE* file)
{
	// adding one to .size() because the string doesn't count '\0'
	uint32_t sizeOfString = static_cast<uint32_t>( str.size() +1);
	fwrite(reinterpret_cast<char*>(&sizeOfString), sizeof(uint32_t), 1, file);

	if (sizeOfString > 0) fwrite(str.c_str(), sizeof(char), sizeOfString, file); 
	
}



std::string& Read( FILE* file)
{
	//Read the num of chars
	char* sizeBuffer = new char[sizeof(uint32_t)];
	fread(sizeBuffer, sizeof(uint32_t), 1, file);
	uint32_t* sizeOfString = reinterpret_cast<uint32_t*>(sizeBuffer);

	//Read a string
	char* stringBuffer = new char[sizeof(char)* (*sizeOfString)];
	fread(stringBuffer, sizeof(char),static_cast<size_t>(*sizeOfString), file);
	std::string* tmp = new std::string(stringBuffer);
	
	delete[] stringBuffer;
	delete sizeOfString;

	return *tmp;
	
}

