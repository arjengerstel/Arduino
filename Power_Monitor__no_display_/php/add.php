<?php
   	include("connect.php");
   	
   	$link=Connection();

	$start=$_POST["start"]
	$end=$_POST["end"]
	$num=$_POST["num"]

	$query = "INSERT INTO `plog` (`start_time`, `end_time`, `num_pulses`) 
		VALUES ('".$start."','".$end."','".$num."')"; 
   	
   	mysql_query($query,$link);
	mysql_close($link);

   	header("Location: index.php");
?>
