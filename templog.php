<!DOCTYPE HTML>
<html>
<head>
  <meta http-equiv="Content-Type" content="text/html; charset=utf-8">
  <meta name="viewport" content="user-scalable=yes, width=device-width"> 
  <title>ARDUINO - Aktuelle Temperatur</title>
</head>
<body>
 
<table border="1">
  <tr>
    <td>Datum</td>
    <td>Temp 1</td>
    <td>Temp 2</td>
    <td>Temp 3</td>
    <td>Temp 4</td>
    <td>Temp 5</td>
    <td>Feuchtigkeit</td>
    <td>Luftdruk</td>
    <td>Temp 6</td>
  </tr>
 
<?php
mysql_connect("localhost","[db]","[password]");
mysql_select_db("[db]");

$sql = "select * from TempLog where id like '%' order by timestamp DESC";
 
$q_data  = mysql_query($sql);
if(mysql_num_rows($q_data) > 0)
{
  while($r_data = mysql_fetch_array($q_data))
  {
    echo "<tr>\n";
    echo "  <td>".$r_data['timestamp']."</td>\n";
    echo "  <td>".$r_data['temp1']."</td>\n";
    echo "  <td>".$r_data['temp2']."</td>\n";
    echo "  <td>".$r_data['temp3']."</td>\n";
    echo "  <td>".$r_data['temp4']."</td>\n";
    echo "  <td>".$r_data['temp5']."</td>\n";
    echo "  <td>".$r_data['feucht']."</td>\n";
    echo "  <td>".$r_data['druck']."</td>\n";
    echo "  <td>".$r_data['temp6']."</td>\n";
    echo "</tr>\n";
  }
}
else
{
  $E = 1;
  $M = "Es wurden keine Temperaturwerte in der Datenbank gefunden!";
}
?>
 
    </table>
  </body>
</html>
