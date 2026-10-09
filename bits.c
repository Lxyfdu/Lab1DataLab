/* 
 * CS:APP Data Lab 
 * 
 * <Please put your name and userid here>
 *  Name: 梁心一
 *  UserID: 25800190015
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
  4. Interprets integer expressions using the Data Lab 32-bit bit-vector
     model: results outside the signed range retain their low 32 bits.


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
#include "bits.h"

// P1
/* 
 * signMask - return a mask with only the most significant bit set (0x80000000)
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 2
 *   Rating: 1
 */
int signMask(void) {
  // 1<<31 将1左移31位，得到 0x80000000
  return 1<<31;
}

// P2
/* 
 * bitXor - x^y using only ~ and & 
 *   Example: bitXor(4, 5) = 1, bitXor(7, 7) = 0
 *   Legal ops: ~ &
 *   Max ops: 8
 *   Rating: 2
 */
int bitXor(int x, int y) {
  /*~(x&y) 生成剔除 x 和 y 中都为 1 的位的掩码
  ~(~x&~y) 生成x|y，与掩码按位与就得到异或*/
	return ~(~x&~y)&(~(x&y));
}

// P3
/*
 * negativePart - return -x if x < 0, otherwise return 0
 *   Examples: negativePart(-10) = 10, negativePart(5) = 0
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 3
 */
int negativePart(int x){
  //y是x的负值，x>>31，由于算数右移，根据x的正负生成全0或者全1的掩码
  int y=~x+1;
  return y&(x>>31);
}


// P4
/*
 * copyByteWithin - copy byte src of x to byte dst, leaving all other bytes unchanged
 *   Bytes are numbered from 0 (least significant) to 3 (most significant).
 *   You can assume 0 <= src <= 3 and 0 <= dst <= 3.
 *   Example: copyByteWithin(0x11223344, 0, 2) = 0x11443344
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4
 */
int copyByteWithin(int x, int src, int dst) {
  /*
  1.存下src,dst表示的位移数量，节省<<的出现次数
  2.用byte提取src位置的字节
  3.构造在dst位置位0的掩码，将dst位置的字节清0
  4.将提取的字节写入dst位置
  */
  int src_shift=src<<3;
  int dst_shift=dst<<3;
  int byte=x>>src_shift&0xFF; 
  int cleared_x=x&~(0xFF<<dst_shift);
  return cleared_x|(byte<<dst_shift); 
}

// P5
/* 
 * logicalShift - shift x to the right by n bits, using a logical shift
 *   Can assume that 0 <= n <= 31
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 4
 */
int logicalShift(int x, int n) {
  //构造最高n位全是0，其余是1的掩码，将其与算术右移的结果&
  int  mask =~((1<<31)>>n<<1);
  return (x>>n)&mask;
}

// P6
/*
 * swapNibblePairs - swap the low and high 4 bits within each byte of x
 *   Examples: swapNibblePairs(0xAB) = 0xBA
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 18
 *   Rating: 4
 */
int swapNibblePairs(int x) {
  //构造x左移四位和右移四位，&两个掩码得到交换结果的一半，再相加得到结果
  int lx=x<<4;
  int rx=x>>4;
  int mask1=0x0F|(0x0F<<8)|(0x0F<<16)|(0x0F<<24);
  int mask2=mask1<<4;
  return (lx&mask2)+(rx&mask1);
}

// P7
/*
 * secondLowestZeroBit - return a mask that marks the position of the second least significant 0 bit
 *   Examples: secondLowestZeroBit(0xFFFFFFFA) = 0x4, secondLowestZeroBit(0x7FFFFFFF) = 0
 *             secondLowestZeroBit(-1) = 0
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 4
 */
int secondLowestZeroBit(int x) {
  //用x|(x+1)去掉最低位的0，取反后用lowbit函数找最小的1(即原本次小的0)，如果没找到说明原本0不够2个，自然返回0
  int y=~(x|(x+1));
  return y&(~y+1);
}

// P8
/*
 * oddParity - return the odd parity bit of x, that is,
 *      when the number of 1s in the binary representation of x is even, then the return 1, otherwise return 0.
 *   Examples: oddParity(5) = 1, oddParity(7) = 0
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 56
 *   Rating: 5
 */
int oddParity(int x) {
  //二分法，每次把前一半的和后一半的异或，最后最低位就是全部32位异或的结果
  x=x^(x>>16);
  x=x^(x>>8);
  x=x^(x>>4);
  x=x^(x>>2);
  x=x^(x>>1);
  return !(x&1);
}

// P9
/* 
 * rotateRightBits - rotate x to right by n bits
 *   you can assume n >= 0
 *   Examples: rotateRightBits(0x12345678, 8) = 0x78123456
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 5
 */

int rotateRightBits(int x, int n) {
  /*
  1.将n取模，防止溢出
  2.标准逻辑右移得到rx
  3.将x先左移31-n位再左移1位，利用左移自动溢出抹去高位的特性获取循环回高位的左半部分lx。
  4.按位或拼接rx与lx得到最终结果。
 */
  n=n&31;
  int mask=~((1<<31)>>n<<1);
  int rx=x>>n&mask;
  int lx=x<<(31+~n+1)<<1;
  return rx|lx;
}

// P10
/*
 * roundEvenPow2 - round nonnegative x to the nearest multiple of 2^n.
 *   If x is exactly halfway between two multiples, choose the multiple whose
 *   quotient by 2^n is even.
 *   You can assume 0 <= x <= 0x3fffffff and 1 <= n <= 16.
 *   Examples: roundEvenPow2(10, 2) = 8, roundEvenPow2(14, 2) = 16
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 5
 */
int roundEvenPow2(int x, int n) {
  /*
  1.h代表半数1<<(n-1)，b为基础偏置量h-1。
  2.利用(x+b+((x>>n)&1))>>n计算商：大于h自动进位，等于h则仅在商为奇数时进位，小于h不进位。
  3.将计算得到的商左移n位恢复。
  */
  int h=1<<(n+~0);
  int b=h+~0;
  return (((x+b)+((x>>n)&1))>>n)<<n;
}

// P11
/* 
 * midpointTowardFirst - return the exact mathematical midpoint (x+y)/2
 *   without overflow. If the exact midpoint lies halfway between two
 *   integers, choose the adjacent integer that is closer to the first
 *   argument x.
 *   Examples: midpointTowardFirst(4, 7) = 5,
 *             midpointTowardFirst(7, 4) = 6
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 32
 *   Rating: 5
 */
int midpointTowardFirst(int x, int y) {
  /*
  1.利用(x&y)+((x^y)>>1)计算无溢出基础平均值。
  2.当x+y为奇数(diff&1为1)时，右移会自动向下取整偏向较小值：
  若x>y，结果偏向了较小者y，需+1向较大者x靠拢；
  若x<y，结果已天然偏向较小者x，无需修正。
  3.分符号无溢出判断x>y：
  异号时：x非负即大于y，取(~x>>31)&1；
  同号时：y-x为负即x>y，取((y+~x)>>31)&1。
  */
  int diff=x^y;
  int diffSign=diff>>31;
  int xGreater=((diffSign&(~x>>31))|(~diffSign&((y+~x)>>31)))&1;
  return (x&y)+(diff>>1)+((diff&1)&xGreater);
}


// P12
/* 
 * isBetweenEitherOrder - return 1 when x lies in the inclusive interval whose
 *   endpoints are a and b. The endpoints may be given in either order.
 *   Example: isBetweenEitherOrder(5, 8, 3) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 48
 *   Rating: 7
 */
int isBetweenEitherOrder(int x, int a, int b) {
/*
  1.判断x是否介于a和b之间，等价于判断(x-a)和(x-b)是否“异号或至少有一个为0”。
  2.为了防止减法溢出，先检验符号位
  若x与端点同号，做减法比较大小；
  若x与端点异号，由x本身的符号决定大小
  3.得出x>=a和x>=b成立一个（用异或）
    或x刚好等于某个端点时返回1。
  */
  int diff_a=x^a;
  int diff_b=x^b;
  int xa=((~diff_a&(a+~x+1))|(diff_a&~x))>>31&1;
  int xb= ((~diff_b&(b+~x+1))|(diff_b&~x))>>31&1;
  int eq_a=!(x^a);
  int eq_b=!(x^b);
  return (xa^xb)|(eq_a|eq_b);
}

// P13
/* 
 * mul5Sat - return x*5, and if x*5 overflow, change the result to 
 * INT_MAX(0x7fffffff) or INT_MIN(0x80000000) correspondingly
 *   Examples: mul5Sat(1) = 0x5, mul5Sat(0x40000000) = 0x7fffffff
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 30
 *   Rating: 7
 */
int mul5Sat(int x) {
  /*
  5倍分解为4倍+1倍，如果没有溢出，则4x不能溢出（即前三位要相同）,且5倍不溢出，按照加法溢出判断，5x与x要同号
  如果正溢出，则正数越乘越小，负溢出则负数越乘越大
  */
  int x4=x<<2;
  int x5=x4+x;
  int sx=x>>31;
  int overflow=!!((x>>29)^sx)|!!((x5^x)>>31);
  int sat=(1<<31)+~sx;
  int mask=~overflow+1;
  return (mask&sat)|(~mask&x5);
}

// P14
/* 
 * classifyAdd3 - classify the exact mathematical sum x+y+z.
 *   Return 1 if the sum is greater than INT_MAX, -1 if it is less than
 *   INT_MIN, and 0 otherwise. You may not use a wider integer type.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 52
 *   Rating: 7
 */
int classifyAdd3(int x, int y, int z){
  /*
  1.分两步累加并记录每一步的溢出情况：上溢出记为+1，下溢出记为-1
  2.只有两次溢出的记录和位0（都不溢出或者相反溢出）才符合条件
  */
  int s1;
  int s2;
  int up1;
  int down1;
  int up2;
  int down2;
  int c1;
  int c2;
  s1=x+y;
  up1=(~x&~y&s1)>>31&1;
  down1=(x&y&~s1)>>31&1;
  c1=up1+~down1+1;

  s2=s1+z;
  up2=(~s1&~z&s2)>>31&1;
  down2=(s1&z&~s2)>>31&1;
  c2=up2+~down2+1;

  return c1+c2;
}

// P15
/*
 * floatScaleThreeHalves - Return bit-level equivalent of expression f*3/2 for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   Use round-to-nearest-even. Preserve the sign of both +0 and -0.
 *   When argument is NaN, return argument.
 *   Legal ops: Any integer / unsigned operations incl. ||, &&. also if, while
 *   Max ops: 60
 *   Rating: 7
 */
unsigned floatScaleThreeHalves(unsigned uf){
  unsigned sign=uf&0x80000000u;
  unsigned exp=(uf>>23)&0xFFu;
  unsigned frac=uf&0x7FFFFFu;
  unsigned m;
  unsigned p;
  unsigned out;
  unsigned rem;

  if(exp==255u){
    return uf;
  }
  if(exp==0u){
    m=frac;
    p=3u*m;
    out=p>>1;
    if((p&1u)&&(out&1u)){
      out=out+1u;
    }
    return sign|out;
  }
  m=0x800000u|frac;
  p=3u*m;
  if(p<0x02000000u){
    out=p>>1;
    if((p&1u)&&(out&1u)){
      out=out+1u;
    }
  }else{
    out=p>>2;
    rem=p&3u;
    if(rem>2u||(rem==2u&&(out&1u))){
      out=out+1u;
    }
    exp=exp+1u;
  }
  if(exp>=255u){
    return sign|0x7F800000u;
  }
  return sign|(exp<<23)|(out&0x7FFFFFu);
}

// P16
/* 
 * floatRoundEven - round the floating-point value represented by uf to the
 *   nearest integer, with halfway cases rounded to the even integer. Return
 *   the bit-level representation of that integer as a single-precision float.
 *   If rounding produces zero, preserve the input sign; thus a negative
 *   value that rounds to zero returns -0. When uf is NaN or infinity,
 *   return uf unchanged.
 *   Legal ops: Any integer / unsigned operations incl. ||, &&. also if, while
 *   Max ops: 65
 *   Rating: 10
 */
unsigned floatRoundEven(unsigned uf){
  /*
  1.提取符号位s、阶码exp。
  2.处理无小数部分或特殊值(exp>=150)：直接返回uf。
  3.处理|x|<1的情况：
  若exp<126（即|x|<0.5）或exp==126且frac==0,（即|x|==0.5）:舍入为0，保留符号位；
  其它则舍入为1.0，保留符号位。
  4.处理1<=|x|<2^23(127<=exp<150)的情况：
  计算小数位数shift=22-E(其中E=exp-127)；
  构造向偶数舍入偏置量bias；
  uf加上bias后清零低(shift+1)位小数。
  */
  unsigned s=uf&0x80000000u;
  unsigned exp=(uf>>23)&0xFFu;
  unsigned shift;
  unsigned round_bit;
  unsigned lsb;
  unsigned bias;

  if(exp>=150u){
    return uf;
  }

  if(exp<127u){
    if(exp<126u||(exp==126u&&(uf&0x7FFFFFu)==0u)){
      return s;
    }
    return s|(127u<<23);
  }

  shift=149u-exp;
  round_bit=1u<<shift;
  lsb=round_bit<<1;
  bias=round_bit-1u+((uf>>(shift+1u))&1u);
  uf=uf+bias;

  return s|(uf&~(lsb-1u));
}

// P17
/*
 * float_i2f - Return bit-level equivalent of expression (float) x.
 *   Result is returned as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point values.
 *   Legal ops: Any integer / unsigned operations incl. ||, &&. also if, while
 *   Max ops: 40
 *   Rating: 10
 */
unsigned float_i2f(int x){
  /*：
  先取出符号位，并用无符号运算求绝对值，以正确处理INT_MIN。
  再查找绝对值最高有效位的位置，确定浮点数的阶码。
  将有效数对齐到24位；若需要丢弃低位，则依据最近偶数规则舍入。
  如果舍入导致有效数进位溢出，就增加阶码，最后组合符号位、阶码和尾数。
  输入为0时直接返回正零。
  */
  unsigned sign;
  unsigned absX;
  unsigned exp;
  unsigned tmp;
  unsigned shift;
  unsigned sig;
  unsigned rem;
  unsigned half;

  sign=x&0x80000000u;
  absX=x;
  if(x<0){
    absX=~absX+1u;
  }
  if(absX==0u){
    return 0u;
  }
  tmp=absX;
  exp=0u;
  while(tmp>>1){
    tmp=tmp>>1;
    exp=exp+1u;
  }
  if(exp<=23u){
    sig=absX<<(23u-exp);
  }else{
    shift=exp-23u;
    sig=absX>>shift;
    rem=absX&((1u<<shift)-1u);
    half=1u<<(shift-1u);

    if(rem>half||(rem==half&&(sig&1u))){
      sig=sig+1u;
    }
    if(sig>>24){
      exp=exp+1u;
    }
  }
  return sign|((exp+127u)<<23)|(sig&0x7FFFFFu);
}



// P18
/*
 * bitCount - return count of number of 1's in the binary representation of x
 *   Examples: bitCount(5) = 2, bitCount(7) = 3
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 40
 *   Rating: 10
 */
int bitCount(int x){
  /*
  先构造掩码，将每一位的计数两两相加。
  再逐步合并相邻的2位、4位、8位和16位计数，
  最终得到整个32位整数中1的总数。
  */
  int mask1=0x55|(0x55<<8);
  int mask2=0x33|(0x33<<8);
  int mask4=0x0F|(0x0F<<8);
  int mask8=0xFF|(0xFF<<16);
  int mask16=0xFF|(0xFF<<8);

  mask1=mask1|(mask1<<16);
  mask2=mask2|(mask2<<16);
  mask4=mask4|(mask4<<16);

  x=(x&mask1)+((x>>1)&mask1);
  x=(x&mask2)+((x>>2)&mask2);
  x=(x&mask4)+((x>>4)&mask4);
  x=(x&mask8)+((x>>8)&mask8);
  x=(x&mask16)+((x>>16)&mask16);

  return x;
}

// P19
/*
 * bitReverse - Reverse bits in an 32-bit integer
 *   Examples: bitReverse(0x80000004) = 0x20000001
 *             bitReverse(0x7FFFFFFF) = 0xFFFFFFFE
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 34
 *   Rating: 10
 */
int bitReverse(int x){
  /*
  依次交换相邻的1位、2位、4位和8位，最后交换高低16位。
  每轮通过掩码提取，再移位到对应位置并合并
   */
  int m8=0xFF|(0xFF<<16);
  int m4=m8^(m8<<4);
  int m2=m4^(m4<<2);
  int m1=m2^(m2<<1);
  int low16=0xFF|(0xFF<<8);

  x=((x>>1)&m1)|((x&m1)<<1);
  x=((x>>2)&m2)|((x&m2)<<2);
  x=((x>>4)&m4)|((x&m4)<<4);
  x=((x>>8)&m8)|((x&m8)<<8);
  x=(x<<16)|((x>>16)&low16);

  return x;
}

