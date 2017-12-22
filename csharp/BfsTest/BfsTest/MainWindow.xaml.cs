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
        internal static extern int EscapeMaze(int floors, int height, int width, char[,,] mazeData);
        [DllImport(TestDllName, CallingConvention = CallingConvention.Cdecl)]
        private static extern int add(int[,] data);
        private void buttonEscapeClick(object s, RoutedEventArgs e)
        {
            var data = textData.Text;
            var firstLine = data.Substring(0, data.IndexOf(Environment.NewLine));
            data = data.Remove(0, data.IndexOf(Environment.NewLine));
            var firstData = firstLine.Split(' ');
            var floors = int.Parse(firstData[0]);
            var height = int.Parse(firstData[1]);
            var width = int.Parse(firstData[2]);
            var mazeData = new char[floors, height, width];
            data = data.Replace(Environment.NewLine, "").Replace(" ", "");
            for (var x = 0; x < floors; x++)
            {
                for (var y = 0; y < height; y++)
                {
                    for (var z = 0; z < width; z++)
                    {
                        mazeData[x, y, z] = data[x * (width * height) + y * width + z];
                    }
                }
            }
            var result = EscapeMaze(floors, height, width, mazeData);
            MessageBox.Show(result.ToString());
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
