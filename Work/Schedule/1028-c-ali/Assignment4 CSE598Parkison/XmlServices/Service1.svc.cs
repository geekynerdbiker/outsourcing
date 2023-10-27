using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Net;
using System.Runtime.Serialization;
using System.ServiceModel;
using System.ServiceModel.Web;
using System.Text;
using System.Xml;
using System.Xml.Linq;
using System.Xml.Schema;
using System.Xml.XPath;

namespace XmlServices
{
    // NOTE: You can use the "Rename" command on the "Refactor" menu to change the class name "Service1" in code, svc and config file together.
    // NOTE: In order to launch WCF Test Client for testing this service, please select Service1.svc or Service1.svc.cs at the Solution Explorer and start debugging.
    public class Service1 : IService1
    {
        public string verification(string xmlUrl, string xsdUrl)
        {
            string schemaString, errors = null, result = null;
            bool validated = true;
            XmlSchemaSet schema = new XmlSchemaSet();

            try
            {
                schemaString = File.ReadAllText(xsdUrl);
                schema.Add("", XmlReader.Create(new StringReader(schemaString)));
                XDocument xmlDoc = XDocument.Load(xmlUrl);
                xmlDoc.Validate(schema, (o, e) => { errors = e.Message; validated = false; });

                if (validated)
                {
                    result = "Valid";
                }
                else
                {
                    result = "Invalid: " + errors;
                }
            }catch (Exception e)
            {
                string exception = e.ToString();
                result = "Invalid: " + exception.Substring(exception.IndexOf(':') + 1,
                    exception.IndexOf(Environment.NewLine) - exception.IndexOf(':'));
            }         
            return result;
        }

        public string search(string xmlUrl, string key)
        {
            XDocument xmlDoc = XDocument.Load(xmlUrl);
            List<string> list = new List<string>();
            StringBuilder builder = new StringBuilder();

            foreach (var element in xmlDoc.Descendants("Person"))
            {
                foreach(var child in element.Descendants("First"))
                {
                    if (child.Value.ToLower() == key.ToLower())
                    {
                        list.Add(element.ToString());
                    }
                }
                foreach (var child in element.Descendants("Last"))
                {
                    if (child.Value.ToLower() == key.ToLower())
                    {
                        list.Add(element.ToString());
                    }
                }
            }                       
            
            foreach (string result in list.ToArray())
            {               
                XDocument xml = XDocument.Parse(result);
                int count = xml.Elements().Count();
                foreach (XElement element in xml.Descendants("Person"))
                {
                    foreach (XElement children in element.Descendants())
                    {
                        string select = children.Name.ToString();
                        switch (select)
                        {
                            case "First":
                                builder.Append("First Name: " + children.Value + "\n");
                                break;
                            case "Last":
                                builder.Append("Last Name: " + children.Value + "\n");
                                break;
                            case "Id":
                                builder.Append("User ID: " + children.Value + "\n");
                                break;
                            case "Password":
                                builder.Append("Password: " + children.Value + "\nEncrypted: " +
                                    children.FirstAttribute.Value.ToUpper() + "\n");
                                break;
                            case "Work":
                                builder.Append("Work Phone: " + formatPhone(children.Value) + "\n");
                                break;
                            case "Cell":
                                builder.Append("Cell Phone: " + formatPhone(children.Value) + "\n");
                                if (children.FirstAttribute != null)
                                {
                                    builder.Append("Provider: " + children.FirstAttribute.Value + "\n");
                                }
                                break;
                            case "Category":
                                builder.Append("Category: " + children.Value);
                                break;
                            default:
                                continue;
                        }
                    }
                }
                builder.Append("\n\n");
            }
            string results = builder.ToString();
            if (String.IsNullOrEmpty(results))
            {
                results = "No Results...";
            }
            return results;
        }

        private string formatPhone(string phoneNumber)
        {
            StringBuilder builder = new StringBuilder();
            char[] numbers = phoneNumber.ToCharArray();
            for (int i = 0; i < numbers.Length; i++)
            {
                if (i == 3 || i == 6)
                {
                    builder.Append("-" + numbers[i]);
                }
                else
                {
                    builder.Append(numbers[i]);
                }
            }
            return builder.ToString();
        }
    }
}
