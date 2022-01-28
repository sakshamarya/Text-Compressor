#include<bits/stdc++.h>
using namespace std;

class treeNode{

	public:
		char ch;
		treeNode* left;
		treeNode* right;

		treeNode(char x)
		{
			ch=x;
			left=NULL;
			right=NULL;
		}

};

string decode(treeNode* root, string &encodedText)
{

	string decodedText;

	int i=0;

	while(i<encodedText.size())
	{

		treeNode* temp = root;
		int j=i;

		while(temp->left || temp->right)
		{
			if(encodedText[j]=='1')
			{
				temp=temp->right;
			}
			else{
				temp=temp->left;
			}
			j++;
		}

		decodedText.push_back(temp->ch);
		i=j;

	}

	return decodedText;
}


int main()
{

	string a;
	cin>>a;

	int n=a.size();

	unordered_map<char,int> m;

	for(int i=0;i<n;i++)
	{
		if(m.find(a[i])==m.end())
		{
			m[a[i]]=1;
		}
		else{
			m[a[i]]++;
		}
	}

	set<pair<int,pair<vector<char>,treeNode*>>> s;

	for(auto i:m)
	{
		treeNode* temp = new treeNode(i.first);
		s.insert({i.second,{{i.first},temp}});
	}

	unordered_map<char,string> codes;

	treeNode* root; // root of the huffman tree

	while(s.size()>=2)
	{
		auto temp1=*(s.begin());
		s.erase(s.begin());
		auto temp2=*(s.begin());
		s.erase(s.begin());

		vector<char> currChars;

		for(auto j:temp1.second.first)
		{
			currChars.push_back(j);
			codes[j].push_back('0');
		}

		for(auto j:temp2.second.first)
		{
			currChars.push_back(j);
			codes[j].push_back('1');
		}

		treeNode* temp = new treeNode('*');
		temp->left = temp1.second.second;
		temp->right = temp2.second.second;

		if(s.size()==0)
		{
			root=temp;
		}

		s.insert({temp1.first+temp2.first, {currChars, temp}});

	}

	cout<<"Codes for characters -> "<<endl;

	for(auto i:codes)
	{
		string code=i.second;
		reverse(code.begin(),code.end());
		codes[i.first]=code;

		cout<<i.first<<"-> ";
		for(auto j:code)
		{
			cout<<j<<" ";
		}
		cout<<endl;
	}

	cout<<"Before compression, the size of the string is "<<sizeof(char)*8*n<<endl;

	int newStringSize=0,tableSize=0;

	for(auto i:m)
	{
		newStringSize+=(i.second)*(codes[i.first].size());
	}

	for(auto i:codes)
	{
		tableSize+=(sizeof(i.first)*8)+codes[i.first].size();
	}

	cout<<"After compression, the size of the string is "<<newStringSize+tableSize<<endl;

	string encodedText="";

	for(int i=0;i<n;i++)
	{
		encodedText+=codes[a[i]];
	}

	cout<<"Encoded Text is "<<encodedText<<endl;

	cout<<"Decoded Text is "<<decode(root,encodedText)<<endl;

	if(a == decode(root,encodedText))
	{
		cout<<"Decoded text is same as the encoded text."<<endl;
	}


	return 0;
}
