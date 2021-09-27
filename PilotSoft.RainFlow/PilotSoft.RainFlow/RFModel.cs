using System;
using System.Collections.Generic;

namespace PilotSoft.RainFlow
{
    /// <summary>
    /// model used in rainflow algorithm
    /// </summary>
    public class RFModel
    {
        public List<float> Index { get; set; } = new List<float>();//index
        public List<float> Range { get; set; } = new List<float>();//range
        public List<float> Mean { get; set; } = new List<float>(); //mean
        public List<float> Count { get; set; } = new List<float>();//count
        public List<float> Start { get; set; } = new List<float>();//start index
        public List<float> End { get; set; } = new List<float>();  //end index

        /// <summary>
        /// clear all properties
        /// </summary>
        public void ClearAll()
        {
            Index.Clear();
            Range.Clear();
            Mean.Clear();
            Count.Clear();
            Start.Clear();
            End.Clear();
        }

        public void FormatOutput(double point1, double point2,
                                    double count,
                                    double start, double end)
        {
            Range.Add((float)Math.Abs(point1 - point2)); //添加幅值
            Mean.Add((float)((point1 + point2) * 0.5)); //添加均值
            Count.Add((float)count);                     //添加计数
            Start.Add((float)start);                      //添加开始点
            End.Add((float)end);                        //添加结束点
        }

        public override string ToString()
        {
            var str = string.Empty;

            str += "Index" + "\t" + "Count" + "\t" + "Range" + "\t" + "Mean" + "\t" + "Start" + "\t" + "End" + "\n";
            str += "-----" + "\t" + "-----" + "\t" + "-----" + "\t" + "----" + "\t" + "-----" + "\t" + "---" + "\n";
            for (int i = 0; i < Count.Count; i++)
            {
                str += Index[i] + "\t";
                str += Count[i] + "\t";
                str += Range[i] + "\t";
                str += Mean[i] + "\t";
                str += Start[i] + "\t";
                str += End[i] + "\t";
                str += "\n";
            }

            return str;
        }
    }
}
