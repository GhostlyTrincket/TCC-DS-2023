<?php

function connect() {
	$db_name = "moisture";
	$db_pass = "plantstatus";
	$db_user = "leafroot";
	$db_host = "192.168.1.13";
	$db_sock = 3306;

	$mysql = mysqli_connect($db_host, $db_user, $db_pass, $db_name, $db_sock);
	
	if($mysql->connect_errno) {
		echo "Could not connect to DB ".$db_name."!\n";
		exit(1);
	}

	return $mysql;
}
