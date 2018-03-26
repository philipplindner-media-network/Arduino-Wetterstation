<?php
/*
Hold alle Daten ab uns speicher diese in deine MySQL Datenbank
*/
$s = simplexml_load_file("http://[Arduion-IP]");

$temp01=$s->tem0;
$temp02=$s->tem1;
$temp03=$s->tem2;
$temp04=$s->tem3;
$temp05=$s->tem4;

$tempEx01=$temp01;
$tempEx02=$temp02;
$tempEx03=$temp03;
$tempEx04=$temp04;
$tempEx05=$temp05;

//Mysql Vaiabel
$my_01=$tempEx01[0];
$my_02=$tempEx02[0];
$my_03=$tempEx03[0];
$my_04=$tempEx04[0];
$my_05=$tempEx05[0];
$my_06=$s->luftF;
$my_07=$s->luftD;
$my_08=$s->luftT;

mysql_connect("localhost","[DB]","[password]");
mysql_select_db("[db]");

$sql = "INSERT INTO `templog`.`TempLog` (`temp1`, `temp2`, `temp3`, `temp4`, `temp5`, `feucht`, `druck`, `temp6`, `timestamp`, `id`) VALUES ('$my_01', '$my_02', '$my_03', '$my_04', '$my_05', '$my_06', '$my_07', '$my_08', CURRENT_TIMESTAMP, NULL);";
mysql_query($sql);
echo "Daten Geschriben";
?>
