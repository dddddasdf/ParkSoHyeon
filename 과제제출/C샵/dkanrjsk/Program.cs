using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace dkanrjsk
{
    class Program
    {
        static public void ReferenceOut(out int value) { value = 10; }
        static public void ReferenceRef(ref int value) { value = 20; }

        public int SUM(params int[] args)
        {
            int result = 0;
            for (int i = 0; args.Length > i; i++)
            {
                result += args[i];
            }

            return result;
        }

        static void Main(string[] args)
        {
            //int a = int.Parse("123");

            //int a;
            //if (int.TryParse("123", out a));

            //int[] arr = new int[3] { 0, 1, 2 };
            //int[] arr2 = new int[] { 0, 1, 2 };
            //int[] arr3 = { 0, 1, 2 };


            //int[,] MultiArr = new int[2, 3] { { 0, 1, 2 }, { 3, 4, 5 } };

            //int a = MultiArr.Length;
            //int b = MultiArr.Rank;
            //int c = MultiArr.GetLength(0);
            //int d = MultiArr.GetLength(1);

            //Console.Write("{0}, {1}, {2}, {3}", a, b, c, d);

            //in은 또 뭐임
            //int[] a = new int[] { 0, 1, 2 };
            //int i = 0;
            //foreach (var value in a)
            //{
            //    Console.Write("{0}\n", a[i]);
            //    i++;
            //}

            //int value;
            //ReferenceOut(out value);
            //Console.WriteLine(value.ToString());
            //ReferenceRef(ref value);
            //Console.WriteLine(value.ToString());

            //const랑 비슷하단 건가 ref가

            //SUM(1, 2);
            //ㄴ왜 안 되지 이거

            //double x = 5;
            //double y = 10;
            //double z = Math.Pow(x, y);

            //Console.Write("{0}", z);

            int DivA = 27;
            int DivB = 5;
            int DivResult;
            int Divdd = Math.DivRem(DivA, DivB, out DivResult);

            Console.Write("{0}, {1}", Divdd, DivResult);

            //out이 기존 C C++에서 쓰던 포인터와 비슷한 것?

            Console.ReadKey();
        }
    }
}
