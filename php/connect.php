<?php

function connect() {
	$db_name = "teste_db";
	$db_pass = "ghostlyTr1nk37";
	$db_user = "root";
	$db_host = "localhost";
	
//	$db_name = "moisture";
//	$db_pass = "plantstatus";
//	$db_user = "leafroot";
//	$db_host = "192.168.1.109";

	$mysql = mysqli_connect($db_host, $db_user, $db_pass, $db_name);
	
	if($mysql->error) {
		echo("Could not connect to ".$db_name." database! Please verify host or name!");
		exit(1);
	}

	return $mysql;
}
