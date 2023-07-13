#include<iostream>
#include "Data_handling.h"
#include "extendable_hashing.h"
#include<fstream>
using namespace std;
fstream indset(".//index.txt", ios::app);
fstream recset(".//recset.txt", ios::app);
int main()
{
	if (dirExists("./Database") == true)
	{
		cout << "\nDatabase already exists data has been loaded, continue ";
		string line, line2;
		ifstream load(".//index.txt");
		if (load.is_open())
		{
			int i = 0;
			while (getline(load, line))
			{
				i++;
				insert(line);
			}
			load.close();
		}
		ifstream load2(".//recset.txt");
		if (load2.is_open())
		{
			int i = 0;
			while (getline(load2, line))
			{
				i++;
				append(line);
			}
			load2.close();
		}
	}
	else
	{
		_mkdir("./Database");
		int n;
		cout << "\nThe database has been created , enter the number of attributes of a record to continue ";
		cin >> n;
		records(n);
		dat * temp = beg;
		while (temp != NULL)
		{
			recset << temp->data << "\n";
			temp = temp->next;
		}
	}
	int ch = 1;
	while (ch != 4)
	{
		cout << "\nEnter : \n1 for entering records \n2 for deleting record(s) \n3 search for record(s) \n4 for exiting: ";
		cin >> ch;
	if (ch == 1)
	{
		string key_value, line;
		cout << "\nEnter the key value for the record : ";
		cin >> key_value;
		if(search(root,key_value)){
			cout<<"Tuple with the key already exists\n";
			continue;
		}
		indset << key_value << "\n";
		create_data(key_value);
		cout<<"file created"<<endl;
		insert(key_value);
		cout<<"key inserted"<<endl;
	}
	else if (ch == 2)
	{
		string key_value;
		cout<<"Enter:\n1 for match delete\n2 for range delete:";
		int match_range;
		cin>>match_range;
		if(match_range==1){
		cout << "\nEnter the key value for the record to be deleted : ";
		cin >> key_value;
		del(root, key_value);
		rdir(key_value);
		}
		else if(match_range==2){
			cout<<"Enter the lower and upper limits respectively: ";
			int lower,upper;
			cin>>lower>>upper;
			for(int i=lower;i<=upper;i++){
				string key_value=to_string(i);
				del(root,key_value);
				rdir(key_value);
			} 
		}
	}
	else if (ch == 3)
	{
		string to_search;
		cout<<"Enter:\n1 for match search\n2 for range search:";
		int match_range;
		cin>>match_range;
		if(match_range==1){
		cout << "\nEnter the key value to be searched : ";
		cin >> to_search;
		if (search(root, to_search) == true)
		{
			cout<<"Enter no. of columns you want: ";
			int col;
			cin>>col;
			string temp[col];
			cout << "\nEnter the record(s) which you want to print : ";
			for(int i=0;i<col;i++){
			cin >> temp[i];
			}
			for(int i=0;i<col;i++)
			readit(to_search, temp[i]);
			
		}
		
		else
		{
			cout << "\nData does not exist in the system ";
		}
		}
		else if(match_range==2){
			int upper,lower;
			cout<<"Enter lower and upper limits respectively:\n";
			cin>>lower>>upper;
			cout<<"Enter no. of columns you want: ";
					int col;
					cin>>col;
					string temp[col];
					cout << "\nEnter the record(s) which you want to print : ";
					for(int i=0;i<col;i++){
						cin >> temp[i];
					}
			for(int i=lower;i<=upper;i++){
				string to_search=to_string(i);
				if (search(root, to_search) == true)
				{
					cout<<"\n\nKey value is: "<<to_search<<endl;
					for(int i=0;i<col;i++)
					readit(to_search, temp[i]);
				}
			}
		}
	}
}
}