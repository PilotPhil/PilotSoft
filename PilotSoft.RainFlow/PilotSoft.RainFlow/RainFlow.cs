using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace PilotSoft.RainFlow
{
    using DF = List<float>;//类似于typedef

    public class RainFlow
    {
        protected virtual void ExtractPeakValley(ref DF series, ref RFModel rfm)
        {
            int id = 1;
            rfm.Index.Add(0);//索引
            int lt = series.Count;//获取序列原始长度

            for (var it = 1; it < series.Count - 1; ++it)//从1开始判断，并非0，因为0 1 2 才构成判断峰谷的序列长度条件。并到倒数第二结束判断
            {
                var isPeak = series[it] > series[it - 1] && series[it] > series[it + 1];     //判断是否为峰：it-1<it>it+1
                var isValley = series[it] < series[it - 1] && series[it] < series[it + 1];   //判断是否为谷：it-1>it<it+1

                if (isPeak == false && isValley == false)//非峰非谷 擦除此点
                {
                    series.RemoveAt(it);//对参数series进行了删改
                    it--;
                }
                else//否则索引添加，添加的是原始未删减序列中元素的标号
                {
                    rfm.Index.Add(id);
                }
                id++;
            }
            rfm.Index.Add(lt - 1);
        }

        protected virtual void ExtractCycles(ref DF series, ref RFModel rfm)
        {
            List<double> points = new List<double>();
            List<double> id = new List<double>();

            for (int i = 0; i < series.Count; i++)//在此循环中，利用points逐个元素拷贝series，并没有对series做出改动，所以使用引用传递是安全的
            {
                points.Add(series[i]);//拷贝峰谷点到双向序列中
                id.Add(rfm.Index[i]);

                while (points.Count >= 3)//序列长度大于等于3就一直运行
                {
                    double x1 = points.ElementAt(points.Count - 3);//获取序列中三个点（倒数：因为上面append是往后面添加）
                    double x2 = points.ElementAt(points.Count - 2);
                    double x3 = points.ElementAt(points.Count - 1);

                    double X = Math.Abs(x3 - x2);//幅值绝对值
                    double Y = Math.Abs(x2 - x1);//幅值绝对值

                    if (X < Y)//是否构成循环？
                    {
                        break;
                    }
                    else if (points.Count == 3)
                    {
                        //Y include Z
                        //yes:
                        //1.count Y as 1/2 cycle
                        //2.discard the first reversal of Y
                        //3.set Z to the second reversal of Y

                        rfm.FormatOutput(points.ElementAt(0), points.ElementAt(1), 0.5, id.ElementAt(0), id.ElementAt(1));//1/2 cycle，只有三个点，索引用0 1 即可
                        points.RemoveAt(0);//Removes the head item in the queue
                        id.RemoveAt(0);//Removes the head item in the queue
                    }
                    else
                    {
                        //Y include Z
                        //no:
                        //1.count Y as 1 cycle
                        //2.discard both points of Y

                        rfm.FormatOutput(points.ElementAt(points.Count - 3), points.ElementAt(points.Count - 2), 1.0,
                                     id.ElementAt(points.Count - 3), id.ElementAt(points.Count - 2));

                        double last = points.ElementAt(points.Count - 1);//先保存最后一个点
                        points.RemoveAt(points.Count - 1);//删除末尾三个点
                        points.RemoveAt(points.Count - 1);
                        points.RemoveAt(points.Count - 1);
                        points.Add(last);//添加最后一个点

                        double last2 = id.ElementAt(id.Count - 1);
                        id.RemoveAt(id.Count - 1);
                        id.RemoveAt(id.Count - 1);
                        id.RemoveAt(id.Count - 1);
                        id.Add(last2);
                    }
                }
            }
            while (points.Count > 1)//做完上述循环后，序列长度肯定小于等于3
            {
                rfm.FormatOutput(points.ElementAt(0), points.ElementAt(1), 0.5, id.ElementAt(0), id.ElementAt(1));
                points.RemoveAt(0);//Removes the head item in the queue
                id.RemoveAt(0);//Removes the head item in the queue
            }
        }

        public RFModel Apply(DF series)
        {
            RFModel rfm = new RFModel();
            ExtractPeakValley(ref series,ref rfm);
            ExtractCycles(ref series,ref rfm);

            return rfm;
        }
    }
}
