#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<algorithm>
using namespace std;

int get_Code(char c)
{
	if (c == 'а') return 0;
	if (c == 'б') return 1;
	if (c == 'в') return 2;
	if (c == 'г') return 3;
	if (c == 'д') return 4;
	if (c == 'е') return 5;
	if (c == 'ж') return 6;
	if (c == 'з') return 7;
	if (c == 'и') return 8;
	if (c == 'й') return 9;
	if (c == 'к') return 10;
	if (c == 'л') return 11;
	if (c == 'м') return 12;
	if (c == 'н') return 13;
	if (c == 'о') return 14;
	if (c == 'п') return 15;
	if (c == 'р') return 16;
	if (c == 'с') return 17;
	if (c == 'т') return 18;
	if (c == 'у') return 19;
	if (c == 'ф') return 20;
	if (c == 'х') return 21;
	if (c == 'ц') return 22;
	if (c == 'ч') return 23;
	if (c == 'ш') return 24;
	if (c == 'щ') return 25;
	if (c == 'ъ') return 26;
	if (c == 'ы') return 27;
	if (c == 'ь') return 28;
	if (c == 'э') return 29;
	if (c == 'ю') return 30;
	if (c == 'я') return 31;
	if (c == '.') return -1;
	if (c == '#') return -2; 
}

char get_Char(int code)
{
	if (code == 0) return 'а';
	if (code == 1) return 'б';
	if (code == 2) return 'в';
	if (code == 3) return 'г';
	if (code == 4) return 'д';
	if (code == 5) return 'е';
	if (code == 6) return 'ж';
	if (code == 7) return 'з';
	if (code == 8) return 'и';
	if (code == 9) return 'й';
	if (code == 10) return 'к';
	if (code == 11) return 'л';
	if (code == 12) return 'м';
	if (code == 13) return 'н';
	if (code == 14) return 'о';
	if (code == 15) return 'п';
	if (code == 16) return 'р';
	if (code == 17) return 'с';
	if (code == 18) return 'т';
	if (code == 19) return 'у';
	if (code == 20) return 'ф';
	if (code == 21) return 'х';
	if (code == 22) return 'ц';
	if (code == 23) return 'ч';
	if (code == 24) return 'ш';
	if (code == 25) return 'щ';
	if (code == 26) return 'ъ';
	if (code == 27) return 'ы';
	if (code == 28) return 'ь';
	if (code == 29) return 'э';
	if (code == 30) return 'ю';
	if (code == 31) return 'я';	
}

struct letter
{
	char symbol;
	bool leaf;
	vector<int> children;

	letter()
	{
		symbol = ' ';
		leaf = true;
		children.assign(32, -1);
	}

	letter(char c, bool is_Leaf)
	{
		symbol = c;
		leaf = is_Leaf;
		children.assign(32, -1);
	}

};

class bor
{
	public:
	vector <letter> edges;

	bor()
	{
		edges.resize(1);
	}

	void push_Char_After_Char(int place, char c)
	{
		letter new_letter(c, false);
		edges.push_back(new_letter);
		edges[place].children[get_Code(c)] = edges.size() - 1; 
	}

	void push_String(string &s)
	{
		int cur_position = 0;
		/*for(size_t i = 0; i<s.length(); ++i)
		{
			
			if (edges[cur_position].children[get_Code(s[i])] == -1)
			{
				push_Char_After_Char(cur_position, s[i]);
				cur_position = edges.size() - 1;
			}
			else{
				cur_position = edges[cur_position].children[get_Code(s[i])];
			}
		}*/

		for(auto currentLetter: s){
			if (edges.at(cur_position).children.at(get_Code(currentLetter)) == -1)
			{
				push_Char_After_Char(cur_position, currentLetter);
				cur_position = (int)edges.size() - 1;
				
			}
			else{
				cur_position = edges.at(cur_position).children.at(get_Code(currentLetter));
			}
		}
		edges[cur_position].leaf = true;
	}

};

struct word
{
	string s;
	vector<pair<int, int> > coordinates;

	word(){};

	word(string &push_s, vector<pair<int, int> > &push_coordinates)
	{
		s = push_s;
		coordinates = push_coordinates;
	};

};

bool operator < (word w1, word w2)
{
	return (w1.s.length() < w2.s.length());
}

int N, M;
vector<vector<char> > table;
bor BOR;

vector <word> Words;

vector<string> possible_strings;
vector<vector<pair<int, int> > > coordinates;

vector<pair<int, int> > moves;

void dfs(int x, int y, int cur_position, vector<vector<bool> > cur_used, bool used_empty, string &cur_string, vector<pair<int, int> > &cur_coords)
{
	//cout << x << " " << y << " " << used_empty << " ";
	//for(int i = 0; i<cur_string.size(); ++i) cout << get_Code(cur_string[i]) << "^";
	//cout << "\n";
	cur_used[x][y] = true;

	if (BOR.edges[cur_position].leaf && used_empty)
	{
		//cerr << "success!\n" << cur_string << "\n";
		cur_coords.push_back(make_pair(x, y));
		cur_string += table[x][y];
		
		Words.push_back(word(cur_string, cur_coords));

		cur_string.pop_back();
		cur_coords.pop_back();
	}
	
	if (table[x][y] == '.' && !used_empty)
	{
		for(int i = 0; i<32; ++i)
		{
			table[x][y] = get_Char(i);
			if (BOR.edges[cur_position].children[i] !=-1)
				dfs(x, y, BOR.edges[cur_position].children[i], cur_used, true, cur_string, cur_coords);
		}
		table[x][y] = '.';
	}
	else
	for(size_t i = 0; i<moves.size(); ++i)
	{	
		int dx = moves[i].first;
		int dy = moves[i].second;

		int xx = x + dx;
		int yy = y + dy;

		if(table[xx][yy] == '#')
			continue;

		if (table[xx][yy] == '.' && used_empty)
			continue;

		if (cur_used[xx][yy])
			continue;

		cur_coords.push_back(make_pair(x, y));
		cur_string += table[x][y];
		

		if (table[xx][yy] != '.')
		{
			if (BOR.edges[cur_position].children[get_Code(table[xx][yy])] != -1)
				dfs(xx, yy, BOR.edges[cur_position].children[get_Code(table[xx][yy])], cur_used, used_empty, cur_string, cur_coords);
		}
		else
		{
			dfs(xx, yy, cur_position, cur_used, used_empty, cur_string, cur_coords);
		}

		cur_string.pop_back();
		cur_coords.pop_back();
	}

	cur_used[x][y] = false;
}

int main()
{
	ifstream in("input.txt");
	ofstream out("output.txt");
	//freopen("output.txt", "r", stdout);
	
	string s;
	int cnt = 0;
	while(in >> s)
	{
		++cnt;
		BOR.push_String(s);
	}
	return 0;
	cerr << "done!\n";

	ifstream fin("table.txt");
	
	fin >> N >> M;
	
	table.assign(N + 2, vector<char>(M + 2, '#'));

	for(int i = 1; i<=N; ++i)
		for(int j = 1; j<=M; ++j)
			fin >> table[i][j];

	moves.push_back(make_pair(0, 1));
	moves.push_back(make_pair(0, -1));
	moves.push_back(make_pair(1, 0));
	moves.push_back(make_pair(-1, 0));

	for(int i = 1; i<=N; ++i)
		for(int j = 1; j<=M; ++j)
		{
			vector<vector<bool> > cur_used;
			vector<pair<int, int> > cur_coords;
			string cur_string;
			cur_used.assign(N + 2, vector<bool> (M + 2, false));

			int cur_position = 0;
			if (table[i][j] != '.' && BOR.edges[cur_position].children[get_Code(table[i][j])] != -1)
				dfs(i, j, BOR.edges[cur_position].children[get_Code(table[i][j])], cur_used, false, cur_string, cur_coords);
			else
			if (table[i][j] == '.')
				dfs(i, j, 0, cur_used, false, cur_string, cur_coords);
			
		}

	sort(Words.begin(), Words.end());

	out << Words.size() << "\n";

	for(size_t i = 0; i<Words.size(); ++i)
	{
		out << Words[i].s << "\n";

		for(int j = 0; j<Words[i].coordinates.size(); ++j)
			out << Words[i].coordinates[j].first << " " << Words[i].coordinates[j].second << "\n";
	}

}
