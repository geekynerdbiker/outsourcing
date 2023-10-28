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
                    result = "No Error";
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

            foreach (var element in xmlDoc.Descendants("Park"))
            {
                foreach (var child in element.Descendants("Name"))
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
                foreach (XElement element in xml.Descendants("Park"))
                {
                    foreach (XElement children in element.Descendants())
                    {
                        string select = children.Name.ToString();
                        switch (select)
                        {
                            case "Name":
                                builder.Append("Name: " + children.Value + "\n");
                                break;
                            case "Type":
                                builder.Append("Type: " + children.Value + "\n");
                                break;
                            case "Owner":
                                builder.Append("Owner: " + children.Value + "\n");
                                break;
                            case "Address":
                                builder.Append("Address: " + children.Value + "\n");
                                break;
                            case "URL":
                                builder.Append("URL: " + children.Value + "\n");
                                break;
                            case "NeighboringStates":
                                builder.Append("NeighboringStates: " + children.Value + "\n");
                                break;
                            case "Establishedn":
                                builder.Append("Establishedn: " + children.Value + "\n");
                                break;
                            case "Founder":
                                builder.Append("Founder: " + children.Value + "\n");
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

        public string XPathSearch(string xmlUrl, string key)
        {
            XDocument xmlDoc = XDocument.Load(xmlUrl);
            List<string> list = new List<string>();
            StringBuilder builder = new StringBuilder();

            foreach (var element in xmlDoc.Descendants("Park"))
            {
                foreach (var child in element.Descendants("Name"))
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
                foreach (XElement element in xml.Descendants("Park"))
                {
                    foreach (XElement children in element.Descendants())
                    {
                        string select = children.Name.ToString();
                        switch (select)
                        {
                            case "Name":
                                builder.Append("Name: " + children.Value + "\n");
                                break;
                            case "Type":
                                builder.Append("Type: " + children.Value + "\n");
                                break;
                            case "Owner":
                                builder.Append("Owner: " + children.Value + "\n");
                                break;
                            case "Address":
                                builder.Append("Address: " + children.Value + "\n");
                                break;
                            case "URL":
                                builder.Append("URL: " + children.Value + "\n");
                                break;
                            case "NeighboringStates":
                                builder.Append("NeighboringStates: " + children.Value + "\n");
                                break;
                            case "Establishedn":
                                builder.Append("Establishedn: " + children.Value + "\n");
                                break;
                            case "Founder":
                                builder.Append("Founder: " + children.Value + "\n");
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

        public void addPark(string xmlUrl, string childName, string attName, string attValue)
        {
            XmlDocument xmlDoc;
            XmlElement childElement;
            XmlAttribute xmlAtb;
            XmlNode parentNode;
        
            xmlDoc = new XmlDocument();
            xmlDoc.Load(Server.MapPath(xmlUrl));
        
            parentNode = xmlDoc.SelectSingleNode("Parks");
            childElement = xmlDoc.CreateElement(childName);
        
            xmlAtb = xmlDoc.CreateAttribute(attName);
            xmlAtb.Value = attValue;
        
            childElement.SetAttributeNode(xmlAtb);
        
            parentNode.AppendChild(childElement);
        
            xmlDoc.Save(Server.MapPath(xmlUrl));
            xmlDoc = null;
        }
    }
}
