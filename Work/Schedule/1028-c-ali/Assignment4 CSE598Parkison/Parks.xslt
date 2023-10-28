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
			<h1 class="header">Parks</h1>
			<table class="table">
				<tr class="table-headers"> 
					<td>Name</td> 
					<td>Type</td> 
					<td>Owner</td>
					<td>Address</td>
					<td>URL</td> 
					<td>NeighboringStates</td> 
					<td>Establishedn</td> 
					<td>Founder</td>
				</tr>
				<xsl:for-each select="Parks/Park">
					<xsl:sort select="Name"/>
					<tr class="table-data">
						<td><xsl:value-of select="Name"/></td>
						<td><xsl:value-of select="Type"/></td>
						<td><xsl:value-of select="Owner"/></td>
						<td><xsl:value-of select="Address"/></td>
            			<td><xsl:value-of select="URL"/></td>
						<td><xsl:value-of select="NeighboringStates"/></td>
						<td><xsl:value-of select="Establishedn"/></td>
						<td><xsl:value-of select="Founder"/></td>
					</tr>
				</xsl:for-each>
			</table>
		</body> 
    </html>
	</xsl:template>
</xsl:stylesheet>