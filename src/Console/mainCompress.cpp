#include <iostream>
using namespace std;

#include <stdlib.h>

#include "Compression.h"

#include "matrix.h"


int main(int argc, char* argv[])
{
	cout << endl;
	if ( (argc == 2) && (string(argv[1]).compare("--help") == 0) )
	{
		// HELP
		cout << "--------------------- HELP ---------------------" << endl;
		cout << "________________________________________________" << endl << endl;
		cout << "How to make a compression? Use the following expression:" << endl;
		cout << "Compress height width input.raw output.comp start=1 raise=4 blocksize=1" << endl;
		cout << "\t input.raw = the imgage that you want to compress." << endl;
		cout << "\t output.comp = the compressed imgage saved in a compressed file format." << endl;
		cout << "\t height = the height of your image." << endl;
		cout << "\t width = the width of your image." << endl;
		cout << "\t start = the start value of the quantization." << endl;
		cout << "\t raise = the raise value of the quantization." << endl;
		cout << "\t blocksize = the blocksize of dct." << endl;
		cout << "\t restriction: Height and width must be divisible by the blocksize." << endl;
		cout << "________________________________________________" << endl << endl;
		exit(0);
	}
	if (argc < 5 || argc > 8)
	{
		cout << "Error: Use \"Compress height width input.raw output.comp start=1 raise=4 blocksize=1\"." << endl;
		cout << "FOR HELP: \"Compress --help\"" << endl << endl; 
		exit(0);
	}
	int height = atoi(argv[1]);
	int width = atoi(argv[2]);
	int start = 1;
	int raise = 4;
	int blocksize = 1;
	if (height <= 0 || width <= 0){
		cout << "Error: Height and Width must be > 0." << endl;
		cout << "Error: Use \"Compress height width input.raw output.comp start=1 raise=4 blocksize=1\"." << endl;
		cout << "FOR HELP: \"Compress --help\"" << endl << endl; 
		exit(0);
	}

	if (argc >= 6)
	{
		start = atoi(argv[5]);
		if (start < 1)
		{
			cout << "Error: start >= 1." << endl;
			cout << "FOR HELP: \"Compress --help\"" << endl << endl;
			exit(0);
		}
	}
	if (argc >= 7)
	{
		raise = atoi(argv[6]);
		if (raise < 1)
		{
			cout << "Error: raise >= 1." << endl;
			cout << "FOR HELP: \"Compress --help\"" << endl << endl; 
			exit(0);
		}
	}
	if (argc >= 8)
	{
		blocksize = atoi(argv[7]);
		if (blocksize < 1)
		{
			cout << "Error: raise >= 1." << endl;
			cout << "FOR HELP: \"Compress --help\"" << endl << endl; 
			exit(0);
		}
		if ( (width % blocksize !=0) || (height % blocksize !=0) )
		{
			cout << "Error: Wrong blocksize." << endl;
			cout << "Error: Height and width must be divisible by the blocksize." << endl;
			cout << "FOR HELP: \"Compress --help\"" << endl << endl; 
			exit(0);
		}
	}

	cout << endl << "Begin Compressing " << argv[3] << " (" << height << "," << width << ")..." << endl;
	Compression *com = new Compression(string(argv[3]));
	com->setHeight(height);
	com->setWidth(width);
	com->setQStart(start);
	com->setQRaise(raise);
	com->setBlocksize(blocksize);
	com->renewMatrix(); // matrix herinstellen met nieuwe hoogte en breedte
	if (com->Read() == 0){
		cerr << "Error: File niet kunnen openen" << endl;
		cout << "FOR HELP: \"Compress --help\"" << endl << endl; 
		exit(0);
	}
	com->dct();
	com->quantisation();
	com->toArray();
	com->rle();
	com->toFile(string(argv[4]));
	delete com;
	return 0;
}