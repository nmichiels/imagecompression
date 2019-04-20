#include <iostream>
using namespace std;

#include <stdlib.h>

#include "Decompression.h"

#include "matrix.h"


int main(int argc, char* argv[])
{
	cout << endl;
	if ( (argc == 2) && (string(argv[1]).compare("--help") == 0) )
	{
		// HELP
		cout << "--------------------- HELP ---------------------" << endl;
		cout << "________________________________________________" << endl << endl;
		cout << "How to make a decompression? Use the following expression: " << endl;
		cout << "Decompress input.comp output.raw" << endl;
		cout << "\t input.comp = the compressed image that you want to decompress." << endl;
		cout << "\t output.raw = the decompressed image saved in a readable *.raw file." << endl;
		cout << "________________________________________________" << endl << endl;
		exit(0);
	}
	if (argc != 3)
	{
		cout << "Error: Use \"Decompress input.comp output.raw." << endl;
		cout << "FOR HELP: \"Decompress --help\"" << endl << endl; 
		exit(0);
	}
	
	Decompression *deco=new Decompression(string(argv[1]));
	if (deco->Open() == 0){
		cerr << "Main: File niet kunnen openen" << endl;
		cout << "FOR HELP: \"Decompress --help\"" << endl << endl; 
		exit(0);
	}
	deco->Read();
	deco->toMatrix();
	deco->antiQuantisation();
	deco->antiDct();
	deco->toFile(string(argv[2]));

	// Image Properties
	cout << "--------------------- Image Properties ---------------------" << endl;
	cout << "____________________________________________________________" << endl << endl;
	cout << "\t Height : " << deco->getHeight() << endl;
	cout << "\t Width : " << deco->getWidth() << endl;
	cout << "\t Quantisation Start : " << deco->getQStart() << endl;
	cout << "\t Quantisation Raise : " << deco->getQRaise() << endl;
	cout << "\t Blocksize : " << deco->getBlocksize() << endl;
	cout << "____________________________________________________________" << endl << endl;

	delete deco;
	return 0;
}