using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;

namespace Lr_4
{
    public class Triangle
    {
        private double[] nums = new double[3];
        private double[] nums_buf = new double[3];
        public double A
        {
            get { return nums[0]; }
            set { nums[0] = value; }
        }

        public double B
        {
            get { return nums[1]; }
            set { nums[1] = value; }
        }

        public double C
        {
            get { return nums[2]; }
            set { nums[2] = value; }
        }

        public Triangle()
        {

        }

        public Triangle(double a, double b, double c)
        {
            nums[0] = a;
            nums[1] = b;
            nums[2] = c;
        }

        public static bool operator true(Triangle tr)
        {
            if (tr.nums[0] <= 0 || tr.nums[1] <= 0 || tr.nums[2] <= 0)
            {
                return false;
            }

            tr.nums.CopyTo(tr.nums_buf, 0);
            Array.Sort(tr.nums_buf);
            if (tr.nums_buf[2] >= (tr.nums_buf[0] + tr.nums_buf[1]))
            {
                return false;
            }

            return true;
        }

        public static bool operator false(Triangle tr)
        {
            if (tr.nums[0] <= 0 || tr.nums[1] <= 0 || tr.nums[2] <= 0)
            {
                return true;
            }

            tr.nums.CopyTo(tr.nums_buf, 0);
            Array.Sort(tr.nums_buf);
            if (tr.nums_buf[2] >= (tr.nums_buf[0] + tr.nums_buf[1]))
            {
                return true;
            }

            return false;
        }

        public double Square
        {
            get
            {
                nums.CopyTo(nums_buf, 0);
                Array.Sort(nums_buf);

                var p = Perimeter / 2;

                return Math.Sqrt(p * (p - A) * (p - B) * (p - C));
            }
        }

        public double Perimeter
        {
            get
            {
                return A + B + C;
            }
        }
    }
}