<%@ Page Title="" Language="C#" MasterPageFile="~/Site.Master" AutoEventWireup="true" CodeBehind="Verification.aspx.cs" Inherits="WebApplication.Verification" %>
<asp:Content ID="Content1" ContentPlaceHolderID="MainContent" runat="server">
	<div style="height: 80px">
		<h1>Verification</h1>
		</div>
	<div style="height: 50px">
		<asp:TextBox ID="TextBox1" runat="server" Width="500px" ForeColor="Black"></asp:TextBox>
		XML Url</div>
	<div style="height: 50px">
		<asp:TextBox ID="TextBox2" runat="server" Width="500px" ForeColor="Black"></asp:TextBox>
		XSD Url</div>
	<div style="height: 50px">
		<asp:Button ID="Button1" Text="Compare" runat="server" Width="100px" ForeColor="Black" OnClick="Button1_Click"></asp:Button>
		</div>
	<div>
		<asp:TextBox ID="TextBox3" runat="server" Width="703px" ForeColor="Black" Height="80px" TextMode="MultiLine"></asp:TextBox>
		Results</div>
</asp:Content>
