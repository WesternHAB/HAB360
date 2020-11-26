<?xml version="1.0" encoding="utf-8"?>
<!DOCTYPE eagle SYSTEM "eagle.dtd">
<eagle version="9.5.2">
<drawing>
<settings>
<setting alwaysvectorfont="no"/>
<setting verticaltext="up"/>
</settings>
<grid distance="0.1" unitdist="inch" unit="inch" style="lines" multiple="1" display="no" altdistance="0.01" altunitdist="inch" altunit="inch"/>
<layers>
<layer number="1" name="Top" color="4" fill="1" visible="no" active="no"/>
<layer number="16" name="Bottom" color="1" fill="1" visible="no" active="no"/>
<layer number="17" name="Pads" color="2" fill="1" visible="no" active="no"/>
<layer number="18" name="Vias" color="2" fill="1" visible="no" active="no"/>
<layer number="19" name="Unrouted" color="6" fill="1" visible="no" active="no"/>
<layer number="20" name="Dimension" color="24" fill="1" visible="no" active="no"/>
<layer number="21" name="tPlace" color="7" fill="1" visible="no" active="no"/>
<layer number="22" name="bPlace" color="7" fill="1" visible="no" active="no"/>
<layer number="23" name="tOrigins" color="15" fill="1" visible="no" active="no"/>
<layer number="24" name="bOrigins" color="15" fill="1" visible="no" active="no"/>
<layer number="25" name="tNames" color="7" fill="1" visible="no" active="no"/>
<layer number="26" name="bNames" color="7" fill="1" visible="no" active="no"/>
<layer number="27" name="tValues" color="7" fill="1" visible="no" active="no"/>
<layer number="28" name="bValues" color="7" fill="1" visible="no" active="no"/>
<layer number="29" name="tStop" color="7" fill="3" visible="no" active="no"/>
<layer number="30" name="bStop" color="7" fill="6" visible="no" active="no"/>
<layer number="31" name="tCream" color="7" fill="4" visible="no" active="no"/>
<layer number="32" name="bCream" color="7" fill="5" visible="no" active="no"/>
<layer number="33" name="tFinish" color="6" fill="3" visible="no" active="no"/>
<layer number="34" name="bFinish" color="6" fill="6" visible="no" active="no"/>
<layer number="35" name="tGlue" color="7" fill="4" visible="no" active="no"/>
<layer number="36" name="bGlue" color="7" fill="5" visible="no" active="no"/>
<layer number="37" name="tTest" color="7" fill="1" visible="no" active="no"/>
<layer number="38" name="bTest" color="7" fill="1" visible="no" active="no"/>
<layer number="39" name="tKeepout" color="4" fill="11" visible="no" active="no"/>
<layer number="40" name="bKeepout" color="1" fill="11" visible="no" active="no"/>
<layer number="41" name="tRestrict" color="4" fill="10" visible="no" active="no"/>
<layer number="42" name="bRestrict" color="1" fill="10" visible="no" active="no"/>
<layer number="43" name="vRestrict" color="2" fill="10" visible="no" active="no"/>
<layer number="44" name="Drills" color="7" fill="1" visible="no" active="no"/>
<layer number="45" name="Holes" color="7" fill="1" visible="no" active="no"/>
<layer number="46" name="Milling" color="3" fill="1" visible="no" active="no"/>
<layer number="47" name="Measures" color="7" fill="1" visible="no" active="no"/>
<layer number="48" name="Document" color="7" fill="1" visible="no" active="no"/>
<layer number="49" name="Reference" color="7" fill="1" visible="no" active="no"/>
<layer number="51" name="tDocu" color="16" fill="1" visible="no" active="no"/>
<layer number="52" name="bDocu" color="7" fill="1" visible="no" active="no"/>
<layer number="88" name="SimResults" color="9" fill="1" visible="yes" active="yes"/>
<layer number="89" name="SimProbes" color="9" fill="1" visible="yes" active="yes"/>
<layer number="90" name="Modules" color="5" fill="1" visible="yes" active="yes"/>
<layer number="91" name="Nets" color="2" fill="1" visible="yes" active="yes"/>
<layer number="92" name="Busses" color="1" fill="1" visible="yes" active="yes"/>
<layer number="93" name="Pins" color="2" fill="1" visible="no" active="yes"/>
<layer number="94" name="Symbols" color="4" fill="1" visible="yes" active="yes"/>
<layer number="95" name="Names" color="7" fill="1" visible="yes" active="yes"/>
<layer number="96" name="Values" color="7" fill="1" visible="yes" active="yes"/>
<layer number="97" name="Info" color="7" fill="1" visible="yes" active="yes"/>
<layer number="98" name="Guide" color="6" fill="1" visible="yes" active="yes"/>
</layers>
<schematic xreflabel="%F%N/%S.%C%R" xrefpart="/%S.%C%R">
<libraries>
<library name="frames" urn="urn:adsk.eagle:library:229">
<description>&lt;b&gt;Frames for Sheet and Layout&lt;/b&gt;</description>
<packages>
</packages>
<symbols>
<symbol name="LETTER_L" urn="urn:adsk.eagle:symbol:13870/1" library_version="1">
<frame x1="0" y1="0" x2="248.92" y2="185.42" columns="12" rows="17" layer="94" border-left="no" border-top="no" border-right="no" border-bottom="no"/>
</symbol>
<symbol name="DOCFIELD" urn="urn:adsk.eagle:symbol:13864/1" library_version="1">
<wire x1="0" y1="0" x2="71.12" y2="0" width="0.1016" layer="94"/>
<wire x1="101.6" y1="15.24" x2="87.63" y2="15.24" width="0.1016" layer="94"/>
<wire x1="0" y1="0" x2="0" y2="5.08" width="0.1016" layer="94"/>
<wire x1="0" y1="5.08" x2="71.12" y2="5.08" width="0.1016" layer="94"/>
<wire x1="0" y1="5.08" x2="0" y2="15.24" width="0.1016" layer="94"/>
<wire x1="101.6" y1="15.24" x2="101.6" y2="5.08" width="0.1016" layer="94"/>
<wire x1="71.12" y1="5.08" x2="71.12" y2="0" width="0.1016" layer="94"/>
<wire x1="71.12" y1="5.08" x2="87.63" y2="5.08" width="0.1016" layer="94"/>
<wire x1="71.12" y1="0" x2="101.6" y2="0" width="0.1016" layer="94"/>
<wire x1="87.63" y1="15.24" x2="87.63" y2="5.08" width="0.1016" layer="94"/>
<wire x1="87.63" y1="15.24" x2="0" y2="15.24" width="0.1016" layer="94"/>
<wire x1="87.63" y1="5.08" x2="101.6" y2="5.08" width="0.1016" layer="94"/>
<wire x1="101.6" y1="5.08" x2="101.6" y2="0" width="0.1016" layer="94"/>
<wire x1="0" y1="15.24" x2="0" y2="22.86" width="0.1016" layer="94"/>
<wire x1="101.6" y1="35.56" x2="0" y2="35.56" width="0.1016" layer="94"/>
<wire x1="101.6" y1="35.56" x2="101.6" y2="22.86" width="0.1016" layer="94"/>
<wire x1="0" y1="22.86" x2="101.6" y2="22.86" width="0.1016" layer="94"/>
<wire x1="0" y1="22.86" x2="0" y2="35.56" width="0.1016" layer="94"/>
<wire x1="101.6" y1="22.86" x2="101.6" y2="15.24" width="0.1016" layer="94"/>
<text x="1.27" y="1.27" size="2.54" layer="94">Date:</text>
<text x="12.7" y="1.27" size="2.54" layer="94">&gt;LAST_DATE_TIME</text>
<text x="72.39" y="1.27" size="2.54" layer="94">Sheet:</text>
<text x="86.36" y="1.27" size="2.54" layer="94">&gt;SHEET</text>
<text x="88.9" y="11.43" size="2.54" layer="94">REV:</text>
<text x="1.27" y="19.05" size="2.54" layer="94">TITLE:</text>
<text x="1.27" y="11.43" size="2.54" layer="94">Document Number:</text>
<text x="17.78" y="19.05" size="2.54" layer="94">&gt;DRAWING_NAME</text>
</symbol>
</symbols>
<devicesets>
<deviceset name="LETTER_L" urn="urn:adsk.eagle:component:13920/1" prefix="FRAME" uservalue="yes" library_version="1">
<description>&lt;b&gt;FRAME&lt;/b&gt;&lt;p&gt;
LETTER landscape</description>
<gates>
<gate name="G$1" symbol="LETTER_L" x="0" y="0"/>
<gate name="G$2" symbol="DOCFIELD" x="147.32" y="0" addlevel="must"/>
</gates>
<devices>
<device name="">
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
<library name="cust_parts">
<packages>
<package name="EBYTE_SX1262_900M30S_FOOTPRINT">
<smd name="12_GND" x="-11.991046875" y="16.645203125" dx="1.5" dy="2.4" layer="1" rot="R90"/>
<smd name="14_BUSY" x="-11.96540625" y="11.563265625" dx="1.5" dy="2.4" layer="1" rot="R90"/>
<smd name="15_NRST" x="-11.98591875" y="9.037609375" dx="1.5" dy="2.4" layer="1" rot="R90"/>
<smd name="16_MISO" x="-11.914125" y="6.4557" dx="1.5" dy="2.4" layer="1" rot="R90"/>
<smd name="13_DIO1" x="-11.916690625" y="14.11204375" dx="1.5" dy="2.4" layer="1" rot="R90"/>
<smd name="17_MOSI" x="-11.937203125" y="3.93755" dx="1.5" dy="2.4" layer="1" rot="R90"/>
<smd name="18_SCK" x="-11.98591875" y="1.43501875" dx="1.5" dy="2.4" layer="1" rot="R90"/>
<smd name="19_NSS" x="-11.90740625" y="-1.10014375" dx="1.5" dy="2.4" layer="1" rot="R90"/>
<smd name="20_GND" x="-11.991825" y="-8.73080625" dx="1.5" dy="2.4" layer="1" rot="R90"/>
<smd name="21_ANT" x="-11.930309375" y="-11.26269375" dx="1.5" dy="2.4" layer="1" rot="R90"/>
<smd name="22_GND" x="-11.961065625" y="-13.8176375" dx="1.5" dy="2.4" layer="1" rot="R90"/>
<smd name="11_GND" x="11.9456125" y="16.621815625" dx="1.5" dy="2.4" layer="1" rot="R90"/>
<smd name="10_VCC" x="11.937884375" y="14.113053125" dx="1.5" dy="2.4" layer="1" rot="R90"/>
<smd name="9_VCC" x="11.91485625" y="11.588871875" dx="1.5" dy="2.4" layer="1" rot="R90"/>
<smd name="8_DIO2" x="11.953340625" y="9.049278125" dx="1.5" dy="2.4" layer="1" rot="R90"/>
<smd name="7_TXEN" x="11.907128125" y="6.47891875" dx="1.5" dy="2.4" layer="1" rot="R90"/>
<smd name="6_RXEN" x="11.984096875" y="3.93939375" dx="1.5" dy="2.4" layer="1" rot="R90"/>
<smd name="5_GND" x="11.91485625" y="1.361325" dx="1.5" dy="2.4" layer="1" rot="R90"/>
<smd name="4_GND" x="11.9456125" y="-1.155146875" dx="1.5" dy="2.4" layer="1" rot="R90"/>
<smd name="3_GND" x="11.9456125" y="-8.70004375" dx="1.5" dy="2.4" layer="1" rot="R90"/>
<smd name="2_GND" x="11.953340625" y="-11.231928125" dx="1.5" dy="2.4" layer="1" rot="R90"/>
<smd name="1_GND" x="11.9456125" y="-13.84846875" dx="1.5" dy="2.4" layer="1" rot="R90"/>
<wire x1="12.005203125" y1="-19.205309375" x2="11.964365625" y2="19.2583875" width="0.2032" layer="51"/>
<wire x1="11.964365625" y1="19.2583875" x2="-12.026578125" y2="19.28196875" width="0.0254" layer="51"/>
<wire x1="-12.026578125" y1="19.28196875" x2="-11.998821875" y2="-19.238909375" width="0.2032" layer="51"/>
<wire x1="-11.998821875" y1="-19.238909375" x2="12.0019125" y2="-19.201815625" width="0.0254" layer="51"/>
<text x="-12.20991875" y="19.732459375" size="1.778" layer="25">&gt;NAME</text>
<text x="-12.57088125" y="-21.515340625" size="1.778" layer="27">&gt;VALUE</text>
<wire x1="-11.9888" y1="18.288" x2="-11.9888" y2="19.304" width="0.2032" layer="21"/>
<wire x1="-11.9888" y1="19.304" x2="11.9888" y2="19.304" width="0.2032" layer="21"/>
<wire x1="11.9888" y1="18.288" x2="11.9888" y2="19.304" width="0.2032" layer="21"/>
<wire x1="11.9888" y1="-15.4432" x2="11.9888" y2="-19.304" width="0.2032" layer="21"/>
<wire x1="11.9888" y1="-19.304" x2="-11.9888" y2="-19.304" width="0.2032" layer="21"/>
<wire x1="-11.9888" y1="-19.304" x2="-11.9888" y2="-15.4432" width="0.2032" layer="21"/>
<wire x1="-11.9888" y1="-2.6416" x2="-11.9888" y2="-7.112" width="0.2032" layer="21"/>
<wire x1="11.9888" y1="-2.6416" x2="11.9888" y2="-7.112" width="0.2032" layer="21"/>
</package>
</packages>
<symbols>
<symbol name="EBYTE_SX1262_900M30S">
<pin name="12_GND" x="-5.08" y="35.56" length="middle" direction="pwr"/>
<pin name="13_DIO1" x="-5.08" y="33.02" length="middle"/>
<pin name="14_BUSY" x="-5.08" y="30.48" length="middle"/>
<pin name="15_NRST" x="-5.08" y="27.94" length="middle"/>
<pin name="16_MISO" x="-5.08" y="25.4" length="middle"/>
<pin name="17_MOSI" x="-5.08" y="22.86" length="middle"/>
<pin name="18_SCK" x="-5.08" y="20.32" length="middle"/>
<pin name="19_NSS" x="-5.08" y="17.78" length="middle"/>
<pin name="20_GND" x="-5.08" y="10.16" length="middle" direction="pwr"/>
<pin name="21_ANT" x="-5.08" y="7.62" length="middle"/>
<pin name="22_GND" x="-5.08" y="5.08" length="middle" direction="pwr"/>
<pin name="1_GND" x="30.48" y="5.08" length="middle" direction="pwr" rot="R180"/>
<rectangle x1="0" y1="0" x2="25.4" y2="38.1" layer="94"/>
<pin name="2_GND" x="30.48" y="7.62" length="middle" direction="pwr" rot="R180"/>
<pin name="3_GND" x="30.48" y="10.16" length="middle" direction="pwr" rot="R180"/>
<pin name="4_GND" x="30.48" y="17.78" length="middle" direction="pwr" rot="R180"/>
<pin name="5_GND" x="30.48" y="20.32" length="middle" direction="pwr" rot="R180"/>
<pin name="6_RXEN" x="30.48" y="22.86" length="middle" rot="R180"/>
<pin name="7_TXEN" x="30.48" y="25.4" length="middle" rot="R180"/>
<pin name="8_DIO2" x="30.48" y="27.94" length="middle" rot="R180"/>
<pin name="9_VCC" x="30.48" y="30.48" length="middle" direction="pwr" rot="R180"/>
<pin name="10_VCC" x="30.48" y="33.02" length="middle" direction="pwr" rot="R180"/>
<pin name="11_GND" x="30.48" y="35.56" length="middle" direction="pwr" rot="R180"/>
<text x="0" y="38.1" size="1.778" layer="94">&gt;NAME</text>
<text x="0" y="-2.54" size="1.778" layer="94">&gt;VALUE</text>
</symbol>
</symbols>
<devicesets>
<deviceset name="EBYTE_SX1262_900M30S">
<gates>
<gate name="G$1" symbol="EBYTE_SX1262_900M30S" x="-12.7" y="-20.32"/>
</gates>
<devices>
<device name="" package="EBYTE_SX1262_900M30S_FOOTPRINT">
<connects>
<connect gate="G$1" pin="10_VCC" pad="10_VCC"/>
<connect gate="G$1" pin="11_GND" pad="11_GND"/>
<connect gate="G$1" pin="12_GND" pad="12_GND"/>
<connect gate="G$1" pin="13_DIO1" pad="13_DIO1"/>
<connect gate="G$1" pin="14_BUSY" pad="14_BUSY"/>
<connect gate="G$1" pin="15_NRST" pad="15_NRST"/>
<connect gate="G$1" pin="16_MISO" pad="16_MISO"/>
<connect gate="G$1" pin="17_MOSI" pad="17_MOSI"/>
<connect gate="G$1" pin="18_SCK" pad="18_SCK"/>
<connect gate="G$1" pin="19_NSS" pad="19_NSS"/>
<connect gate="G$1" pin="1_GND" pad="1_GND"/>
<connect gate="G$1" pin="20_GND" pad="20_GND"/>
<connect gate="G$1" pin="21_ANT" pad="21_ANT"/>
<connect gate="G$1" pin="22_GND" pad="22_GND"/>
<connect gate="G$1" pin="2_GND" pad="2_GND"/>
<connect gate="G$1" pin="3_GND" pad="3_GND"/>
<connect gate="G$1" pin="4_GND" pad="4_GND"/>
<connect gate="G$1" pin="5_GND" pad="5_GND"/>
<connect gate="G$1" pin="6_RXEN" pad="6_RXEN"/>
<connect gate="G$1" pin="7_TXEN" pad="7_TXEN"/>
<connect gate="G$1" pin="8_DIO2" pad="8_DIO2"/>
<connect gate="G$1" pin="9_VCC" pad="9_VCC"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
<library name="con-lstb">
<description>&lt;b&gt;Pin Headers&lt;/b&gt;&lt;p&gt;
Naming:&lt;p&gt;
MA = male&lt;p&gt;
# contacts - # rows&lt;p&gt;
W = angled&lt;p&gt;
&lt;author&gt;Created by librarian@cadsoft.de&lt;/author&gt;</description>
<packages>
<package name="MA10-1" urn="urn:adsk.eagle:footprint:8300/1" locally_modified="yes">
<description>&lt;b&gt;PIN HEADER&lt;/b&gt;</description>
<wire x1="-12.065" y1="1.27" x2="-10.795" y2="1.27" width="0.1524" layer="21"/>
<wire x1="-10.795" y1="1.27" x2="-10.16" y2="0.635" width="0.1524" layer="21"/>
<wire x1="-10.16" y1="-0.635" x2="-10.795" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="-10.16" y1="0.635" x2="-9.525" y2="1.27" width="0.1524" layer="21"/>
<wire x1="-9.525" y1="1.27" x2="-8.255" y2="1.27" width="0.1524" layer="21"/>
<wire x1="-8.255" y1="1.27" x2="-7.62" y2="0.635" width="0.1524" layer="21"/>
<wire x1="-7.62" y1="-0.635" x2="-8.255" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="-8.255" y1="-1.27" x2="-9.525" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="-9.525" y1="-1.27" x2="-10.16" y2="-0.635" width="0.1524" layer="21"/>
<wire x1="-12.7" y1="0.635" x2="-12.7" y2="-0.635" width="0.1524" layer="21"/>
<wire x1="-12.065" y1="1.27" x2="-12.7" y2="0.635" width="0.1524" layer="21"/>
<wire x1="-12.7" y1="-0.635" x2="-12.065" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="-10.795" y1="-1.27" x2="-12.065" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="-7.62" y1="0.635" x2="-6.985" y2="1.27" width="0.1524" layer="21"/>
<wire x1="-6.985" y1="1.27" x2="-5.715" y2="1.27" width="0.1524" layer="21"/>
<wire x1="-5.715" y1="1.27" x2="-5.08" y2="0.635" width="0.1524" layer="21"/>
<wire x1="-5.08" y1="-0.635" x2="-5.715" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="-5.715" y1="-1.27" x2="-6.985" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="-6.985" y1="-1.27" x2="-7.62" y2="-0.635" width="0.1524" layer="21"/>
<wire x1="-4.445" y1="1.27" x2="-3.175" y2="1.27" width="0.1524" layer="21"/>
<wire x1="-3.175" y1="1.27" x2="-2.54" y2="0.635" width="0.1524" layer="21"/>
<wire x1="-2.54" y1="-0.635" x2="-3.175" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="-4.445" y1="1.27" x2="-5.08" y2="0.635" width="0.1524" layer="21"/>
<wire x1="-5.08" y1="-0.635" x2="-4.445" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="-3.175" y1="-1.27" x2="-4.445" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="-1.905" y1="1.27" x2="-0.635" y2="1.27" width="0.1524" layer="21"/>
<wire x1="-0.635" y1="1.27" x2="0" y2="0.635" width="0.1524" layer="21"/>
<wire x1="0" y1="-0.635" x2="-0.635" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="0" y1="0.635" x2="0.635" y2="1.27" width="0.1524" layer="21"/>
<wire x1="0.635" y1="1.27" x2="1.905" y2="1.27" width="0.1524" layer="21"/>
<wire x1="1.905" y1="1.27" x2="2.54" y2="0.635" width="0.1524" layer="21"/>
<wire x1="2.54" y1="-0.635" x2="1.905" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="1.905" y1="-1.27" x2="0.635" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="0.635" y1="-1.27" x2="0" y2="-0.635" width="0.1524" layer="21"/>
<wire x1="-1.905" y1="1.27" x2="-2.54" y2="0.635" width="0.1524" layer="21"/>
<wire x1="-2.54" y1="-0.635" x2="-1.905" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="-0.635" y1="-1.27" x2="-1.905" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="2.54" y1="0.635" x2="3.175" y2="1.27" width="0.1524" layer="21"/>
<wire x1="3.175" y1="1.27" x2="4.445" y2="1.27" width="0.1524" layer="21"/>
<wire x1="4.445" y1="1.27" x2="5.08" y2="0.635" width="0.1524" layer="21"/>
<wire x1="5.08" y1="-0.635" x2="4.445" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="4.445" y1="-1.27" x2="3.175" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="3.175" y1="-1.27" x2="2.54" y2="-0.635" width="0.1524" layer="21"/>
<wire x1="5.715" y1="1.27" x2="6.985" y2="1.27" width="0.1524" layer="21"/>
<wire x1="6.985" y1="1.27" x2="7.62" y2="0.635" width="0.1524" layer="21"/>
<wire x1="7.62" y1="-0.635" x2="6.985" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="5.715" y1="1.27" x2="5.08" y2="0.635" width="0.1524" layer="21"/>
<wire x1="5.08" y1="-0.635" x2="5.715" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="6.985" y1="-1.27" x2="5.715" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="8.255" y1="1.27" x2="9.525" y2="1.27" width="0.1524" layer="21"/>
<wire x1="9.525" y1="1.27" x2="10.16" y2="0.635" width="0.1524" layer="21"/>
<wire x1="10.16" y1="-0.635" x2="9.525" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="10.16" y1="0.635" x2="10.795" y2="1.27" width="0.1524" layer="21"/>
<wire x1="10.795" y1="1.27" x2="12.065" y2="1.27" width="0.1524" layer="21"/>
<wire x1="12.065" y1="1.27" x2="12.7" y2="0.635" width="0.1524" layer="21"/>
<wire x1="12.7" y1="-0.635" x2="12.065" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="12.065" y1="-1.27" x2="10.795" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="10.795" y1="-1.27" x2="10.16" y2="-0.635" width="0.1524" layer="21"/>
<wire x1="8.255" y1="1.27" x2="7.62" y2="0.635" width="0.1524" layer="21"/>
<wire x1="7.62" y1="-0.635" x2="8.255" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="9.525" y1="-1.27" x2="8.255" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="12.7" y1="0.635" x2="12.7" y2="-0.635" width="0.1524" layer="21"/>
<pad name="1" x="-11.43" y="0" drill="1.016" shape="long" rot="R90"/>
<pad name="2" x="-8.89" y="0" drill="1.016" shape="long" rot="R90"/>
<pad name="3" x="-6.35" y="0" drill="1.016" shape="long" rot="R90"/>
<pad name="4" x="-3.81" y="0" drill="1.016" shape="long" rot="R90"/>
<pad name="5" x="-1.27" y="0" drill="1.016" shape="long" rot="R90"/>
<pad name="6" x="1.27" y="0" drill="1.016" shape="long" rot="R90"/>
<pad name="7" x="3.81" y="0" drill="1.016" shape="long" rot="R90"/>
<pad name="8" x="6.35" y="0" drill="1.016" shape="long" rot="R90"/>
<pad name="9" x="8.89" y="0" drill="1.016" shape="long" rot="R90"/>
<pad name="10" x="11.43" y="0" drill="1.016" shape="long" rot="R90"/>
<text x="-12.7" y="1.651" size="1.27" layer="25" ratio="10">&gt;NAME</text>
<text x="1.27" y="-2.921" size="1.27" layer="27" ratio="10">&gt;VALUE</text>
<rectangle x1="-9.144" y1="-0.254" x2="-8.636" y2="0.254" layer="51"/>
<rectangle x1="-11.684" y1="-0.254" x2="-11.176" y2="0.254" layer="51"/>
<rectangle x1="-6.604" y1="-0.254" x2="-6.096" y2="0.254" layer="51"/>
<rectangle x1="-4.064" y1="-0.254" x2="-3.556" y2="0.254" layer="51"/>
<rectangle x1="1.016" y1="-0.254" x2="1.524" y2="0.254" layer="51"/>
<rectangle x1="-1.524" y1="-0.254" x2="-1.016" y2="0.254" layer="51"/>
<rectangle x1="3.556" y1="-0.254" x2="4.064" y2="0.254" layer="51"/>
<rectangle x1="6.096" y1="-0.254" x2="6.604" y2="0.254" layer="51"/>
<rectangle x1="11.176" y1="-0.254" x2="11.684" y2="0.254" layer="51"/>
<rectangle x1="8.636" y1="-0.254" x2="9.144" y2="0.254" layer="51"/>
</package>
</packages>
<packages3d>
<package3d name="MA10-1" urn="urn:adsk.eagle:package:8346/1" type="box">
<description>PIN HEADER</description>
<packageinstances>
<packageinstance name="MA10-1"/>
</packageinstances>
</package3d>
</packages3d>
<symbols>
<symbol name="MA10-1">
<wire x1="3.81" y1="-12.7" x2="-1.27" y2="-12.7" width="0.4064" layer="94"/>
<wire x1="1.27" y1="-5.08" x2="2.54" y2="-5.08" width="0.6096" layer="94"/>
<wire x1="1.27" y1="-7.62" x2="2.54" y2="-7.62" width="0.6096" layer="94"/>
<wire x1="1.27" y1="-10.16" x2="2.54" y2="-10.16" width="0.6096" layer="94"/>
<wire x1="1.27" y1="0" x2="2.54" y2="0" width="0.6096" layer="94"/>
<wire x1="1.27" y1="-2.54" x2="2.54" y2="-2.54" width="0.6096" layer="94"/>
<wire x1="1.27" y1="7.62" x2="2.54" y2="7.62" width="0.6096" layer="94"/>
<wire x1="1.27" y1="5.08" x2="2.54" y2="5.08" width="0.6096" layer="94"/>
<wire x1="1.27" y1="2.54" x2="2.54" y2="2.54" width="0.6096" layer="94"/>
<wire x1="1.27" y1="12.7" x2="2.54" y2="12.7" width="0.6096" layer="94"/>
<wire x1="1.27" y1="10.16" x2="2.54" y2="10.16" width="0.6096" layer="94"/>
<wire x1="-1.27" y1="15.24" x2="-1.27" y2="-12.7" width="0.4064" layer="94"/>
<wire x1="3.81" y1="-12.7" x2="3.81" y2="15.24" width="0.4064" layer="94"/>
<wire x1="-1.27" y1="15.24" x2="3.81" y2="15.24" width="0.4064" layer="94"/>
<text x="-1.27" y="-15.24" size="1.778" layer="96">&gt;VALUE</text>
<text x="-1.27" y="16.002" size="1.778" layer="95">&gt;NAME</text>
<pin name="1" x="7.62" y="-10.16" visible="pad" length="middle" direction="pas" swaplevel="1" rot="R180"/>
<pin name="2" x="7.62" y="-7.62" visible="pad" length="middle" direction="pas" swaplevel="1" rot="R180"/>
<pin name="3" x="7.62" y="-5.08" visible="pad" length="middle" direction="pas" swaplevel="1" rot="R180"/>
<pin name="4" x="7.62" y="-2.54" visible="pad" length="middle" direction="pas" swaplevel="1" rot="R180"/>
<pin name="5" x="7.62" y="0" visible="pad" length="middle" direction="pas" swaplevel="1" rot="R180"/>
<pin name="6" x="7.62" y="2.54" visible="pad" length="middle" direction="pas" swaplevel="1" rot="R180"/>
<pin name="7" x="7.62" y="5.08" visible="pad" length="middle" direction="pas" swaplevel="1" rot="R180"/>
<pin name="8" x="7.62" y="7.62" visible="pad" length="middle" direction="pas" swaplevel="1" rot="R180"/>
<pin name="9" x="7.62" y="10.16" visible="pad" length="middle" direction="pas" swaplevel="1" rot="R180"/>
<pin name="10" x="7.62" y="12.7" visible="pad" length="middle" direction="pas" swaplevel="1" rot="R180"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="MA10-1" prefix="SV" uservalue="yes">
<description>&lt;b&gt;PIN HEADER&lt;/b&gt;</description>
<gates>
<gate name="1" symbol="MA10-1" x="0" y="0"/>
</gates>
<devices>
<device name="" package="MA10-1">
<connects>
<connect gate="1" pin="1" pad="1"/>
<connect gate="1" pin="10" pad="10"/>
<connect gate="1" pin="2" pad="2"/>
<connect gate="1" pin="3" pad="3"/>
<connect gate="1" pin="4" pad="4"/>
<connect gate="1" pin="5" pad="5"/>
<connect gate="1" pin="6" pad="6"/>
<connect gate="1" pin="7" pad="7"/>
<connect gate="1" pin="8" pad="8"/>
<connect gate="1" pin="9" pad="9"/>
</connects>
<package3dinstances>
<package3dinstance package3d_urn="urn:adsk.eagle:package:8346/1"/>
</package3dinstances>
<technologies>
<technology name="">
<attribute name="MF" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OC_FARNELL" value="unknown" constant="no"/>
<attribute name="OC_NEWARK" value="unknown" constant="no"/>
<attribute name="POPULARITY" value="4" constant="no"/>
</technology>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
<library name="supply1" urn="urn:adsk.eagle:library:371">
<description>&lt;b&gt;Supply Symbols&lt;/b&gt;&lt;p&gt;
 GND, VCC, 0V, +5V, -5V, etc.&lt;p&gt;
 Please keep in mind, that these devices are necessary for the
 automatic wiring of the supply signals.&lt;p&gt;
 The pin name defined in the symbol is identical to the net which is to be wired automatically.&lt;p&gt;
 In this library the device names are the same as the pin names of the symbols, therefore the correct signal names appear next to the supply symbols in the schematic.&lt;p&gt;
 &lt;author&gt;Created by librarian@cadsoft.de&lt;/author&gt;</description>
<packages>
</packages>
<symbols>
<symbol name="GND" urn="urn:adsk.eagle:symbol:26925/1" library_version="1">
<wire x1="-1.905" y1="0" x2="1.905" y2="0" width="0.254" layer="94"/>
<text x="-2.54" y="-2.54" size="1.778" layer="96">&gt;VALUE</text>
<pin name="GND" x="0" y="2.54" visible="off" length="short" direction="sup" rot="R270"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="GND" urn="urn:adsk.eagle:component:26954/1" prefix="GND" library_version="1">
<description>&lt;b&gt;SUPPLY SYMBOL&lt;/b&gt;</description>
<gates>
<gate name="1" symbol="GND" x="0" y="0"/>
</gates>
<devices>
<device name="">
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
</libraries>
<attributes>
</attributes>
<variantdefs>
</variantdefs>
<classes>
<class number="0" name="default" width="0" drill="0">
</class>
</classes>
<parts>
<part name="FRAME1" library="frames" library_urn="urn:adsk.eagle:library:229" deviceset="LETTER_L" device=""/>
<part name="EBYTE_SX1262_900M30S" library="cust_parts" deviceset="EBYTE_SX1262_900M30S" device=""/>
<part name="SV1" library="con-lstb" deviceset="MA10-1" device="" package3d_urn="urn:adsk.eagle:package:8346/1"/>
<part name="SV2" library="con-lstb" deviceset="MA10-1" device="" package3d_urn="urn:adsk.eagle:package:8346/1"/>
<part name="GND1" library="supply1" library_urn="urn:adsk.eagle:library:371" deviceset="GND" device=""/>
<part name="GND2" library="supply1" library_urn="urn:adsk.eagle:library:371" deviceset="GND" device=""/>
<part name="GND3" library="supply1" library_urn="urn:adsk.eagle:library:371" deviceset="GND" device=""/>
<part name="GND4" library="supply1" library_urn="urn:adsk.eagle:library:371" deviceset="GND" device=""/>
<part name="GND5" library="supply1" library_urn="urn:adsk.eagle:library:371" deviceset="GND" device=""/>
<part name="GND7" library="supply1" library_urn="urn:adsk.eagle:library:371" deviceset="GND" device=""/>
<part name="GND8" library="supply1" library_urn="urn:adsk.eagle:library:371" deviceset="GND" device=""/>
<part name="GND9" library="supply1" library_urn="urn:adsk.eagle:library:371" deviceset="GND" device=""/>
<part name="GND10" library="supply1" library_urn="urn:adsk.eagle:library:371" deviceset="GND" device=""/>
</parts>
<sheets>
<sheet>
<plain>
</plain>
<instances>
<instance part="FRAME1" gate="G$2" x="-66.04" y="154.94" smashed="yes"/>
<instance part="EBYTE_SX1262_900M30S" gate="G$1" x="-12.7" y="-20.32" smashed="yes">
<attribute name="NAME" x="-12.7" y="17.78" size="1.778" layer="94"/>
<attribute name="VALUE" x="-12.7" y="-22.86" size="1.778" layer="94"/>
</instance>
<instance part="SV1" gate="1" x="-45.72" y="2.54" smashed="yes">
<attribute name="VALUE" x="-46.99" y="-12.7" size="1.778" layer="96"/>
<attribute name="NAME" x="-46.99" y="18.542" size="1.778" layer="95"/>
</instance>
<instance part="SV2" gate="1" x="45.72" y="5.08" smashed="yes" rot="R180">
<attribute name="VALUE" x="46.99" y="20.32" size="1.778" layer="96" rot="R180"/>
<attribute name="NAME" x="46.99" y="-10.922" size="1.778" layer="95" rot="R180"/>
</instance>
<instance part="GND1" gate="1" x="-25.4" y="-17.78" smashed="yes">
<attribute name="VALUE" x="-27.94" y="-20.32" size="1.778" layer="96"/>
</instance>
<instance part="GND2" gate="1" x="-27.94" y="-10.16" smashed="yes" rot="R270">
<attribute name="VALUE" x="-30.48" y="-7.62" size="1.778" layer="96" rot="R270"/>
</instance>
<instance part="GND3" gate="1" x="-22.86" y="25.4" smashed="yes" rot="R180">
<attribute name="VALUE" x="-20.32" y="27.94" size="1.778" layer="96" rot="R180"/>
</instance>
<instance part="GND4" gate="1" x="27.94" y="22.86" smashed="yes" rot="R180">
<attribute name="VALUE" x="30.48" y="25.4" size="1.778" layer="96" rot="R180"/>
</instance>
<instance part="GND5" gate="1" x="30.48" y="-10.16" smashed="yes">
<attribute name="VALUE" x="27.94" y="-12.7" size="1.778" layer="96"/>
</instance>
<instance part="GND7" gate="1" x="27.94" y="-7.62" smashed="yes" rot="R90">
<attribute name="VALUE" x="30.48" y="-10.16" size="1.778" layer="96" rot="R90"/>
</instance>
<instance part="GND8" gate="1" x="30.48" y="-20.32" smashed="yes">
<attribute name="VALUE" x="27.94" y="-22.86" size="1.778" layer="96"/>
</instance>
<instance part="GND9" gate="1" x="27.94" y="-15.24" smashed="yes" rot="R90">
<attribute name="VALUE" x="30.48" y="-17.78" size="1.778" layer="96" rot="R90"/>
</instance>
<instance part="GND10" gate="1" x="25.4" y="-10.16" smashed="yes" rot="R90">
<attribute name="VALUE" x="27.94" y="-12.7" size="1.778" layer="96" rot="R90"/>
</instance>
</instances>
<busses>
</busses>
<nets>
<net name="N$2" class="0">
<segment>
<pinref part="EBYTE_SX1262_900M30S" gate="G$1" pin="13_DIO1"/>
<pinref part="SV1" gate="1" pin="9"/>
<wire x1="-17.78" y1="12.7" x2="-38.1" y2="12.7" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$3" class="0">
<segment>
<pinref part="SV1" gate="1" pin="8"/>
<pinref part="EBYTE_SX1262_900M30S" gate="G$1" pin="14_BUSY"/>
<wire x1="-38.1" y1="10.16" x2="-17.78" y2="10.16" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$4" class="0">
<segment>
<pinref part="EBYTE_SX1262_900M30S" gate="G$1" pin="15_NRST"/>
<pinref part="SV1" gate="1" pin="7"/>
<wire x1="-17.78" y1="7.62" x2="-38.1" y2="7.62" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$5" class="0">
<segment>
<pinref part="SV1" gate="1" pin="6"/>
<pinref part="EBYTE_SX1262_900M30S" gate="G$1" pin="16_MISO"/>
<wire x1="-38.1" y1="5.08" x2="-17.78" y2="5.08" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$6" class="0">
<segment>
<pinref part="EBYTE_SX1262_900M30S" gate="G$1" pin="17_MOSI"/>
<pinref part="SV1" gate="1" pin="5"/>
<wire x1="-17.78" y1="2.54" x2="-38.1" y2="2.54" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$7" class="0">
<segment>
<pinref part="SV1" gate="1" pin="4"/>
<pinref part="EBYTE_SX1262_900M30S" gate="G$1" pin="18_SCK"/>
<wire x1="-38.1" y1="0" x2="-17.78" y2="0" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$8" class="0">
<segment>
<pinref part="EBYTE_SX1262_900M30S" gate="G$1" pin="19_NSS"/>
<pinref part="SV1" gate="1" pin="3"/>
<wire x1="-17.78" y1="-2.54" x2="-38.1" y2="-2.54" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$10" class="0">
<segment>
<pinref part="SV1" gate="1" pin="1"/>
<pinref part="EBYTE_SX1262_900M30S" gate="G$1" pin="21_ANT"/>
<wire x1="-38.1" y1="-7.62" x2="-38.1" y2="-12.7" width="0.1524" layer="91"/>
<wire x1="-38.1" y1="-12.7" x2="-17.78" y2="-12.7" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$12" class="0">
<segment>
<pinref part="SV2" gate="1" pin="2"/>
<pinref part="EBYTE_SX1262_900M30S" gate="G$1" pin="10_VCC"/>
<wire x1="38.1" y1="12.7" x2="17.78" y2="12.7" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$13" class="0">
<segment>
<pinref part="EBYTE_SX1262_900M30S" gate="G$1" pin="9_VCC"/>
<pinref part="SV2" gate="1" pin="3"/>
<wire x1="17.78" y1="10.16" x2="38.1" y2="10.16" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$14" class="0">
<segment>
<pinref part="SV2" gate="1" pin="4"/>
<pinref part="EBYTE_SX1262_900M30S" gate="G$1" pin="8_DIO2"/>
<wire x1="38.1" y1="7.62" x2="17.78" y2="7.62" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$15" class="0">
<segment>
<pinref part="EBYTE_SX1262_900M30S" gate="G$1" pin="7_TXEN"/>
<pinref part="SV2" gate="1" pin="5"/>
<wire x1="17.78" y1="5.08" x2="38.1" y2="5.08" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$16" class="0">
<segment>
<pinref part="SV2" gate="1" pin="6"/>
<pinref part="EBYTE_SX1262_900M30S" gate="G$1" pin="6_RXEN"/>
<wire x1="38.1" y1="2.54" x2="17.78" y2="2.54" width="0.1524" layer="91"/>
</segment>
</net>
<net name="GND" class="0">
<segment>
<pinref part="EBYTE_SX1262_900M30S" gate="G$1" pin="22_GND"/>
<wire x1="-17.78" y1="-15.24" x2="-25.4" y2="-15.24" width="0.1524" layer="91"/>
<pinref part="GND1" gate="1" pin="GND"/>
</segment>
<segment>
<pinref part="SV1" gate="1" pin="2"/>
<pinref part="EBYTE_SX1262_900M30S" gate="G$1" pin="20_GND"/>
<wire x1="-38.1" y1="-5.08" x2="-17.78" y2="-5.08" width="0.1524" layer="91"/>
<wire x1="-17.78" y1="-5.08" x2="-17.78" y2="-10.16" width="0.1524" layer="91"/>
<wire x1="-17.78" y1="-10.16" x2="-25.4" y2="-10.16" width="0.1524" layer="91"/>
<pinref part="GND2" gate="1" pin="GND"/>
</segment>
<segment>
<pinref part="SV1" gate="1" pin="10"/>
<pinref part="EBYTE_SX1262_900M30S" gate="G$1" pin="12_GND"/>
<wire x1="-38.1" y1="15.24" x2="-17.78" y2="15.24" width="0.1524" layer="91"/>
<wire x1="-17.78" y1="15.24" x2="-22.86" y2="15.24" width="0.1524" layer="91"/>
<wire x1="-22.86" y1="15.24" x2="-22.86" y2="22.86" width="0.1524" layer="91"/>
<pinref part="GND3" gate="1" pin="GND"/>
</segment>
<segment>
<pinref part="EBYTE_SX1262_900M30S" gate="G$1" pin="11_GND"/>
<pinref part="SV2" gate="1" pin="1"/>
<wire x1="17.78" y1="15.24" x2="27.94" y2="15.24" width="0.1524" layer="91"/>
<wire x1="27.94" y1="15.24" x2="38.1" y2="15.24" width="0.1524" layer="91"/>
<wire x1="27.94" y1="15.24" x2="27.94" y2="20.32" width="0.1524" layer="91"/>
<pinref part="GND4" gate="1" pin="GND"/>
</segment>
<segment>
<pinref part="EBYTE_SX1262_900M30S" gate="G$1" pin="5_GND"/>
<pinref part="SV2" gate="1" pin="7"/>
<wire x1="30.48" y1="0" x2="38.1" y2="0" width="0.1524" layer="91"/>
<wire x1="17.78" y1="0" x2="30.48" y2="0" width="0.1524" layer="91"/>
<wire x1="30.48" y1="0" x2="30.48" y2="-7.62" width="0.1524" layer="91"/>
<pinref part="GND5" gate="1" pin="GND"/>
</segment>
<segment>
<pinref part="SV2" gate="1" pin="8"/>
<pinref part="EBYTE_SX1262_900M30S" gate="G$1" pin="4_GND"/>
<wire x1="38.1" y1="-2.54" x2="20.32" y2="-2.54" width="0.1524" layer="91"/>
<wire x1="20.32" y1="-2.54" x2="17.78" y2="-2.54" width="0.1524" layer="91"/>
<wire x1="20.32" y1="-2.54" x2="20.32" y2="-7.62" width="0.1524" layer="91"/>
<wire x1="20.32" y1="-7.62" x2="25.4" y2="-7.62" width="0.1524" layer="91"/>
<pinref part="GND7" gate="1" pin="GND"/>
</segment>
<segment>
<pinref part="SV2" gate="1" pin="10"/>
<pinref part="EBYTE_SX1262_900M30S" gate="G$1" pin="2_GND"/>
<wire x1="38.1" y1="-7.62" x2="38.1" y2="-12.7" width="0.1524" layer="91"/>
<wire x1="38.1" y1="-12.7" x2="30.48" y2="-12.7" width="0.1524" layer="91"/>
<wire x1="30.48" y1="-12.7" x2="17.78" y2="-12.7" width="0.1524" layer="91"/>
<wire x1="30.48" y1="-12.7" x2="30.48" y2="-17.78" width="0.1524" layer="91"/>
<pinref part="GND8" gate="1" pin="GND"/>
</segment>
<segment>
<pinref part="EBYTE_SX1262_900M30S" gate="G$1" pin="1_GND"/>
<wire x1="17.78" y1="-15.24" x2="25.4" y2="-15.24" width="0.1524" layer="91"/>
<pinref part="GND9" gate="1" pin="GND"/>
</segment>
<segment>
<pinref part="SV2" gate="1" pin="9"/>
<pinref part="EBYTE_SX1262_900M30S" gate="G$1" pin="3_GND"/>
<wire x1="38.1" y1="-5.08" x2="17.78" y2="-5.08" width="0.1524" layer="91"/>
<wire x1="17.78" y1="-5.08" x2="17.78" y2="-10.16" width="0.1524" layer="91"/>
<wire x1="17.78" y1="-10.16" x2="22.86" y2="-10.16" width="0.1524" layer="91"/>
<pinref part="GND10" gate="1" pin="GND"/>
</segment>
</net>
</nets>
</sheet>
</sheets>
</schematic>
</drawing>
<compatibility>
<note version="8.2" severity="warning">
Since Version 8.2, EAGLE supports online libraries. The ids
of those online libraries will not be understood (or retained)
with this version.
</note>
<note version="8.3" severity="warning">
Since Version 8.3, EAGLE supports URNs for individual library
assets (packages, symbols, and devices). The URNs of those assets
will not be understood (or retained) with this version.
</note>
<note version="8.3" severity="warning">
Since Version 8.3, EAGLE supports the association of 3D packages
with devices in libraries, schematics, and board files. Those 3D
packages will not be understood (or retained) with this version.
</note>
</compatibility>
</eagle>
