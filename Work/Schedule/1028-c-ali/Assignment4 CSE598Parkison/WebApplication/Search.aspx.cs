using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Xml.Linq;

namespace WebApplication
{
    public partial class Search : System.Web.UI.Page
    {      
        protected void Button1_Click(object sender, EventArgs e)
        {
            using (XmlService.Service1Client proxy = new XmlService.Service1Client())
            {                              
                TextBox3.Text = proxy.search(TextBox1.Text, TextBox2.Text);
            }
        }
    }    
}