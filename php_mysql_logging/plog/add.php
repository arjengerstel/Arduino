<?php
   	echo "add.php started";
	
	include("connect.php");
   	
   	$link=Connection();

	$start_interval=$_GET["start_interval"];
	$end_interval=$_GET["end_interval"];
	$duration=$_GET["duration"];
	$power_use=$_GET["power_use"];
	$pulse_count=$_GET["pulse_count"];
	
	echo $start_interval;
	
	$query = "INSERT INTO `plog` (`start_time`, `end_time`, `duration`, `power_use`, `num_pulses`) 
		VALUES ('".$start_interval."','".$end_interval."','".$duration."','".$power_use."','".$pulse_count."')"; 
   	
   	mysql_query($query,$link);
	mysql_close($link);
	
?>