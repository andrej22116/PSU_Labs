using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;

namespace Lr_3
{
    public partial class MainForm : System.Web.UI.Page
    {
        private GCD gcd = new GCD();

        protected void Page_Load(object sender, EventArgs e)
        {

        }

        protected void CalcGcd2_Click(object sender, EventArgs e)
        {
            try
            {
                long time = 0;
                GcdRes1.Text = gcd.calc(int.Parse(Gcd2Tb1.Text),
                                        int.Parse(Gcd2Tb2.Text),
                                        ref time,
                                        Gcd2_fast.Checked)
                                        .ToString() + ", time: " + time.ToString() + "ticks.";
            }
            catch (Exception ex)
            {
                GcdRes1.Text = ex.ToString();
            }
        }

        protected void CalcGcd3_Click(object sender, EventArgs e)
        {
            try
            {
                long time = 0;
                GcdRes2.Text = gcd.calc(int.Parse(Gcd3Tb1.Text),
                                        int.Parse(Gcd3Tb2.Text),
                                        int.Parse(Gcd3Tb3.Text),
                                        ref time,
                                        Gcd3_fast.Checked)
                                        .ToString() + ", time: " + time.ToString() + "ticks.";
            }
            catch (Exception ex)
            {
                GcdRes2.Text = ex.ToString();
            }
        }

        protected void CalcGcd4_Click(object sender, EventArgs e)
        {
            try
            {
                long time = 0;
                GcdRes3.Text = gcd.calc(int.Parse(Gcd4Tb1.Text),
                                        int.Parse(Gcd4Tb2.Text),
                                        int.Parse(Gcd4Tb3.Text),
                                        int.Parse(Gcd4Tb4.Text),
                                        ref time,
                                        Gcd4_fast.Checked)
                                        .ToString() + ", time: " + time.ToString() + "ticks.";
            }
            catch (Exception ex)
            {
                GcdRes3.Text = ex.ToString();
            }
        }

        protected void Gcd2_Click(object sender, EventArgs e)
        {
            MultiView1.ActiveViewIndex = 0;
        }

        protected void Gcd3_Click(object sender, EventArgs e)
        {
            MultiView1.ActiveViewIndex = 1;
        }

        protected void Gcd4_Click(object sender, EventArgs e)
        {
            MultiView1.ActiveViewIndex = 2;
        }
    }
}