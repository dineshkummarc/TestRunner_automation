<?xml version="1.0" ?> 
<xsl:stylesheet xmlns:xsl="http://www.w3.org/TR/WD-xsl">

   <xsl:template match="//">
      <xsl:define-template-set>

         <xsl:template match="RESULTENTRY">
	         <SPAN STYLE="font-family:arial;font-weight:bold;font-size:12pt;color:gray">
			         <xsl:apply-templates select="STARTTIME" /> 
			         <xsl:apply-templates select="MESSAGE" /> 
			         <xsl:apply-templates select="ENDTIME" /> 
			         <xsl:apply-templates select="DURATION" /> 
           </SPAN>
         </xsl:template>

         <xsl:template match="OPENTIME">	
	         <SPAN STYLE="font-family:arial;font-weight:bold;font-size:12pt;color:darkred"> 
		         Open Time = <xsl:value-of/> <br /> <br />
	         </SPAN>
         </xsl:template>

         <xsl:template match="CLOSETIME">	
	         <SPAN STYLE="font-family:arial;font-weight:bold;font-size:12pt;color:darkred"> 
		         Close Time = <xsl:value-of/> <br /> <br /> 
	         </SPAN> 
         </xsl:template> 

      </xsl:define-template-set> 
      <xsl:apply-templates /> 
   </xsl:template> 

   <xsl:template match="MESSAGE"> 
      <SPAN STYLE="font-family:arial;font-weight:bold;font-size:12pt;color:gray"> 
         Result Entry = <xsl:value-of/> <br/> 
      </SPAN> 
   </xsl:template> 

   <xsl:template match="STARTTIME">	
      <SPAN STYLE="font-family:arial;font-weight:bold;font-size:12pt;color:darkblue"> 
         Start Time = <xsl:value-of/> <br/> 
      </SPAN> 
   </xsl:template> 

   <xsl:template match="ENDTIME"> 
      <SPAN STYLE="font-family:arial;font-weight:bold;font-size:12pt;color:green"> 
         End Time = <xsl:value-of/> <br/> 
      </SPAN> 
   </xsl:template> 

   <xsl:template match="DURATION"> 
      <SPAN STYLE="font-family:arial;font-weight:bold;font-size:12pt;color:red"> 
         Duration = <xsl:value-of/> <br /> <br /> 
      </SPAN> 
   </xsl:template> 

</xsl:stylesheet>

