using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace PilotSoft.RainFlow
{
    using DF = List<float>;
    public class Damage
    {
        //param k in S-N Cruve
        public double K { get; set; } = 5.8E12;

        //ultra stress like 235MPa 
        public float UStress { get; set; } = 235;

        //mean stress res
        private DF MeanStress { get; set; } = new DF();

        //损伤度 只读
        public double damage { get; private set; }

        /// <summary>
        /// correct by mean stress
        /// </summary>
        /// <param name="rfm">rainflow result</param>
        protected virtual void MeanStressCorrection(RFModel rfm)
        {
            MeanStress.Clear();

            for (int i = 0; i < rfm.Range.Count; i++)
            {
                MeanStress.Add((2 * UStress * rfm.Range.ElementAt(i)) / (UStress - rfm.Mean.ElementAt(i)));
            }
        }

        /// <summary>
        /// compute the cumulative damage
        /// </summary>
        /// <param name="damage"></param>
        protected virtual double DamageCompute()
        {
            this.damage = 0;//先归零

            foreach (double m in MeanStress)
                this.damage += 1 / Math.Pow(10, Math.Log10(K) - 3 * Math.Log10(m));

            return this.damage;
        }

        /// <summary>
        /// apply
        /// </summary>
        /// <param name="rfm">rainflow res</param>
        /// <returns></returns>
        public double Apply(RFModel rfm)
        {
            //1.
            MeanStressCorrection(rfm);

            //2.
            var res = DamageCompute();

            return res;
        }

    }
}
