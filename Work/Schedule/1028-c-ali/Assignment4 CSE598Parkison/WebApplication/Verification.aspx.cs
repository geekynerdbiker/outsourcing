using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;

namespace WebApplication
{
    public partial class Verification : System.Web.UI.Page
    {       
        protected void Button1_Click(object sender, EventArgs e)
        {
            XmlService.Service1Client proxy = new XmlService.Service1Client();
            TextBox3.Text = proxy.verification(TextBox1.Text, TextBox2.Text);
        }
    }
}