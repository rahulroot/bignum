#include "bignum.h"

/*
 * Big number stored like arg[0] = contains length of string.
 * arg[1....arg[0]-1 ] = str read from tail 
 */

void print_big(BigN arg)
{
	int j = 1;
	while(arg[j] == 0)
		j++;
	for(int i = j; i < arg[0]; ++i )
		cout << arg[i];
	cout << endl;
}

void read_big(const string &str, BigN arg)
{
	arg[0] = str.size();
	for(int i = 1; i <= arg[0]; ++i)
		arg[i] = str[arg[0]-i] - '0';
}

int compare_big(BigN a, BigN b)
{
	int sign = 0;
  if ( a[0] < b[0] )
  {
    sign = -1;
  }
  else if ( a[0] == b[0] )
  {
    int len = a[0];
    for( int i = len; i > 0; --i)
    {
      if ( a[i] < b[i] )
      {
        sign = -1;
        return sign;
      }
    }
  }
  return sign;
}

/* this is private method */
void sub_big(BigN a, BigN b, BigN result)
{
	int len = a[0] > b[0] ? a[0] : b[0];
  int j = 1;
  for(int i = 1; i <= len; ++i)
  {
    if( a[i] < b[i] )
    {
      int k = i;
      while(a[++k] == 0)
        ;
      a[k]--;
      k--;
      while(k > i)
      {
        a[k] = 9;
        k--;
      }
      a[i] = a[i] + 10;
      result[j] = a[i] - b[i];
    }
    else
    {
      result[j] = a[i] - b[i];
    }
    j++;
    result[0]++;
  }
  while( (result[0] > 1) && ( result[result[0]] == 0))
    --result[0];
}

/* use this method to calculate the substraction on big number */
void solve_sub(BigN a, BigN b, BigN result)
{
	int sign = compare();
  if(sign < 0)
    sub(b, a);
  else
    sub(a, b);

  if(sign < 0)
    cout << '-';
  print(result);
}

void add_big(BigN a, BigN b, BigN result)
{
	 int len = a[0] > b[0] ? a[0] : b[0];
   int i, c = 0;

   for(i=1; i<=len; ++i)
   {
     int newdig = a[i] + b[i] + c;
     if(newdig > 9)
     {
       result[i] = newdig % 10;
       c = 1;
     }
     else
     {
       result[i] = newdig;
       c = 0;
     }
     result[0]++;
   }

   if(c != 0)
     result[++result[0]] = c;
}

void div_big(BigN num, int div, BigN quo, int &rem)
{
	rem = 0;
  memset(&quo, 0, sizeof(quo));
  for(int i = 1; i <= num[0]; ++i)
  {
    rem = (rem * 10) + num[i];
    quo[i] = rem / div;
    rem -= (quo[i] * div);
    ++quo[0];
  }

}
