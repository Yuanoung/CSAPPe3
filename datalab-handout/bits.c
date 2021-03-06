/* 
 * CS:APP Data Lab 
 * 
 * <Please put your name and userid here>
 * 
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.  
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:
 
  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code 
  must conform to the following style:
 
  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>
    
  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.

 
  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting if the shift amount
     is less than 0 or greater than 31.


EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }

FLOATING POINT CODING RULES

For the problems that require you to implement floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants. You can use any arithmetic,
logical, or comparison operations on int or unsigned data.

You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions.
  4. Use any form of casting.
  5. Use any data type other than int or unsigned.  This means that you
     cannot use arrays, structs, or unions.
  6. Use any floating point data types, operations, or constants.


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to 
     check the legality of your solutions.
  2. Each function has a maximum number of operations (integer, logical,
     or comparison) that you are allowed to use for your implementation
     of the function.  The max operator count is checked by dlc.
     Note that assignment ('=') is not counted; you may use as many of
     these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. Use the BDD checker to formally verify your functions
  5. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies 
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 * 
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the BDD checker to formally verify that your solutions produce 
 *      the correct answers.
 */

#endif

/* 
 * absVal - absolute value of x
 *   Example: absVal(-1) = 1.
 *   You may assume -TMax <= x <= TMax
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 10
 *   Rating: 4
 * 
 * if x < 0, should return ~x + 1 = ((0xFFFFFFFF + 0) ^ x) + 1
 * else return x                  = ((0xFFFFFFFF + 1) ^ x) + 0
 * 
 * ps: ~x = 0xFFFFFFFF ^ x
 */
int absVal(int x)
{
  int mask = ~0;             // 0xFFFFFFFF
  int neg = (x >> 31) & 0x1; // x is negative？
  return ((mask + !neg) ^ x) + neg;
}

/* 
 * addOK - Determine if can compute x+y without overflow
 *   Example: addOK(0x80000000,0x80000000) = 0,
 *            addOK(0x80000000,0x70000000) = 1, 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3
 * 
 * sum = x + y
 * 当x，y符号相同，sum与x（或者y）符号不同时，发生溢出
 */
int addOK(int x, int y)
{
  int sum = x + y;

  int neg_overflow = ((x & y & ~sum) >> 31) & 0x1;  // 是否负溢出
  int pos_overflow = ((~x & ~y & sum) >> 31) & 0x1; // 是否正溢出

  return !(neg_overflow | pos_overflow);
}

/* 
 * allEvenBits - return 1 if all even-numbered bits in word set to 1
 *   where bits are numbered from 0 (least significant) to 31 (most significant)
 *   Examples allEvenBits(0xFFFFFFFE) = 0, allEvenBits(0x55555555) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 2
 * 
 * 题目求的是，所有偶数位上都为1时，返回1,否则返回0.
 * 
 * x &= x >> 16;
 * x &= x >> 8;
 * 
 * 如果在偶数位上有一个为0,那么都会反应到最低字节上。
 */
int allEvenBits(int x)
{
  int mask = 0x55; // 0101 0101

  x &= x >> 16;
  x &= x >> 8;
  return !((x & mask) ^ mask);
}

/* 
 * allOddBits - return 1 if all odd-numbered bits in word set to 1
 *   where bits are numbered from 0 (least significant) to 31 (most significant)
 *   Examples allOddBits(0xFFFFFFFD) = 0, allOddBits(0xAAAAAAAA) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 2
 */
int allOddBits(int x)
{
  int mask = 0xAA; // 1010 1010

  x &= x >> 16;
  x &= x >> 8;
  return !((x & mask) ^ mask);
}

/* 
 * anyEvenBit - return 1 if any even-numbered bit in word set to 1
 *   where bits are numbered from 0 (least significant) to 31 (most significant)
 *   Examples anyEvenBit(0xA) = 0, anyEvenBit(0xE) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 2
 */
int anyEvenBit(int x)
{
  int mask = 0x55; // 0101 0101

  x |= x >> 16;
  x |= x >> 8;
  return !!(x & mask);
}

/* 
 * anyOddBit - return 1 if any odd-numbered bit in word set to 1
 *   where bits are numbered from 0 (least significant) to 31 (most significant)
 *   Examples anyOddBit(0x5) = 0, anyOddBit(0x7) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 2
 */
int anyOddBit(int x)
{
  int mask = 0xAA; // 1010 1010

  x |= x >> 16;
  x |= x >> 8;
  return !!(x & mask);
}

/* 
 * bang - Compute !x without using !
 *   Examples: bang(3) = 0, bang(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4 
 */
int bang(int x)
{
  // 经过以下移位,如果x有某一位为1,那么x的最低有效位为1,否则为0
  x |= x >> 16;
  x |= x >> 8;
  x |= x >> 4;
  x |= x >> 2;
  x |= x >> 1;

  // 对LSB取反
  return (0x1 & x) ^ 0x1;
}

/* 
 * bitAnd - x&y using only ~ and | 
 *   Example: bitAnd(6, 5) = 4
 *   Legal ops: ~ |
 *   Max ops: 8
 *   Rating: 1
 * 
 * 一个定律
 */
int bitAnd(int x, int y)
{
  return ~(~x | ~y);
}

/*
 * bitCount - returns count of number of 1's in word
 *   Examples: bitCount(5) = 2, bitCount(7) = 3
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 40
 *   Rating: 4
 * 
 * 分治法：
 * 如果我们可以知道前16位，以及后16位分别包含1的位数，那么最后的结果为2者相加。
 * 一直分解到，前后各一位
 * AB      R
 * 00      00
 * 01      01
 * 10      01
 * 11      10
 * 通过观察我们可以发现A+B=R，而且AB所在的位正好可以表示R。也就是说
 * X = AB
 * X = (B & 0x1) + ((A >> 1) & 0x1)
 * 
 * 前后各2位，也是同样的思路，只不过要在 前后各一位 的基础上。
 * 这样一直计算到前后各16位，最终的结果就是我们想要的
 * 
 * bitCount(0x57168ace):
 * mask                         x
 *              0101 0111 0001 0110 1000 1010 1100 1110  (0x57168ace) 
 * 0x55555555   0101 0110 0001 0101 0100 0101 1000 1001          
 * 0x33333333   0010 0011 0001 0010 0001 0010 0010 0011
 * 0x0F0F0F0F   0000 0101 0000 0011 0000 0011 0000 0101
 * 0x00FF00FF   0000 0000 0000 1000 0000 0000 0000 1000 
 * 0x0000FFFF   0000 0000 0000 0000 0000 0000 0001 0000
 */
int bitCount(int x)
{
  int mask = 0x55 | (0x55 << 8); // mask=0x55555555
  mask |= mask << 16;
  x = (x & mask) + ((x >> 1) & mask);

  mask = 0x33 | (0x33 << 8); // mask=0x33333333
  mask |= mask << 16;
  x = (x & mask) + ((x >> 2) & mask);

  mask = 0x0F | (0x0F << 8); // mask=0x0F0F0F0F
  mask |= mask << 16;
  x = (x & mask) + ((x >> 4) & mask);

  mask = 0xFF | (0xFF << 16); // mask=0x00FF00FF
  x = (x & mask) + ((x >> 8) & mask);

  mask = 0xFF | (0xFF << 8); // mask=0x0000FFFF
  x = (x & mask) + ((x >> 16) & mask);

  return x;
}

/* 
 * bitMask - Generate a mask consisting of all 1's 
 *   lowbit and highbit
 *   Examples: bitMask(5,3) = 0x38
 *   Assume 0 <= lowbit <= 31, and 0 <= highbit <= 31
 *   If lowbit > highbit, then mask should be all 0's
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 * 
 * bitMask(5,3)  = 0x38
 *  11 1111 - 00 0111 = 0x38
 *  result = (((1 << highbit) + ~0) << 1) + 1;            (1)
 *  为什么不写成：
 *      result = (((1 << highbit + 1) + ~0) << 1) + 1;    (2)
 *  因为当highbit = 31时，对于(1)result为0xFFFFFFFF, 而对于(2)result为0
 */
int bitMask(int highbit, int lowbit)
{
  int result = (((1 << highbit) + ~0) << 1) + 1;
  result = result >> lowbit << lowbit;
  return result;
}

/* 
 * bitMatch - Create mask indicating which bits in x match those in y
 *            using only ~ and & 
 *   Example: bitMatch(0x7, 0xE) = 0x6
 *   Legal ops: ~ &
 *   Max ops: 14
 *   Rating: 1
 * 
 * x^y: 相同位为0, 不同位为1.
 * 然后转成符号只包含 ~ &
 */
int bitMatch(int x, int y)
{
  return ~(x & ~y) & ~(~x & y);
}

/* 
 * bitNor - ~(x|y) using only ~ and & 
 *   Example: bitNor(0x6, 0x5) = 0xFFFFFFF8
 *   Legal ops: ~ &
 *   Max ops: 8
 *   Rating: 1
 */
int bitNor(int x, int y)
{
  return ~x & ~y;
}

/* 
 * bitOr - x|y using only ~ and & 
 *   Example: bitOr(6, 5) = 7
 *   Legal ops: ~ &
 *   Max ops: 8
 *   Rating: 1
 */
int bitOr(int x, int y)
{
  return ~(~x & ~y);
}

/*
 * bitParity - returns 1 if x contains an odd number of 0's
 *   Examples: bitParity(5) = 0, bitParity(7) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 4
 * 
 * 奇数个零，也就是奇数个1.
 * 对于拥有奇数个1的x来说，所有位异或的结果为1
 */
int bitParity(int x)
{
  x ^= x >> 16;
  x ^= x >> 8;
  x ^= x >> 4;
  x ^= x >> 2;
  x ^= x >> 1;
  return x & 0x1;
}

/*
 * bitReverse - Reverse bits in a 32-bit word
 *   Examples: bitReverse(0x80000002) = 0x40000001
 *             bitReverse(0x89ABCDEF) = 0xF7D3D591
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 45
 *   Rating: 4
 * 
 * 分治法：
 * 如果前后16均已倒序，那么前后交换即可.
 * 问题的规模一直缩小到前后各1位的情况．
 * X = AB
 * X = ((X & 0x1) << 1) | ((x >> 1) & 0x1)
 */
int bitReverse(int x)
{
  int mask = 0x55 | (0x55 << 8);
  mask |= mask << 16;
  x = ((x & mask) << 1) | ((x >> 1) & mask);

  mask = 0x33 | (0x33 << 8);
  mask |= mask << 16;
  x = ((x & mask) << 2) | ((x >> 2) & mask);

  mask = 0x0F | (0x0F << 8);
  mask |= mask << 16;
  x = ((x & mask) << 4) | ((x >> 4) & mask);

  mask = 0xFF | (0xFF << 16);
  x = ((x & mask) << 8) | ((x >> 8) & mask);

  mask = 0xFF | (0xFF << 8);
  x = ((x & mask) << 16) | ((x >> 16) & mask);

  return x;
}

/* 
 * bitXor - x^y using only ~ and & 
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 14
 *   Rating: 1
 */
int bitXor(int x, int y)
{
  return ~(~(x & ~y) & ~(~x & y));
}

/* 
 * byteSwap - swaps the nth byte and the mth byte
 *  Examples: byteSwap(0x12345678, 1, 3) = 0x56341278
 *            byteSwap(0xDEADBEEF, 0, 2) = 0xDEEFBEAD
 *  You may assume that 0 <= n <= 3, 0 <= m <= 3
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 25
 *  Rating: 2
 */
int byteSwap(int x, int n, int m)
{
  int nMove = n << 3;
  int mMove = m << 3;

  int nByte = (x >> nMove) & 0xFF;
  int mByte = (x >> mMove) & 0xFF;
  x = x ^ (nByte << nMove) ^ (mByte << mMove);    // 对应的位清零
  return x | (nByte << mMove) | (mByte << nMove); // 设置交换
}

/* 
 * conditional - same as x ? y : z 
 *   Example: conditional(2,4,5) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 * 
 * if x == 0:
 *    mask = ~0 + !x = 0
 *    (mask & y) | (~mask & z) = z
 * if x != 0:
 *    mask = ~0 + !x = 0xFFFFFFFF
 *    (mask & y) | (~mask & z) = y
 */
int conditional(int x, int y, int z)
{
  int mask = ~0 + !x;
  return (mask & y) | (~mask & z);
}

/* 
 * copyLSB - set all bits of result to least significant bit of x
 *   Example: copyLSB(5) = 0xFFFFFFFF, copyLSB(6) = 0x00000000
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int copyLSB(int x)
{
  return ~0 + !(x & 0x1);
}
/*
 * distinctNegation - returns 1 if x != -x.
 *     and 0 otherwise 
 *   Legal ops: ! ~ & ^ | +
 *   Max ops: 5
 *   Rating: 2
 */
int distinctNegation(int x)
{
  return !!(x ^ (~x + 1));
}

/* 
 * dividePower2 - Compute x/(2^n), for 0 <= n <= 30
 *  Round toward zero
 *   Examples: dividePower2(15,1) = 7, dividePower2(-33,4) = -2
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
int dividePower2(int x, int n)
{
  // int mask = (1 << n) + ~0;
  // int neg = (x >> 31) & 0x1;
  // int bias = (mask + !neg) & mask;

  int bias = (x >> 31);
  bias ^= bias << n;

  return (x + bias) >> n;
}

/* 
 * evenBits - return word with all even-numbered bits set to 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 1
 */
int evenBits(void)
{
  int mask = 0x55;
  mask |= mask << 8;
  return mask | (mask << 16);
}

/*
 * ezThreeFourths - multiplies by 3/4 rounding toward 0,
 *   Should exactly duplicate effect of C expression (x*3/4),
 *   including overflow behavior.
 *   Examples: ezThreeFourths(11) = 8
 *             ezThreeFourths(-9) = -6
 *             ezThreeFourths(1073741824) = -268435456 (overflow)
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 3
 * 
 * 溢出，不溢出　/4结果是一样的．书本上有证明
 */
int ezThreeFourths(int x)
{
  x = (x << 1) + x;

  // int mask = 3;
  // int neg = (x >> 31) & 0x1;
  // int bias = (mask + !neg) & mask;

  int bias = x >> 31;
  bias ^= bias << 2;

  return (x + bias) >> 2;
}

/* 
 * fitsBits - return 1 if x can be represented as an 
 *  n-bit, two's complement integer.
 *   1 <= n <= 32
 *   Examples: fitsBits(5,3) = 0, fitsBits(-4,3) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 * 
 * https://stackoverflow.com/questions/14792521/bitwise-operations-and-shifts
 * 
 */
int fitsBits(int x, int n)
{
  int move;
  move = 32 + (~n + 1);
  return !(x ^ ((x << move) >> move));
}
/* 
 * fitsShort - return 1 if x can be represented as a 
 *   16-bit, two's complement integer.
 *   Examples: fitsShort(33000) = 0, fitsShort(-32768) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 1
 */
int fitsShort(int x)
{
  return !(x ^ ((x << 16) >> 16));
}
/* 
 * floatAbsVal - Return bit-level equivalent of absolute value of f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representations of
 *   single-precision floating point values.
 *   When argument is NaN, return argument..
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 10
 *   Rating: 2
 */
unsigned floatAbsVal(unsigned uf)
{
  return 2;
}
/* 
 * floatFloat2Int - Return bit-level equivalent of expression (int) f
 *   for floating point argument f.
 *   Argument is passed as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point value.
 *   Anything out of range (including NaN and infinity) should return
 *   0x80000000u.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
int floatFloat2Int(unsigned uf)
{
  return 2;
}
/* 
 * floatInt2Float - Return bit-level equivalent of expression (float) x
 *   Result is returned as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point values.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned floatInt2Float(int x)
{
  return 2;
}
/* 
 * floatIsEqual - Compute f == g for floating point arguments f and g.
 *   Both the arguments are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representations of
 *   single-precision floating point values.
 *   If either argument is NaN, return 0.
 *   +0 and -0 are considered equal.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 25
 *   Rating: 2
 */
int floatIsEqual(unsigned uf, unsigned ug)
{
  return 2;
}
/* 
 * floatIsLess - Compute f < g for floating point arguments f and g.
 *   Both the arguments are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representations of
 *   single-precision floating point values.
 *   If either argument is NaN, return 0.
 *   +0 and -0 are considered equal.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 3
 */
int floatIsLess(unsigned uf, unsigned ug)
{
  return 2;
}
/* 
 * floatNegate - Return bit-level equivalent of expression -f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representations of
 *   single-precision floating point values.
 *   When argument is NaN, return argument.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 10
 *   Rating: 2
 */
unsigned floatNegate(unsigned uf)
{
  return 2;
}
/* 
 * floatPower2 - Return bit-level equivalent of the expression 2.0^x
 *   (2.0 raised to the power x) for any 32-bit integer x.
 *
 *   The unsigned value that is returned should have the identical bit
 *   representation as the single-precision floating-point number 2.0^x.
 *   If the result is too small to be represented as a denorm, return
 *   0. If too large, return +INF.
 * 
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. Also if, while 
 *   Max ops: 30 
 *   Rating: 4
 */
unsigned floatPower2(int x)
{
  return 2;
}
/* 
 * floatScale1d2 - Return bit-level equivalent of expression 0.5*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned floatScale1d2(unsigned uf)
{
  return 2;
}
/* 
 * floatScale2 - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned floatScale2(unsigned uf)
{
  return 2;
}
/* 
 * floatScale64 - Return bit-level equivalent of expression 64*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 35
 *   Rating: 4
 */
unsigned floatScale64(unsigned uf)
{
  return 2;
}
/* 
 * floatUnsigned2Float - Return bit-level equivalent of expression (float) u
 *   Result is returned as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point values.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned floatUnsigned2Float(unsigned u)
{
  return 2;
}
/* 
 * getByte - Extract byte n from word x
 *   Bytes numbered from 0 (least significant) to 3 (most significant)
 *   Examples: getByte(0x12345678,1) = 0x56
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 2
 */
int getByte(int x, int n)
{
  int move = n << 3;
  return (x >> move) & 0xFF;
}

/* 
 * greatestBitPos - return a mask that marks the position of the
 *               most significant 1 bit. If x == 0, return 0
 *   Example: greatestBitPos(96) = 0x40
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 70
 *   Rating: 4 
 * 
 * 将从最高位为1的开始，一直到LSB置为1.
 * 
 * x ^ ((x >> 1) & mask):  这里为什么要mask呢？
 * 如果x为负数，这最后的结果为0，但是最后的结果应该为0x80000000
 */
int greatestBitPos(int x)
{
  int mask = (1 << 31) + ~0;
  x |= x >> 1;
  x |= x >> 2;
  x |= x >> 4;
  x |= x >> 8;
  x |= x >> 16;

  return x ^ ((x >> 1) & mask);
}

/* howManyBits - return the minimum number of bits required to represent x in
 *             two's complement
 *  Examples: howManyBits(12) = 5
 *            howManyBits(298) = 10
 *            howManyBits(-5) = 4
 *            howManyBits(0)  = 1
 *            howManyBits(-1) = 1
 *            howManyBits(0x80000000) = 32
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 90
 *  Rating: 4
 */
int howManyBits(int x)
{
  return 0;
}
/* 
 * implication - return x -> y in propositional logic - 0 for false, 1
 * for true
 *   Example: implication(1,1) = 1
 *            implication(1,0) = 0
 *   Legal ops: ! ~ ^ |
 *   Max ops: 5
 *   Rating: 2
 */
int implication(int x, int y)
{
  return (!x) | y;
}
/*
 * intLog2 - return floor(log base 2 of x), where x > 0
 *   Example: intLog2(16) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 90
 *   Rating: 4
 */
int intLog2(int x)
{
  int result = 0;
  int b4 = !!(x >> 16);
  int b3 = 0;
  int b2 = 0;
  int b1 = 0;
  int b0 = 0;
  result = b4 << 4;
  b3 = !!(x >> (8 + result));
  result = result | (b3 << 3);
  b2 = !!(x >> (4 + result));
  result = result | (b2 << 2);
  b1 = !!(x >> (2 + result));
  result = result | (b1 << 1);
  b0 = !!(x >> (1 + result));
  result = result | b0;
  return result;
}
/* 
 * isAsciiDigit - return 1 if 0x30 <= x <= 0x39 (ASCII codes for characters '0' to '9')
 *   Example: isAsciiDigit(0x35) = 1.
 *            isAsciiDigit(0x3a) = 0.
 *            isAsciiDigit(0x05) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 3
 */
int isAsciiDigit(int x)
{
  x = ~x;
  //0x3a+x，符号位为0；0x30+x，符号位为1
  //return !(((0x3a+x)+~(0x30+x))>>31);
  return !(((0x3a + x) >> 31) + ~((0x30 + x) >> 31));
}
/* 
 * isEqual - return 1 if x == y, and 0 otherwise 
 *   Examples: isEqual(5,5) = 1, isEqual(4,5) = 0
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int isEqual(int x, int y)
{
  return !(x ^ y);
}
/* 
 * isGreater - if x > y  then return 1, else return 0 
 *   Example: isGreater(4,5) = 0, isGreater(5,4) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 * 
 * ---
 */
int isGreater(int x, int y)
{
  int ny = ~y;
  int v1 = x & ny;
  int v2 = x ^ ny;
  int v3 = x + ny;
  int v4 = (v2 & v3) | v1;
  return !(v4 >> 31);
}
/* 
 * isLess - if x < y  then return 1, else return 0 
 *   Example: isLess(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLess(int x, int y)
{
  int mask = !!(x ^ y);
  int ny = ~y;
  int v1 = x & ny;
  int v2 = x ^ ny;
  int v3 = x + ny;
  int v4 = (v2 & v3) | v1;
  return (v4 >> 31) & 0x1 & mask;
}
/* 
 * isLessOrEqual - if x <= y  then return 1, else return 0 
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLessOrEqual(int x, int y)
{
  int ny = ~y;
  int v1 = x & ny;
  int v2 = x ^ ny;
  int v3 = x + ny;
  int v4 = (v2 & v3) | v1;
  return (v4 >> 31) & 0x1;
}
/* 
 * isNegative - return 1 if x < 0, return 0 otherwise 
 *   Example: isNegative(-1) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 2
 */
int isNegative(int x)
{
  int sign = (x >> 31) & 0x1;
  return sign;
}
/* 
 * isNonNegative - return 1 if x >= 0, return 0 otherwise 
 *   Example: isNonNegative(-1) = 0.  isNonNegative(0) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 2
 */
int isNonNegative(int x)
{
  int sign = (x >> 31) & 0x1;
  return !sign;
}
/* 
 * isNonZero - Check whether x is nonzero using
 *              the legal operators except !
 *   Examples: isNonZero(3) = 1, isNonZero(0) = 0
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 10
 *   Rating: 4 
 */
int isNonZero(int x)
{
  return ((x | (~x + 1)) >> 31) & 1;
}
/* 
 * isNotEqual - return 0 if x == y, and 1 otherwise 
 *   Examples: isNotEqual(5,5) = 0, isNotEqual(4,5) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 2
 */
int isNotEqual(int x, int y)
{
  return !!(x ^ y);
}
/*
 * isPallindrome - Return 1 if bit pattern in x is equal to its mirror image
 *   Example: isPallindrome(0x01234567E6AC2480) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 45
 *   Rating: 4
 */
int isPallindrome(int x)
{
  int s = x;
  int mask = 0x55 | (0x55 << 8);
  mask |= mask << 16;
  x = ((x & mask) << 1) | ((x >> 1) & mask);

  mask = 0x33 | (0x33 << 8);
  mask |= mask << 16;
  x = ((x & mask) << 2) | ((x >> 2) & mask);

  mask = 0x0F | (0x0F << 8);
  mask |= mask << 16;
  x = ((x & mask) << 4) | ((x >> 4) & mask);

  mask = 0xFF | (0xFF << 16);
  x = ((x & mask) << 8) | ((x >> 8) & mask);

  mask = 0xFF | (0xFF << 8);
  x = ((x & mask) << 16) | ((x >> 16) & mask);

  return !(x ^ s);
}
/* 
 * isPositive - return 1 if x > 0, return 0 otherwise 
 *   Example: isPositive(-1) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 2
 */
int isPositive(int x)
{
  int sign = (x >> 31) & 0x1;
  return !sign & !!x;
}
/*
 * isPower2 - returns 1 if x is a power of 2, and 0 otherwise
 *   Examples: isPower2(5) = 0, isPower2(8) = 1, isPower2(0) = 0
 *   Note that no negative number is a power of 2.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 4
 * 
 * 只需证明除了符号位外，其他位只有一个1.
 * 
 * x      00800000
 * step1: 00FFFFFF
 * step2: 007FFFFF
 * step3: 00800000
 * step4: !(step3 ^ x)
 * 
 */
int isPower2(int x)
{
  int dup = x;
  x |= x >> 1;
  x |= x >> 2;
  x |= x >> 4;
  x |= x >> 8;
  x |= x >> 16;
  x >>= 1;
  x += 1;
  return !(x ^ dup);
}

/*
 * isTmax - returns 1 if x is the maximum, two's complement number,
 *     and 0 otherwise 
 *   Legal ops: ! ~ & ^ | +
 *   Max ops: 10
 *   Rating: 1
 * 
 * x+1 = ~x 的有 0x7FFFFFFF, 0xFFFFFFFF
 * 结果屏蔽掉0xFFFFFFFF就可以了
 */
int isTmax(int x)
{
  return !((x + 1) ^ (~x)) & !!(x + 1);
}

/*
 * isTmin - returns 1 if x is the minimum, two's complement number,
 *     and 0 otherwise 
 *   Legal ops: ! ~ & ^ | +
 *   Max ops: 10
 *   Rating: 1
 * 
 * -x = ~x + 1 == x 的有，TMin与0
 * 如果表达式最后不加上 & !!x,TMin与0都返回1
 */
int isTmin(int x)
{
  return !(x ^ (~x + 1)) & !!x;
}

/*
 * isZero - returns 1 if x == 0, and 0 otherwise 
 *   Examples: isZero(5) = 0, isZero(0) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 2
 *   Rating: 1
 */
int isZero(int x)
{
  return !x;
}
/* 
 * leastBitPos - return a mask that marks the position of the
 *               least significant 1 bit. If x == 0, return 0
 *   Example: leastBitPos(96) = 0x20
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 2 
 * 
 * x = 96       = 1001 0110
 * ~x+1         = 0110 1011
 * x & (~x + 1) = 0000 0010
 * 
 */
int leastBitPos(int x)
{
  return x & (~x + 1);
}
/*
 * leftBitCount - returns count of number of consective 1's in
 *     left-hand (most significant) end of word.
 *   Examples: leftBitCount(-1) = 32, leftBitCount(0xFFF0F0F0) = 12
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 50
 *   Rating: 4
 */
int leftBitCount(int x)
{
  int v = x;
  int r; // store our result here
  int shift;
  int full = !(~x); // we must add one if we have 0xffffffff

  // Check the top 16 bits and add them to our result if they exist
  r = !(~(v >> 16)) << 4;
  v <<= r;
  // check the remaining 8 bits
  shift = !(~(v >> 24)) << 3;
  v <<= shift;
  r |= shift;
  // remaining 4 bits
  shift = !(~(v >> 28)) << 2;
  v <<= shift;
  r |= shift;
  // remaining 2 bits
  shift = !(~(v >> 30)) << 1;
  v <<= shift;
  r |= shift;
  // remaining 1 bits
  r ^= 1 & ((v >> 31));

  // remember to add one if we have 32 on bits
}
/* 
 * logicalNeg - implement the ! operator, using all of 
 *              the legal operators except !
 *   Examples: logicalNeg(3) = 0, logicalNeg(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4 
 * 
 * 如果x不为0，那么LSB为1，否则为0
 * LSB ^ 0x1 = ~LSB
 */
int logicalNeg(int x)
{
  x |= x >> 1;
  x |= x >> 2;
  x |= x >> 4;
  x |= x >> 8;
  x |= x >> 16;

  return (0x1 & x) ^ 0x1;
}
/* 
 * logicalShift - shift x to the right by n, using a logical shift
 *   Can assume that 0 <= n <= 31
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3 
 * 
 * int mask = ((!!n & 0x1) << move) + ~0;
 * 这里为什么要!!n & 0x1， 因为0这种情况需要特殊处理。
 * n=0，move=32，mask=～0，不加则mask为0
 */
int logicalShift(int x, int n)
{
  x >>= n;
  int move = 32 + (~n + 1);
  int mask = ((!!n & 0x1) << move) + ~0;
  return x & mask;
}
/* 
 * minusOne - return a value of -1 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 2
 *   Rating: 1
 * 
 * -1 == ~0 = ~1 + 1 = 0xFFFFFFFF
 */
int minusOne(void)
{
  return ~0;
}

/*
 * multFiveEighths - multiplies by 5/8 rounding toward 0.
 *   Should exactly duplicate effect of C expression (x*5/8),
 *   including overflow behavior.
 *   Examples: multFiveEighths(77) = 48
 *             multFiveEighths(-22) = -13
 *             multFiveEighths(1073741824) = 13421728 (overflow)
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 3
 */
int multFiveEighths(int x)
{
  return 2;
}
/* 
 * negate - return -x 
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int negate(int x)
{
  return ~x + 1;
}
/* 
 * oddBits - return word with all odd-numbered bits set to 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 2
 */
int oddBits(void)
{
  int x = 0xAA | (0xAA << 8);
  x |= x << 16;

  return x;
}
/* 
 * remainderPower2 - Compute x%(2^n), for 0 <= n <= 30
 *   Negative arguments should yield negative remainders
 *   Examples: remainderPower2(15,2) = 3, remainderPower2(-35,3) = -3
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3
 */
int remainderPower2(int x, int n)
{
  return 2;
}
/* 
 * replaceByte(x,n,c) - Replace byte n in x with c
 *   Bytes numbered from 0 (LSB) to 3 (MSB)
 *   Examples: replaceByte(0x12345678,1,0xab) = 0x1234ab78
 *   You can assume 0 <= n <= 3 and 0 <= c <= 255
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 10
 *   Rating: 3
 */
int replaceByte(int x, int n, int c)
{
  int step = n << 3;
  x ^= ((x >> step) & 0xFF) << step;
  return x | (c << step);
}
/* 
 * rotateLeft - Rotate x to the left by n
 *   Can assume that 0 <= n <= 31
 *   Examples: rotateLeft(0x87654321,4) = 0x76543218
 *   Legal ops: ~ & ^ | + << >> !
 *   Max ops: 25
 *   Rating: 3 
 */
int rotateLeft(int x, int n)
{
  return 2;
}
/* 
 * rotateRight - Rotate x to the right by n
 *   Can assume that 0 <= n <= 31
 *   Examples: rotateRight(0x87654321,4) = 0x76543218
 *   Legal ops: ~ & ^ | + << >> !
 *   Max ops: 25
 *   Rating: 3 
 */
int rotateRight(int x, int n)
{
  return 2;
}
/*
 * satAdd - adds two numbers but when positive overflow occurs, returns
 *          maximum possible value, and when negative overflow occurs,
 *          it returns minimum positive value.
 *   Examples: satAdd(0x40000000,0x40000000) = 0x7fffffff
 *             satAdd(0x80000000,0xffffffff) = 0x80000000
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 30
 *   Rating: 4
 * 
 * s = x + y
 * 发生正溢出:      0x7FFFFFFF & (结果 & (~0 + no_overflow))
 * 发生负溢出:      0x80000000 & (结果 & (~0 + no_overflow))
 * 没有发生溢出:     0xFFFFFFFF & (结果 & (~0 + no_overflow))
 */
int satAdd(int x, int y)
{
  int s = x + y;

  int neg_overflow = ((x & y & ~s) >> 31) & 0x1;
  int pos_overflow = ((~x & ~y & s) >> 31) & 0x1;
  int no_overflow = !(neg_overflow | pos_overflow);

  int neg_overflow_mask = neg_overflow << 31;
  int pos_overflow_mask = (pos_overflow << 31) + ~0 + !pos_overflow;
  int no_overflow_mask = (~no_overflow + 1);

  return (neg_overflow_mask | pos_overflow_mask | no_overflow_mask) & (s | (~0 + no_overflow));
}

/*
 * satMul2 - multiplies by 2, saturating to Tmin or Tmax if overflow
 *   Examples: satMul2(0x30000000) = 0x60000000
 *             satMul2(0x40000000) = 0x7FFFFFFF (saturate to TMax)
 *             satMul2(0x80000001) = 0x80000000 (saturate to TMin)
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3
 */
int satMul2(int x)
{
  return 2;
}
/*
 * satMul3 - multiplies by 3, saturating to Tmin or Tmax if overflow
 *  Examples: satMul3(0x10000000) = 0x30000000
 *            satMul3(0x30000000) = 0x7FFFFFFF (Saturate to TMax)
 *            satMul3(0x70000000) = 0x7FFFFFFF (Saturate to TMax)
 *            satMul3(0xD0000000) = 0x80000000 (Saturate to TMin)
 *            satMul3(0xA0000000) = 0x80000000 (Saturate to TMin)
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 25
 *  Rating: 3
 */
int satMul3(int x)
{
  return 2;
}
/* 
 * sign - return 1 if positive, 0 if zero, and -1 if negative
 *  Examples: sign(130) = 1
 *            sign(-23) = -1
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 10
 *  Rating: 2
 * 
 * s是符号位，　mask = 0xFFFFFFFF(-1)
 * mask + !s: 如果x为负数，结果为-1,如果x为非负数，结果为0.
 * 这不是我们想要的，怎么加上一个数，才能满足题目的条件?
 * 
 *      负  正  零
 * s    1   0   0
 * !x   0   0   1
 * 
 * 这个数：1) 负数为0,
 *        2) 正数为1,
 *       3)  零为0
 * 可以得到这个数为: !(s ^ !x)
 */
int sign(int x)
{
  int mask = ~0;
  int s = (x >> 31) & 0x1;

  return mask + !s + !(s ^ !x);
}

/* 
 * signMag2TwosComp - Convert from sign-magnitude to two's complement
 *   where the MSB is the sign bit
 *   Example: signMag2TwosComp(0x80000005) = -5.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 4
 * 
 * 题意: 如果为负数，将符号位置为０后取反＋１;正数则不变
 * 
 * x为正数: x = (x ^ (0xFFFFFFFF + 1)) + 0
 * x为负数: x = (x ^ (0xFFFFFFFF + 0)) + 1
 *         x = (x ^ (mask + !sign)) + sign
 */
int signMag2TwosComp(int x)
{
  int mask = ~0;
  int sign = (x >> 31) & 0x1;
  x = x & ((1 << 31) + ~0); // 符号位置为0
  return (x ^ (mask + !sign)) + sign;
}

/* 
 * specialBits - return bit pattern 0xffca3fff
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 3
 *   Rating: 1
 * 
 * 11111111110010100011111111111111
 *           00101000
 *                         11010111
 *           11010111(左移14位，然后取反)
 */
int specialBits(void)
{
  int x = 0xD7 << 14;
  return ~x;
}
/* 
 * subtractionOK - Determine if can compute x-y without overflow
 *   Example: subtractionOK(0x80000000,0x80000000) = 1,
 *            subtractionOK(0x80000000,0x70000000) = 0, 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3
 * 
 * x与y符号不同，相减才有可能溢出
 * s = x - y
 * s与ｘ符号不同，发生溢出
 */
int subtractionOK(int x, int y)
{
  int negativeY = ~y + 1;
  int s = x + (~y + 1);

  int xy = x ^ y;
  int xs = x ^ s;

  return !(((xy & xs) >> 31) & 0x1);
}

/* 
 * thirdBits - return word with every third bit (starting from the LSB) set to 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 1
 */
int thirdBits(void)
{
  int r = 0x49 | (0x49 << 9);
  r |= r << 18;
  return r;
}

/* 
 * TMax - return maximum two's complement integer 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmax(void)
{
  return (1 << 31) + ~0;
}
/* 
 * tmin - return minimum two's complement integer 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmin(void)
{
  return 1 << 31;
}
/*
 * trueFiveEighths - multiplies by 5/8 rounding toward 0,
 *  avoiding errors due to overflow
 *  Examples: trueFiveEighths(11) = 6
 *            trueFiveEighths(-9) = -5
 *            trueFiveEighths(0x30000000) = 0x1E000000 (no overflow)
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 25
 *  Rating: 4
 */
int trueFiveEighths(int x)
{
  return 2;
}
/*
 * trueThreeFourths - multiplies by 3/4 rounding toward 0,
 *   avoiding errors due to overflow
 *   Examples: trueThreeFourths(11) = 8
 *             trueThreeFourths(-9) = -6
 *             trueThreeFourths(1073741824) = 805306368 (no overflow)
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 4
 */
int trueThreeFourths(int x)
{
  return 2;
}
/* 
 * twosComp2SignMag - Convert from two's complement to sign-magnitude 
 *   where the MSB is the sign bit
 *   You can assume that x > TMin
 *   Example: twosComp2SignMag(-5) = 0x80000005.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 4
 */
int twosComp2SignMag(int x)
{
  return 2;
}
/* 
 * upperBits - pads n upper bits with 1's
 *  You may assume 0 <= n <= 32
 *  Example: upperBits(4) = 0xF0000000
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 10
 *  Rating: 1
 */
int upperBits(int n)
{
  return 2;
}
