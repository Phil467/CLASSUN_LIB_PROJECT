
#include "utilities.h"

int TAB_PRINT_ID;

double fxi(double xi, double*cf, size_t P)
{
    double y = 0;
    for (int i=P-1; i>=0; i--)
    {
        y += cf[P-1-i]*(pow(xi, i));
    }
	return y;
}

double* fx(double*x, size_t n, double*cf, size_t P)
{
    double*y = (double*)malloc(sizeof(double)*n);
	for (int j=0; j<n; j++)
	{
		double k=0;
		for (int i=P-1; i>=0; i--)
		{
			k += cf[P-1-i]*(pow(x[j], i));
		}
		y[j] = k;
	}
	return y;
}

void fx2(double*x, double*& y, size_t n, double*cf, size_t P)
{
    for (int j=0; j<n; j++)
	{
		double k=0;
		for (int i=P-1; i>=0; i--)
		{
			k += cf[P-1-i]*(pow(x[j], i));
		}
		y[j] = k;
	}
}

void fx21(double*x, double*& y, size_t id1, size_t id2, double*cf, size_t P)
{
    for (int j=id1; j<id2; j++)
	{
		double k=0;
		for (int i=P-1; i>=0; i--)
		{
			k += cf[P-1-i]*(pow(x[j-id1], i));
		}
		y[j] = k;
	}
}


double* getIntPowList(size_t n, double p)
{
	double* l = (double*)malloc(sizeof(double)*n);
	for (int i=1; i<n+1; i++)
		l[i-1] = pow((double)i,p);
	return l;
}

double* getCumulList(double*l, size_t n)
{
	double*r = (double*)malloc(sizeof(double)*n);
	r[0] = l[0];
	for (int i = 1; i<n; i++)
		r[i] = r[i-1] + l[i];
	return r;
}


void printArray1D(double* arr, size_t n, const char*title, size_t wordLen)
{
    if (strcasecmp(title,"Table")==0)
        std::cout<<"Table id : "<<TAB_PRINT_ID<<"\n";
    else
        std::cout<<title<<"\n";
    for (int i=0; i<n; i++)
    {
        std::cout<<setw(wordLen)<<arr[i];
    }
    std::cout<<"\n\n";
    TAB_PRINT_ID++;
}

void printArray1D(size_t* arr, size_t n, const char*title, size_t wordLen)
{
    if (strcasecmp(title,"Table")==0)
        std::cout<<"Table id : "<<TAB_PRINT_ID<<"\n";
    else
        std::cout<<title<<"\n";
    for (int i=0; i<n; i++)
    {
        std::cout<<setw(wordLen)<<arr[i];
    }
    std::cout<<"\n\n";
    TAB_PRINT_ID++;
}

void printArray2D(double** arr, size_t nx, size_t ny, const char*title, size_t wordLen)
{
    if (strcasecmp(title,"Table")==0)
        std::cout<<"Table id : "<<TAB_PRINT_ID<<"\n";
    else
        std::cout<<title<<"\n";
    for (int j=0; j<ny; j++)
    {
    	for (int i=0; i<nx; i++)
		{
			std::cout<<setw(wordLen)<<setprecision(2)<<arr[j][i]<<"  ";
		}
    	std::cout<<"\n";
    }
    std::cout<<"\n\n";
    TAB_PRINT_ID++;
}

void printArray2D(size_t** arr, size_t nx, size_t ny, const char*title, size_t wordLen)
{
    if (strcasecmp(title,"Table")==0)
        std::cout<<"Table id : "<<TAB_PRINT_ID<<"\n";
    else
        std::cout<<title<<"\n";
    for (int j=0; j<ny; j++)
    {
    	for (int i=0; i<nx; i++)
		{
			std::cout<<setw(wordLen)<<arr[j][i]<<"  ";
		}
    	std::cout<<"\n";
    }
    std::cout<<"\n\n";
    TAB_PRINT_ID++;
}

Fraction findFraction(double nb, double prec)
{
	double anb = fabs(nb), r=1.0;
	int n1 = int(anb);
	int n2 = n1 + 1;
	int i=0, j=0;

	while (abs(r) > prec)
	{
		if (r > 0)
			i = i+1;
		if (r < 0)
			j = j+1;
		r = double(n1*i + n2*j)/(i+j) - anb;
		// if j == 100 or i == 100:
			// break
	}
	Fraction f = {int64_t((nb/anb)*(n1*i + n2*j)), int64_t(i+j)};

	return f;
}

Fraction* findFractionList(double*nbs, size_t n, double prec)
{
	Fraction*frac = (Fraction*)malloc(sizeof(Fraction)*n);
	for (int i=0; i<n; i++)
		frac[i] = findFraction(nbs[i], prec);
	return frac;
}

void printFactionsArray(Fraction* arr, size_t n, const char*title, size_t wordLen)
{
    if (strcasecmp(title,"Table")==0)
        std::cout<<"Table id : "<<TAB_PRINT_ID<<"\n";
    else
        std::cout<<title<<"\n";
    for (int i=0; i<n; i++)
    {
        std::cout<<arr[i].a<<"/"<<arr[i].b<<"  ";
    }
    std::cout<<"\n\n";
    TAB_PRINT_ID++;
}


double* linspace(double a, double b, size_t n)
{
    if (n<2)
    {
        std::cout<<"\nlinspace message : n must be greater than 2 !\n";
        exit(0);
    }
    else
    {
        double *r = (double*)malloc(sizeof(double)*(n+1));
        double step = (b-a)/(n-1);
        size_t j=0;
        for (double i=a; i<=b; i+=step)
        {
            r[j] = i;
            j++;
        }
        return r;
    }
}

double* linspaceExcb(double a, double b, size_t n)
{
    if (n<1)
    {
        std::cout<<"\nError from linspaceExcb() : n must be greater than 2 !\n";
        exit(0);
    }
    else
    {
        double *r = (double*)malloc(sizeof(double)*(n+1));//normally n
        double step = (b-a)/n;
        size_t j=0;
        for (double i=a; i<b; i+=step)
        {
            r[j] = i;
            j++;
        }
        return r;
    }
}



double* array2dToArray1D2(double** a2d, size_t nx, size_t ny)
{
	double *a1d = (double*)malloc(sizeof(double)*nx*ny);
	size_t k;
	for(size_t j = 0; j<ny; j++)
	{
		for(size_t i = 0; i<nx; i++)
		{
			k = j*nx + i;
			a2d[j][i] = a1d[k];
		}
	}
	return a1d;
}


void array2dToArray1D(double** a2d, size_t nx, size_t ny, double*& a1d)
{
	size_t k;
	for(size_t j = 0; j<ny; j++)
	{
		for(size_t i = 0; i<nx; i++)
		{
			k = j*nx + i;
			a2d[j][i] = a1d[k];
		}
	}
}

size_t firstDegreePyramidalArrayIndexLevel(size_t level)
{
	return (level*(level+1)/2);
}

size_t secondDegreePyramidalArrayIndexLevel(size_t level)
{
	//double idf = level*level*level/3.0 + level*level/2.0 + level/6.0 , dec = idf - (double)(int)(idf);
	double idf = level*(level*(level/3.0 + 0.5) + 1/6.0) , dec = idf - (double)(int)(idf);
	size_t id = size_t(idf);
	if (dec >= 0.5)
		id += 1;
	return id;
}

double getRandomDouble(int64_t min, int64_t max, size_t exponent)
{
	return (min + rand()%(max-min))/pow(10,double(exponent));
}

double*getRandomDoubleArray1D(size_t n, int64_t min, int64_t max, size_t exponent)
{
	double*arr = (double*)malloc(n*sizeof(double));
	for (int i=0; i<n; i++)
	{
		arr[i] = getRandomDouble(min, max, exponent);
	}
	return arr;
}

double**getRandomDoubleArray2D(size_t nx, size_t ny, int64_t min, int64_t max, size_t exponent)
{
	double**arr = (double**)malloc(ny*sizeof(double*));
	for (int i=0; i<ny; i++)
	{
		arr[i] = getRandomDoubleArray1D(nx, min, max, exponent);
	}
	return arr;
}

double sum(double*arr, size_t n)
{
	double s=0.0;
	for (int i=0; i<n; i++)
		s+=arr[i];
	return s;
}

double round(double nb, size_t ndigits)
{
	double pw = pow(10,(double)ndigits),  nb1 = nb*pw;
	double decimal = nb1-(double)(int)nb1;
	if (decimal >= 0.5)
		nb1 += 1;
	return (double)((int)nb1)/pw;
}

double roundZero(double nb)
{
	double nb1 = nb, decimal = nb-(double)(int)nb;
	if (decimal >= 0.5)
		nb1 += 1;
	return (double)((int)nb1);
}

double* arrayRound(double*arr, size_t n, size_t ndigits)
{
	double*arr2 = (double*)malloc(n*sizeof(double));
	for (int i=0; i<n; i++)
		arr2[i] = round(arr[i], ndigits);
	return arr2;
}

void arrayRound2(double*&arr, size_t n, size_t ndigits)
{
	double*arr2 = (double*)malloc(n*sizeof(double));
	for (int i=0; i<n; i++)
		arr2[i] = round(arr2[i], ndigits);
}

double* arrayBoost(double* arr, size_t n, double fact)
{
	double*arr2 = (double*)malloc(n*sizeof(double));
	for (int i=0; i<n; i++)
		arr2[i] = arr[i]*fact;
	return arr2;
}

void minmax1D(double*arr, size_t n, size_t& minval, size_t& maxval)
{
	minval = arr[0];
	maxval = arr[0];
	for (int i=0; i<n; i++)
	{
		if(minval > arr[i])
			minval = arr[i];
		if(maxval < arr[i])
			maxval = arr[i];
	}
}

void minmax2D(double**arr, size_t nx, size_t ny, double& minval, double& maxval)
{
	minval = arr[0][0];
	maxval = arr[0][0];
	for (int j=0; j<ny; j++)
	{
		for (int i=0; i<nx; i++)
		{
			if(minval > arr[j][i])
				minval = arr[j][i];
			if(maxval < arr[j][i])
				maxval = arr[j][i];
		}
	}
}

void arrayBoost2(double*& arr, size_t n, double fact)
{
	for (int i=0; i<n; i++)
		arr[i] = arr[i]*fact;

}

/*void setStrRGB(char*str,   size_t pos,  csRGBA c)
{
	*(str+pos)=c.b;
	*(str+pos+1)=c.g;
	*(str+pos+2)=c.r;
	*(str+pos+3)=0;
}*/

void setStrRGB2(char*str,   size_t pos,  size_t r, size_t g, size_t b)
{
	*(str+pos)=(unsigned char)r;
	*(str+pos+1)=(unsigned char)g;
	*(str+pos+2)=(unsigned char)r;
	*(str+pos+3)=0;
}

size_t**fullUInt2D(size_t nx, size_t ny, size_t nb)
{
	size_t**arr = (size_t**)malloc(sizeof(size_t*)*ny);
	for (int j=0; j<ny; j++)
	{
		arr[j] = (size_t*)malloc(sizeof(size_t)*nx);
		for (int i=0; i<nx; i++)
		{
			arr[j][i]=nb;
		}
	}
	return arr;
}

int**fullInt2D(size_t nx, size_t ny, int nb)
{
	int**arr = (int**)malloc(sizeof(int*)*ny);
	for (int j=0; j<ny; j++)
	{
		arr[j] = (int*)malloc(sizeof(int)*nx);
		for (int i=0; i<nx; i++)
		{
			arr[j][i]=nb;
		}
	}
	return arr;
}

double**fullDouble2D(size_t nx, size_t ny, double nb)
{
	double**arr = (double**)malloc(sizeof(double*)*ny);
	for (int j=0; j<ny; j++)
	{
		arr[j] = (double*)malloc(sizeof(double)*nx);
		for (int i=0; i<nx; i++)
		{
			arr[j][i]=nb;
		}
	}
	return arr;
}


double* trimDouble1D(double*map, size_t nx, size_t ny, int x, int cx)
{
    double*ret=0;
    if(x>=0 && x<=nx && cx>x && cx<nx)
    {
        double*ret=(double*)malloc(cx*sizeof(double));
        for(int i=0; i<cx; i++)
        {
            ret[i] = map[i+x];
        }
    }
    else
    {
        std::cout<<"From trimDouble1D() : Invalid trimming sizes."<<std::endl;
        ret = map;
    }
    return ret;
}

int* trimInt1D(int*map, size_t nx, size_t ny, int x, int cx)
{
    int*ret=0;
    if(x>=0 && x<=nx && cx>x && cx<nx)
    {
        int*ret=(int*)malloc(cx*sizeof(int));
        for(int i=0; i<cx; i++)
        {
            ret[i] = map[i+x];
        }
    }
    else
    {
        std::cout<<"From trimInt1D() : Invalid trimming sizes."<<std::endl;
        ret = map;
    }
    return ret;
}

char* trimDouble1D(char*map, size_t nx, size_t ny, int x, int cx)
{
    char*ret=0;
    if(x>=0 && x<=nx && cx>x && cx<nx)
    {
        char*ret=(char*)malloc(cx*sizeof(char));
        for(int i=0; i<cx; i++)
        {
            ret[i] = map[i+x];
        }
    }
    else
    {
        std::cout<<"From trimDouble1D() : Invalid trimming sizes."<<std::endl;
        ret = map;
    }
    return ret;
}

double** trimDouble2D(double**map, size_t nx, size_t ny, int x, int y, int cx, int cy)
{
    double**ret=0;
    if(x>=0 && x<=nx && y>=0 && y<=ny && cx>x && cx<nx && cy>y && cy<=ny)
    {
        double**ret=(double**)malloc(cy*sizeof(double*));
        for(int j=0; j<cy; j++)
        {
            ret[j] = (double*)malloc(cx*sizeof(double));
            for(int i=0; i<cx; i++)
                ret[j][i] = map[j+y][i+x];
        }
    }
    else
    {
        std::cout<<"From trimDouble2D() : Invalid trimming sizes."<<std::endl;
        ret = map;
    }
    return ret;
}

int** trimInt2D(int**map, size_t nx, size_t ny, int x, int y, int cx, int cy)
{
    int**ret=0;
    if(x>=0 && x<=nx && y>=0 && y<=ny && cx>x && cx<nx && cy>y && cy<=ny)
    {
        int**ret=(int**)malloc(cy*sizeof(int*));
        for(int j=0; j<cy; j++)
        {
            ret[j] = (int*)malloc(cx*sizeof(int));
            for(int i=0; i<cx; i++)
                ret[j][i] = map[j+y][i+x];
        }
    }
    else
    {
        std::cout<<"From trimInt2D() : Invalid trimming sizes."<<std::endl;
        ret = map;
    }
    return ret;
}

char** trimChar2D(char**map, size_t nx, size_t ny, int x, int y, int cx, int cy)
{
    char**ret=0;
    if(x>=0 && x<=nx && y>=0 && y<=ny && cx>x && cx<nx && cy>y && cy<=ny)
    {
        char**ret=(char**)malloc(cy*sizeof(char*));
        for(int j=0; j<cy; j++)
        {
            ret[j] = (char*)malloc(cx*sizeof(char));
            for(int i=0; i<cx; i++)
                ret[j][i] = map[j+y][i+x];
        }
    }
    else
    {
        std::cout<<"From trimInt2D() : Invalid trimming sizes."<<std::endl;
        ret = map;
    }
    return ret;
}




