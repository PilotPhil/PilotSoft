using System;
using System.Collections.Generic;

namespace PilotSoft.RainFlow
{
    using DF = List<float>;
    /// <summary>
    /// model used in rainflow algorithm
    /// </summary>
    public class RFModel
    {
        public DF Index { get; set; } = new DF();//index
        public DF Range { get; set; } = new DF();//range
        public DF Mean { get; set; } = new DF(); //mean
        public DF Count { get; set; } = new DF();//count
        public DF Start { get; set; } = new DF();//start index
        public DF End { get; set; } = new DF();  //end index

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

        /// <summary>
        /// formate output temp res
        /// </summary>
        /// <param name="point1"></param>
        /// <param name="point2"></param>
        /// <param name="count"></param>
        /// <param name="start"></param>
        /// <param name="end"></param>
        public void FormatOutput(double point1, double point2,
                                    double count,
                                    double start, double end)
        {
            Range.Add((float)Math.Abs(point1 - point2)); //add range value
            Mean.Add((float)((point1 + point2) * 0.5)); //add mean value
            Count.Add((float)count);                     //add count
            Start.Add((float)start);                      //add start point
            End.Add((float)end);                        //add end point
        }

        /// <summary>
        /// for Console.WriteLine
        /// </summary>
        /// <returns></returns>
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
