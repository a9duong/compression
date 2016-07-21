#include "encode.h"
#include <iterator>
#include <sstream>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;
// Implement Encode Here if Needed

string Encode::mtfEncode( string str )
{
        fillSymbolTable();

        vector<int> output;
        for( string::iterator it = str.begin(); it != str.end(); it++ )
        {
                for( int i = 0; i < 96; i++ )
                {
                        if( *it == symbolTable[i] )
                        {
                                output.push_back( i );
                                moveToFront( i );
                                break;
                        }
                }
        }
        string r;
        string k;
        int result;
        for( vector<int>::iterator it = output.begin(); it != output.end(); it++ )
        {
                ostringstream ss;
                ss << *it;
                r+= ss.str() + " ";

        }
        return r;
}

string Encode::mtfDecode( string str )
{
        fillSymbolTable();
        istringstream iss( str ); vector<int> output;
        copy( istream_iterator<int>( iss ), istream_iterator<int>(), back_inserter<vector<int> >( output ) );
        string r;
        for( vector<int>::iterator it = output.begin(); it != output.end(); it++ )
        {
                r.append( 1, symbolTable[*it] );
                moveToFront( *it );
        }
        return r;
}

void Encode::fillSymbolTable()
{
        for( int x = 0; x < 95; x++ ){
                symbolTable[x] = x + 32;
        }
        symbolTable[95] = 31;
}

int cmp(Encode::suffix a, Encode::suffix b){
        return (a.rank[0] == b.rank[0]) ? (a.rank[1] < b.rank[1] ? 1 : 0) : (a.rank[0] < b.rank[0] ? 1 : 0);
}

int *Encode::buildSArray(string txt, int n){
        Encode::suffix suffixes[n];

        for (int i = 0; i < n; i++){
                suffixes[i].index = i;
                suffixes[i].rank[0] = txt[i] - 'a';
                suffixes[i].rank[1] = ((i+1) < n) ? (txt[i + 1] - 'a'): -1;
        }

        sort(suffixes, suffixes + n, cmp);

        int ind[n];

        for (int k = 4; k < 2*n; k = k*2){
                int rank = 0;
                int prev_rank = suffixes[0].rank[0];
                suffixes[0].rank[0] = rank;
                ind[suffixes[0].index] = 0;

                for (int i = 1; i < n; i++){
                        if (suffixes[i].rank[0] == prev_rank && suffixes[i].rank[1] == suffixes[i-1].rank[1]){
                                prev_rank = suffixes[i].rank[0];
                                suffixes[i].rank[0] = rank;
                        } else {
                                prev_rank = suffixes[i].rank[0];
                                suffixes[i].rank[0] = ++rank;
                        }
                        ind[suffixes[i].index] = i;
                }

                for (int i = 0; i < n; i++){
                        int nextindex = suffixes[i].index + k/2;
                        suffixes[i].rank[1] = (nextindex < n) ? suffixes[ind[nextindex]].rank[0] : -1;
                }

                sort(suffixes, suffixes+n, cmp);
        }

        int *suffixArr = new int[n];
        for (int i = 0; i < n; i++) {
                suffixArr[i] = suffixes[i].index;
        }
        return suffixArr;
}



string Encode::bwtEncodeBlock(const string &source){
        int size = static_cast<int>(source.size() + 1);
        string s = source;
        unsigned char a = 31;
        s.push_back(a);
        string c = s;

        int *suffixArray = buildSArray(s, size);

        for (int i = 0; i < size; i++){
                c[i] = s[(suffixArray[i] + size - 1) % size];
        }
        return c;
}




string Encode::bwtEncode(const string &source) {
        const int BLOCK_SIZE = 4096;

        if (source.length() > BLOCK_SIZE) {
                return bwtEncodeBlock(source.substr(0, BLOCK_SIZE)) + bwtEncode(source.substr(BLOCK_SIZE));
        } else {
                return bwtEncodeBlock(source);
        }
}

bool pairCompare(const pair<char, int>& firstElem, const pair<char, int>& secondElem) {
        return firstElem.first < secondElem.first;
}

string Encode::bwtDecode(const string &c){

        vector<pair <char, int> > arr;
        pair<char,int> tuple;
        for (int i = 0; i < c.size(); i++){
                tuple = make_pair(c[i], i);
                arr.push_back(tuple);
        }

        stable_sort(arr.begin(), arr.end(), pairCompare);

        int n[arr.size()];

        for (int i = 0; i < arr.size(); i++){
                n[i] = arr[i].second;
        }

        int j = n[0];
        unsigned char a = 31;
        string s = "";

        while (true){
                j = n[j];
                s += c[j];
                if (c[j] == a) break;
        }

        return s;
}

unsigned char *Encode::rleEncode(string s){
    vector <unsigned int> rle;
    
    stringstream ss(s);
    unsigned int token;

    while (ss >> token){
        rle.push_back(token); 
    }

    vector <unsigned int> v;
    
    int cur;
    int k;
    int count;

    for (int i = 0; i < rle.size(); i++){
        cur = rle[i];
        if (cur == 0){
            
            k = i+1;
            count = 1;
            while (true){
                if (rle[k] != cur) break;
                count++;
                k++;
            }

        v.push_back(count);
        v.push_back(cur);
        i+=count-1;
        } else {
            v.push_back(cur);
        }
    }

    cout << "length of rle: " << rle.size() << " length of v: " << v.size() << endl;

 /*   for (int i = 0; i < v.size(); i+=2){
        cout << "count: " << (int)v[i] << " thing: " << (int)v[i+1] << endl;
    }*/


unsigned char * a;
return a;
}


int main(){
        string txt;
        getline(cin, txt);
        Encode a;
        string s = a.bwtEncode(txt);
        
        string t = a.mtfEncode(s);

 /*       vector<unsigned int> rle;
        cout << t << endl;
        stringstream ss(t);
        unsigned int token;

        while (ss >> token){
            rle.push_back(token);
        }

        for (int i = 0; i < rle.size(); i++){
            cout << rle[i] << endl;
        }*/
    string h = a.mtfDecode(t);
 //     cout << t << endl;
      //cout << h << endl;
      a.rleEncode(t);
      //string d = a.bwtDecode(h);
      //cout << d << endl;
        return 0;
}

/*

   int main(){
   string source;
   getline(cin, source);

// Coded text
unsigned char * coded = NULL;
unsigned int length = test.Compress( source, coded );

// Decode text
Encode test2;
string result = test2.Decompress( coded, length );

return 0;
 */
