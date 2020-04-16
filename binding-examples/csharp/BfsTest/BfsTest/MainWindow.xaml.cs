using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using Algorithm.Graph;

namespace BfsTest
{
    /// <summary>
    /// MainWindow.xaml 的交互逻辑
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow() => InitializeComponent();

        
        internal const string DllName = @"C:\Users\The18\Documents\Visual Studio 2017\Projects\3rd Party\Leo-AlgorithmModule\lib\algorithm_module.dll";
        internal const string TestDllName = @"C:\Users\The18\Documents\Visual Studio 2017\Projects\BfsTest\x64\Debug\DllTest.dll";
        [DllImport(DllName, CallingConvention = CallingConvention.Cdecl)]
        internal static extern int EscapeMaze(int floors, int height, int width, string mazeData);
        [DllImport(TestDllName, CallingConvention = CallingConvention.Cdecl)]
        private static extern int add(int[,] data);

        
        int a, b, t;
        char[,,] s;
        static readonly int[] dr = { -1, 0, 1, 0, 0, 0 };
        static readonly int[] dc = { 0, -1, 0, 1, 0, 0 };
        static readonly int[] dh = { 0, 0, 0, 0, 1, -1 };
        struct Node
        {
            public int R { get; set; }
            public int C { get; set; }
            public int H { get; set; }
            public Node(int r = 0, int c = 0, int h = 0)
            {
                R = r;
                C = c;
                H = h;
            }
        };

        private void buttonEscapeClick(object sender, RoutedEventArgs eventArgs)
        {
            var data = textData.Text;
            var firstLine = data.Substring(0, data.IndexOf(Environment.NewLine));
            data = data.Remove(0, data.IndexOf(Environment.NewLine));
            var firstData = firstLine.Split(' ');
            var floors = int.Parse(firstData[0]);
            var height = int.Parse(firstData[1]);
            var width = int.Parse(firstData[2]);
            data = data.Replace(Environment.NewLine, "").Replace(" ", "");

            var bfs = new Bfs();
            t = floors;
            a = height;
            b = width;
            s = new char[t, a, b];
            int nextOf(int v, int e)
            {
                for (var e1 = e + 1; e1 < 6; e1++)
                {
                    if (walk(v, e1) != Bfs.Nil)
                    {
                        return e1;
                    }
                }
                return Bfs.Nil;
            }
            bool inside(Node v) {
                return
                    v.R >= 0 && v.R < a &&
                    v.C >= 0 && v.C < b &&
                    v.H >= 0 && v.H < t &&
                    s[v.H, v.R, v.C] != '#';
            }
            int encoder(int h, int r, int c) => h * (a * b) + r * b + c; 
            int walk(int v, int i)
            {
                var next = new Node(v % (a * b) / b + dr[i], v % b + dc[i], v / (a * b) + dh[i]);

                if (inside(next))
                {
                    return encoder(next.H, next.R, next.C);
                }
                else
                {
                    return Bfs.Nil;
                }
            }
            bfs.Attributes.FirstOf = v => nextOf(v, Bfs.Nil);
            bfs.Attributes.NextOf = nextOf;
            bfs.Attributes.DestinationOf = walk;
            int start = Bfs.Nil, dest = Bfs.Nil;
            for (var i = 0; i < t; i++)
            {
                for (var j = 0; j < a; j++)
                {
                    for (var k = 0; k < b; k++)
                    {
                        s[i, j, k] = data[i * (a * b) + j * b + k];
                        if (s[i, j, k] == 'S')
                        {
                            start = encoder(i, j, k);
                        }
                        else if (s[i, j, k] == 'E')
                        {
                            dest = encoder(i, j, k);
                        }
                    }
                }
            }
            bfs.StartNode = start;
            bfs.DestinationNode = dest;
            bfs.Run();

            //var result = EscapeMaze(floors, height, width, data);
            MessageBox.Show(bfs.Steps.ToString());
        }

        private void buttonEscapeRightClick(object s, MouseButtonEventArgs e)
        {
            var data = new int[2, 2]
            {
                {1,2},{3,4}
            };

            MessageBox.Show(add(data).ToString());

        }
    }
}
