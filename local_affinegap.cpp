#include<bits/stdc++.h>
using namespace std;

int D(char x,char y,int match,int mismatch){
	if(x==y) return match;
	else return -1*mismatch;
}

int max_4(int a,int b,int c,int d){
	return max(max(a,b),max(c,d));
}

void print_in80s(vector <char> v1,vector <char> v2){
	//int itr = 1;
	int len = v1.size();
	cout << "Length of local alignment = " << len << endl;
	int i = 0;
	while(i<len){
		//cout << "ee";
		for(int j=i;j<min(len,i+80);j++){
			cout << v1[j];
			//cout << "ee";
		}
		cout << "\n";
		for(int j=i;j<min(len,i+80);j++){
			cout << v2[j];
		}
		cout << "\n\n";
		i = i+80;
	}
}

int main(){
	
	string s1 ;
	string s2 ;	//sequences to be aligned

	int match;
	int mismatch;
	int d;		//d in -d - sigma
	int x;		//sigma
	
	cin >> match >> mismatch >> d >> x;
	cin >> s1;
	cin >> s2;
	
	int m1[s1.length()+1][s2.length()+1];
	int m2[s1.length()+1][s2.length()+1];
	int m[s1.length()+1][s2.length()+1];
	
	for(int i=0;i<1;i++){
		for(int j=0;j<s2.length()+1;j++){
			m1[i][j]=0;
			m2[i][j]=0;
			m[i][j] =0;
		}
	}
	
	for(int i=0;i<s1.length()+1;i++){
		for(int j=0;j<1;j++){
			m1[i][j]=0;
			m2[i][j]=0;
			m[i][j] =0;
		}
	}
	
	int max_score = 0;
	vector <pair <int,int> > pos;
	
	vector <char> from[s1.length()+1][s2.length()+1];	//= N null 0,T top 1,L left 2,D diagonal 3
	for(int i=0;i<1;i++){
		for(int j=0;j<s2.length()+1;j++){
			from[i][j].push_back('N');
		}
	}
	
	for(int i=0;i<s1.length()+1;i++){
		for(int j=0;j<1;j++){
			if(i!=0 || j!=0)from[i][j].push_back('N');
		}
	}
	
	for(int i=1;i<s1.length()+1;i++){
		for(int j=1;j<s2.length()+1;j++){
			m1[i][j] = max(m1[i-1][j] - x,m[i-1][j] - d - x);
			m2[i][j] = max(m2[i][j-1] - x,m[i][j-1] - d - x);
			m[i][j] = max_4(m[i-1][j-1] + D(s1[i-1],s2[j-1],match,mismatch),m1[i][j],m2[i][j],0);
			
			if(max_score<m[i][j]){
				max_score = m[i][j];
			}
			//trace path
			if(m[i][j]==0){
				from[i][j].push_back('N');
			}
			if(m[i][j]==m[i-1][j-1] + D(s1[i-1],s2[j-1],match,mismatch)){
				from[i][j].push_back('D');
			}
			if(m[i][j]==m1[i][j]){
				from[i][j].push_back('T');
			}
			if(m[i][j]==m2[i][j]){
				from[i][j].push_back('L');
			}
				
			
		}
	}
	
	//getting score and positions
	
	if(max_score!=0){
		cout << "--- MAXIMUM SCORE = "<< max_score << " ---"<< endl;
		for(int i=1;i<s1.length()+1;i++){
			for(int j=1;j<s2.length()+1;j++){
				if(m[i][j]==max_score) pos.push_back(make_pair(i,j));
			}
		}
	}
	else {
		cout << "--- MAXIMUM SCORE is NULL ---" << endl;
		exit(0);
	}
	
	pair <int,int> pos_start[pos.size()];
	
	vector <char> path[pos.size()]; 
	
	//preparing data
	for(int i=0;i<pos.size();i++){
		int x_end = pos[i].first;
		int y_end = pos[i].second;
		int x = pos[i].first;
		int y = pos[i].second;
		while(from[x][y][0]!='N'){
			path[i].push_back(from[x][y][0]);
			if(from[x][y][0]=='D'){
				x--;
				y--;
			}
			else if(from[x][y][0]=='T'){
				x--;
			}
			else if(from[x][y][0]=='L'){
				y--;
			}
		}
		int x_st = x;
		int y_st = y;
		pos_start[i] = make_pair(x_st,y_st);
	}
	
	//putting paths in order
	for(int i=0;i<pos.size();i++){
		reverse(path[i].begin(),path[i].end());
	}
	
	//printing matrices	
	/*for(int i=0;i<pos.size();i++){
		for(int j=0;j<path[i].size();j++){
			cout << path[i][j] << ' ';	
		}
		cout << endl;
	}
	
	
	for(int i=0;i<s1.length()+1;i++){
		for(int j=0;j<s2.length()+1;j++){
			cout << m1[i][j] << ' ';
		}
		cout << endl;
	}
	
	for(int i=0;i<s1.length()+1;i++){
		for(int j=0;j<s2.length()+1;j++){
			cout << m2[i][j] << ' ';
		}
		cout << endl;
	}
	
	for(int i=0;i<s1.length()+1;i++){
		for(int j=0;j<s2.length()+1;j++){
			cout << m[i][j] << ' ';
		}
		cout << endl;
	}
	
	for(int i=0;i<s1.length()+1;i++){
		for(int j=0;j<s2.length()+1;j++){
			for(int k=0;k<from[i][j].size();k++){
				cout << from[i][j][k];
			}
			cout << ' ';
		}
		cout << endl;
	}*/
	
	//printing alignments
	int n_al = pos.size();	//number of alignments to be printed
	
	for(int i=0;i<n_al;i++){
		cout << "--- ALIGNMENT " << i+1 << " ---" << endl;
		cout << "Indexes of alignments in sequences : ";
		cout<<'('<<pos_start[i].first+1<<","<<pos[i].first<<')'<<" AND "<<'('<<pos_start[i].second+1<<","<<pos[i].second<<')'<<endl;
		pair <int,int> start = pos_start[i];
		pair <int,int> end = pos[i];
		vector <char> align1;
		vector <char> align2;
		int itr = 0;	
		while((start!=end) && itr < path[i].size()){
			if(path[i][itr]=='D'){
				start.first = start.first + 1;
				start.second = start.second + 1;
				align1.push_back(s1[start.first-1]);
				align2.push_back(s2[start.second-1]);
			}
			else if(path[i][itr]=='T'){
				start.first = start.first + 1;
				align1.push_back(s1[start.first-1]);
				align2.push_back('-');	
			}
			else if(path[i][itr]=='L'){
				start.second = start.second + 1;
				align1.push_back('-');
				align2.push_back(s2[start.second-1]);
				
			}
			itr++;
		}
		
		/*for(int len=0;len<align1.size();len++){
			cout << align1[len];
		}
		cout << endl;
		for(int len=0;len<align2.size();len++){
			cout << align2[len];
		}
		cout << endl;
		cout << "new output\n";*/
		print_in80s(align1,align2);
	}
	
	return 0;
}
