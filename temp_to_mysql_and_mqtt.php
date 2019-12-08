<?php
$server_xml="http://[Arduino IP]";
//auslesen der server
$s=simplexml_load_file($server_xml);
$temp01 =$s->tem0;
$temp02 =$s->tem1;
$temp03 =$s->tem2;
$temp04 =$s->tem3;
$temp05 =$s->tem4;
$lufrF  =$s->luftF;
$luftT  =$s->luftT;
$SeID   =$s->seriennummer;

//Zusammenfürung
$name[0]="SensorAusen [".$SeID."]";
$task[0]="Temperatur Server 1";
$vName[0]="Temperatur";
$value[0]=$temp01;

$name[1]="SensorAusen [".$SeID."]";
$task[1]="Temperatur Server 2";
$vName[1]="Temperatur";
$value[1]=$temp02;

$name[2]="SensorAusen [".$SeID."]";
$task[2]="Temperatur Ausen 1";
$vName[2]="Temperatur";
$value[2]=$temp03;

$name[3]="SensorAusen [".$SeID."]";
$task[3]="Temperatur Schlafzimmer";
$vName[3]="Temperatur";
$value[3]=$temp04;

$name[4]="SensorAusen [".$SeID."]";
$task[4]="Temperatur Ausen 2";
$vName[4]="Temperatur";
$value[4]=$temp05;

$name[5]="SensorAusen [".$SeID."]";
$task[5]="Luftfeuchte 01";
$vName[5]="Luftfeuchte";
$value[5]=$lufrF;

$name[6]="SensorAusen [".$SeID."]";
$task[6]="Temperatur Ausen 3";
$vName[6]="Temperatur";
$value[6]=$luftT;


$data=date("d.m.Y H:i:s");
//DB inport
for($i=0;$i<7;$i++)
{
        $db=mysqli_connect("-IP Mysql-","-user mysql-","-passwd mysql-","-db name mysql-");

        $sql = "INSERT INTO `Templog` (`id`, `name`, `Task`, `Valuename`, `Value`, `uploade`) VALUES (NULL, '$name[$i]', '$task[$i]', '$vName[$i]', '$value[$i]', current_timestamp())";
        $res=mysqli_query($db,$sql);
        //manuelle ausgabe
        echo $name[$i] ."<br>".$task[$i]."<br>".$vName[$i]."<br>".$value[$i]."<br> IN MYsql und MQTT GESENDET";

}
//MQTT
exec("curl -X POST 'http://[user]:[password]@broker.shiftr.io/smarthome/R176YQI9ASLBD/Server01/' -d '".$value[0]."'");
exec("curl -X POST 'http://[user]:[password]@broker.shiftr.io/smarthome/R176YQI9ASLBD/Server02/' -d '".$value[1]."'");
exec("curl -X POST 'http://[user]:[password]@broker.shiftr.io/smarthome/R176YQI9ASLBD/Ausen01/' -d '".$value[2]."'");
exec("curl -X POST 'http://[user]:[password]@broker.shiftr.io/smarthome/R176YQI9ASLBD/Schlafzimmer/' -d '".$value[3]."'");
exec("curl -X POST 'http://[user]:[password]@broker.shiftr.io/smarthome/R176YQI9ASLBD/Ausen02/' -d '".$value[4]."'");
exec("curl -X POST 'http://[user]:[password]@broker.shiftr.io/smarthome/R176YQI9ASLBD/Luftfeuchte/' -d '".$value[5]."'");
exec("curl -X POST 'http://[user]:[password]@broker.shiftr.io/smarthome/R176YQI9ASLBD/Ausen03/' -d '".$value[6]."'");
exec("curl -X POST 'http://[user]:[password]@broker.shiftr.io/smarthome/R176YQI9ASLBD/lstdata/' -d '".$data."'");

?>
