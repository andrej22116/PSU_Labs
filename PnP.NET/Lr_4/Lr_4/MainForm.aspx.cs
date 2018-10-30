using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;

namespace Lr_4
{
    public partial class MainForm : System.Web.UI.Page
    {
        protected void Page_Load(object sender, EventArgs e)
        {

        }

        protected void Button1_Click(object sender, EventArgs e)
        {
            try
            {
                var tr = new Triangle(  double.Parse(TextBox1.Text),
                                        double.Parse(TextBox2.Text),
                                        double.Parse(TextBox3.Text));
                if (tr)
                {
                    Label1.Text = "Всё ок, треугольник норм!"
                        +   "\nПериметр треугольника: " + tr.Perimeter
                        +   "\nПлощадь треугольника: " + tr.Square;
                }
                else
                {
                    Label1.Text = "Не получится из этого треугольника!";
                }
            }
            catch (Exception ex)
            {
                Label1.Text = ex.ToString();
            }
        }
    }
}