char *toBinary(int x)
{
	int i, r, count;
	char *a;
	count = 0;
	a = (char*)malloc(8+1);
	for(i = 7; i>=0; i--)
	{
		r = x >> i;
		if (r & 1)
			*(a+count) = 1 + '0';
		else
			*(a+count) = 0 + '0';
			
		count = count + 1;	
	}
	*(a+count) = '\0';
	return a; 
}

char toChars(char *resString)
{
	int i;
	char result = 0;
	if(resString == NULL)
		return;
	for(i=0; i<8; i++)
	{
		if(resString[i]=='1')
		    {
		      result |= (1<< (7-i) );
		    }
  	}
  	return result;
}

int toDecimal(char *resString)
{
	int i, n=0;
	if(resString == NULL)
	return;
	int count = 0;
	for(i=0; i<8; i++) {
		if ( resString[i] == '1' ) 
		    n = n + pow(2, 7 - count );
		count++; 
	}
	return n;
}
