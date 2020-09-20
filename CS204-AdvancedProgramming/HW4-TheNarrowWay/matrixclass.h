#ifndef _matrixclass
#define _matrixclass

using namespace std;

template <class Type>
class Matrix2D {
private: 
	int rows, cols;
	Type ** data;
public:	
	Matrix2D<Type>(int r, int c);																//constructor
	Type GetIndex(int i, int j);																//getter
	void SetIndex(int i, int j, Type val);														//setter
	Matrix2D();																					//default constructor
	~Matrix2D();																				//destructor
	friend istream & operator >> <Type> (istream & is, Matrix2D<Type> & mat);					// ">>" operator
	friend ostream & operator << <Type> (ostream & is, Matrix2D<Type> & mat);					// "<<" operator
	Matrix2D<Type> & operator += ( Matrix2D<Type> & mat);										// "+=" operator
	Matrix2D<Type> & operator = ( Matrix2D<Type> & mat);										// "=" operator
	Matrix2D ( Matrix2D<Type> &);																//copy constructor
	friend Matrix2D<Type> operator + <Type> ( Matrix2D<Type> & lhs,  Matrix2D<Type> & rhs);
};

/*************** IMPLEMENTATION ***************/

template <class Type>
Matrix2D<Type>::Matrix2D()		//default constructor -> setting all the values to minimum values
{
	rows = 0;
	cols = 0;
	data = NULL;
}

template <class Type>
Matrix2D<Type>::~Matrix2D()		//destructor -> deleting all the matrix
{

	for(int i=0; i < rows; i++)
	{
		delete [] data[i];
	}
	delete [] data;			//to delete the last one
}

template <class Type>
istream & operator >> (istream & is, Matrix2D<Type>	& mat)		// ">>" operator
{
	int r=0, c=0;
	string line, line2;
	Type temp;
	while(getline(is,line))			// to determine # of rows & cols
	{
		r++;
		istringstream iss(line);
		if ( c == 0)
		{
			while(iss >> temp)
			{
				c++;
			}
		}
	}

	mat.rows = r;					//creating a matrix due to the # of rows and columns
	mat.cols = c;
	mat.data = new Type * [r];		
	for(int i=0; i < r; i++)
	{
		mat.data[i] = new Type[c];
	}

	is.clear();						
	is.seekg(0);					// move the cursor to the beginning of the file again

	r=0;							// filling the matrix with given file
	while(getline(is,line2))
	{
		istringstream iss2(line2);
		c=0;
		while(iss2 >> temp)
		{
			mat.data[r][c] = temp;
			c++;
		}
		r++;
	}
	return is;
}

template <class Type>
ostream & operator << (ostream & os, Matrix2D<Type> & mat)		// "<<" operator
{
	for(int i=0; i < mat.rows; i++)					// traversing the matrix and displaying vaules
	{
		for(int j=0; j < mat.cols; j++)
		{
			os << setw(5) << mat.data[i][j];		// setw(5) -> to have pretty and neat outputs 	
		}
		os << endl;
	}
	return os;
}

template <class Type>
Matrix2D<Type> & Matrix2D<Type>::operator += ( Matrix2D<Type> & mat)	// "+=" operator
{
	for(int i=0; i < mat.rows; i++)				// traversing the matrix and adding the values of another matrix to that one
	{
		for(int j=0; j < mat.cols; j++)
		{
			data[i][j] += mat.data[i][j];
		}
	}
	return *this;
}

template <class Type>
Matrix2D<Type> & Matrix2D<Type>::operator = ( Matrix2D<Type> & mat)		// "=" operator
{
	if(this != &mat)			
	{
		for(int i=0; i < rows; i++)			// deleting the matrix
		{
			delete [] data[i];
		}
		delete [] data;

		data = new Type * [mat.rows];		// creating the matrix with the appropriate # of rows and cols
		for(int i=0; i < mat.rows; i++)
		{
			data[i] = new Type [mat.cols];
		}


		for(int j=0; j < rows; j++)			// to equalize the matrices 
		{
			for(int k=0; k < cols; k++)
			{
				data[j][k] = mat.data[j][k];
			}
		}
	}
	return *this;
}

template <class Type>
Matrix2D<Type>::Matrix2D ( Matrix2D<Type> & copy)		// copy constructor
{
	rows = copy.rows;				//copying the # of rows and cols
	cols = copy.cols;

	data = new Type * [rows];		//creating a new matrix due to the # of rows and cols to make a deep copy
	for(int i=0; i < rows; i++)
	{
		data[i] = new Type[cols];
	}

	for (int i=0; i < rows; i++)	// "copy" part
	{
		for (int j=0; j < cols; j++)
		{
			data[i][j] = copy.data[i][j];
		}
	}
}

template <class Type>
Matrix2D<Type> operator + ( Matrix2D<Type> & lhs,  Matrix2D<Type> & rhs)		// "+" operator
{
	Matrix2D<Type> *last = new Matrix2D<Type>(lhs);

	for(int i=0; i < lhs.rows; i++)
	{
		for(int j=0; j < lhs.cols; j++)
		{
			last->data[i][j] += rhs.data[i][j];
		}
	}
	return *last;
}

/*************** GIVEN FUNCTIONS *************/

template <class Type>
Matrix2D<Type>::Matrix2D(int r, int c)			// constructor
{
	rows=r;
	cols=c;
	data = new Type* [r]; 

	for (int i = 0; i<rows; i++) 
		data[i] = new Type[cols];
}

template <class Type>
Type Matrix2D<Type>::GetIndex(int i, int j)		// getter -- accessor
{
	return data[i][j];
}

template <class Type>
void Matrix2D<Type>::SetIndex(int i, int j, Type value)		// setter -- mutator
{
	data[i][j] = value;
}

#endif