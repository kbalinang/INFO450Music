//INFO450Music Project by Kristoffer Louie Balinang
#include "stdafx.h"
#include <iostream>
#include <stdio.h>
#include <fstream>
#include "windows.h"


using namespace std;


class node
{
	char artist[20];
	char title[20];
	node *next;
public:
	node(char a[20], char t[20]);
	friend class linkedList;
};

node::node(char a[20], char t[20])
{
	strcpy_s(artist, a); 
	strcpy_s(title, t);
	next = NULL;
}

// Linked List Class
class linkedList
{
	char filename[50];
	node *head;
	node *tail;
public:
	linkedList();
	void setFilename(char f[]);
	void readList();
	void addNodeToEnd(node *nptr);
	void showList();;
	void playSong();
	void skipSong();
	int deleteSong();
};

linkedList::linkedList()
{
	head = NULL;
	tail = NULL;
}

void linkedList::setFilename(char f[])
{
	strcpy_s(filename, f);
}

void linkedList::readList()
{
	ifstream infile(filename);
	if (!infile)
	{
		return;
	}

	while (!infile.eof())
	{
		node *ptr;
		char artist[20];
		char title[20];

		infile.getline(artist,20, ',');
		if (strlen(artist))
		{
			infile.getline(title,20);
			ptr = new node(artist, title);
			addNodeToEnd(ptr);
		}
	}
	infile.close();
}
void linkedList::showList()
{
	node *ptr;
	ptr = head;
	system("pause");
	system("cls");
	cout << "Song Playlist" << endl;
	cout << "--------------------------" << endl;
	if (ptr == NULL)
	{
		cout << "<ALERt> Nothing in this file! " << endl;
		return;
	}
	while (ptr != NULL)
	{
		cout << "Artist: " << ptr->artist << "\t Title: " << ptr->title << endl;
		ptr = ptr->next;
	}
}


void linkedList::playSong()
{
	char response[20];
	node *ptr;
	ptr = head;
	cout << "Type the song you want to play (case sensitive)" << endl;
	cin.clear();
	cin.ignore();
	gets_s(response);
	while (ptr != NULL)
	{
		if (strcmp(response, ptr->title) == 0)
		{
			cout << "Playing " << ptr->title << " by " << ptr->artist << endl;
		}
		ptr = ptr->next;
	}
}
void linkedList::skipSong()
{
	char response[20];
	node *ptr;
	ptr = head;
	cout << "Type the song you want to skip (case sensitive)" << endl;
	cin.clear();
	cin.ignore();
	gets_s(response);
	while (ptr != NULL)
	{
		if (strcmp(response, ptr->title) == 0)
		{
			cout << "Playing " << ptr->title << " by " << ptr->artist << endl;
			cout << "Stopped playing " << ptr->title << " by " << ptr->artist << endl;
			ptr = ptr->next;
			if (ptr->title )
			cout << "Now playing " << ptr->title << " by " << ptr->artist << endl;
		}
		ptr = ptr->next;
	}
	
}
int linkedList::deleteSong()
{
	char response[20];
	node *ptr = head;
	cout << "Type the song you want to delete (case sensitive)" << endl;
	cin.clear();
	cin.ignore();
	gets_s(response);

	if (ptr == NULL) 
		return -1;
	if (strcmp(response, ptr->title) == 0)
	{
		if (head == tail)
		{
			head = NULL;
			tail = NULL;
		}
		else
			head = head->next;
			delete ptr;
			return 0;
	}

	while (ptr != NULL)
	{
		if (ptr->next && (strcmp((ptr->next)->title, response) == 0))
		{
			if (tail == ptr->next)
				tail = ptr;
			node *tbd = ptr->next;
			ptr->next = (ptr->next)->next;
			delete tbd;
			return 0;
		}
		ptr = ptr->next;
	}
	return -1;
}
void linkedList::addNodeToEnd(node *ptr)
{
	// if list is empty
	if (head == NULL)
	{
		head = ptr;
		tail = ptr;
	}
	else
	{
		tail->next = ptr;
		tail = ptr;
	}
}




int main()
{
	bool answer = true;
	char response;

	char filename[50];
	cout << "Welcome to your MyPod" << endl;
	cout << "---------------------" << endl;
	cout << "Enter a file name: " << endl;
	gets_s(filename);
	linkedList *mylist = new linkedList();
	
	mylist->setFilename(filename);
	mylist->readList();
	do
	{
		mylist->showList();

		cout << " " << endl;
		cout << "--------------------------" << endl;
		cout << "What would you like to do?" << endl;
		cout << "[P]lay " << endl;
		cout << "[S]kip " << endl;
		cout << "[D]elete " << endl;
		cout << "[Q]uit " << endl;
		cin >> response;
		cout << " " << endl;

		if ((response == 'P') || (response == 'p'))
		{
			mylist->playSong();
			answer = true;
			
		}
		else if ((response == 'S') || (response == 's'))
		{
			mylist->skipSong();
			answer = true;
		}
		else if ((response == 'D') || (response == 'd'))
		{
			if (mylist->deleteSong())
				mylist->showList();
			answer = true;
		}
		else if ((response == 'Q') || (response == 'q'))
		{
			system("cls");
			cout << "Good Bye!" << endl;
			answer = false;
		}
		else
		{
			system("cls");
			cout << "Invalid response" << endl;
			answer = true;
		}
	} while (answer);
}
