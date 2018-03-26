<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<title>WetterStaion</title>
<meta name="author" content="post">
<meta name="editor" content="html-editor phase 5">
<meta http-equiv="refresh" content="30; URL=weterstation.php">
</head>
<body text="#FFFFFF" bgcolor="#000000" link="#FF0000" alink="#FF0000" vlink="#FF0000">
<center>
<img src="http://philipp-lindner-server.p7.de:8080/?action=stream"  width="900" height="700" />
<br>
<br>
 <?php
 $s = simplexml_load_file("http://192.168.178.70");
 $temp03=$s->tem2;
 $temp05=$s->tem4;



 //berechungen
 $korektur="1.0";
//Ausen
$ausen01=$temp03+$temp05;
$ausen02=$ausen01/2;
$ausenTP=$ausen02+$korektur;
$ausenTN=$ausen02-$korektur;

$LuF=$s->luftF;
$LuD=$s->luftD;

//Ausgabe Ausentemperatur:
echo "Ausentemperatur bei: ".$ausenTP." °C (+) ". $korektur ." °C <br>";
echo "Ausentemperatur Bei: ".$ausenTN." °C (-) ". $korektur ." °C <br>";

echo "Bei eine Luftfeuchtigkeit bei ".$LuF." und eine Luftdruk bei ".$LuD."<br>";

echo "Letzte Messung (Aufruf der seite): " . date("d.m.Y H:i:s");

 ?>
</center>
</body>
</html>
