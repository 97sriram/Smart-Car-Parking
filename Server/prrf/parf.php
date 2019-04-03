<?php

header("Access-Control-Allow-Origin: *");
header("Content-Type: application/json; charset=UTF-8");


$resp = array();


 
$filepath = realpath (dirname(__FILE__));
require_once($filepath."/dbconnect.php");

$db = new DB_CONNECT();	
 
$result = mysql_query("SELECT rfidnum FROM slotrfid") or die(mysql_error());


	
	while($row=mysqli_fetch_assoc($result))
	{
		$resp[]=$row;
		
	}
		/*echo '<pre>';
		print_r($json_array);
		echo '</pre>';*/
	echo json_encode($resp);
?>