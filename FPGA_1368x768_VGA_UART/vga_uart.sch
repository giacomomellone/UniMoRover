<?xml version="1.0" encoding="UTF-8"?>
<drawing version="7">
    <attr value="spartan6" name="DeviceFamilyName">
        <trait delete="all:0" />
        <trait editname="all:0" />
        <trait edittrait="all:0" />
    </attr>
    <netlist>
        <signal name="btn(4:0)" />
        <signal name="VGA_HS" />
        <signal name="VGA_VS" />
        <signal name="VGA_R(3:0)" />
        <signal name="VGA_G(3:0)" />
        <signal name="VGA_B(3:0)" />
        <signal name="SEG(7:0)" />
        <signal name="AN(3:0)" />
        <signal name="RsTx" />
        <signal name="XLXN_59(2:0)" />
        <signal name="RsRx" />
        <signal name="XLXN_71" />
        <signal name="XLXN_79(7:0)" />
        <signal name="XLXN_92(7:0)" />
        <signal name="XLXN_97" />
        <signal name="XLXN_104" />
        <signal name="XLXN_105" />
        <signal name="XLXN_106" />
        <signal name="CLOCK_100" />
        <signal name="XLXN_111" />
        <signal name="XLXN_112" />
        <port polarity="Input" name="btn(4:0)" />
        <port polarity="Output" name="VGA_HS" />
        <port polarity="Output" name="VGA_VS" />
        <port polarity="Output" name="VGA_R(3:0)" />
        <port polarity="Output" name="VGA_G(3:0)" />
        <port polarity="Output" name="VGA_B(3:0)" />
        <port polarity="Output" name="SEG(7:0)" />
        <port polarity="Output" name="AN(3:0)" />
        <port polarity="Output" name="RsTx" />
        <port polarity="Input" name="RsRx" />
        <port polarity="Input" name="CLOCK_100" />
        <blockdef name="VGA">
            <timestamp>2017-7-12T16:47:55</timestamp>
            <rect width="64" x="384" y="84" height="24" />
            <line x2="448" y1="96" y2="96" x1="384" />
            <line x2="0" y1="32" y2="32" x1="64" />
            <rect width="64" x="0" y="-44" height="24" />
            <line x2="0" y1="-32" y2="-32" x1="64" />
            <line x2="448" y1="-480" y2="-480" x1="384" />
            <line x2="448" y1="-416" y2="-416" x1="384" />
            <rect width="64" x="384" y="-364" height="24" />
            <line x2="448" y1="-352" y2="-352" x1="384" />
            <rect width="64" x="384" y="-300" height="24" />
            <line x2="448" y1="-288" y2="-288" x1="384" />
            <rect width="64" x="384" y="-236" height="24" />
            <line x2="448" y1="-224" y2="-224" x1="384" />
            <rect width="64" x="384" y="-108" height="24" />
            <line x2="448" y1="-96" y2="-96" x1="384" />
            <rect width="64" x="384" y="-44" height="24" />
            <line x2="448" y1="-32" y2="-32" x1="384" />
            <rect width="320" x="64" y="-512" height="652" />
            <rect width="64" x="0" y="-252" height="24" />
            <line x2="0" y1="-240" y2="-240" x1="64" />
        </blockdef>
        <blockdef name="uart">
            <timestamp>2017-7-11T14:48:11</timestamp>
            <line x2="384" y1="-352" y2="-352" x1="320" />
            <line x2="320" y1="-304" y2="-304" x1="384" />
            <line x2="320" y1="-224" y2="-224" x1="384" />
            <rect width="64" x="320" y="-140" height="24" />
            <line x2="384" y1="-128" y2="-128" x1="320" />
            <line x2="384" y1="-32" y2="-32" x1="320" />
            <rect width="256" x="64" y="-384" height="384" />
            <rect width="64" x="0" y="-364" height="24" />
            <line x2="0" y1="-352" y2="-352" x1="64" />
            <line x2="64" y1="-272" y2="-272" x1="0" />
            <line x2="0" y1="-176" y2="-176" x1="64" />
            <line x2="0" y1="-32" y2="-32" x1="64" />
            <line x2="0" y1="-96" y2="-96" x1="64" />
        </blockdef>
        <blockdef name="gnd">
            <timestamp>2000-1-1T10:10:10</timestamp>
            <line x2="64" y1="-64" y2="-96" x1="64" />
            <line x2="52" y1="-48" y2="-48" x1="76" />
            <line x2="60" y1="-32" y2="-32" x1="68" />
            <line x2="40" y1="-64" y2="-64" x1="88" />
            <line x2="64" y1="-64" y2="-80" x1="64" />
            <line x2="64" y1="-128" y2="-96" x1="64" />
        </blockdef>
        <blockdef name="TX_counter">
            <timestamp>2017-7-11T14:59:56</timestamp>
            <rect width="256" x="64" y="-192" height="192" />
            <line x2="384" y1="-64" y2="-64" x1="320" />
            <line x2="320" y1="-160" y2="-160" x1="384" />
            <line x2="0" y1="-64" y2="-64" x1="64" />
            <line x2="0" y1="-144" y2="-144" x1="64" />
        </blockdef>
        <blockdef name="RX_fsm">
            <timestamp>2017-7-12T16:43:51</timestamp>
            <rect width="256" x="64" y="-256" height="256" />
            <rect width="64" x="0" y="-44" height="24" />
            <line x2="0" y1="-32" y2="-32" x1="64" />
            <line x2="320" y1="-32" y2="-32" x1="384" />
            <line x2="320" y1="-208" y2="-208" x1="384" />
            <line x2="0" y1="-208" y2="-208" x1="64" />
            <rect width="64" x="320" y="-140" height="24" />
            <line x2="384" y1="-128" y2="-128" x1="320" />
        </blockdef>
        <block symbolname="VGA" name="XLXI_1">
            <blockpin signalname="CLOCK_100" name="CLOCK_100" />
            <blockpin signalname="btn(4:0)" name="BTN(4:0)" />
            <blockpin signalname="VGA_HS" name="VGA_HS" />
            <blockpin signalname="VGA_VS" name="VGA_VS" />
            <blockpin signalname="VGA_R(3:0)" name="VGA_R(3:0)" />
            <blockpin signalname="VGA_G(3:0)" name="VGA_G(3:0)" />
            <blockpin signalname="VGA_B(3:0)" name="VGA_B(3:0)" />
            <blockpin signalname="SEG(7:0)" name="SEG(7:0)" />
            <blockpin signalname="AN(3:0)" name="AN(3:0)" />
            <blockpin signalname="XLXN_79(7:0)" name="COMMAND(7:0)" />
            <blockpin signalname="XLXN_59(2:0)" name="ALERT(2:0)" />
        </block>
        <block symbolname="uart" name="XLXI_2">
            <blockpin signalname="RsTx" name="tx" />
            <blockpin signalname="RsRx" name="rx" />
            <blockpin signalname="XLXN_71" name="par_en" />
            <blockpin signalname="XLXN_92(7:0)" name="rx_data(7:0)" />
            <blockpin signalname="XLXN_112" name="rx_ready" />
            <blockpin signalname="XLXN_79(7:0)" name="tx_data(7:0)" />
            <blockpin signalname="XLXN_104" name="tx_end" />
            <blockpin signalname="XLXN_105" name="tx_req" />
            <blockpin signalname="XLXN_106" name="rst" />
            <blockpin signalname="CLOCK_100" name="clk" />
        </block>
        <block symbolname="gnd" name="XLXI_7">
            <blockpin signalname="XLXN_71" name="G" />
        </block>
        <block symbolname="RX_fsm" name="XLXI_15">
            <blockpin signalname="XLXN_92(7:0)" name="rx_data(7:0)" />
            <blockpin signalname="XLXN_97" name="rst" />
            <blockpin signalname="CLOCK_100" name="clk" />
            <blockpin signalname="XLXN_112" name="rx_ready" />
            <blockpin signalname="XLXN_59(2:0)" name="ALERT(2:0)" />
        </block>
        <block symbolname="gnd" name="XLXI_16">
            <blockpin signalname="XLXN_97" name="G" />
        </block>
        <block symbolname="gnd" name="XLXI_26">
            <blockpin signalname="XLXN_106" name="G" />
        </block>
        <block symbolname="TX_counter" name="XLXI_13">
            <blockpin signalname="XLXN_105" name="tx_req" />
            <blockpin signalname="XLXN_104" name="tx_end" />
            <blockpin signalname="XLXN_111" name="rst" />
            <blockpin signalname="CLOCK_100" name="clk" />
        </block>
        <block symbolname="gnd" name="XLXI_29">
            <blockpin signalname="XLXN_111" name="G" />
        </block>
    </netlist>
    <sheet sheetnum="1" width="2688" height="1900">
        <attr value="CM" name="LengthUnitName" />
        <attr value="4" name="GridsPerUnit" />
        <branch name="btn(4:0)">
            <wire x2="560" y1="592" y2="592" x1="320" />
        </branch>
        <branch name="VGA_HS">
            <wire x2="1184" y1="144" y2="144" x1="1008" />
        </branch>
        <branch name="VGA_VS">
            <wire x2="1184" y1="208" y2="208" x1="1008" />
        </branch>
        <branch name="VGA_R(3:0)">
            <wire x2="1184" y1="272" y2="272" x1="1008" />
        </branch>
        <branch name="VGA_G(3:0)">
            <wire x2="1184" y1="336" y2="336" x1="1008" />
        </branch>
        <branch name="VGA_B(3:0)">
            <wire x2="1184" y1="400" y2="400" x1="1008" />
        </branch>
        <branch name="SEG(7:0)">
            <wire x2="1184" y1="528" y2="528" x1="1008" />
        </branch>
        <branch name="AN(3:0)">
            <wire x2="1184" y1="592" y2="592" x1="1008" />
        </branch>
        <instance x="560" y="624" name="XLXI_1" orien="R0">
        </instance>
        <branch name="RsTx">
            <wire x2="1904" y1="864" y2="864" x1="1840" />
        </branch>
        <iomarker fontsize="28" x="1184" y="144" name="VGA_HS" orien="R0" />
        <iomarker fontsize="28" x="1184" y="208" name="VGA_VS" orien="R0" />
        <iomarker fontsize="28" x="1184" y="272" name="VGA_R(3:0)" orien="R0" />
        <iomarker fontsize="28" x="1184" y="336" name="VGA_G(3:0)" orien="R0" />
        <iomarker fontsize="28" x="1184" y="400" name="VGA_B(3:0)" orien="R0" />
        <iomarker fontsize="28" x="1184" y="528" name="SEG(7:0)" orien="R0" />
        <iomarker fontsize="28" x="1184" y="592" name="AN(3:0)" orien="R0" />
        <instance x="1808" y="1744" name="XLXI_15" orien="M0">
        </instance>
        <branch name="XLXN_59(2:0)">
            <wire x2="64" y1="384" y2="1616" x1="64" />
            <wire x2="1424" y1="1616" y2="1616" x1="64" />
            <wire x2="560" y1="384" y2="384" x1="64" />
        </branch>
        <branch name="RsRx">
            <wire x2="1888" y1="912" y2="912" x1="1840" />
        </branch>
        <branch name="XLXN_79(7:0)">
            <wire x2="1344" y1="720" y2="720" x1="1008" />
            <wire x2="1344" y1="720" y2="864" x1="1344" />
            <wire x2="1456" y1="864" y2="864" x1="1344" />
        </branch>
        <branch name="XLXN_97">
            <wire x2="1424" y1="1712" y2="1744" x1="1424" />
        </branch>
        <instance x="1360" y="1872" name="XLXI_16" orien="R0" />
        <instance x="1952" y="1136" name="XLXI_7" orien="R0" />
        <iomarker fontsize="28" x="1904" y="864" name="RsTx" orien="R0" />
        <instance x="528" y="1104" name="XLXI_13" orien="R0">
        </instance>
        <branch name="XLXN_105">
            <wire x2="1456" y1="1040" y2="1040" x1="912" />
        </branch>
        <instance x="1392" y="1344" name="XLXI_26" orien="R0" />
        <instance x="416" y="1168" name="XLXI_29" orien="R0" />
        <branch name="XLXN_111">
            <wire x2="528" y1="1040" y2="1040" x1="480" />
        </branch>
        <iomarker fontsize="28" x="320" y="656" name="CLOCK_100" orien="R180" />
        <branch name="XLXN_92(7:0)">
            <wire x2="1920" y1="1712" y2="1712" x1="1808" />
            <wire x2="1920" y1="1088" y2="1088" x1="1840" />
            <wire x2="1920" y1="1088" y2="1712" x1="1920" />
        </branch>
        <branch name="XLXN_71">
            <wire x2="2016" y1="992" y2="992" x1="1840" />
            <wire x2="2016" y1="992" y2="1008" x1="2016" />
        </branch>
        <branch name="XLXN_106">
            <wire x2="1456" y1="1184" y2="1216" x1="1456" />
        </branch>
        <branch name="CLOCK_100">
            <wire x2="384" y1="656" y2="656" x1="320" />
            <wire x2="384" y1="656" y2="960" x1="384" />
            <wire x2="528" y1="960" y2="960" x1="384" />
            <wire x2="384" y1="960" y2="1328" x1="384" />
            <wire x2="1312" y1="1328" y2="1328" x1="384" />
            <wire x2="1312" y1="1328" y2="1536" x1="1312" />
            <wire x2="1424" y1="1536" y2="1536" x1="1312" />
            <wire x2="560" y1="656" y2="656" x1="384" />
            <wire x2="1312" y1="1120" y2="1328" x1="1312" />
            <wire x2="1456" y1="1120" y2="1120" x1="1312" />
        </branch>
        <branch name="XLXN_104">
            <wire x2="1456" y1="944" y2="944" x1="912" />
        </branch>
        <instance x="1456" y="1216" name="XLXI_2" orien="R0">
        </instance>
        <iomarker fontsize="28" x="1888" y="912" name="RsRx" orien="R0" />
        <branch name="XLXN_112">
            <wire x2="1856" y1="1536" y2="1536" x1="1808" />
            <wire x2="1856" y1="1184" y2="1184" x1="1840" />
            <wire x2="1856" y1="1184" y2="1536" x1="1856" />
        </branch>
        <iomarker fontsize="28" x="320" y="592" name="btn(4:0)" orien="R180" />
        <text style="fontsize:24;fontname:Arial" x="1044" y="700">Generated by Display7.vhd</text>
        <text style="fontsize:24;fontname:Arial" x="524" y="1600">Translated from received byte (ASCII)</text>
        <text style="fontsize:24;fontname:Arial" x="1088" y="1024">50ms interval</text>
        <text style="fontsize:24;fontname:Arial" x="1496" y="1776">When rx_ready = 1, then read the rx_data(7:0)</text>
        <text style="fontsize:24;fontname:Arial" x="1212" y="104">To VGA</text>
        <text style="fontsize:24;fontname:Arial" x="1128" y="480">To 7 segment dispay</text>
        <text style="fontsize:24;fontname:Arial" x="364" y="572">Command pad</text>
        <text style="fontsize:24;fontname:Arial" x="484" y="640">To PLL.vhd</text>
        <text style="fontsize:28;fontname:Arial" x="2104" y="1880">Mazzocchi, Mellone, Pistoni, Truffellini, Vidoni</text>
        <text style="fontsize:28;fontname:Arial" x="2104" y="1840">PSE 2016/2017</text>
    </sheet>
</drawing>