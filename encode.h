#include <iostream>
#include <string>

using namespace std;

/*  Skeleton for Encode
    You may add as many functions/fields as required to implement your solution. 
    You may NOT store a copy of the source text!  Doing so results in a score of 0. */

class Encode
{
        public:
                struct suffix{
                    int index;
                    int rank[2];
                };

                Encode() {};
                ~Encode() {};


                /*  Compress:
                    ----------------------------------------------------
                    Compress the source text into result.
                    This function is responsible for allocating result.
                    The caller is responsible for freeing result.
                    Compress returns the length of the result. 
                    ---------------------------------------------------- */
                unsigned int Compress( const string &source, unsigned char *& result );


                /*  Decompress:
                    ----------------------------------------------------
                    Decompress codedText with the given length into a
                    string.  Returns the decoded text as a string.
                    Assumes codedText is not null, length > 0.
                    ---------------------------------------------------- */
                string Decompress( unsigned char * codedText, unsigned int length );


        

                /*  SetBit:
                    ----------------------------------------------------
                    Set the k-th bit of the unsigned char (data) to 1.
                    Assumes data is initially 0.
Examples:
SetBit( 0, data ) --> data = 0000 0001
SetBit( 1, data ) --> data = 0000 0010
SetBit( 2, data ) --> data = 0000 0100
---------------------------------------------------- */
                void SetBit( unsigned int k, unsigned char * data )
                {
                        (* data) |= ( 1 << k );
                }

                string mtfEncode(string str);

                string mtfDecode( string str);
                
                int *buildSArray(string txt, int n);

                string bwtEncodeBlock(const string &source);

                string bwtEncode(const string &source);

                string bwtDecode(const string &c);

                unsigned char *rleEncode(string s); 

                unsigned char symbolTable[96];
                void fillSymbolTable();
                void moveToFront( int i )
                {
                        unsigned char t = symbolTable[i];
                        for( int z = i - 1; z >= 0; z-- )
                                symbolTable[z + 1] = symbolTable[z];

                        symbolTable[0] = t;
                }

};
