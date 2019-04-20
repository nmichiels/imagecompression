#ifndef MATRIX
#define MATRIX 1
#include <math.h>

template <typename E>
class Matrix{
public:
/*	Matrix(int height, int width);
	Matrix(const Matrix& m);
	void zeros();
	void ones();
	void eye();
*/	int Height(){return height;}
	int Width() {return width;}
	void setHeight(int height){this->height =  height;}
	void setWidth(int width) {this->width =  width;}
/*	E* operator[](int i);
	const Matrix operator*(const Matrix &m);
	const Matrix operator*=(const Matrix &m);
	const Matrix operator+(const Matrix &m);
	const Matrix operator+=(const Matrix &m);
	const Matrix operator-(const Matrix &m);
	const Matrix operator-=(const Matrix &m);
	const Matrix operator= (const Matrix &m);
	const Matrix operator= (const E** &m);
	const Matrix transpose();
*/

	Matrix(int height=512, int width=512):width(width),height(height){
		matrix =new E*[height];
		for(int i=0;i<height;i++)
			matrix[i]=new E[width];
	}
 Matrix( Matrix& m){

		matrix =new E*[height=m.Height()];
		width=m.Width();
		for(int i=0;i<height;i++)
			matrix[i]=new E[width];

		for(int i=0;i<height;i++)
			for(int j=0; j<width;j++)
				matrix[i][j]=m[i][j];
	}
 void zeros(){
		for(int i=0;i<height;i++)
			for(int j=0;j<width;j++)
				matrix[i][j]=0;
	}
 void Matrix<E>::ones(){
		for(int i=0;i<height;i++)
			for(int j=0;j<width;j++)
				matrix[i][j]=0;
	}
 void Matrix<E>::renew(){
	matrix =new E*[height];
		for(int i=0;i<height;i++)
			matrix[i]=new E[width];
	for(int i=0;i<height;i++)
			for(int j=0;j<width;j++)
				matrix[i][j]=0;
 }
void eye(){
		for(int i=0;i<height;i++)
			for(int j=0;j<width;j++)
				if(i==j)
					matrix[i][j]=1;
				else
					matrix[i][j]=0;
	}
E* operator[](int i){
		return matrix[i];
	}
const Matrix operator*(const Matrix &m){
		assert(m.Height()==width);
		Matrix m2(height,m.Width);
		m2.zeros();
		for(int i =0;i< height;i++)
			for(int j=0; j<m.width;j++)
				for(int k=0;k<width;k++)
					m2[i][j] += matrix[i][k]*m[k][j];
		return m2;
	}
 const Matrix operator*=(const Matrix &m){
		Matrix m2(height,m.Width);
		m2=*this;
		*this=m2*m;
		return *this;
	}
const Matrix operator+(const Matrix &m){
		assert(m.Height()==height && width==m.Width());
		Matrix m2(height,width);
		for(int i =0;i< height;i++)
			for(int j=0; j<m.width;j++)
					m2[i][j] = matrix[i][j]+m[i][j];
		return m2;
	}
const Matrix operator+=(const Matrix &m){
		Matrix m2(height,m.Width);
		m2=*this;
		*this=m2+m;
		return *this;
	}
const Matrix operator-(const Matrix &m){
		assert(m.Height()==height && width==m.Width());
		Matrix m2(height,width);
		for(int i =0;i< height;i++)
			for(int j=0; j<m.width;j++)
					m2[i][j] = matrix[i][j]-m[i][j];
		return m2;
	}
 const Matrix operator-=(const Matrix &m){
		Matrix m2(height,m.Width);
		m2=*this;
		*this=m2-m;
		return *this;
	}
const Matrix operator= (Matrix &m){
		if(matrix != NULL)
		{
			for(int i=0;i<height;i++)
				delete [] matrix[i];
			delete [] matrix;
		}
		matrix =new E*[height=m.Height()];
		width=m.Width();
		for(int i=0;i<height;i++)
			matrix[i]=new E[width];
		for(int i=0;i<height;i++)
			for(int j=0; j<width;j++)
				matrix[i][j]=m[i][j];
		return *this;
	}
 const Matrix operator= (const E** &m){

	}
Matrix transpose(){
		Matrix m(width,height);
		for(int i=0; i<width ; i++)
			for(int j=0;j<height;j++)
				m[j][i]=matrix[i][j];
		return m;
	}

Matrix dctmultiply1(Matrix<double> &m){
	Matrix<double> m2(height,width);
	m2.zeros();
	for (int i=0;i<height;i+=m.Height())
		for(int j=0;j<width;j+=m.Width())
			for(int a=0;a<m.Height();a++)
				for(int b=0;b<m.Width();b++)
					for(int c=0;c<m.Height();c++)
						m2[i+a][j+b]+=(m[a][c]*(double)matrix[c+i][j+b]);

	Matrix<double> m3(height,width);
	m3.zeros();
	m=m.transpose();
	for (int i=0;i<height;i+=m.Height())
		for(int j=0;j<width;j+=m.Width())
			for(int a=0;a<m.Height();a++)
				for(int b=0;b<m.Width();b++)
					for(int c=0;c<m.Height();c++)
						m3[i+a][j+b]+=(m2[i+a][c+j]*m[c][b]);

	Matrix<int> m4(height,width);
	for(int i=0;i<height;i++)
		for(int j=0;j<width;j++)
			m4[i][j]=(int)(m3[i][j]+0.5);
	return m4;
}
 

Matrix quanti(Matrix &m){
	Matrix m3(height,width);
	m3.zeros();
	for (int i=0;i<height;i+=m.Height())
		for(int j=0;j<width;j+=m.Width()){
			for(int a=0;a<m.Height();a++)
				for(int b=0;b<m.Width();b++)
					m3[i+a][j+b]=(int)((double(matrix[i+a][j+b])/(double(m[a][b])))+0.5);
			}
	return m3;
}

int maximum(){
	int m=0;
	for(int i=0;i<height;i++)
		for(int j=0;j<width;j++)
			if(m<matrix[i][j])
				m=matrix[i][j];
return m;
}

int minimum(){
	int m=0;
	for(int i=0;i<height;i++)
		for(int j=0;j<width;j++)
			if(m>matrix[i][j])
				m=matrix[i][j];
return m;
}

Matrix antiquanti(Matrix &m){
	Matrix m3(height,width);
	m3.zeros();
	for (int i=0;i<height;i+=m.Height())
		for(int j=0;j<width;j+=m.Width())
			for(int a=0;a<m.Height();a++)
				for(int b=0;b<m.Width();b++)
					m3[i+a][j+b]=matrix[i+a][j+b]*m[a][b];
	return m3;
}

~Matrix(){
	for(int i=0;i<height;i++)
			delete [] matrix[i];
		delete [] matrix;
}

void zigzag(E* rij, int height, int width){
	int move=-1,ph=0,rp=0,mx=max(width,height)*2-1;
	for( int a =0; a<this->height; a+=height)
		for( int b=0; b<this->width; b+=width,move=-1,ph=0)
			for(int i=0 ;i<mx;i++){//telkens zijn de coordinaten samen i
				for(;ph>=0 && ph<=i &&ph<height && (i-ph)<width;ph+=move)
					rij[rp++]=matrix[a+ph][b+i-ph];
				ph-=move;
				if( (ph+1)<height&&((move==-1 && (i-ph+1)>=width)||(move==1 && (i-ph)<=0))) ph++;
				move=-move;//ph wisselt af tsn naar boven en naar beneden
			}
}

void antizigzag(E* rij, int height, int width){
	int move=-1,ph=0,rp=0,mx=max(width,height)*2-1;
	for( int a =0; a<this->height; a+=height)
		for( int b=0; b<this->width; b+=width,move=-1,ph=0)
			for(int i=0 ;i<mx;i++){//telkens zijn de coordinaten samen i
				for(;ph>=0 && ph<=i &&ph<height && (i-ph)<width;ph+=move)
					matrix[a+ph][b+i-ph]=rij[rp++];
				ph-=move;
				if( (ph+1)<height&&((move==-1 && (i-ph+1)>=width)||(move==1 && (i-ph)<=0))) ph++;
				move=-move;//ph wisselt af tsn naar boven en naar beneden
			}
}

void qInitialise( int start, int raise){
	int move=1,ph=0,rp=0,mx=max(width,height)*2-1,current=start;
	matrix[0][0]=start;
	for(int i=1 ;i<mx;i++){//telkens zijn de coordinaten samen i
		for(;ph>=0 && ph<=i &&ph<height && (i-ph)<width;ph+=move)
			matrix[ph][i-ph]=current;
		ph-=move;
		current+=raise;
		if( (ph+1)<height&&((move==-1 && (i-ph+1)>=width)||(move==1 && (i-ph)<=0))) ph++;
			move=-move;//ph wisselt af tsn naar boven en naar beneden
	}
}

void toDctMatrix(){
	for(int i=0;i<height;i++)
		for(int j=0;j<width;j++)
		{
			if(i==0)
				matrix[i][j]=sqrt(1.0/(double)height)*cos((2.0*(double)j+1.0)*(double)i*3.14/(2.0*(double)height));
			else
				matrix[i][j]=sqrt(2.0/(double)height)*cos((2.0*(double)j+1.0)*(double)i*3.14/(2.0*(double)height));
		}
}



private:
	E** matrix;
	int width;
	int height;
	



};
#endif