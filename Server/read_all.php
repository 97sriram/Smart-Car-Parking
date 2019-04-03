<?php

header("Access-Control-Allow-Origin: *");
header("Content-Type: application/json; charset=UTF-8");


$response = array();
 
$filepath = realpath (dirname(__FILE__));
require_once($filepath."/dbconnect.php");

$db = new DB_CONNECT();	
 
$result = mysql_query("SELECT * FROM smartcar") or die(mysql_error());
 
if (mysql_num_rows($result) > 0) {
    
    $response["smart"] = array();
 
    while ($row = mysql_fetch_array($result)) {
        // temperoary user array
        $smart = array();
        $smart["s1"] = $row["slot1"];
        $smart["s2"] = $row["slot2"];

        array_push($response["smart"], $smart);
    }
    $response["success"] = 1;
 
    echo json_encode($response);
}	
else 
{
	$response["success"] = 0;
    $response["message"] = "No data on weather found";
 
    echo json_encode($response);
}
?>