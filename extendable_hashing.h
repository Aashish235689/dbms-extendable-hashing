#pragma once
#include<bits/stdc++.h>
#include<iostream>
// #include<direct.h>
// #include <filesystem>
#include <fstream>
#include <string>
// #include<windows.h>
// #include "linked.h"
using namespace std;
// # define counted 100

class buckets{
    public:
    vector<string> keys;
    map<string,string> address;
    int size=0;
};
int counted=1;
class hashnode{
    public:
    map<string,buckets*> hashing;

    hashnode(){
        // hashing =vector<bucket*>(2,NULL);
        hashing["0"]=NULL;
        hashing["1"]=NULL;
    }
}*root=NULL;


string toBinary(string const &str) {
    string binary ="";
    for (char const &c: str) {
        binary += bitset<8>(c).to_string();
    }
    return binary;
}

string to_be_searched(string str,int c){
    string x="";
    // int k=1;
    int i=str.length()-1;
    for(int j=0;j<c;j++){
        x+=str[i];
        i--;
    }
    reverse(x.begin(),x.end());
    return x;
}

bool search(hashnode* root,string key){
    // cout<<"IN SEARCH\n";
    if(root==NULL){
        return 0;
    }
    string bin_inp=toBinary(key);
    // cout<<"bin_inp "<<bin_inp<<endl;
    string tbs=to_be_searched(bin_inp,counted);
    // cout<<"tbs "<<tbs<<endl;
    if(root->hashing[tbs]==NULL)
    return 0;
    buckets* bucket=root->hashing[tbs];
    for(int i=0;i<bucket->keys.size()&&i<4;i++){
        if(bucket->keys[i]==key)
        return 1;
    }
    return 0;
}

// string to_binary(int n){
//     string s="";
//     while(n>0){
//         s+=char(n%2+int('0'));
//         n/=2;
//     }
//     reverse(s.begin(),s.end());
//     return s;
// }

void more_buckets(){
    // cout<<"IN BUCKETS\n\n";
    hashnode* new_root=new hashnode();
    counted++;
    int c=counted-1;
    bool f=0;
    // cout<<"Initial new root "<<new_root->hashing.size()<<endl;
    int j=pow(2,c);
    // int i=0;
    buckets *bucket=root->hashing[toBinary("0")];
    int k=0;
    while(k<j){
        // if(!f){
            string str=to_be_searched(toBinary(to_string(k)),c);
            // cout<<"root "<<str<<endl;
            bucket=root->hashing[str];
            k++;
        // }
        for(int i=0;i<j*2;i++){
            string str_new=to_be_searched(toBinary(to_string(i)),c);
            if(str_new==str)
            new_root->hashing[to_be_searched(toBinary(to_string(i)),counted)]=bucket;
            // cout<<str<<endl;
            // for(int a=0;a<bucket->keys.size();a++)
            // cout<<bucket->keys[a]<<" ";
            // cout<<endl;
        }
        // i++;
        // f=!f;
    }
    // cout<<""
    root=new_root;
}
//to_binary->toBinary
void pointer_changer(buckets* bucket,string specialised_key){
    int j=pow(2,counted);
    for(int i=0;i<j;i++){
        string str=toBinary(to_string(i));
        str=to_be_searched(str,counted);
        // cout<<str<<" "<<specialised_key<<endl;
        if(str==specialised_key){
            root->hashing[specialised_key]=new buckets();
            // cout<<"C1\n";
            cout<<bucket->keys.size()<<endl;
            for(int k=0;k<bucket->keys.size();k++){
                // cout<<bucket->keys[k]<<" "<<to_be_searched(toBinary(bucket->keys[k]),counted)<<endl;
                if(specialised_key==to_be_searched(toBinary(bucket->keys[k]),counted))
                root->hashing[specialised_key]->keys.push_back(bucket->keys[k]);
            }
            // cout<<"C2\n";
            // for(int k=0;k<root->hashing[specialised_key]->keys.size();k++){
            //     bucket->keys.erase(find(bucket->keys.begin(),bucket->keys.end(),root->hashing[specialised_key]->keys[k]));
            // }
            // cout<<"C3\n";
            break;
        }
    }
}

void insert(string input){
    // cout<<"start"<<endl;
    if(root==NULL){
        // cout<<"NULL root"<<endl;
        root=new hashnode();
        root->hashing["0"]=new buckets();
        root->hashing["1"]=new buckets();
    }
    string bin_inp=toBinary(input);
    // cout<<"binary input"<<bin_inp<<endl;
    string tbs=to_be_searched(bin_inp,counted);
    buckets* bucket=root->hashing[tbs];
    // cout<<"before search\n";
    if(search(root,input))
    {
        cout<<"Tuple with same key already exists"<<endl;
        // return ;
    }
    else if(bucket->keys.size()<4){
        // cout<<"less size"<<endl;
        bucket->keys.push_back(input);
        bucket->address[input]="C:\\Users\\aashi\\Downloads\\21CSB0A03(project 2) B+ to extendable hashing\\DBMS project2\\Database\\"+input;
        //address
    }
    else{
        // cout<<"packed"<<endl;
        int j=pow(2,counted);
        int c=0;
        // buckets* the_bucket=NULL;
        bucket=root->hashing[tbs];
        for(int i=0;i<j;i++){
            if(root->hashing[to_be_searched(toBinary(to_string(i)),counted)]==bucket)
            {
                c++;
            }
        }
        // cout<<"no. of pointers "<<c<<endl;
        if(c>1){
            //pointer_changer
            bucket=root->hashing[to_be_searched(bin_inp,counted)];
            // tbs=
            pointer_changer(bucket,tbs);
        }
        bucket=root->hashing[tbs];
        // cout<<"bucket after pointer changer"<<bucket->keys.size()<<endl;
        if(bucket->keys.size()<4){
            bucket->keys.push_back(input);
            bucket->address[input]="C:\\Users\\aashi\\Downloads\\21CSB0A03(project 2) B+ to extendable hashing\\DBMS project2\\Database\\"+input;
        }
        else{
            // cout<<"more buckets needed\n";
            more_buckets();
            // cout<<"more buckets created\n";
            tbs=to_be_searched(bin_inp,counted);
            cout<<tbs<<endl;
            bucket=root->hashing[tbs];
            // cout<<"before pointer changer\n";
            pointer_changer(bucket,tbs);
            // cout<<"after pointer changer\n";
            // bucket->keys.push_back(input);
            insert(input);
        }

    }
    // cout<<"After search\n";
    // cout<<"bucket size"<<bucket->keys.size()<<endl;
    // cout<<root->hashing.size()<<endl;
}

void del(hashnode* root,string input){
    string key=to_be_searched(toBinary(input),counted);
    if(search(root,input)){
        root->hashing[key]->keys.erase(find(root->hashing[key]->keys.begin(),root->hashing[key]->keys.end(),input));
        cout<<"DELETED"<<endl;
    }
    else cout<<"Key not found\n";
}

// int main(){
//     string input;
//     counted=1;
//     int n;

//     while(n!=-1){

//         cout<<"1. Input\n2. Search\n3. Delete\n";
//         cin>>n;
//         if(n==-1)
//         break;
//         cin>>input;
//         switch(n){
//         case 1: insert(input);break;
//         case 2: cout<<search(root,input)<<endl;break;
//         case 3: del(root,input);
//         }
//     }
//     // cin>>input;
    
// }