<%@ Page Title="Search" Language="C#" MasterPageFile="~/Site.Master" AutoEventWireup="true" CodeBehind="Search.aspx.cs" Inherits="WebApplication.Search" %>
<asp:Content ID="Content1" ContentPlaceHolderID="MainContent" runat="server">
	<div style="height: 80px">
		<h1>Search</h1>
		</div>
	<div style="height: 50px">
		<asp:TextBox ID="TextBox1" runat="server" Width="500px" ForeColor="Black"></asp:TextBox>
		XML Url</div>
	<div style="height: 50px">
		<asp:TextBox ID="TextBox2" runat="server" Width="500px" ForeColor="Black"></asp:TextBox>
		Query</div>
	<div style="height: 50px">
		<asp:Button ID="Button1" Text="Search" runat="server" Width="100px" ForeColor="Black" OnClick="Button1_Click"></asp:Button>
		</div>
	<div style="height: 200px">
		<asp:TextBox ID="TextBox3" runat="server" Width="500px" ForeColor="Black" Height="200px" TextMode="MultiLine"></asp:TextBox>
		Results</div>
</asp:Content>
