<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
	<xsl:template match="/">
		<html>
			<head>
			<style>
        .header{
        font-weight: bold;
        font-family: Arial;
        padding-left: 300px;
        }
        .table{
        border: solid 1px black;
        }
        .table-headers{
        font-weight: bold;
        font-style: italic;
        font-family: Arial;
        text-align: center;
        }
        .table-data{
        font-size" 12pt;
        font-family: Arial;
        color:  #575352;
        text-align: center;
        }
        td, th{
        border: solid 1px black;
        }
        tr:nth-child(even){background-color: #f2f2f2;}
      </style>
			</head>			
			<body>
			<h1 class="header">Persons</h1>
			<table class="table">
				<tr class="table-headers"> 
					<td>First Name</td> 
					<td>Last Name</td> 
					<td>Id</td>
					<td>Password</td>
					<td>Encryption</td>
					<td>Work Phone</td> 
					<td>Cell Phone</td> 
					<td>Provider</td> 
					<td>Category</td>
				</tr>
				<xsl:for-each select="Persons/Person">
					<xsl:sort select="Name/Last" />
					<tr class="table-data">
						<td><xsl:value-of select="Name/First"/></td>
						<td><xsl:value-of select="Name/Last"/></td>
						<td><xsl:value-of select="Credential/Id"/></td>
						<td><xsl:value-of select="Credential/Password"/></td>
            <td style="text-transform: uppercase"><xsl:value-of select="Credential/Password/@Encryption"/></td>
						<td><xsl:value-of select="Phone/Work"/></td>
						<td><xsl:value-of select="Phone/Cell"/></td>
						<td><xsl:value-of select="Phone/Cell/@Provider"/></td>
						<td><xsl:value-of select="Category"/></td>
					</tr>
				</xsl:for-each>
			</table>
		</body> 
    </html>
	</xsl:template>
</xsl:stylesheet>