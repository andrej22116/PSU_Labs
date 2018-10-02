using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace PnP_NET_LR_1_Console
{
    class Program
    {
        System.IO.TextReader input;
        System.IO.TextWriter output;

        static void Main(string[] args)
        {
            var program = new Program(args);
        }

        Program(string[] args)
        {
            try
            {
                initStreams(args);
                parse();

            }
            catch (Exception ex)
            {
                Console.WriteLine(ex);
            }
            finally
            {
                input.Close();
                output.Close();
            }
        }

        void initStreams(string[] args)
        {
            if (args.Length == 0)
            {
                input = Console.In;
                output = Console.Out;
            }
            else if (args.Length > 0)
            {
                input = new System.IO.StreamReader(new System.IO.FileStream(args[0], System.IO.FileMode.Open, System.IO.FileAccess.Read));
                if (args.Length > 1)
                {
                    output = new System.IO.StreamWriter(new System.IO.FileStream(args[1], System.IO.FileMode.Create, System.IO.FileAccess.Write));
                }
                else
                {
                    output = Console.Out;
                }
            }
        }

        void parse()
        {
            string line;
            while ((line = input.ReadLine()) != null)
            {
                var splitLineArray = line.Split(new char[]{ ',' });
                if (splitLineArray.Length > 2 || splitLineArray.Length < 2)
                {
                    continue;
                }
                try
                {
                    double.Parse(splitLineArray[0], System.Globalization.CultureInfo.InvariantCulture);
                    double.Parse(splitLineArray[1], System.Globalization.CultureInfo.InvariantCulture);
                }
                catch(Exception)
                {
                    continue;
                }
                output.WriteLine("X:{0,-10}Y:{1}", splitLineArray[0], splitLineArray[1]);
            }
        }
    }
}
