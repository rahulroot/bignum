#include <bits/stdc++.h>
using namespace std;

#define	MAXDIGITS	1000		/* maximum length bignum */ 

#define PLUS		1		/* positive sign bit */
#define MINUS		-1		/* negative sign bit */

typedef struct {
  int digits[MAXDIGITS];         /* represent the number */
	int signbit;			/* 1 if positive, -1 if negative */ 
  int lastdigit;			/* index of high-order digit */
} bignum;

void subtract_bignum(bignum &a, bignum &b, bignum &c);
void add_bignum(bignum &a, bignum &b, bignum &c);
int compare_bignum(bignum &a, bignum &b);
void digit_shift(bignum &n, int d);		/* multiply n by 10^d */
void multiply_bignum(bignum &a, bignum &b, bignum &c);
void zero_justify(bignum &n);

typedef unsigned long long int ullong;


void print_bignum(bignum n)
{
	int i;

	if (n.signbit == MINUS) 
		cout <<"- ";
	for (i=n.lastdigit; i>=0; i--)
		cout << n.digits[i];
	cout << endl;
}

void to_bignum(ullong s, bignum &n)
{
	int i;				/* counter */
	ullong t;				/* int to work with */

	if (s >= 0) 
		n.signbit = PLUS;
	else 
		n.signbit = MINUS;

	for (i=0; i<MAXDIGITS; i++) 
		n.digits[i] = 0;

	n.lastdigit = -1;

	t = llabs(s);

	while (t > 0) {
		n.lastdigit ++;
		int rem = ( t % 10);
		n.digits[n.lastdigit] = rem;
		t = t / 10;
	}

	if (s == 0) n.lastdigit = 0;
}

void initialize_bignum(bignum &n)
{
	to_bignum(0,n);
}


int max(int a, int b)
{
	if (a > b) 
		return(a); 
	else 
		return(b);
}

void subtract_bignum(bignum &a, bignum &b, bignum &c)
{
	int borrow;			/* has anything been borrowed? */
	int v;				/* placeholder digit */
	int i;				/* counter */

	initialize_bignum(c);

	if ( (a.signbit == MINUS) || (b.signbit == MINUS) ) 
	{
     b.signbit = -1 * b.signbit;
     add_bignum(a,b,c);
     b.signbit = -1 * b.signbit;
		 return;
  }

	if (compare_bignum(a,b) == PLUS) 
	{
		subtract_bignum(b,a,c);
		c.signbit = MINUS;
		return;
	}

  c.lastdigit = max(a.lastdigit,b.lastdigit);
  borrow = 0;

  for (i=0; i<=(c.lastdigit); i++) 
	{
		v = (a.digits[i] - borrow - b.digits[i]);
		if (a.digits[i] > 0)
			borrow = 0;
		if (v < 0) {
			v = v + 10;
			borrow = 1;
		}
    c.digits[i] = (char) v % 10;
  }

	zero_justify(c);
}

/*	c = a +-/* b;	*/

void add_bignum(bignum &a, bignum &b, bignum &c)
{
	int carry;			/* carry digit */
	int i;				/* counter */

	initialize_bignum(c);

	if (a.signbit == b.signbit) 
		c.signbit = a.signbit;
	else 
	{
		/* is a is -ve, subtract it from b and store the result in c */
		if (a.signbit == MINUS) 
		{
			a.signbit = PLUS;
			subtract_bignum(b,a,c);
			a.signbit = MINUS;
		} 
		else 
		{
			/* Here, b is -ve, subtract it from a and store the result in c */
      b.signbit = PLUS;
      subtract_bignum(a,b,c);
      b.signbit = MINUS;
		}
		return;
	}

	c.lastdigit = max(a.lastdigit,b.lastdigit)+1;
	carry = 0;

	for (i=0; i<=(c.lastdigit); i++) {
		int rem = (carry+ a.digits[i]+ b.digits[i])%10;
		c.digits[i] = rem;
		carry = (carry + a.digits[i] + b.digits[i]) / 10;
	}
	zero_justify(c);
}



int compare_bignum(bignum &a, bignum &b)
{
	int i;				/* counter */

	if ((a.signbit == MINUS) && (b.signbit == PLUS)) 
		return(PLUS);
	if ((a.signbit == PLUS) && (b.signbit == MINUS)) 
		return(MINUS);

	if (b.lastdigit > a.lastdigit) 
		return (PLUS * a.signbit);
	if (a.lastdigit > b.lastdigit) 
		return (MINUS * a.signbit);

	for (i = a.lastdigit; i>=0; i--) 
	{
		if (a.digits[i] > b.digits[i]) 
			return(MINUS * a.signbit);
		if (b.digits[i] > a.digits[i]) 
			return(PLUS * a.signbit);
	}

	return(0);
}

void zero_justify(bignum &n)
{
	while ((n.lastdigit > 0) && (n.digits[ n.lastdigit ] == 0))
		n.lastdigit --;

  if ( (n.lastdigit == 0) && (n.digits[0] == 0) )
		n.signbit = PLUS;	/* hack to avoid -0 */
}


void digit_shift(bignum &n, int d)		/* multiply n by 10^d */
{
	int i;				/* counter */

	if ((n.lastdigit == 0) && (n.digits[0] == 0)) 
		return;

	for (i=n.lastdigit; i>=0; i--)
		n.digits[i+d] = n.digits[i];

	for (i=0; i<d; i++) 
		n.digits[i] = 0;

	n.lastdigit = n.lastdigit + d;
}



void multiply_bignum(bignum &a, bignum &b, bignum &c)
{
	bignum row;			/* represent shifted row */
	bignum tmp;			/* placeholder bignum */
	int i,j;			/* counters */

	initialize_bignum(c);

	row = a;

	for (i=0; i<=b.lastdigit; i++) 
	{
		cout <<"ith iteration "  << i << endl;
		for (j=1; j<=b.digits[i]; j++) 
		{
			cout <<"jth iteration " << j <<' '<< b.digits[i] << endl;
			cout <<"adding c and row and put in tmp: " << endl;
			add_bignum(c,row,tmp);
			cout <<"row : "; print_bignum(row);
			cout <<"tmp : "; print_bignum(tmp);
			c = tmp;
			cout <<"c : "; print_bignum(c);
		}
		digit_shift(row,1);
		cout <<"After shifting row ";
		print_bignum(row);
	}
	c.signbit = a.signbit * b.signbit;
	zero_justify(c);
}


void divide_bignum(bignum &a, bignum &b, bignum &c)
{
  bignum row;                     /* represent shifted row */
  bignum tmp;                     /* placeholder bignum */
	int asign, bsign;		/* temporary signs */
  int i,j;                        /* counters */

	initialize_bignum(c);

	c.signbit = a.signbit * b.signbit;

	asign = a.signbit;
	bsign = b.signbit;

	a.signbit = PLUS;
  b.signbit = PLUS;

	initialize_bignum(row);
	initialize_bignum(tmp);

	c.lastdigit = a.lastdigit;

	for (i=a.lastdigit; i>=0; i--) 
	{
		digit_shift(row,1);
		row.digits[0] = a.digits[i];
		c.digits[i] = 0;
		while (compare_bignum(row,b) != PLUS) 
		{
			c.digits[i] ++;
			subtract_bignum(row,b,tmp);
			row = tmp;
		}
	}
	zero_justify(c);
	a.signbit = asign;
	b.signbit = bsign;
}



int main()
{
	ullong a,b;
	bignum n1,n2,n3,zero;
	freopen("./sample.txt", "r", stdin);

	while ( cin >> a >> b ) 
	{
		cout <<"a = " << a <<" b = " << b << endl;
		to_bignum(a,n1);
		to_bignum(b,n2);

		add_bignum(n1,n2,n3);
		cout << "addition -- ";
		print_bignum(n3);

		cout <<"compare_bignum a ? b = " << compare_bignum(n1, n2) << endl;

		subtract_bignum(n1,n2,n3);
		cout <<"subtraction -- ";
		print_bignum(n3);

    multiply_bignum(n1,n2,n3);
		cout <<"multiplication -- ";
    print_bignum(n3);

		to_bignum(0,zero);
		if (compare_bignum(zero, n2) == 0)
			cout <<"division -- NaN" << endl;
    else 
		{
			divide_bignum(n1,n2,n3);
			cout <<"division -- ";
     	print_bignum(n3);
		}
		cout <<"--------------------------" << endl;
	}
	return 0;
}

