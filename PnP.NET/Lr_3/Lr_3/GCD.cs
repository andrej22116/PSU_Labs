using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Diagnostics;

namespace Lr_3
{
    public class GCD
    {
        public int calc(int a, int b, ref long time, bool fast = false)
        {
            var sw = new Stopwatch();
            sw.Start();

            if ( a < b ) { swap(ref a, ref b); }

            int res = 0;
            if ( fast )
            {
                res = calcStainGcd(a, b);
            }
            else
            {
                res = calcEvclideGcd(a, b);
            }

            sw.Stop();
            time = sw.ElapsedTicks;

            return res;
        }

        public int calc(int a, int b, int c, ref long time, bool fast = false)
        {
            var sw = new Stopwatch();
            sw.Start();

            if ( a < b ) { swap(ref a, ref b); }

            int res = 0;
            if ( fast )
            {
                res = calcStainGcd(a, calcStainGcd(b, c));
            }
            else
            {
                res = calcEvclideGcd(a, calcStainGcd(b, c));
            }

            sw.Stop();
            time = sw.ElapsedTicks;

            return res;
        }

        public int calc(int a, int b, int c, int d, ref long time, bool fast = false)
        {
            var sw = new Stopwatch();
            sw.Start();

            if ( a < b ) { swap(ref a, ref b); }

            int res = 0;
            if ( fast )
            {
                res = calcStainGcd(a, calcStainGcd(b, calcStainGcd(c, d)));
            }
            else
            {
                res = calcEvclideGcd(a, calcEvclideGcd(b, calcEvclideGcd(c, d)));
            }

            sw.Stop();
            time = sw.ElapsedTicks;

            return res;
        }
        
        private int calcEvclideGcd(int a, int b)
        {
            while ( b != 0 ) { b = a % (a = b); }                
            return a;
        }

        private int calcStainGcd(int a, int b)
        {
            if ( a == 0 ) { return b; }
            if ( b == 0 ) { return a; } 
            if ( a == b ) { return a; }

            if ( a == 1 || b == 1 ) { return 1; }
            if ( (a & 1) == 0 )
            {
                return ( (b & 1) == 0 )
                    ? calcStainGcd(a >> 1, b >> 1) << 1
                    : calcStainGcd(a >> 1, b);
            }
            else
            {
                return ( (b & 1) == 0 )
                    ? calcStainGcd(a, b >> 1)
                    : calcStainGcd(b, a > b ? a - b : b - a);
            }
        }

        private static void swap(ref int x, ref int y)
        {
            int t = y;
            y = x;
            x = t;
        }
    }
}