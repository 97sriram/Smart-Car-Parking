<?php

header("Access-Control-Allow-Origin: *");
header("Content-Type: application/json; charset=UTF-8");


$response = array();
$smart = array();
$resp=array();

 
$filepath = realpath (dirname(__FILE__));
require_once($filepath."/dbconnect.php");

$db = new DB_CONNECT();	
 
$result = mysql_query("SELECT * FROM slotrfid") or die(mysql_error());
 
if (mysql_num_rows($result) > 0) {
    
    $response["smart"] = array();
 
    while ($row = mysql_fetch_array($result)) {
        
        
        $smart["s1"] = $row["rfidnum"];

        array_push($resp, $smart);
    }
 
    echo json_encode($resp);
}	
//else 
//{
//	$response["success"] = 0;
//    $response["message"] = "No data on weather found";
// 
//    echo json_encode($response);
//}
?>